
#ifndef MAINS_H
#define	MAINS_H

#include <xc.h>
#include <stdbool.h>

#define LED PORTAbits.RA1
const _Bool LEDon = false;
const _Bool LEDoff = true;

#define READ_SW_PIN PORTAbits.RA2
#define IR_PIN PORTAbits.RA4

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

const LATAbits_t LATA_QUIET = {
	.LATA0 = 0,
	.LATA1 = 1,
	.LATA2 = 1,
	.LATA4 = 0,
	.LATA5 = 0};
const LATAbits_t LATA_PRECHARGE = {
	.LATA0 = 1,
	.LATA1 = 1,
	.LATA2 = 1,
	.LATA4 = 0,
	.LATA5 = 1};
const LATAbits_t LATA_READ_SWITCH = {
	.LATA0 = 1,
	.LATA1 = 1,
	.LATA2 = 0,
	.LATA4 = 0,
	.LATA5 = 1};
const WPUAbits_t WPUA_PRECHARGE = {
	.WPUA0 = 1,
	.WPUA1 = 1,
	.WPUA2 = 0,
	.WPUA3 = 0,
	.WPUA4 = 0,
	.WPUA5 = 1};
const WPUAbits_t WPUA_NORMAL = {
	.WPUA0 = 1,
	.WPUA1 = 1,
	.WPUA2 = 1,
	.WPUA3 = 0,
	.WPUA4 = 0,
	.WPUA5 = 1};
const TRISAbits_t TRISA_NORMAL = {
	.TRISA0 = 0,
	.TRISA1 = 0,
	.TRISA2 = 1,
	.TRISA4 = 0,
	.TRISA5 = 0};
const TRISAbits_t TRISA_READ_SWITCH = {
	.TRISA0 = 1,
	.TRISA1 = 1,
	.TRISA2 = 0,
	.TRISA4 = 0,
	.TRISA5 = 1};

const OPTION_REGbits_t OPTION_INIT = {
	.nWPUEN = 0,
	.TMR0CS = 0,
	.PSA = 0,
	.PS = 0x5 };
const T1CONbits_t T1CON_INIT = {
	.TMR1CS = 0x0,
	.T1CKPS = 0x0,
	.TMR1ON = 1 };
const OSCCONbits_t OSCCON_INIT = {
	.IRCF = 0xf,
	.SCS = 0 };
const FVRCONbits_t FVRCON_READ_BATT = {
		.FVREN = 1,
		.TSEN = 0,
		.CDAFVR = 0,
		.ADFVR = 2
	};
const ADCON0bits_t ADCON0_READ_BATT = {
		.CHS = 0x1f,
		.GO_nDONE = 0,
		.ADON = 1
	};
const ADCON1bits_t ADCON1_READ_BATT = {
		.ADFM = 0,
		.ADCS = 0,
		.ADPREF = 0
	};

const uint8_t SW_MASK = 0x23;
#endif	/* MAINS_H */