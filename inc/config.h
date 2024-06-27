/* 
 * File:   config.h
 * Author: Ed Stott
 *
 * Created on 27 June 2024, 14:32
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include "types.h"
#include "defines.h"



const exorockConfig_t testMode = {
	false,
	{
		RF_FIXED_FREQ,
		f_to_NCO_inc(89000)
	},
	true,
	{
		MODULATE_RF_PLUS_AF,
		MODULATE_NAME_STATIC,
		f_to_pri_mod_prd(600),
		5,
		"#TEST"		
	},
	{
		IR_STATIC,
		f_to_IR_prd(353)
	}
};

const exorockConfig_t* configlist[N_CONFIGS] = {
	&testMode,
	&testMode,
	&testMode,
	&testMode,
	&testMode,
	&testMode,
	&testMode,
	&testMode
};
#endif	/* CONFIG_H */

