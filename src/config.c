

#include "types.h"
#include "defines.h"
#include "config.h"
#include "modulation.h"


/* Test mode uses all the outputs*/
const exorockConfig_t testMode = {
	false,
	{
		RF_FIXED_FREQ,
		f_to_NCO_inc(89000)
	},
	{
		AF_ON
	},
	{
		MODULATE_RF_PLUS_AF,
		MODULATE_NAME_LOOKUP_CONFIG_PLUS_SWITCH,
		f_to_pri_mod_prd(600),
		5,
		"#TEST"		
	},
	{
		IR_STATIC,
		f_to_IR_prd(353)
	}
};

/* Default mode does nothing*/
const exorockConfig_t defaultConfig = {
	false,
	{
		RF_OFF,
		0
	},
	{
		AF_OFF
	},
	{
		MODULATE_OFF,
		MODULATE_NAME_STATIC,
		0,
		0,
		""		
	},
	{
		IR_OFF,
		0
	}
};

const exorockConfig_t* configList[N_CONFIGS] = {
	&testMode,
	&testMode,
	&testMode,
	&testMode,
	&testMode,
	&testMode,
	&testMode,
	&testMode
};

