/*
 * WIFI.c
 */

#include "aplicacion.h"



void inicializar_wifi()
{
	uint16_t i=0,caracter_wifi=0;
	uint8_t usuario_guardado[10];
	uint8_t contrasena_guardada[10];

	Enviar_Parametros("ATE0");
	PushTx(0x0D);
	PushTx(0x0A);
	for(i=0;i<5;i++)
	{
		delay=1;
		while(delay);
	}


	Enviar_Parametros("AT+CWMODE=2");			//ponemos al modulo como AP
	for(i=0;i<65000;i++);
	PushTx(0x0D);
	PushTx(0x0A);
	for(i=0;i<5;i++)
	{
		delay=1;
		while(delay);
	}
//	while(flag_okey!=1);								//esperamos a recibir el OK
//	flag_okey=0;

	Enviar_Parametros("AT+CIPSTO");						//Le seteamos un tiempo sin actividad en el servisor de 7000 segundos sin que se desconecte
	for(i=0;i<65000;i++);
	Enviar_Parametros("=7000");
	for(i=0;i<65000;i++);
	PushTx(0x0D);
	PushTx(0x0A);
	for(i=0;i<5;i++)
	{
		delay=1;
		while(delay);
	}
//	while(flag_okey!=1);								//esperamos a recibir el OK
//	flag_okey=0;

	Enviar_Parametros("AT+CWSAP=");						//configuro usuario y contraseña generico
	PushTx(comilla);									//lo envio asi proque no puedo enviar comillas doble de una
	for(i=0;i<12000;i++);

	if(SECTOR19[0]!=0xFF)
	{
		for(i=0;SECTOR19[i]!='|';i++)
		{
//			PushTx(SECTOR9[i]);
			usuario_guardado[i]=SECTOR19[i];
			caracter_wifi++;
		}

		PushTx(comilla);
		PushTx(',');
		PushTx(comilla);
		for(i=0;i<12000;i++);
		for(i=(caracter_wifi+1);SECTOR19[i]!='|';i++)
		{
			contrasena_guardada[i-caracter_wifi-1]=SECTOR19[i];
		}
//			PushTx(SECTOR9[i]);
	}
	else
	{
		Enviar_Parametros("PODADORA");
		PushTx(comilla);
		PushTx(',');
		PushTx(comilla);
		for(i=0;i<8000;i++);
		Enviar_Parametros("12345678");

	}

	for(i=0;i<8000;i++);
	for(i=0;i<8000;i++);
	PushTx(comilla);
	Enviar_Parametros(",3,3");
	PushTx(0x0D);
	PushTx(0x0A);

//	while(flag_okey!=1);								//esperamos a recibir el OK
//	flag_okey=0;
//	delay=1;
//	while(delay);
	for(i=0;i<5;i++)
	{
		delay=1;
		while(delay);
	}

	Enviar_Parametros("AT+CIPMUX=1");			//le permitimos aceptar multiples conexiones
	for(i=0;i<8000;i++);
	PushTx(0x0D);
	PushTx(0x0A);
//	while(flag_okey!=1);
//	flag_okey=0;
//	delay=1;
//	while(delay);

	for(i=0;i<5;i++)
	{
		delay=1;
		while(delay);
	}



	Enviar_Parametros("AT+CIPSERVER=1");	//elegimos puerto de conexion
	for(i=0;i<8000;i++);
	Enviar_Parametros(",350");
	PushTx(0x0D);
	PushTx(0x0A);
//	while(flag_okey!=1);
//	flag_okey=0;

	for(i=0;i<5;i++)
	{
		delay=1;
		while(delay);
	}


	//El equipo que se quiera comunicar con la podadora, deberá de conectarse a la red que genere el módulo y
	//usar una comunicación TCP (IP=192.168.4.1 y el puerto 350) para la transmisión y recepción de información

}
