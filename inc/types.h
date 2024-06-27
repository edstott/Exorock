/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TYPES_H
#define	TYPES_H
#include <stdbool.h>

#define MAX_NAME_LEN 8

typedef struct {
	enum {
		RF_OFF,
		RF_FIXED_FREQ,
		RF_SWEEP
	} RFMode;
	
	uint16_t NCOIncrement;
	
} RFConfig_t;

typedef struct {
	enum {
		MODULATE_OFF,
		MODULATE_RF,
		MODULATE_AF,
		MODULATE_AF_PLUS_RF,
		MODULATE_RF_PLUS_AF
	} modulationChannel;
	
	enum {
		MODULATE_SQUARE,
		MODULATE_NAME_STATIC,
		MODULATE_NAME_LOOKUP_RANDOM,
		MODULATE_NAME_LOOKUP_CONFIG
	} modulationMode;
	
	uint8_t primaryModulationPeriod;
	uint8_t secondaryModulationDivider;
	
	char name[MAX_NAME_LEN];
	
} modulationConfig_t;

typedef struct {
	
	enum {
		IR_OFF,
		IR_STATIC,
		IR_RANDOM_LOOKUP,
		IR_CONFIG_LOOKUP
	} IRMode;
	
	uint8_t IRPeriod;
	
} IRConfig_t;



typedef struct {
	_Bool examMode;
	
	RFConfig_t RFConfig;
	
	_Bool AFenable;
	
	modulationConfig_t modulationConfig;
	
	IRConfig_t IRConfig;	
			
} exorockConfig_t;

#endif	/* XC_HEADER_TEMPLATE_H */
