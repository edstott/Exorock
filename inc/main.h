
#ifndef MAINS_H
#define	MAINS_H

#include <xc.h>
#define LED PORTAbits.RA1

#pragma config FOSC = INTOSC
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config BOREN = OFF
#pragma config CLKOUTEN = OFF
#pragma config WRT = OFF
#pragma config STVREN = ON
#pragma config BORV = LO
#pragma config LPBOR = OFF
#pragma config LVP = OFF

typedef enum {
    INIT,
    INIT_START_FLASH_1,
    INIT_START_FLASH_2,
    INIT_END_FLASH_1,
    INIT_END_FLASH_2,
    BATT_FLASH_1,
    BATT_FLASH_2,
    BATT_FLASH_3,
    BATT_FLASH_4,
    BATT_FLASH_5,
    MODE_DISPLAY_0,
    MODE_DISPLAY_1,
    MODE_DISPLAY_2,
    MODE_DISPLAY_3
} state_t;

const LATAbits_t LATA_OUT_QUIET = {0,1,1,0,0};
const TRISAbits_t TRISA_NORMAL = {0,0,0,0,0};
const OPTION_REGbits_t OPTION_INIT = {0,1,1,0,0,0,0,0};
const T1CONbits_t T1CON_INIT = {1,0,0,0,1,1,0,0};
const uint8_t SW_MASK = 0x23;
#endif	/* MAINS_H */