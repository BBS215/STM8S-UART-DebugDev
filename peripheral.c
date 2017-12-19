#include "peripheral.h"
/*
////////// LEDS /////////////////////

//																						LED0				LED1				LED2
const GPIO_Pin_TypeDef	LED_pin[LEDS_CNT] = { GPIO_PIN_5,	GPIO_PIN_4,	GPIO_PIN_2	};
GPIO_TypeDef* const		LED_port[LEDS_CNT] = 	{ GPIOB,			GPIOB,			GPIOD				};

uint8_t g_LEDS_mode[LEDS_CNT];
	
void Leds_init(void)
{
	uint8_t i;
	for(i=0;i<LEDS_CNT;i++)
	{
		GPIO_Init(LED_port[i], LED_pin[i], GPIO_MODE_OUT_PP_HIGH_SLOW);
		Led_setmode(i, LED_OFF);
	}
}

void Led_setmode(uint8_t num, uint8_t mode)
{
	if (num >= LEDS_CNT) return;
	g_LEDS_mode[num] = mode;
	if (mode == LED_ON) {
		GPIO_WriteLow(LED_port[num], LED_pin[num]);
	} else
	if (mode == LED_OFF) {
		GPIO_WriteHigh(LED_port[num], LED_pin[num]);
	}
}
*/
/// UART ///////////////////////////////////////////

void UART_init(void)
{
	UART1_DeInit();
	UART1_Init((uint32_t)UART_SPEED, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
				UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
	UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
	UART1_Cmd(ENABLE);
}

uint8_t UART_send(uint8_t *p_buf, uint16_t size)
{
	uint16_t i;
	if (!p_buf) return -1;
	if (!size) return -2;
	for(i=0;i<size;i++)
	{
		UART1_SendData8(p_buf[i]);
		while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); // Loop until the end of transmission
	}
	return 0;
}

void UART_RX_INTR(void)
{
	EVENT_UART_RX_Byte(UART1_ReceiveData8());
}



