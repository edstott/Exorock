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
#include "modulation.h"
#include "rf.h"

typedef struct {
	_Bool examMode;
	_Bool extraModeBit;
	
	RFConfig_t RFConfig;
	
	AFConfig_t AFConfig;
	
	modulationConfig_t modulationConfig;
	
	IRConfig_t IRConfig;	
			
} exorockConfig_t;
    
extern const exorockConfig_t* configList[N_CONFIGS];
extern const exorockConfig_t defaultConfig;

#endif	/* CONFIG_H */