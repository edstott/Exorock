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
#include "rf.h"
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

void configIR(IRConfig_t *pIRconfig){
    
}

void main(void) {
    OSCCONbits = OSCCON_INIT;
	
    const exorockConfig_t *pConfig;
    uint8_t stateTimer = 0;
    uint8_t LEDtimer = 0;
    state_t state = INIT;
	
    uint8_t mode = 0;
	uint8_t switchInput;
    
    ANSELA = 0x00;
    OPTION_REGbits = OPTION_INIT;
	
	TMR1 = 0;
    PIR1bits.TMR1IF = 0;
    T1CONbits = T1CON_INIT;
	   
    WPUAbits = WPUA_NORMAL; 
    LATAbits = LATA_QUIET;
    TRISAbits = TRISA_NORMAL;
	
	/*Read voltage reference*/
	FVRCONbits = FVRCON_READ_BATT;
	while (!FVRCONbits.FVRRDY) {}
	
	IR_PIN = true;
    
	ADCON1bits = ADCON1_READ_BATT;
	ADCON0bits = ADCON0_READ_BATT;
	
	//Wait for acquisition
	for (uint8_t i=0; i<10; i++) {}
	
	ADCON0bits.GO = 1;
	IR_PIN = false;
	while (ADCON0bits.GO) {}
	
	ADCON0bits.ADON = 0;
	FVRCONbits.FVREN = 0;
			
	uint8_t battVoltage = ADRESH;
	   
    LATAbits = LATA_READ_SWITCH;
    TRISAbits = TRISA_READ_SWITCH;

    while (true) {
        /* Wait for timer*/
        while (!PIR1bits.TMR1IF) {}
        PIR1bits.TMR1IF = 0;

        /* Switch on LED if LED timer active*/
        if (LEDtimer > 0) {
            LED = LEDon;
            LEDtimer--;
        } else {
            LED = LEDoff;
        }

        /* Decrement state timer. On zero, find next state and update timers*/
        if (stateTimer > 0) {
            stateTimer--;
        } else {
            switch (state) {
                case INIT:
    
					switchInput = PORTA;
    
					LATAbits = LATA_QUIET;
					TRISAbits = TRISA_NORMAL;

					if (~switchInput & 0x20) mode |= 0x01;
					if (~switchInput & 0x01) mode |= 0x02;
					if (~switchInput & 0x02) mode |= 0x04;

					if (mode < N_CONFIGS) {
						pConfig = configList[mode % N_CONFIGS];
					} else {
						pConfig = &defaultConfig;
					}
					
					//Insert the extra bit for mode display
					mode = (uint8_t)(mode << 1) | pConfig->extraModeBit;

					/* Configure system state with pointers to configuration structs*/
					systemState.modulationState.pModulationConfig = &pConfig->modulationConfig;

					configModulation(&systemState.modulationState);
					configRF(&pConfig->RFConfig);

					LATAbits = LATA_QUIET;
					TRISAbits = TRISA_NORMAL;
					
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
                    if (battVoltage < mV_to_ADC(BATT_THRESHOLD_1)) {
                        LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    } else {
                        LEDtimer = 0;
                    }
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = BATT_FLASH_3;
                    break;

                case BATT_FLASH_3:
                    if (battVoltage < mV_to_ADC(BATT_THRESHOLD_2)) {
                        LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    } else {
                        LEDtimer = 0;
                    }
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = BATT_FLASH_4;
                    break;

                case BATT_FLASH_4:
                    if (battVoltage < mV_to_ADC(BATT_THRESHOLD_3)) {
                        LEDtimer = millis_to_t1_counter(LED_MEDIUM_FLASH);
                    } else {
                        LEDtimer = 0;
                    }
                    stateTimer = millis_to_t1_counter(INIT_SEQUENCE_INTERVAL);
                    state = BATT_FLASH_5;
                    break;

                case BATT_FLASH_5:
                    if (battVoltage < mV_to_ADC(BATT_THRESHOLD_4)) {
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
                    } else if (mode & 0x01) {
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
                    } else if (mode & 0x02) {
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
                    } else if (mode & 0x04) {
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
                    } else if (mode & 0x08) {
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
