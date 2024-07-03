/* 
 * File:   rf.h
 * Author: Ed Stott
 *
 * Created on 03 July 2024, 16:16
 */

#ifndef RF_H
#define	RF_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdbool.h>
	
typedef struct {
	enum {
		RF_OFF,
		RF_FIXED_FREQ,
		RF_SWEEP
	} RFMode;
	
	uint16_t NCOIncrement;
	
} RFConfig_t;

void configRF(const RFConfig_t *pRFconfig);

void updateRF(RFConfig_t *pRFconfig);

void enableRFoutput(_Bool outState);

const NCO1CONbits_t NCO1CON_INIT = {
	.N1EN = 1,
	.N1OE = 1,
	.N1OUT = 0,
	.N1POL = 0,
	.N1PFM = 0
};
const NCO1CLKbits_t NCO1CLK_INIT = {
	.N1PWS = 1,
	.N1CKS = 1
};

#define NCO_INC_MIN_F f_to_NCO_inc(40000)

#ifdef	__cplusplus
}
#endif

#endif	/* RF_H */

