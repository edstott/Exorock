/*
 * File:   main.c
 * Author: Ed Stott
 *
 * Created on 27 June 2024, 13:42
 */


#include <xc.h>
#include "types.h"
#include "defines.h"
#include "config.h"
#include "modulation.h"
#include "main.h"

struct {
    modulationState_t modulationState;
} systemState ;

void __interrupt() mainISR(){
    if (INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
    }
    
    if (PIR1bits.TMR2IF) {
        PIR1bits.TMR2IF = 0;
        updateModulation(&systemState.modulationState);
    }
}

void configAF(AFConfig_t *pAFconfig){

}

void configRF(RFConfig_t *pRFconfig){
    
}

void configIR(IRConfig_t *pIRconfig){
    
}

void main(void) {
    uint8_t mode = 0;
    const exorockConfig_t *pConfig;
    uint8_t stateTimer = 0;
    uint8_t LEDtimer = 0;
    state_t state = INIT;
    
    OSCCONbits.IRCF = 0x0f;
    ANSELA = 0x00;
    OPTION_REGbits = OPTION_INIT;
    T1CONbits = T1CON_INIT;
    
    TRISAbits = TRISA_NORMAL;
    LATA = SW_MASK;
    WPUA = SW_MASK;
    
    NOP();
    
    TRISA = SW_MASK;
    READ_SW_PIN = 0;
    
    NOP();
    
    mode = PORTA & SW_MASK;
    
    LATAbits = LATA_OUT_QUIET;
    TRISAbits = TRISA_NORMAL;
    WPUA  = 0;
    
    

    if (mode < N_CONFIGS) {
        pConfig = configList[mode % N_CONFIGS];
    } else {
        pConfig = &defaultConfig;
    }

    /* Configure system state with pointers to configuration structs*/
    systemState.modulationState.pModulationConfig = &pConfig->modulationConfig;

    configModulation(&systemState.modulationState);
    
    uint8_t battVoltage = 0;
    uint8_t displayMode = mode;

    while (true) {
        /* Wait for timer*/
        while (!PIR1bits.TMR1IF) {}
        PIR1bits.TMR1IF = 0;

        /* Switch on LED if LED timer active*/
        if (LEDtimer > 0) {
            LED = true;
            LEDtimer--;
        } else {
            LED = false;
        }

        /* Decrement state timer. On zero, find next state and update timers*/
        if (stateTimer > 0) {
            stateTimer--;
        } else {
            switch (state) {
                case INIT:
                    LEDtimer = 0;
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = INIT_START_FLASH_1;
                    break;

                case INIT_START_FLASH_1:
                    LEDtimer = millis_to_t1_counter(LED_SHORT_FLASH);
                    stateTimer = millis_to_t1_counter(DOUBLE_FLASH_INTERVAL);
                    state = INIT_START_FLASH_2;
                    break;

                case INIT_START_FLASH_2:
                    LEDtimer = millis_to_t1_counter(LED_SHORT_FLASH);
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = BATT_FLASH_1;
                    break;

                case BATT_FLASH_1:
                    LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = BATT_FLASH_2;
                    break;

                case BATT_FLASH_2:
                    if (battVoltage > mV_to_ADC(BATT_THRESHOLD_1)) {
                        LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    } else {
                        LEDtimer = 0;
                    }
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = BATT_FLASH_3;
                    break;

                case BATT_FLASH_3:
                    if (battVoltage > mV_to_ADC(BATT_THRESHOLD_2)) {
                        LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    } else {
                        LEDtimer = 0;
                    }
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = BATT_FLASH_4;
                    break;

                case BATT_FLASH_4:
                    if (battVoltage > mV_to_ADC(BATT_THRESHOLD_3)) {
                        LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    } else {
                        LEDtimer = 0;
                    }
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = BATT_FLASH_5;
                    break;

                case BATT_FLASH_5:
                    if (battVoltage > mV_to_ADC(BATT_THRESHOLD_4)) {
                        LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    } else {
                        LEDtimer = 0;
                    }
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = INIT_END_FLASH_1;
                    break;

                case INIT_END_FLASH_1:
                    LEDtimer = millis_to_t1_counter(LED_SHORT_FLASH);
                    stateTimer = millis_to_t1_counter(DOUBLE_FLASH_INTERVAL);
                    state = INIT_END_FLASH_2;
                    break;

                case INIT_END_FLASH_2:
                    LEDtimer = millis_to_t1_counter(LED_SHORT_FLASH);
                    stateTimer = millis_to_t1_counter(MODE_DISPLAY_INTERVAL);
                    state = MODE_DISPLAY_0;
                    break;

                case MODE_DISPLAY_0:
                    if (pConfig->examMode) {
                        LEDtimer = millis_to_t1_counter(LED_SHORT_FLASH);
                    } else if (displayMode & 0x01) {
                        LEDtimer = millis_to_t1_counter(LED_LONG_FLASH);
                    } else {
                        LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    }
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = MODE_DISPLAY_1;
                    break;

                case MODE_DISPLAY_1:
                    if (pConfig->examMode) {
                        LEDtimer = 0;
                    } else if (displayMode & 0x02) {
                        LEDtimer = millis_to_t1_counter(LED_LONG_FLASH);
                    } else {
                        LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    }
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = MODE_DISPLAY_2;
                    break;

                case MODE_DISPLAY_2:
                    if (pConfig->examMode) {
                        LEDtimer = 0;
                    } else if (displayMode & 0x04) {
                        LEDtimer = millis_to_t1_counter(LED_LONG_FLASH);
                    } else {
                        LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    }
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = MODE_DISPLAY_3;
                    break;
                    
                case MODE_DISPLAY_3:
                    if (pConfig->examMode) {
                        LEDtimer = 0;
                    } else if (displayMode & 0x08) {
                        LEDtimer = millis_to_t1_counter(LED_LONG_FLASH);
                    } else {
                        LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    }
                    stateTimer = millis_to_t1_counter(MODE_DISPLAY_INTERVAL);
                    state = MODE_DISPLAY_0;
                    break;
                    
            }
        }


    }


    return;
}
