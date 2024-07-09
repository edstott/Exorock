

#include <stdbool.h>
#include <xc.h>
#include "modulation.h"

#pragma switch space


modulationState_t modulationState;


void setPrimaryOutput(_Bool outState){
    switch (modulationState.pModulationConfig->modulationChannel) {

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

void setSecondaryOutput(_Bool outState){
    switch (modulationState.pModulationConfig->modulationChannel) {

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

void configModulation(const modulationConfig_t *pModulationConfig){
	modulationState.pModulationConfig = pModulationConfig;
	if (1) {
		CFGS = 1;
		GIE = 0;
		
		PMADR = (uint16_t)&idloc[0];
		RD = 1;
		NOP();
		NOP();
		
		PMADR = (uint16_t)nameList;
		PMADR += PMDATL;
		RD = 1;
		NOP();
		NOP();
		
		modulationState.name[0] = PMDATL & 0x7f;
		modulationState.name[1] = (uint8_t)(PMDATH << 1);
		if (PMDATL & 0x80) modulationState.name[1] |= 1; 
		
		PMADR++;
		RD = 1;
		NOP();
		NOP();
		
		modulationState.name[2] = PMDATL & 0x7f;
		modulationState.name[3] = (uint8_t)(PMDATH << 1);
		if (PMDATL & 0x80) modulationState.name[3] |= 1; 		
		
		GIE = 1;
		
	}
    
}

void updateModulation(){
    static uint8_t bitIndex = 0;
    static int8_t byteIndex = -PREAMBLE_BYTES;
    static char currentChar = 0;
    static _Bool secondaryModulationState = false;
    static uint8_t secondaryModulationCounter = 0;
    if (modulationState.pModulationConfig->modulationChannel != MODULATE_OFF){
        
        switch (modulationState.pModulationConfig->modulationMode) {

            case MODULATE_SQUARE:
                setPrimaryOutput(bitIndex & 0x01);
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
                    if (byteIndex == MAX_NAME_LEN) {
						byteIndex = -PREAMBLE_BYTES;
					}
                }
                if (byteIndex < 0) {
                    setPrimaryOutput(true);
                } else {
                    switch (bitIndex) {
                        case 0:
                            currentChar = modulationState.name[byteIndex];
                            setPrimaryOutput(false);
                        case 9:
                            setPrimaryOutput(true);
                        default:
                            setPrimaryOutput(currentChar & 0x01);
							currentChar = currentChar >> 1;
                    }


                }
                break;

            default:
                setPrimaryOutput(true);

        }

        if (modulationState.pModulationConfig->modulationChannel == MODULATE_AF_PLUS_RF || modulationState.pModulationConfig->modulationChannel == MODULATE_RF_PLUS_AF) {
            secondaryModulationCounter--;
            if (secondaryModulationCounter == 0) {
                secondaryModulationCounter = modulationState.pModulationConfig->secondaryModulationDivider;
                secondaryModulationState = !secondaryModulationState;
                setSecondaryOutput(secondaryModulationState);
            }
        }


    }

    return;
}