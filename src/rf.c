
#include "defines.h"
#include "rf.h"

uint16_t NCOsweep = NCO_INC_MIN_F;

void configRF(const RFConfig_t *pRFconfig){
	
		if (pRFconfig->RFMode != RF_OFF) {

		NCO1INC = pRFconfig->NCOIncrement;
		APFCONbits.NCO1SEL = 1;
		NCO1CLKbits = NCO1CLK_INIT;
		NCO1CONbits = NCO1CON_INIT;
		}
    return;
}

void updateRF(RFConfig_t *pRFconfig);

void enableRFoutput(_Bool outState);
