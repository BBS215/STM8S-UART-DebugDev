#ifndef __PERIPHERAL_H
#define __PERIPHERAL_H

#include "main.h"
/*
/// LEDS ///////////////////////////////////////////

#define LEDS_CNT 3

#define LED_0		0
#define LED_1		1
#define LED_2		2

#define LED_OFF 0
#define LED_ON 	1

void Leds_init(void);
void Led_setmode(uint8_t num, uint8_t mode);
*/

/// UART ///////////////////////////////////////////

#define UART_SPEED 115200

void UART_init(void);
void EVENT_UART_RX_Byte(uint8_t byte);
uint8_t UART_send(uint8_t *p_buf, uint16_t size);

#endif // __PERIPHERAL_H


