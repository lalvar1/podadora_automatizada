/*
 * Systick.c
 */

#include "Aplicacion.h"
volatile uint8_t contador=0,contador2=0,contador3=0,n_yaw;
volatile uint16_t contador4=0,contador_control=0;
volatile uint16_t contador_prox=0;

volatile uint16_t contador_eventos=0;




void InicSysTick(void){ //si divido x 4, interrumpe cada 2,5ms


		STRELOAD  = ( STCALIB/4 ) - 1 ;   //N=1 para 10ms
		STCURR = 0;

		ENABLE = 1;
		TICKINT = 1;
		CLKSOURCE = 1;
		return;
}

void SysTick_Handler(void)
{

	if(delay)						//delay necesario para hacer tiempo entre comandos que le envío al esp8266
	{
		contador++;
		if(contador==80)
		{
			contador=0;
			delay=0;
		}
	}

	if((estado_imu!=INICIANDO_MAGNETO)&&(estado_imu!=INICIANDO_MPU)&&(estado_medicion!=CALIBRANDO_MAGNETO))
	{

		contador2++;

		if(contador2==6)			//en un principio cada 2,5ms*6=15 ms pide datos nuevos a los sensores
		{

			if(estado_pid==MUESTREANDO)
			{
				medicion_actual+=angulos[2];
				n_yaw++;

				if(n_yaw==5)
				{
					n_yaw=0;
					estado_pid=CALCULANDO;
				}
			}

			contador2=0;
			ARRANCAR_I2C0;
		}

	}

	if(estado_medicion==CALIBRANDO_MAGNETO)
	{
		contador3++;

		if(contador3==40)				//Cada 100 ms tomo una muestra
		{
			contador3=0;
			ARRANCAR_I2C0;
		}
	}

	if((flag_control==ARRANCAR_ADELANTE)||(flag_control==ARRANCAR_ATRAS))
	{

		if (estado_pid==ESPERANDO)				//la idea es controlar cada 100mseg. en ese tiempo 25 mseg me quedo esperando
		{										//Pasado ese tiempo, empiezo a tomar 5 muestras
												//el tiempo que tardo en tomar 5 muestras es 75 mseg.
												//El promedio de esas muestras tomadas se compara con el setpoint  y se realice el control
			contador_control++;
			if(contador_control==200)			//2,5*10=25ms
			{
				contador_control=0;				//reinicio el contador para la proxima
				estado_pid=CALCULANDO;			//aviso que hay que tomar las muestras
			}
		}
	}
	else
	{
		contador_control=0;
		estado_pid=REPOSO;
		err_integral=error_previo=0;
	}



		contador_prox++;
		if(contador_prox==200)
		{
			contador_prox=0;
			T0TCR = 0x00000001;		// Enciendo el temporizador
		}







	contador_eventos++;
	if(contador_eventos==200)		//cada 0,5segundos entro aca
	{
		contador_eventos=0;

		if(estado_secuencia==EN_CURSO)
		{
			if(contador_eventos_dir)
				contador_eventos_dir--;

			if(contador_eventos_cor)
				contador_eventos_cor--;

		}
	}






}


