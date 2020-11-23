/*
 * UART.c
 */
#include "aplicacion.h"

//la formula para setear al baudrate es BAUDRATE= F_periferico/16*U0DLL


void InitUART0 (void)
{
	//1.- Registro PCONP (0x400FC0C4) - bit 3 en 1 prende la UART0:
	PCONP |= 0x01<<3;

//	//2.- Registro PCLKSEL0 (0x400FC1A8) - bits 6 y 7 en 0 seleccionan que el clk de la UART0 sea CCLK/4:

	PCLKSEL0 &= ~(0x03<<6);	//con un CCLK=100Mhz, nos queda PCLOCK=25Mhz
//	PCLKSEL0|=(0x3<<6);		//el clock del periferico esta en 12,5 MHz


//	//3.- Registro U1LCR (0x4001000C) - transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1:

	U0LCR = 0x00000083;
	//4.- Registros U1DLL (0x40010000) y U1DLM (0x40010004) - 115200 baudios:

	U0DLM = 0;
//	U0DLL = 0x7;		//0x7 para 115200

	//para 115200
	U0DLL = 0x8;		//0x8
	U0FDR = 0xA7;		//mulval=10 Y divaddval=7

	//5.- Registros PINSEL0 (0x4002C000) y PINSEL1 (0x4002C004) - habilitan las funciones especiales de los pines:
	//TX1D : PIN ??	-> 		P0[15]	-> PINSEL0: 30:31
	SetPINSEL(TX0,PINSEL_FUNC1);
	//RX1D : PIN ??	-> 		P0[16]	-> PINSEL1: 00:01
	SetPINSEL(RX0,PINSEL_FUNC1);
	//6.- Registro U1LCR, pongo DLAB en 0:
	U0LCR = 0x03;
	//7. Habilito las interrupciones (En la UART -IER- habilito interrupcion de recpecion y transmision y en el NVIC -ISER)
	U0IER = 0x03;
	ISER0 |= (1<<5);

	estado_lectura=ESPERA;
	contador_mensaje=0;
}

