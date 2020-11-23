/*
 * control.c
 */
#include "aplicacion.h"



#define DESVIACION_MAX 	3


//		si tomo el setpoint (ej 45°) y me desvio para la derecha, cuando vuelva a tomar la medicion (ej 10°) voy a tener un error positivo (45-10)=35
//		si tomo el setpoint (ej 45°) y me desvio para la izquierda, cuando vuelva a tomar la medicion (ej 135°) voy a tener un error negativo (45-135)=-90


//		si tomo el setpoint (ej 45) y me desvio mucho a la derecha (medida=-10) el error sería (45+10)=55
//		si tomo el setpoint (ej 45) y me desvio mucho a la izquierda (medida=-170) el error sería (45+170)=215. Para este caso debería ser
//		error=215-360= -145

//
//	//					-170	170										 10		-10
//	//				-135			135								45				-45
//	//			-90						90						90						-90
//	//				-45				45								135				-135
//	//					-10		10										170		-170
//


void analizar_mensaje()
{

	uint8_t dummy,k,vector_k[6];
	uint16_t aux;

		if(caracteres==1)
		{
			mensaje=receptor[0];


			if(mensaje=='a')
			{

				flag_control=STOP;							//paro antes de tomar el setpoint
				motores(PARAR,0,0);

				for(dummy=0;dummy<15;dummy++)				//espero 2 segundos quieto para tomar el nuevo setpoint
				{
					delay=1;
					while(delay);
				}

				err_integral=error_previo=0;

				for(i_angulos=0;i_angulos<249;i_angulos++)
					vector_pid[i_angulos]=0;

				i_angulos=0;

				duty_der=duty_izq=DUTY_AVANZAR;


				motores(AVANZAR,duty_izq,duty_der);		//le digo que avance

				Enviar_Parametros("AT+CIPSEND=");		//envíio el OK
				PushTx(numero_id+48);
				PushTx(',');
				PushTx(2+48);
				PushTx(0x0D);
				PushTx(0x0A);
				while(flag_okey!=1);
				flag_okey=0;
				delay=1;				//hago un delay para establecer al esp8266
				while(delay);
				Enviar_Parametros("OK");
				PushTx(0x0D);
				PushTx(0x0A);
				delay=1;				//hago un delay para establecer al esp8266
				while(delay);
			}

			if(mensaje=='r')
			{

				flag_control=STOP;							//paro antes de tomar el setpoint
				motores(PARAR,0,0);

				err_integral=error_previo=0;

				for(dummy=0;dummy<15;dummy++)				//espero 2 segundos quieto para tomar el nuevo setpoint
				{
					delay=1;
					while(delay);
				}

				duty_der=duty_izq=DUTY_RETROCEDER;

				for(i_angulos=0;i_angulos<249;i_angulos++)
					vector_pid[i_angulos]=0;

				i_angulos=0;

				motores(RETROCEDER,duty_izq,duty_der);		//le digo que retroceda

				Enviar_Parametros("AT+CIPSEND=");		//envíio el OK
				PushTx(numero_id+48);
				PushTx(',');
				PushTx(2+48);
				PushTx(0x0D);
				PushTx(0x0A);
				while(flag_okey!=1);
				flag_okey=0;
				delay=1;				//hago un delay para establecer al esp8266
				while(delay);
				Enviar_Parametros("OK");
				PushTx(0x0D);
				PushTx(0x0A);
				delay=1;				//hago un delay para establecer al esp8266

			}

			if(mensaje=='p')
			{

				motores(PARAR,0,0);

				Enviar_Parametros("AT+CIPSEND=");		//envíio el OK
				PushTx(numero_id+48);
				PushTx(',');
				PushTx(2+48);
				PushTx(0x0D);
				PushTx(0x0A);
				while(flag_okey!=1);
				flag_okey=0;
				delay=1;				//hago un delay para establecer al esp8266
				while(delay);
				Enviar_Parametros("OK");
				PushTx(0x0D);
				PushTx(0x0A);
				delay=1;				//hago un delay para establecer al esp8266

			}

			if(mensaje=='i')
			{

				motores(IZQUIERDA,25,25);


				Enviar_Parametros("AT+CIPSEND=");		//envíio el OK
				PushTx(numero_id+48);
				PushTx(',');
				PushTx(2+48);
				PushTx(0x0D);
				PushTx(0x0A);
				while(flag_okey!=1);
				flag_okey=0;
				delay=1;				//hago un delay para establecer al esp8266
				while(delay);
				Enviar_Parametros("OK");
				PushTx(0x0D);
				PushTx(0x0A);
				delay=1;				//hago un delay para establecer al esp8266

			}

			if(mensaje=='d')
			{

				motores(DERECHA,25,25);

				Enviar_Parametros("AT+CIPSEND=");		//envíio el OK
				PushTx(numero_id+48);
				PushTx(',');
				PushTx(2+48);
				PushTx(0x0D);
				PushTx(0x0A);
				while(flag_okey!=1);
				flag_okey=0;
				delay=1;				//hago un delay para establecer al esp8266
				while(delay);
				Enviar_Parametros("OK");
				PushTx(0x0D);
				PushTx(0x0A);
				delay=1;				//hago un delay para establecer al esp8266


			}


			if(mensaje=='c')				//rutina de calibracion del sensor magnetico
			{

				//envio el OK
				Enviar_Parametros("AT+CIPSEND=");
				PushTx(numero_id+48);
				PushTx(',');
				PushTx(2+48);
				PushTx(0x0D);
				PushTx(0x0A);
				while(flag_okey!=1);
				flag_okey=0;
				delay=1;									//hago un delay para establecer al esp8266
				while(delay);
				Enviar_Parametros("OK");

				estado_medicion=CALIBRANDO_MPU;
				ARRANCAR_I2C0;
				while(estado_medicion==CALIBRANDO_MPU);

				SetPIN(CORTE,RON);
				motores(DERECHA,40,40);

				estado_medicion=CALIBRANDO_MAGNETO;
				grabar=0;
				while(!grabar);


				motores(PARAR,0,0);
				SetPIN(CORTE,ROFF);

				//SI INA esta en 0 y INB esta en 0, las ruedas frenan
				SetPIN(INAT1,ROFF);
				SetPIN(INAT2,ROFF);
				SetPIN(INBT1,ROFF);
				SetPIN(INBT2,ROFF);

				estado_medicion=MIDIENDO;

				vector_calib[0]=prom_gx;
				vector_calib[1]=prom_gy;
				vector_calib[2]=prom_gz;
				vector_calib[3]=prom_ax;
				vector_calib[4]=prom_ay;
				vector_calib[5]=prom_az;
				vector_calib[6]=xsf;
				vector_calib[7]=ysf;
				vector_calib[8]=xoff;
				vector_calib[9]=yoff;

				interrupciones(OFF);
				u32IAP_PrepareSectors(S10,S10);	//siempre que se escriba o se limpie un sector hay que prepararlo
				u32IAP_CopyRAMToFlash(SECTOR10, (uint32_t) vector_calib, 256);		//rutina para escribir el sector
				interrupciones(ON);

				//reinicio las variables de la imu que uso para calcular los angulos
				ang_acce[0]=ang_acce[1]=ang_acce[2]=angulos[0]=angulos[1]=angulos[2]=0;

				//envio el FIN
				Enviar_Parametros("AT+CIPSEND=");
				PushTx(numero_id+48);
				PushTx(',');
				PushTx(3+48);
				PushTx(0x0D);
				PushTx(0x0A);
				while(flag_okey!=1);
				flag_okey=0;
				delay=1;									//hago un delay para establecer al esp8266
				while(delay);
				Enviar_Parametros("FIN");
			}

			if(mensaje=='v')
			{
				Enviar_Parametros("AT+CIPSEND=");		//envio el OK
				PushTx(numero_id+48);
				PushTx(',');
				PushTx(2+48);
				PushTx(0x0D);
				PushTx(0x0A);
				while(flag_okey!=1);
				flag_okey=0;
				delay=1;				//hago un delay para establecer al esp8266
				while(delay);
				Enviar_Parametros("OK");
				PushTx(0x0D);
				PushTx(0x0A);
				delay=1;				//hago un delay para establecer al esp8266
			}

			if(mensaje=='m')
			{
				enviar_datos();
			}

			if(mensaje=='y')
			{
				SetPIN(CORTE,ROFF);

				Enviar_Parametros("AT+CIPSEND=");		//envíio el OK
				PushTx(numero_id+48);
				PushTx(',');
				PushTx(2+48);
				PushTx(0x0D);
				PushTx(0x0A);
				while(flag_okey!=1);
				flag_okey=0;
				delay=1;				//hago un delay para establecer al esp8266
				while(delay);
				Enviar_Parametros("OK");
				PushTx(0x0D);
				PushTx(0x0A);
				delay=1;				//hago un delay para establecer al esp8266
			}

			if(mensaje=='o')
			{
				SetPIN(CORTE,RON);

				Enviar_Parametros("AT+CIPSEND=");		//envíio el OK
				PushTx(numero_id+48);
				PushTx(',');
				PushTx(2+48);
				PushTx(0x0D);
				PushTx(0x0A);
				while(flag_okey!=1);
				flag_okey=0;
				delay=1;				//hago un delay para establecer al esp8266
				while(delay);
				Enviar_Parametros("OK");
				PushTx(0x0D);
				PushTx(0x0A);
				delay=1;				//hago un delay para establecer al esp8266

			}

			if((mensaje=='1')||(mensaje=='2')||(mensaje=='3')||(mensaje=='4')||(mensaje=='5')||(mensaje=='6'))
			{

				if(mensaje=='1')
				{
					kp+=0.1;					//Aumento el valor de Kp. Por ejemplo KP=1.1
					aux=kp*1000;					//aux=11
				}

				if(mensaje=='2')
				{
					kp-=0.1;					//Aumento el valor de Kp. Por ejemplo KP=1.1
					aux=kp*1000;					//aux=11
				}

				if(mensaje=='3')
				{
					kd+=0.1;					//Aumento el valor de Kp. Por ejemplo KP=1.1
					aux=kd*1000;					//aux=11
				}

				if(mensaje=='4')
				{
					kd-=0.1;					//Aumento el valor de Kp. Por ejemplo KP=1.1
					aux=kd*1000;					//aux=11
				}


				if(mensaje=='5')
				{
					ki+=0.001;					//Aumento el valor de Kp. Por ejemplo KP=1.1
					aux=ki*1000;					//aux=11
				}

				if(mensaje=='6')
				{

					for(i_angulos=0;i_angulos<249;i_angulos++)
						vector_pid[i_angulos]=0;

					i_angulos=0;

					set_point=angulos[2];
					motores(DERECHA,25,25);
					flag_control=ARRANCAR_ADELANTE;

				}


				dummy=aux/10000;					//dummy=1519/10000	--->dummy=1
				vector_k[0]=dummy+48;
				aux=aux%10000;					//aux=519
				dummy=aux/1000;					//dummy=519/100	--->dummy=5
				vector_k[1]=dummy+48;
				vector_k[2]=',';
				aux=aux%1000;					//aux=519%100---> AUX=19;
				dummy=aux/100;					//dummy=19/10----> dummy=1
				vector_k[3]=dummy+48;
				aux=aux%100;						//aux=19%10---_>aux=9
				vector_k[4]=aux+48;



				Enviar_Parametros("AT+CIPSEND=");
				PushTx(numero_id+48);
				PushTx(',');
				PushTx(5+48);			//envio 3 caracteres para enviar el vector
				PushTx(0x0D);
				PushTx(0x0A);
				while(flag_okey!=1);
				flag_okey=0;
				delay=1;				//hago un delay para establecer al esp8266
				while(delay);

				for(k=0;k<5;k++)
					PushTx(vector_k[k]);

				PushTx(0x0D);
				PushTx(0x0A);
				delay=1;				//hago un delay para establecer al esp8266
				while(delay);

			}

			caracteres=0;
//			mensaje=0;

		}

}

//
//void controlador_PID()
//{
//
//	error_anterior=error;			//guardo el error y salida que tuve la ultima vez
//
//	error_absoluto=set_point-medicion_actual;
//
//	medicion_actual=0;			//recien despues leerla y calcular el error la reinicio a 0
//
//	if(error_absoluto<=-180)
//	  	error=360+error_absoluto;
//	else if(error_absoluto>=180)
//	   	error=error_absoluto-360;
//	else
//	   	error=error_absoluto;
//
//	if( ( (error<DESVIACION_MAX) && (error>0) ) || ( (error>(-1)*DESVIACION_MAX) && (error<0) ) )
//	{
//		delta_out=0;
//
//		if(flag_control==ARRANCAR_ADELANTE)
//		{
//			duty_der=DUTY_DRECHA_AVANZAR;
//			duty_izq=DUTY_IZQUIERDA_AVANZAR;
//		}
//		else
//		{
//			duty_der=DUTY_DRECHA_RETROCEDER;
//			duty_izq= DUTY_IZQUIERDA_RETROCEDER;
//		}
//	}
//	else
//	{
//		if(flag_control==ARRANCAR_ADELANTE)
//			pid_accion=1;
//		else
//			pid_accion=-1;
//
//		delta_out=pid_accion*(error*ki+delta_error*kp);
//
//
//		duty_der+=delta_out;
//		duty_izq-=delta_out;
//
//
//		if(flag_control==ARRANCAR_ADELANTE)
//		{
//			if(duty_der>LIMITE_SUPERIOR_AVANZAR)
//				duty_der=LIMITE_SUPERIOR_AVANZAR;
//
//			if(duty_izq<LIMITE_INFERIOR_AVANZAR)
//				duty_izq=LIMITE_INFERIOR_AVANZAR;
//
//			if(duty_der<LIMITE_INFERIOR_AVANZAR)
//				duty_der=LIMITE_INFERIOR_AVANZAR;
//
//			if(duty_izq>LIMITE_SUPERIOR_AVANZAR)
//				duty_izq=LIMITE_SUPERIOR_AVANZAR;
//		}
//		else
//		{
//			if(duty_der>LIMITE_SUPERIOR_RETROCEDER)
//				duty_der=LIMITE_SUPERIOR_RETROCEDER;
//
//			if(duty_izq<LIMITE_INFERIOR_RETROCEDER)
//				duty_izq=LIMITE_INFERIOR_RETROCEDER;
//
//			if(duty_der<LIMITE_INFERIOR_RETROCEDER)
//				duty_der=LIMITE_INFERIOR_RETROCEDER;
//
//			if(duty_izq>LIMITE_SUPERIOR_RETROCEDER)
//				duty_izq=LIMITE_SUPERIOR_RETROCEDER;
//		}
//
//	}
//
//	if(flag_control==ARRANCAR_ADELANTE)
//		motores(AVANZAR,(uint16_t)duty_der,(uint16_t)duty_izq);
//
//	if(flag_control==ARRANCAR_ATRAS)
//		motores(RETROCEDER,(uint16_t)duty_der,(uint16_t)duty_der);

//
//}
//
//


#define LIM_INTEGRAL_MAX 3
#define LIM_INTEGRAL_MIN -3

void controlador_PID()
{

	error_absoluto=set_point-angulos[2];

	if(error_absoluto<=-180)
	  	error=360+error_absoluto;
	else if(error_absoluto>=180)
	   	error=error_absoluto-360;
	else
	   	error=error_absoluto;					//calculo el error entre el setpoint y la medicion actual

	if( (error>DESVIACION_MAX) || (error< ( (-1) * DESVIACION_MAX) ) )
	{
		err_proporcional= (int) error;					//obtengo los parametros del PID
		err_integral=  (err_integral + (int) (error_previo));
		err_derivativo= (int) (error - error_previo);

		salida_pwm = ((kp*err_proporcional)+ (ki* err_integral) + (kd*err_derivativo));

		error_previo=error;

		if(flag_control==ARRANCAR_ADELANTE)
		{
			duty_der=DUTY_AVANZAR - salida_pwm;
			duty_izq=DUTY_AVANZAR + salida_pwm;

			if(duty_der>LIMITE_SUPERIOR_AVANZAR)
				duty_der=LIMITE_SUPERIOR_AVANZAR;

			if(duty_izq>LIMITE_SUPERIOR_AVANZAR)
				duty_izq=LIMITE_SUPERIOR_AVANZAR;

			if(duty_der<LIMITE_INFERIOR_AVANZAR)
				duty_der=LIMITE_INFERIOR_AVANZAR;

			if(duty_izq<LIMITE_INFERIOR_AVANZAR)
				duty_izq=LIMITE_INFERIOR_AVANZAR;

			motores(AVANZAR,(uint16_t)duty_izq,(uint16_t)duty_der);

		}
		else
		{

			duty_der=DUTY_RETROCEDER + salida_pwm;
			duty_izq=DUTY_RETROCEDER - salida_pwm;

			if(duty_der>LIMITE_SUPERIOR_RETROCEDER)
				duty_der=LIMITE_SUPERIOR_RETROCEDER;

			if(duty_izq>LIMITE_SUPERIOR_RETROCEDER)
				duty_izq=LIMITE_SUPERIOR_RETROCEDER;

			if(duty_der<LIMITE_INFERIOR_RETROCEDER)
				duty_der=LIMITE_INFERIOR_RETROCEDER;

			if(duty_izq<LIMITE_INFERIOR_RETROCEDER)
				duty_izq=LIMITE_INFERIOR_RETROCEDER;

			motores(RETROCEDER,(uint16_t)duty_izq,(uint16_t)duty_der);

		}
	}

}


