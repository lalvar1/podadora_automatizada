/*
 * FW_TIMERS.c
 */

#include "Aplicacion.h"

#define TRIG1_ON		0
#define TRIG1_OFF 		1
#define ECHO1_WAIT 		2
#define ECHO1_ON		3
#define ECHO1_OFF 		4
#define TRIG2_ON		5
#define TRIG2_OFF 		6
#define ECHO2_WAIT 		7
#define ECHO2_ON		8
#define ECHO2_OFF 		9
#define TRIG3_ON		10
#define TRIG3_OFF 		11
#define ECHO3_WAIT 		12
#define ECHO3_ON		13
#define ECHO3_OFF 		14


volatile uint8_t estado_sensado;
volatile unsigned long contador_timer;			//variable que usare para contar los microsegundos

volatile uint16_t contador_proxi;

void Inic_timer()
{
	IPR0 |= (0x1<<11);

	PCONP |= 1 << 1; 		// Habilitar Timer 0
	PCLKSEL0 |= 1 << 2; 	// Clock for timer PCLK = CCLK Selecciono clock
	T0MR0 = 100;			// Configuro el tiempo del match 0 (100/100Mhz)==>1us
	T0MCR = 0x00000003;		// Configuro match 0 para que interrumpa y se resetee
	T0TCR = 0x00000002;		// Apago y reseteo el contador
	ISER0 |=(0x01 << 1); 	// Habilito Interrupcion TIMER0
	estado_sensado=TRIG1_ON;

	SetPINSEL(TRIG1,PINSEL_GPIO);
	SetPINSEL(ECHO1,PINSEL_GPIO);
	SetDIR(TRIG1,SALIDA);
	SetDIR(ECHO1,ENTRADA);
	SetPIN(TRIG1,OFF);

	SetPINSEL(TRIG2,PINSEL_GPIO);
	SetPINSEL(ECHO2,PINSEL_GPIO);
	SetDIR(TRIG2,SALIDA);
	SetDIR(ECHO2,ENTRADA);
	SetPIN(TRIG2,OFF);

	SetPINSEL(TRIG3,PINSEL_GPIO);
	SetPINSEL(ECHO3,PINSEL_GPIO);
	SetDIR(TRIG3,SALIDA);
	SetDIR(ECHO3,ENTRADA);
	SetPIN(TRIG3,OFF);

	contador_proxi=0;
}


//el timer 0 es el encargado de contar 10 useg.
void TIMER0_IRQHandler (void)
{

	T0IR|=0x1;		//borro el flag del match 0

	switch(estado_sensado)
	{
	case TRIG1_ON:
		SetPIN(TRIG1,ON);				//enciendo señal de trig por 10useg
		contador_proxi++;
		if(contador_proxi==9)
		{
			contador_proxi=0;
			estado_sensado=TRIG1_OFF;
		}
		break;

	case TRIG1_OFF:
		SetPIN(TRIG1,OFF);				//apago la señal de TRIG
		estado_sensado=ECHO1_WAIT;
		break;

	case ECHO1_WAIT:					//me quedo esperando que el la señal echo se active
		if(GetPIN(ECHO1,1))
			estado_sensado=ECHO1_ON;
		break;

	case ECHO1_ON:
		if(GetPIN(ECHO1,1))
			contador_timer++;					//cuento de cuantos useg es el pulso
		else
			estado_sensado=ECHO1_OFF;			//cuando se apaga dejo de contar
		break;

	case ECHO1_OFF:
		distancia1=contador_timer/58.0;
		contador_timer=0;
		estado_sensado=TRIG2_ON;
		break;

	case TRIG2_ON:
		SetPIN(TRIG2,ON);				//enciendo señal de trig por 10useg
		contador_proxi++;
		if(contador_proxi==9)
		{
			contador_proxi=0;
			estado_sensado=TRIG2_OFF;
		}
		break;

	case TRIG2_OFF:
		SetPIN(TRIG2,OFF);
		estado_sensado=ECHO2_WAIT;
		break;

	case ECHO2_WAIT:
		if(GetPIN(ECHO2,1))
			estado_sensado=ECHO2_ON;
		break;

	case ECHO2_ON:
		if(GetPIN(ECHO2,1))
			contador_timer++;
		else
			estado_sensado=ECHO2_OFF;
		break;

	case ECHO2_OFF:
		distancia2=contador_timer/58.0;
		contador_timer=0;
//		T0TCR = 0x00000002;		// Apago y reseteo el contador
		estado_sensado=TRIG3_ON;
		break;


	case TRIG3_ON:
		SetPIN(TRIG3,ON);				//enciendo señal de trig por 10useg
		contador_proxi++;
		if(contador_proxi==9)
		{
			contador_proxi=0;
			estado_sensado=TRIG3_OFF;
		}
		break;

	case TRIG3_OFF:
		SetPIN(TRIG3,OFF);
		estado_sensado=ECHO3_WAIT;
		break;

	case ECHO3_WAIT:
		if(GetPIN(ECHO3,1))
			estado_sensado=ECHO3_ON;
		break;

	case ECHO3_ON:
		if(GetPIN(ECHO3,1))
			contador_timer++;
		else
			estado_sensado=ECHO3_OFF;
		break;

	case ECHO3_OFF:
		distancia3=contador_timer/58.0;
		contador_timer=0;
		T0TCR = 0x00000002;		// Apago y reseteo el contador
		estado_sensado=TRIG1_ON;
		break;
	}

}


//el sensor tiene un rango de 3 a 300 cm.
//la formula para sacar la distancia en cm es=====>  distancia[58]= Tiempo del pulso [useg]/58
//el tiempo del pulso podra ser desde 174 hasta 17400 useg
//el contador se incrementa cada 0.1 useg
//el contador tendra un valor entre 1740 y 174000 y luego debere de dividirlo por 10 para tener la presision de 0.1 useg


