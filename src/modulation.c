

#include <stdbool.h>
#include <xc.h>
#include "modulation.h"

void setPrimaryOutput(modulationState_t *pState, _Bool outState){
    switch (pState->pModulationConfig->modulationChannel) {

		MODULATE_AF:
		MODULATE_AF_PLUS_RF:
        /*enableAFoutput(outState);*/
        return;

		MODULATE_RF_PLUS_AF:
		MODULATE_RF:
        /*enableRFoutput(outState);*/
        return;

        MODULATE_OFF:
        default:
        return;
    }
}

void setSecondaryOutput(modulationState_t *pState, _Bool outState){
    switch (pState->pModulationConfig->modulationChannel) {

		MODULATE_AF_PLUS_RF:
            /*enableRFoutput(outState);*/
            return;

		MODULATE_RF_PLUS_AF:
            /*enableAFoutput(outState);*/
            return;
        
		MODULATE_AF:
		MODULATE_RF:
        MODULATE_OFF:
        default:
            return;
    }
}

void configModulation(modulationState_t *pState){
    PMADRL = (uint8_t)nameList;
    PMADRH = (uint8_t)((uint16_t)nameList >> 8);
    
}

void updateModulation(modulationState_t *pState){
    static uint8_t bitIndex = 0;
    static int8_t byteIndex = -PREAMBLE_BYTES;
    static char currentChar = 0;
    static _Bool secondaryModulationState = false;
    static uint8_t secondaryModulationCounter = 0;
    if (pState->pModulationConfig->modulationChannel != MODULATE_OFF){
        
        switch (pState->pModulationConfig->modulationMode) {

            case MODULATE_SQUARE:
                setPrimaryOutput(pState, bitIndex & 0x01);
                bitIndex ^= 0x01;
                break;

            case MODULATE_NAME_STATIC:
            case MODULATE_NAME_LOOKUP_RANDOM:
            case MODULATE_NAME_LOOKUP_CONFIG:
            case MODULATE_NAME_LOOKUP_CONFIG_PLUS_SWITCH: 
                bitIndex++;
                if (bitIndex == N_BITS) {
                    bitIndex = 0;
                    byteIndex++;
                }
                if (byteIndex < 0) {
                    setPrimaryOutput(pState, true);
                } else {
                    switch (bitIndex) {
                        case 0:
                            currentChar = pState->name[byteIndex];
                            if (currentChar == '\0' || byteIndex == MAX_NAME_LEN) {
                                byteIndex = -PREAMBLE_BYTES;
                                setPrimaryOutput(pState, true);
                            } else {
                                setPrimaryOutput(pState, false);
                            }
                            break;
                        case 1:
                            setPrimaryOutput(pState, currentChar & 0x01);
                            break;
                        case 2:
                            setPrimaryOutput(pState, currentChar & 0x02);
                            break;
                        case 3:
                            setPrimaryOutput(pState, currentChar & 0x04);
                            break;
                        case 4:
                            setPrimaryOutput(pState, currentChar & 0x08);
                            break;
                        case 5:
                            setPrimaryOutput(pState, currentChar & 0x10);
                            break;
                        case 6:
                            setPrimaryOutput(pState, currentChar & 0x20);
                            break;
                        case 7:
                            setPrimaryOutput(pState, currentChar & 0x40);
                            break;
                        case 8:
                            setPrimaryOutput(pState, currentChar & 0x80);
                            break;
                        case 9:
                        default:
                            setPrimaryOutput(pState, true);
                    }


                }
                break;

            default:
                setPrimaryOutput(pState, true);

        }

        if (pState->pModulationConfig->modulationChannel == MODULATE_AF_PLUS_RF || pState->pModulationConfig->modulationChannel == MODULATE_RF_PLUS_AF) {
            secondaryModulationCounter--;
            if (secondaryModulationCounter == 0) {
                secondaryModulationCounter = pState->pModulationConfig->secondaryModulationDivider;
                secondaryModulationState = !secondaryModulationState;
                setSecondaryOutput(pState, secondaryModulationState);
            }
        }


    }

    return;
}