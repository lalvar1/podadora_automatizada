/*
 * UART.h
 */

#ifndef UART_H_
#define UART_H_

#include "aplicacion.h"

//!< /////////////		UARTs		///////////////////////////
	//0x40010000UL : Registro de recepcion de la UART0:
	#define		DIR_UART0		( ( __RW uint32_t  * ) 0x4000C000UL )
	#define		DIR_FDR0		( ( __RW uint32_t  * ) 0x4000C028UL )

	#define		U0RBR		DIR_UART0[0]
	#define		U0THR		DIR_UART0[0]
	#define		U0DLL		DIR_UART0[0]
	#define		U0IER		DIR_UART0[1]
	#define		U0DLM		DIR_UART0[1]
	#define		U0IIR		DIR_UART0[2]
	#define		U0LCR		DIR_UART0[3]
	#define		U0LSR		DIR_UART0[5]

	#define		U0FDR		DIR_FDR0[0]

	#define TOPE 250
	#define TX0 PORT0,2
	#define RX0 PORT0,3


	void InitUART0 (void);
	void PushRx(uint8_t);
	void guardar_dato(uint8_t);
	void PushTx(char);
	uint16_t PopRx(void);
	uint16_t PopTx(void);
	void Enviar_Parametros(char*);
	void enviar_datos();

	//0x40010000UL : Registro de recepcion de la UART1:
	#define		DIR_UART1		( ( __RW uint32_t  * ) 0x40010000UL )

	#define		U1RBR		DIR_UART1[0]
	#define		U1THR		DIR_UART1[0]
	#define		U1DLL		DIR_UART1[0]
	#define		U1IER		DIR_UART1[1]
	#define		U1DLM		DIR_UART1[1]
	#define		U1IIR		DIR_UART1[2]
	#define		U1LCR		DIR_UART1[3]
	#define		U1LSR		DIR_UART1[5]


	#define ESPERA		0
	#define READY_1		1
	#define READY_2		2
	#define READY_3		3
	#define OKEY_1		4
	#define ERROR_1		5
	#define ERROR_2		6
	#define ERROR_3		7
	#define MSG_1		8
	#define MSG_2		9
	#define MSG_3		10
	#define MSG_4A		11
	#define MSG_4B		12
	#define MSG_5		13

	uint8_t estado_lectura;			//variable que maneja los estados de la maquina de estado de lectura de mensajes
	uint8_t contador_mensaje;		//variable que uso como contador para esperar el resto del mensaje en algunos mensajes
	uint8_t k;						//variable que uso para recorrer todo el vector y reiniciarlo
	uint8_t flag_okey;				//flag que me sirve para indicar que llego un mensaje de OK
	uint8_t flag_error;				//flag que me sirve para indicar que llego un mensaje de ERROR
	uint8_t flag_msg;				//flag que me sirve para indicar que llego un mensaje
	uint8_t data[7],receptor[20];

	uint8_t caracteres,unidad_caracter;		//variables que me sirven para saber cuantos caracteres recibi en un mensaje nuevo
	uint8_t numero_id;						//variable que me sirve para guardra el numero de id de quien me envia el mensaje

#endif /* UART_H_ */
