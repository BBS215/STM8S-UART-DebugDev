#ifndef MAIN_H_
#define MAIN_H_

#include "stm8s.h"

#define DEBUG_DEV_CMD_READ_8		(uint8_t)0x1
#define DEBUG_DEV_CMD_READ_16		(uint8_t)0x2
#define DEBUG_DEV_CMD_WRITE_8		(uint8_t)0x3
#define DEBUG_DEV_CMD_WRITE_16	(uint8_t)0x4

#define START_BYTE 	(uint8_t)0x55
#define STOP_BYTE 	(uint8_t)0xAA
/*#define START_BYTE 	(uint8_t)'1'
#define STOP_BYTE 	(uint8_t)'2'*/

typedef struct
{
	uint8_t start_byte;
	uint8_t	cmd;
	union {
		struct {
			uint8_t HI_byte;
			uint8_t LO_byte;
		} addr_8;
		uint16_t addr_16;
	} addr;
	union {
		struct {
			uint8_t HI_byte;
			uint8_t LO_byte;
		} data_8;
		uint16_t data_16;
	} data;
	uint8_t	reserved1;
	uint8_t stop_byte;
} t_Debug_dev_packet;


#endif // MAIN_H_
