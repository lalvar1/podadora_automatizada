/*
 * Kit_Principal.c
 */

#include "Aplicacion.h"

void InicializarKit ( void );

void InicializarKit ( void )
{
	comilla=34;						//segun la tabla ascii el 34 es la comilla doble

	reg_dir=reg_cor=0;				//inicializo numero de registros que tiene el vector

	vector_memoria2[0]='f';			//el primer caracter del vector memoria va a ser f
	ptr_vector_memoria2=ptr_vector_memoria=1;
	vector_memoria[0]='p';

	//inicializo los vectores de los punteros que recorreran los vectores
	contador_eventos_dir=contador_eventos_cor=flag_fin_dir=flag_fin_cor=0;


	estado_pid=ESPERANDO;

	InicPLL();
	inicializar_pwm();


	InicSysTick();
	INIC_I2C1();
	InitUART0();
	inicializar_wifi();
	Inic_timer();



	iser=ISER0;						//guardo el estado actual del registro ISER0 para despues poder deshabilitar
									//y habilitar las interrupciones


//	interrupciones(OFF);
//	u32IAP_PrepareSectors(S19,S19);	//siempre que se escriba o se limpie un sector hay que prepararlo
//	u32IAP_EraseSectors(S19,S19);		//primero borro el sector 9
//	interrupciones(ON);

	//inicializo variables PID
	err_integral=error_previo=0;


	ki=kd=0;
	kp=0.3;


	//InicADC();



}
