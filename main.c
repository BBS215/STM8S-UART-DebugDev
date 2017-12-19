/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "main.h"
#include "init.h"
#include "peripheral.h"

t_Debug_dev_packet g_RX_TX_packet; // �����
uint8_t g_RX_count; // ���-�� �������� ����
uint8_t g_RX_flag; // ���� "����� ������"

void EVENT_UART_RX_Byte(uint8_t byte) // ���� ����� �� UART
{
	if (g_RX_count == 0) {
		if (byte == START_BYTE) { // ������ ���� ������
			((uint8_t*)(&g_RX_TX_packet))[g_RX_count] = byte;
			g_RX_count++;
		}
	} else if (g_RX_count < sizeof(t_Debug_dev_packet)) {
		((uint8_t*)(&g_RX_TX_packet))[g_RX_count] = byte;
		g_RX_count++;
		if (g_RX_count == sizeof(t_Debug_dev_packet)) { // ��������� ���� ������
			if (g_RX_TX_packet.stop_byte == STOP_BYTE) g_RX_flag = 1;
			else g_RX_count = 0;
		}
	}
}

void Control_loop(void)
{
	if (g_RX_flag) {
		switch(g_RX_TX_packet.cmd) {
			case DEBUG_DEV_CMD_READ_8: // ������ �� ������ 8-������� ��������
				g_RX_TX_packet.data.data_8.HI_byte = 0;
				g_RX_TX_packet.data.data_8.LO_byte = *(uint8_t*)(g_RX_TX_packet.addr.addr_16);
				UART_send(((uint8_t*)(&g_RX_TX_packet)), sizeof(t_Debug_dev_packet));
				break;
			case DEBUG_DEV_CMD_READ_16: // ������ �� ������ 16-������� ��������
				g_RX_TX_packet.data.data_16 = *(uint16_t*)(g_RX_TX_packet.addr.addr_16);
				UART_send(((uint8_t*)(&g_RX_TX_packet)), sizeof(t_Debug_dev_packet));
				break;
			case DEBUG_DEV_CMD_WRITE_8: // ������ 8-������� ��������
				*(uint8_t*)(g_RX_TX_packet.addr.addr_16) = g_RX_TX_packet.data.data_8.LO_byte;
				UART_send(((uint8_t*)(&g_RX_TX_packet)), sizeof(t_Debug_dev_packet));
				break;
			case DEBUG_DEV_CMD_WRITE_16: // ������ 16-������� ��������
				*(uint16_t*)(g_RX_TX_packet.addr.addr_16) = g_RX_TX_packet.data.data_16;
				UART_send(((uint8_t*)(&g_RX_TX_packet)), sizeof(t_Debug_dev_packet));
				break;
			default: // ������ �������
				break;
		}
		g_RX_flag = 0;
		g_RX_count = 0;
	}
}

void main(void)
{
	disableInterrupts();
	Init_Clock();
	Init_GPIO();
	UART_init();
	g_RX_count = 0;
	g_RX_flag = 0;
	enableInterrupts();
	
	while(1)
	{
		Control_loop();
	}
}