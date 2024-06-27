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
#define TMR2_PRESCALE 4
#define TMR2_POSTSCALE 2
#define	TMR2_PRD (FOSC4/(AF_HZ*TMR2_PRESCALE))
#define	NCO_OVF 131072l

#define f_to_pri_mod_prd(f) (256-FOSC4/((long)f*TMR0_PRESCALE*2*TMR0_POSTSCALE))
#define f_to_IR_prd(f) (FOSC4/((long)f*TMR2_PRESCALE*TMR2_POSTSCALE*TMR2_PRD))
#define f_to_NCO_inc(f) (NCO_OVF*((long)f/1000)/1000)

#define N_CONFIGS 8

#endif	/* DEFINES_H */

