/* 
 * File:   defines.h
 * Author: Ed Stott
 *
 * Created on 27 June 2024, 14:55
 */

#ifndef DEFINES_H
#define	DEFINES_H

#define FOSC4 4000000
#define AF_HZ 40000
#define TMR0_PRESCALE 64
#define TMR0_POSTSCALE 2
#define TMR1_PRESCALE 1
#define TMR2_PRESCALE 4
#define TMR2_POSTSCALE 2
#define	TMR2_PRD (FOSC4/(AF_HZ*TMR2_PRESCALE))
#define	NCO_OVF 131072l
#define TMR1_OVF 65536
#define VREF 2.048

#define f_to_pri_mod_prd(f) (256-FOSC4/((long)f*TMR0_PRESCALE*2*TMR0_POSTSCALE))
#define f_to_IR_prd(f) (FOSC4/((long)f*TMR2_PRESCALE*TMR2_POSTSCALE*TMR2_PRD))
#define f_to_NCO_inc(f) (NCO_OVF*((long)f/1000)/1000)
#define millis_to_t1_counter(t) t*(FOSC4/1000)/(TMR1_OVF*TMR1_PRESCALE)
#define mV_to_ADC(v) (uint8_t)(VREF*256.0/v)

#define N_CONFIGS 8

#define INIT_SEQUENCE_INTERVAL 500
#define DOUBLE_FLASH_INTERVAL 100
#define MODE_DISPLAY_INTERVAL 3000
#define LED_SHORT_FLASH 100
#define LED_MEDIUM_FLASH 100
#define LED_LONG_FLASH 400

#define BATT_THRESHOLD_1 2.4
#define BATT_THRESHOLD_2 2.8
#define BATT_THRESHOLD_3 2.9
#define BATT_THRESHOLD_4 3.0


#endif	/* DEFINES_H */

