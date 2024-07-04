

#include "types.h"
#include "defines.h"
#include "config.h"
#include "modulation.h"


/* Test mode uses all the outputs*/
const exorockConfig_t testMode = {
	false,
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
		{'T','E','S','T'}		
	},
	{
		IR_STATIC,
		f_to_IR_prd(353)
	}
};

/* Default mode does nothing*/
const exorockConfig_t defaultConfig = {
	false,
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

/* Test mode uses all the outputs*/
const exorockConfig_t lizard1 = {
	false,
	false,
	{
		RF_OFF,
		0
	},
	{
		AF_ON
	},
	{
		MODULATE_AF,
		MODULATE_NAME_STATIC,
		f_to_pri_mod_prd(600),
		1,
		{'L','I','Z','1'}		
	},
	{
		IR_STATIC,
		f_to_IR_prd(571)
	}
};

/* Test mode uses all the outputs*/
const exorockConfig_t lizard2 = {
	false,
	false,
	{
		RF_FIXED_FREQ,
		f_to_NCO_inc(89000)
	},
	{
		AF_ON
	},
	{
		MODULATE_AF_PLUS_RF,
		MODULATE_NAME_STATIC,
		f_to_pri_mod_prd(600),
		5,
		{'L','I','Z','2'}		
	},
	{
		IR_OFF,
		0
	}
};

/* Test mode uses all the outputs*/
const exorockConfig_t lizard3 = {
	false,
	false,
	{
		RF_OFF,
		0
	},
	{
		AF_ON
	},
	{
		MODULATE_AF,
		MODULATE_NAME_STATIC,
		f_to_pri_mod_prd(600),
		1,
		{'L','I','Z','3'}		
	},
	{
		IR_STATIC,
		f_to_IR_prd(353)
	}
};

/* Test mode uses all the outputs*/
const exorockConfig_t lizard4 = {
	false,
	false,
	{
		RF_FIXED_FREQ,
		f_to_NCO_inc(89000)
	},
	{
		AF_ON
	},
	{
		MODULATE_AF_PLUS_RF,
		MODULATE_NAME_STATIC,
		f_to_pri_mod_prd(600),
		5,
		{'L','I','Z','4'}		
	},
	{
		IR_OFF,
		0
	}
};

const exorockConfig_t* configList[N_CONFIGS] = {
	&testMode,
	&lizard1,
	&testMode,
	&lizard2,
	&testMode,
	&lizard3,
	&testMode,
	&lizard4
};

