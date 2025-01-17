#ifndef MODULATION_H
#define	MODULATION_H

#include <xc.h>

#define MAX_NAME_LEN 4
#define PREAMBLE_BYTES 16
#define N_BITS 10

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
		MODULATE_NAME_LOOKUP_CONFIG,
		MODULATE_NAME_LOOKUP_CONFIG_PLUS_SWITCH
	} modulationMode;
	
	uint8_t primaryModulationPeriod;
	uint8_t secondaryModulationDivider;
	
	char name[MAX_NAME_LEN];
	
} modulationConfig_t;

typedef struct {
	const modulationConfig_t *pModulationConfig;
	char name[MAX_NAME_LEN];
} modulationState_t;

void configModulation(const modulationConfig_t *pModulationConfig);
void updateModulation();

extern const uint16_t nameList[];

#pragma warning disable 1262
extern const uint8_t idloc[] __at(0x8000);
#pragma warning enable 1262


#endif	/* MODULATION_H */