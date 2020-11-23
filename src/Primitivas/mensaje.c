/*
 * mensaje.c
 *
 *  Created on: 10 de mar. de 2018
 *      Author: Cristian
 */

#include "aplicacion.h"


void analizar_mensaje2(void)
{
	uint16_t i_msg;
	uint8_t usuario[15],contrasena[15];
	uint8_t caracteres_a_enviar=0;
	uint8_t caracter_user=0;
	uint8_t caracter_psw=0;
	uint32_t direccion=0;
	uint8_t dummy;

			if((receptor[0]=='S')&&(receptor[1]=='1'))
			{
				if(SECTOR1[0]==0xFF)								//si no hay nombre guardado es porque no hay secuencia. Mando 'N'
				{
					Enviar_Parametros("AT+CIPSEND=");
					PushTx(numero_id+48);
					PushTx(',');
					PushTx(1+48);
					PushTx(0x0D);
					PushTx(0x0A);
					while(flag_okey!=1);
					flag_okey=0;
					delay=1;									//hago un delay para establecer al esp8266
					while(delay);
					PushTx('N');
				}
				else
				{
					for(i_msg=0;i_msg<10;i_msg++)				//leo cuantos caracteres tiene el nombre de la secuencia
					{
						if(SECTOR1[i_msg]=='|')
							break;
						else
							caracteres_a_enviar++;
					}

					Enviar_Parametros("AT+CIPSEND=");			//envio de la secuencia
					PushTx(numero_id+48);
					PushTx(',');
					PushTx(caracteres_a_enviar+48);
					PushTx(0x0D);
					PushTx(0x0A);
					while(flag_okey!=1);
					flag_okey=0;
					delay=1;									//hago un delay para establecer al esp8266
					while(delay);

					for(i_msg=0;i_msg<(caracteres_a_enviar);i_msg++)
						PushTx(SECTOR1[i_msg]);
				}

			}


			if((receptor[0]=='S')&&(receptor[1]=='2'))
			{
				if(SECTOR2[0]==0xFF)								//si no hay nombre guardado es porque no hay secuencia. Mando 'N'
				{
					Enviar_Parametros("AT+CIPSEND=");
					PushTx(numero_id+48);
					PushTx(',');
					PushTx(1+48);
					PushTx(0x0D);
					PushTx(0x0A);
					while(flag_okey!=1);
					flag_okey=0;
					delay=1;									//hago un delay para establecer al esp8266
					while(delay);
					PushTx('N');
				}
				else
				{
					for(i_msg=0;i_msg<10;i_msg++)
					{
						if(SECTOR2[i_msg]=='|')
							break;
						else
							caracteres_a_enviar++;
					}

					Enviar_Parametros("AT+CIPSEND=");
					PushTx(numero_id+48);
					PushTx(',');
					PushTx(caracteres_a_enviar+48);
					PushTx(0x0D);
					PushTx(0x0A);
					while(flag_okey!=1);
					flag_okey=0;
					delay=1;									//hago un delay para establecer al esp8266
					while(delay);

					for(i_msg=0;i_msg<(caracteres_a_enviar);i_msg++)
						PushTx(SECTOR2[i_msg]);
				}

			}

			if((receptor[0]=='S')&&(receptor[1]=='3'))
			{
				if(SECTOR3[0]==0xFF)								//si no hay nombre guardado es porque no hay secuencia. Mando 'N'
				{
					Enviar_Parametros("AT+CIPSEND=");
					PushTx(numero_id+48);
					PushTx(',');
					PushTx(1+48);
					PushTx(0x0D);
					PushTx(0x0A);
					while(flag_okey!=1);
					flag_okey=0;
					delay=1;									//hago un delay para establecer al esp8266
					while(delay);
					PushTx('N');
				}
				else
				{
					for(i_msg=0;i_msg<10;i_msg++)
					{
						if(SECTOR3[i_msg]==0x7C)
							break;
						else
							caracteres_a_enviar++;
					}

					Enviar_Parametros("AT+CIPSEND=");
					PushTx(numero_id+48);
					PushTx(',');
					PushTx(caracteres_a_enviar+48);
					PushTx(0x0D);
					PushTx(0x0A);
					while(flag_okey!=1);
					flag_okey=0;
					delay=1;									//hago un delay para establecer al esp8266
					while(delay);

					for(i_msg=0;i_msg<(caracteres_a_enviar);i_msg++)
						PushTx(SECTOR3[i_msg]);
				}

			}


			if((receptor[0]=='B')&&(receptor[1]=='1'))
			{
				interrupciones(OFF);			//apago las interrupciones para escribir en la memoria
				u32IAP_PrepareSectors(S1,S1);	//siempre que se escriba o se limpie un sector hay que prepararlo
				u32IAP_EraseSectors(S1,S1);		//rutina para borrar el sector 1
				interrupciones(ON);

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

			}

			if((receptor[0]=='B')&&(receptor[1]=='2'))
			{
				interrupciones(OFF);			//apago las interrupciones para escribir en la memoria
				u32IAP_PrepareSectors(S2,S2);	//siempre que se escriba o se limpie un sector hay que prepararlo
				u32IAP_EraseSectors(S2,S2);		//rutina para borrar el sector 2
				interrupciones(ON);

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

			}

			if((receptor[0]=='B')&&(receptor[1]=='3'))
			{
				interrupciones(OFF);			//apago las interrupciones para escribir en la memoria
				u32IAP_PrepareSectors(S3,S3);	//siempre que se escriba o se limpie un sector hay que prepararlo
				u32IAP_EraseSectors(S3,S3);		//rutina para borrar el sector 3
				interrupciones(ON);

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

			}


			if((receptor[0]=='Z')&&(receptor[1]=='|'))
			{

				for(i_msg=0;i_msg<15;i_msg++)
					usuario[i_msg]=contrasena[i_msg]=0;

				for(i_msg=0;i_msg<256;i_msg++)
					vector_memoria[i_msg]=0;

				caracter_user=caracter_psw=0;

				//capturo del mensaje el nuevo usuario y la nueva contraseña
				for(i_msg=2;receptor[i_msg]!='|';i_msg++)
				{
					usuario[i_msg-2]=receptor[i_msg];
					caracter_user++;
				}

				for(i_msg=caracter_user+3;receptor[i_msg]!='|';i_msg++)
				{
					contrasena[i_msg-caracter_user-3]=receptor[i_msg];
					caracter_psw++;
				}

				for(i_msg=0;i_msg<caracter_user;i_msg++)
					vector_memoria[i_msg]=usuario[i_msg];

				vector_memoria[caracter_user]='|';

				for(i_msg=0;i_msg<caracter_psw;i_msg++)
				{
					vector_memoria[i_msg+caracter_user+1]=contrasena[i_msg];
				}

				vector_memoria[caracter_user+caracter_psw+1]='|';

				//cambio el usuario y contraseña

				Enviar_Parametros("AT+CWSAP=");						//configuro usuario y contraseña generico
				PushTx(comilla);									//lo envio asi proque no puedo enviar comillas doble de una
				for(i_msg=0;i_msg<8000;i_msg++);
				for(i_msg=0;i_msg<caracter_user;i_msg++)
					PushTx(usuario[i_msg]);
				PushTx(comilla);
				PushTx(',');
				PushTx(comilla);
				for(i_msg=0;i_msg<8000;i_msg++);
				for(i_msg=0;i_msg<caracter_psw;i_msg++)
					PushTx(contrasena[i_msg]);
				PushTx(comilla);
				for(i_msg=0;i_msg<8000;i_msg++);
				Enviar_Parametros(",3,3");
				PushTx(0x0D);
				PushTx(0x0A);

				while(flag_okey!=1);								//esperamos a recibir el OK
				flag_okey=0;
				delay=1;
				while(delay);

				//guardo los nuevos datos en la memoria
				interrupciones(OFF);
				u32IAP_PrepareSectors(S19,S19);	//siempre que se escriba o se limpie un sector hay que prepararlo
				u32IAP_EraseSectors(S19,S19);		//primero borro el sector 9

				u32IAP_PrepareSectors(S19,S19);	//siempre que se escriba o se limpie un sector hay que prepararlo
				u32IAP_CopyRAMToFlash(SECTOR19, (uint32_t) vector_memoria, 256);		//rutina para escribir el sector
				interrupciones(ON);

				//enviar OK

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
			}

			if((receptor[0]=='N')&&(receptor[1]=='1'))
			{
				//limpio el vector por las dudas
				for(i_msg=0;i_msg<256;i_msg++)
					vector_memoria[i_msg]=0;

				ptr_vector_memoria=caracteres-3;
				i_msg=0;
				do
				{
					vector_memoria[i_msg]=receptor[i_msg+3];
					i_msg++;
				}while(i_msg<ptr_vector_memoria);

				interrupciones(OFF);
				u32IAP_PrepareSectors(S1,S1);	//siempre que se escriba o se limpie un sector hay que prepararlo
				u32IAP_CopyRAMToFlash(SECTOR1, (uint32_t) vector_memoria, 256);		//rutina para escribir el sector
				interrupciones(ON);

				estado_podadora=GRABAR_SEC1;


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

				for(i_msg=0;i_msg<256;i_msg++)
					vector_memoria[i_msg]=0;

				vector_memoria[0]='p';
				vector_memoria2[0]='f';
				ptr_vector_memoria=1;
				ptr_vector_memoria2=1;
			}

			if((receptor[0]=='N')&&(receptor[1]=='2'))
			{
				//limpio el vector por las dudas
				for(i_msg=0;i_msg<256;i_msg++)
					vector_memoria[i_msg]=0;

				ptr_vector_memoria=caracteres-3;
				i_msg=0;
				do
				{
					vector_memoria[i_msg]=receptor[i_msg+3];
					i_msg++;
				}while(i_msg<ptr_vector_memoria);


				estado_podadora=GRABAR_SEC2;

				interrupciones(OFF);
				u32IAP_PrepareSectors(S2,S2);	//siempre que se escriba o se limpie un sector hay que prepararlo
				u32IAP_CopyRAMToFlash(SECTOR2, (uint32_t) vector_memoria, 256);		//rutina para escribir el sector
				interrupciones(ON);

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

				for(i_msg=0;i_msg<256;i_msg++)
					vector_memoria[i_msg]=0;

				vector_memoria[0]='p';
				vector_memoria2[0]='f';
				ptr_vector_memoria=1;
				ptr_vector_memoria2=1;
			}

			if((receptor[0]=='N')&&(receptor[1]=='3'))
			{
				//limpio el vector por las dudas
				for(i_msg=0;i_msg<256;i_msg++)
					vector_memoria[i_msg]=0;

				ptr_vector_memoria=caracteres-3;
				i_msg=0;
				do
				{
					vector_memoria[i_msg]=receptor[i_msg+3];
					i_msg++;
				}while(i_msg<ptr_vector_memoria);


				estado_podadora=GRABAR_SEC3;

				interrupciones(OFF);
				u32IAP_PrepareSectors(S3,S3);	//siempre que se escriba o se limpie un sector hay que prepararlo
				u32IAP_CopyRAMToFlash(SECTOR3, (uint32_t) vector_memoria, 256);		//rutina para escribir el sector
				interrupciones(ON);

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

				for(i_msg=0;i_msg<256;i_msg++)
					vector_memoria[i_msg]=0;

				vector_memoria[0]='p';
				vector_memoria2[0]='f';
				ptr_vector_memoria=1;
				ptr_vector_memoria2=1;
			}

			if((receptor[0]=='S')&&(receptor[1]=='T')&&(receptor[2]=='A'))
			{

				estado_secuencia=EN_CURSO;

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
			}

			if((receptor[0]=='P')&&(receptor[1]=='A')&&(receptor[2]=='U'))
			{
				estado_secuencia=PAUSADA;

	    		SetPIN(INAT1,ROFF);
	    		SetPIN(INAT2,ROFF);
	    		SetPIN(INBT1,ROFF);
	    		SetPIN(INBT2,ROFF);
				motores(PARAR,0,0);
				SetPIN(CORTE,ROFF);

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
				Enviar_Parametros("PAU");
			}

			if(((receptor[0]=='a')||(receptor[0]=='p')||(receptor[0]=='r')||(receptor[0]=='d')||(receptor[0]=='i'))&&(receptor[1]=='|'))
			{

				//consigo el numero de eventos del mensaje
				evento_dir=caracteres-3;
				//en funcion de los decimales que tiene el valor numerico del mensaje armo la cantidad de eventos
				if(evento_dir==4)
					evento_dir=(receptor[2]-48)*1000+(receptor[3]-48)*100+(receptor[4]-48)*10+(receptor[5]-48);
				else if (evento_dir==3)
					evento_dir=(receptor[2]-48)*100+(receptor[3]-48)*10+(receptor[4]-48);
				else if (evento_dir==2)
					evento_dir=(receptor[2]-48)*10+(receptor[3]-48);
				else
					evento_dir=(receptor[2]-48);

				//guardo primero la parte alta y luego la parte baja del numero de eventos del comando anterior
				//tambien guardo el "|"
				vector_memoria[ptr_vector_memoria]=(uint8_t)(evento_dir>>8);
				vector_memoria[ptr_vector_memoria+1]=(uint8_t)(evento_dir);
				vector_memoria[ptr_vector_memoria+2]='|';
				reg_dir++;

				if(reg_dir==64)				//llene el vector
				{
					reg_dir=0;

					interrupciones(OFF);

					if(estado_podadora==GRABAR_SEC1)
					{
						u32IAP_PrepareSectors(S1,S1);	//siempre que se escriba o se limpie un sector hay que prepararlo
						u32IAP_CopyRAMToFlash((S1_DIR+(0x100)*(grabados_dir)), (uint32_t) vector_memoria, 256);		//rutina para escribir el sector
					}
					if(estado_podadora==GRABAR_SEC2)
					{
						u32IAP_PrepareSectors(S2,S2);	//siempre que se escriba o se limpie un sector hay que prepararlo
						u32IAP_CopyRAMToFlash(S2_DIR+(0x100)*(grabados_dir), (uint32_t) vector_memoria, 256);		//rutina para escribir el sector
					}
					if(estado_podadora==GRABAR_SEC3)
					{
						u32IAP_PrepareSectors(S3,S3);	//siempre que se escriba o se limpie un sector hay que prepararlo
						u32IAP_CopyRAMToFlash(S3_DIR+(0x100)*(grabados_dir), (uint32_t) vector_memoria, 256);		//rutina para escribir el sector
					}

					interrupciones(ON);

					grabados_dir++;
					ptr_vector_memoria=0;					//reinicio en puntero del vector
					for(i_msg=0;i_msg<256;i_msg++)			//limpio el vector
						vector_memoria[i_msg]=0;

				}
				else
					ptr_vector_memoria+=3;


				//guardo el comando que recibi en el vector
				vector_memoria[ptr_vector_memoria]=receptor[0];
				ptr_vector_memoria++;

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


				//realizo la acción correspondiente
				if(receptor[0]=='a')
				{
					flag_control=STOP;							//paro antes de tomar el setpoint
					motores(PARAR,0,0);

					for(dummy=0;dummy<15;dummy++)				//espero 2 segundos quieto para tomar el nuevo setpoint
					{
						delay=1;
						while(delay);
					}

					err_integral=error_previo=0;

					duty_der=duty_izq=DUTY_AVANZAR;


					motores(AVANZAR,duty_izq,duty_der);		//le digo que avance


				}
				else if(receptor[0]=='p')
				{
					estado_direccion=DETENIDO;
					motores(PARAR,0,0);
				}
				else if(receptor[0]=='r')
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

					motores(RETROCEDER,duty_izq,duty_der);		//le digo que retroceda
				}
				else if(receptor[0]=='i')
				{
					estado_direccion=IZQUIERDA;
					motores(IZQUIERDA,25,25);
				}
				else
				{
					estado_direccion=DERECHA;
					motores(DERECHA,25,25);
				}



			}

			if(((receptor[0]=='o')||(receptor[0]=='f'))&&(receptor[1]=='|'))
			{
				//el primer comando corte que reciba, lo debo guardar como que estuvo en off

				//consigo el numero de eventos del mensaje
				evento_cor=caracteres-3;
				//en funcion de los decimales que tiene el valor numerico del mensaje armo la cantidad de eventos
				if(evento_cor==4)
					evento_cor=(receptor[2]-48)*1000+(receptor[3]-48)*100+(receptor[4]-48)*10+(receptor[5]-48);
				else if (evento_cor==3)
					evento_cor=(receptor[2]-48)*100+(receptor[3]-48)*10+(receptor[4]-48);
				else if (evento_cor==2)
					evento_cor=(receptor[2]-48)*10+(receptor[3]-48);
				else
					evento_cor=(receptor[2]-48);

				//guardo primero la parte alta y luego la parte baja del numero de eventos del comando anterior
				//tambien guardo el "|"
				vector_memoria2[ptr_vector_memoria2]=(uint8_t)(evento_cor>>8);
				vector_memoria2[ptr_vector_memoria2+1]=(uint8_t)(evento_cor);
				vector_memoria2[ptr_vector_memoria2+2]='|';
				reg_cor++;

				if(reg_cor==64)				//llene el vector
				{
					reg_cor=0;

					interrupciones(OFF);

					if(estado_podadora==GRABAR_SEC1)
					{
						u32IAP_PrepareSectors(S1,S1);	//siempre que se escriba o se limpie un sector hay que prepararlo
						u32IAP_CopyRAMToFlash((S1_COR+(0x100)*(grabados_cor)), (uint32_t) vector_memoria2, 256);		//rutina para escribir el sector
					}
					if(estado_podadora==GRABAR_SEC2)
					{
						u32IAP_PrepareSectors(S2,S2);	//siempre que se escriba o se limpie un sector hay que prepararlo
						u32IAP_CopyRAMToFlash(S2_COR+(0x100)*(grabados_cor), (uint32_t) vector_memoria2, 256);		//rutina para escribir el sector
					}
					if(estado_podadora==GRABAR_SEC3)
					{
						u32IAP_PrepareSectors(S3,S3);	//siempre que se escriba o se limpie un sector hay que prepararlo
						u32IAP_CopyRAMToFlash(S3_COR+(0x100)*(grabados_cor), (uint32_t) vector_memoria2, 256);		//rutina para escribir el sector
					}

					interrupciones(ON);

					grabados_cor++;
					ptr_vector_memoria2=0;					//reinicio en puntero del vector
					for(i_msg=0;i_msg<256;i_msg++)			//limpio el vector
						vector_memoria2[i_msg]=0;

				}
				else
					ptr_vector_memoria2+=3;


				//guardo el comando que recibi en el vector
				vector_memoria2[ptr_vector_memoria2]=receptor[0];
				ptr_vector_memoria2++;


				//realizo la acción correspondiente
				if(receptor[0]=='o')
				{
					estado_corte=ON;
					SetPIN(CORTE,RON);

				}
				else
				{
					estado_corte=OFF;
					SetPIN(CORTE,ROFF);
				}

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

			}

			if((receptor[0]=='D')&&(receptor[1]=='E')&&(receptor[2]=='S'))
			{
				//freno t
	    		SetPIN(INAT1,ROFF);
	    		SetPIN(INAT2,ROFF);
	    		SetPIN(INBT1,ROFF);
	    		SetPIN(INBT2,ROFF);
				motores(PARAR,0,0);
				SetPIN(CORTE,ROFF);

				//limpio los vectores donde guardaba las secuencias
				for(i_msg=0;i_msg<256;i_msg++)
					vector_memoria[i_msg]=vector_memoria2[i_msg]=0;


				//reinicio las otras variables que uso para guardar la secuencia
				//las que uso para moverme por el vector
				//las que uso para moverme por la flash cuando grabo
				//las que uso para saber los comandos que tengo en el vector
				grabados_dir=grabados_cor=reg_dir=reg_cor=0;

				vector_memoria2[0]='f';		//el primer caracter del vector memoria va a ser f
				ptr_vector_memoria2=1;
				vector_memoria[0]='p';		//el primer caracter del vector memoria va a ser f
				ptr_vector_memoria2=1;

				//reinicio las variables de estado de corte y dirección
				estado_direccion=estado_corte=SIN_COMANDO;

				//reinicio la variable de estado en secuencia (por si estaba pausada)
				estado_secuencia=EN_CURSO;

				//borro el sector y restituyo el nombre de la secuencia en el sector
				interrupciones(OFF);

				if(estado_podadora==GRABAR_SEC1)
				{
					//rescato el nombre de la secuencia antes de borrar
					i_msg=0;
					do
					{
						vector_memoria[i_msg]=SECTOR1[i_msg];
						i_msg++;
					}while(SECTOR1[i_msg]!='|');

					vector_memoria[i_msg]='|';

					u32IAP_PrepareSectors(S1,S1);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_EraseSectors(S1,S1);		//rutina para borrar el sector
					u32IAP_PrepareSectors(S1,S1);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_CopyRAMToFlash(SECTOR1, (uint32_t) vector_memoria, 256);		//vuelvo a escribir el nombre de la secuencia
				}
				if(estado_podadora==GRABAR_SEC2)
				{
					//rescato el nombre de la secuencia antes de borrar
					i_msg=0;
					do
					{
						vector_memoria[i_msg]=SECTOR2[i_msg];
						i_msg++;
					}while(SECTOR2[i_msg]!='|');

					vector_memoria[i_msg]='|';
					u32IAP_PrepareSectors(S2,S2);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_EraseSectors(S2,S2);		//rutina para borrar el sector
					u32IAP_PrepareSectors(S2,S2);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_CopyRAMToFlash(SECTOR2, (uint32_t) vector_memoria, 256);		//vuelvo a escribir el nombre de la secuencia
				}
				if(estado_podadora==GRABAR_SEC3)
				{
					//rescato el nombre de la secuencia antes de borrar
					i_msg=0;
					do
					{
						vector_memoria[i_msg]=SECTOR3[i_msg];
						i_msg++;
					}while(SECTOR3[i_msg]!='|');

					vector_memoria[i_msg]='|';
					u32IAP_PrepareSectors(S3,S3);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_EraseSectors(S3,S3);		//rutina para borrar el sector
					u32IAP_PrepareSectors(S3,S3);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_CopyRAMToFlash(SECTOR3, (uint32_t) vector_memoria, 256);		//vuelvo a escribir el nombre de la secuencia
				}

				interrupciones(ON);

				for(i_msg=0;i_msg<256;i_msg++)
					vector_memoria[i_msg]=vector_memoria2[i_msg]=0;

				vector_memoria[0]='p';
				ptr_vector_memoria=1;
				vector_memoria2[0]='f';		//el primer caracter del vector memoria va a ser f
				ptr_vector_memoria2=1;

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

			}

			if((receptor[0]=='S')&&(receptor[1]=='T')&&(receptor[2]=='O'))
			{

				caracteres=i_msg=0;
				do
				{
					caracteres++;
					i_msg++;
				}while(receptor[4+i_msg]!='|');

				if(caracteres==4)
					evento_dir=(receptor[4]-48)*1000+(receptor[5]-48)*100+(receptor[6]-48)*10+(receptor[7]-48);
				else if (caracteres==3)
					evento_dir=(receptor[4]-48)*100+(receptor[5]-48)*10+(receptor[6]-48);
				else if (caracteres==2)
					evento_dir=(receptor[4]-48)*10+(receptor[5]-48);
				else
					evento_dir=(receptor[4]-48);

				//guardo primero la parte alta y luego la parte baja del numero de eventos del comando anterior
				//tambien guardo el "|"
				vector_memoria[ptr_vector_memoria]=(uint8_t)(evento_dir>>8);
				vector_memoria[ptr_vector_memoria+1]=(uint8_t)(evento_dir);
				vector_memoria[ptr_vector_memoria+2]='|';
				reg_dir++;

				caracteres=0;
				do
				{
					caracteres++;
					i_msg++;
				}while(receptor[5+i_msg]!='|');

				i_msg-=caracteres;

				//en funcion de los decimales que tiene el valor numerico del mensaje armo la cantidad de eventos
				if(caracteres==4)
					evento_cor=(receptor[5+i_msg]-48)*1000+(receptor[6+i_msg]-48)*100+(receptor[7+i_msg]-48)*10+(receptor[8+i_msg]-48);
				else if (caracteres==3)
					evento_cor=(receptor[5+i_msg]-48)*100+(receptor[6+i_msg]-48)*10+(receptor[7+i_msg]-48);
				else if (caracteres==2)
					evento_cor=(receptor[5+i_msg]-48)*10+(receptor[6+i_msg]-48);
				else
					evento_cor=(receptor[5+i_msg]-48);

				//guardo primero la parte alta y luego la parte baja del numero de eventos del comando anterior
				//tambien guardo el "|"
				vector_memoria2[ptr_vector_memoria2]=(uint8_t)(evento_cor>>8);
				vector_memoria2[ptr_vector_memoria2+1]=(uint8_t)(evento_cor);
				vector_memoria2[ptr_vector_memoria2+2]='|';
				reg_cor++;

				interrupciones(OFF);

				if(estado_podadora==GRABAR_SEC1)
				{
					u32IAP_PrepareSectors(S1,S1);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_CopyRAMToFlash((S1_DIR+(0x100)*(grabados_dir)), (uint32_t) vector_memoria, 256);		//rutina para escribir el sector
					u32IAP_PrepareSectors(S1,S1);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_CopyRAMToFlash((S1_COR+(0x100)*(grabados_cor)), (uint32_t) vector_memoria2, 256);		//rutina para escribir el sector
				}
				if(estado_podadora==GRABAR_SEC2)
				{
					u32IAP_PrepareSectors(S2,S2);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_CopyRAMToFlash(S2_DIR+(0x100)*(grabados_dir), (uint32_t) vector_memoria, 256);		//rutina para escribir el sector
					u32IAP_PrepareSectors(S2,S2);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_CopyRAMToFlash((S2_COR+(0x100)*(grabados_cor)), (uint32_t) vector_memoria2, 256);		//rutina para escribir el sector

				}
				if(estado_podadora==GRABAR_SEC3)
				{
					u32IAP_PrepareSectors(S3,S3);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_CopyRAMToFlash(S3_DIR+(0x100)*(grabados_dir), (uint32_t) vector_memoria, 256);		//rutina para escribir el sector
					u32IAP_PrepareSectors(S3,S3);	//siempre que se escriba o se limpie un sector hay que prepararlo
					u32IAP_CopyRAMToFlash((S3_COR+(0x100)*(grabados_cor)), (uint32_t) vector_memoria2, 256);		//rutina para escribir el sector

				}

				interrupciones(ON);

				//freno
	    		SetPIN(INAT1,ROFF);
	    		SetPIN(INAT2,ROFF);
	    		SetPIN(INBT1,ROFF);
	    		SetPIN(INBT2,ROFF);
				motores(PARAR,0,0);
				SetPIN(CORTE,ROFF);

				//limpio los vectores donde guardaba las secuencias
				for(i_msg=0;i_msg<256;i_msg++)
					vector_memoria[i_msg]=vector_memoria2[i_msg]=0;


				//reinicio las otras variables que uso para guardar la secuencia
				//las que uso para moverme por el vector
				//las que uso para moverme por la flash cuando grabo
				//las que uso para saber los comandos que tengo en el vector
				grabados_dir=grabados_cor=reg_dir=reg_cor=0;

				vector_memoria[0]='p';
				ptr_vector_memoria=1;
				vector_memoria2[0]='f';		//el primer caracter del vector memoria va a ser f
				ptr_vector_memoria2=1;

				//reinicio las variables de estado de corte y dirección
				estado_direccion=estado_corte=SIN_COMANDO;

				//reinicio la variable de estado en secuencia (por si estaba pausada)
				estado_secuencia=estado_podadora=REPOSO;

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

			}

			if((receptor[0]=='|')&&(receptor[1]=='c')&&(receptor[2]=='|'))
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


			if((receptor[0]=='D')&&(receptor[1]=='1'))
			{
				estado_podadora=REALIZAR_SEC1;
				estado_secuencia=EN_CURSO;
				ptr_vector_memoria=ptr_vector_memoria2=0;

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
			}

			if((receptor[0]=='D')&&(receptor[1]=='2'))
			{
				estado_podadora=REALIZAR_SEC2;
				estado_secuencia=EN_CURSO;
				ptr_vector_memoria=ptr_vector_memoria2=0;

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
			}

			if((receptor[0]=='D')&&(receptor[1]=='3'))
			{
				estado_podadora=REALIZAR_SEC3;
				estado_secuencia=EN_CURSO;
				ptr_vector_memoria=ptr_vector_memoria2=0;

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
			}


			if((receptor[0]=='F')&&(receptor[1]=='I')&&(receptor[2]=='N'))
			{
				flag_fin_dir=flag_fin_cor=1;
				contador_eventos_dir=contador_eventos_cor=0;
			}


			if((receptor[0]=='C')&&(receptor[1]=='O')&&(receptor[2]=='N'))
			{

				if( (distancia1>15) && (distancia2>15) && (distancia3>15) && ( GetPIN(PORT2,7,1) )  )
				{
					estado_secuencia=EN_CURSO;

					if(estado_direccion==AVANZANDO)
					{
						duty_der=duty_izq=DUTY_AVANZAR;
						motores(AVANZAR,duty_izq,duty_der);		//le digo que avance				//le digo que avance
					}

					if(estado_direccion==RETROCEDIENDO)
					{
						duty_der=duty_izq=DUTY_RETROCEDER;
						motores(RETROCEDER,duty_izq,duty_der);		//le digo que retroceda
					}


					if(estado_direccion==DERECHA)
					    motores(DERECHA,25,25);


					if(estado_direccion==IZQUIERDA)
					    motores(IZQUIERDA,25,25);

					if(estado_direccion==DETENIDO)
						motores(PARAR,0,0);

					if(estado_corte==ON)
						SetPIN(CORTE,RON);
					else
						SetPIN(CORTE,ROFF);

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
					Enviar_Parametros("CON");
				}
				else
				{
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
					Enviar_Parametros("NO");
				}


			}



			for(i_msg=0;i_msg<caracteres;i_msg++)
				receptor[i_msg]=0;

			caracteres=0;
}






void podadora()
{
	uint8_t dummy;


	if(((estado_podadora==REALIZAR_SEC1)||(estado_podadora==REALIZAR_SEC2)||(estado_podadora==REALIZAR_SEC3))&&(!flag_fin_cor)&&(estado_secuencia==EN_CURSO))
	{
		if((!contador_eventos_cor)&&(!flag_fin_cor))
		{
			if(estado_podadora==REALIZAR_SEC1)
			{
				comando_corte=S1_COR[ptr_vector_memoria2];
				contador_eventos_cor=(S1_COR[ptr_vector_memoria2+1]<<8)|(S1_COR[ptr_vector_memoria2+2]);
				if((S1_COR[ptr_vector_memoria2+4]==S1_COR[ptr_vector_memoria2+5])&&(S1_COR[ptr_vector_memoria2+5]==S1_COR[ptr_vector_memoria2+6]))
					flag_fin_cor=1;
			}
			if(estado_podadora==REALIZAR_SEC2)
			{
				comando_corte=S2_COR[ptr_vector_memoria2];
				contador_eventos_cor=(S2_COR[ptr_vector_memoria2+1]<<8)|(S2_COR[ptr_vector_memoria2+2]);
				if((S2_COR[ptr_vector_memoria2+4]==S2_COR[ptr_vector_memoria2+5])&&(S2_COR[ptr_vector_memoria2+5]==S2_COR[ptr_vector_memoria2+6]))
					flag_fin_cor=1;
			}
			if(estado_podadora==REALIZAR_SEC3)
			{
				comando_corte=S3_COR[ptr_vector_memoria2];
				contador_eventos_cor=(S3_COR[ptr_vector_memoria2+1]<<8)|(S3_COR[ptr_vector_memoria2+2]);
				if((S3_COR[ptr_vector_memoria2+4]==S3_COR[ptr_vector_memoria2+5])&&(S3_COR[ptr_vector_memoria2+5]==S3_COR[ptr_vector_memoria2+6]))
					flag_fin_cor=1;

			}

			ptr_vector_memoria2+=4;
			//en función del valor del comando prendo o apago el motor

			if(comando_corte=='o')
			{
				estado_corte=ON;
				SetPIN(CORTE,RON);
			}
			else
			{
				estado_corte=OFF;
				SetPIN(CORTE,ROFF);
			}



		}
	}


	if(((estado_podadora==REALIZAR_SEC1)||(estado_podadora==REALIZAR_SEC2)||(estado_podadora==REALIZAR_SEC3))&&(!flag_fin_dir)&&(estado_secuencia==EN_CURSO))
	{
		if((!contador_eventos_dir)&&(!flag_fin_dir))
		{
			if(estado_podadora==REALIZAR_SEC1)
			{
				comando_dir=S1_DIR[ptr_vector_memoria];
				contador_eventos_dir=(S1_DIR[ptr_vector_memoria+1]<<8)|(S1_DIR[ptr_vector_memoria+2]);

				if((S1_DIR[ptr_vector_memoria+4]==S1_DIR[ptr_vector_memoria+5])&&(S1_DIR[ptr_vector_memoria+5]==S1_DIR[ptr_vector_memoria+6]))
					flag_fin_dir=1;

			}
			if(estado_podadora==REALIZAR_SEC2)
			{
				comando_dir=S2_DIR[ptr_vector_memoria];
				contador_eventos_dir=(S2_DIR[ptr_vector_memoria+1]<<8)|(S2_DIR[ptr_vector_memoria+2]);
				if((S2_DIR[ptr_vector_memoria+4]==S2_DIR[ptr_vector_memoria+5])&&(S2_DIR[ptr_vector_memoria+5]==S2_DIR[ptr_vector_memoria+6]))
					flag_fin_dir=1;
			}
			if(estado_podadora==REALIZAR_SEC3)
			{
				comando_dir=S3_DIR[ptr_vector_memoria];
				contador_eventos_dir=(S3_DIR[ptr_vector_memoria+1]<<8)|(S3_DIR[ptr_vector_memoria+2]);
				if((S3_DIR[ptr_vector_memoria+4]==S3_DIR[ptr_vector_memoria+5])&&(S3_DIR[ptr_vector_memoria+5]==S3_DIR[ptr_vector_memoria+6]))
					flag_fin_dir=1;
			}

			ptr_vector_memoria+=4;
			//en función del valor del comando avanzo, retrocedo, doblo o freno

			//realizo la acción correspondiente
			if(comando_dir=='a')
			{
				flag_control=STOP;							//paro antes de tomar el setpoint
				motores(PARAR,0,0);

				for(dummy=0;dummy<15;dummy++)				//espero 2 segundos quieto para tomar el nuevo setpoint
				{
					delay=1;
					while(delay);
				}

				err_integral=error_previo=0;
				duty_der=duty_izq=DUTY_AVANZAR;
				motores(AVANZAR,duty_izq,duty_der);		//le digo que avance
			}

			if(comando_dir=='p')
			{
				estado_direccion=DETENIDO;
				motores(PARAR,0,0);
			}

			if(comando_dir=='r')
			{
				flag_control=STOP;							//paro antes de tomar el setpoint
				motores(PARAR,0,0);

				for(dummy=0;dummy<15;dummy++)				//espero 2 segundos quieto para tomar el nuevo setpoint
				{
					delay=1;
					while(delay);
				}

				err_integral=error_previo=0;
				duty_der=duty_izq=DUTY_RETROCEDER;
				motores(RETROCEDER,duty_izq,duty_der);		//le digo que retroceda
			}

			if(comando_dir=='i')
			{
				estado_direccion=IZQUIERDA;
				motores(IZQUIERDA,25,25);
			}

			if(comando_dir=='d')
			{
				estado_direccion=DERECHA;
				motores(DERECHA,25,25);
			}

		}
	}




	if((flag_fin_dir)&&(flag_fin_cor))
	{
		if((!contador_eventos_dir)&&(!contador_eventos_cor))
		{
			//freno
			SetPIN(INAT1,ROFF);
			SetPIN(INAT2,ROFF);
			SetPIN(INBT1,ROFF);
			SetPIN(INBT2,ROFF);
			motores(PARAR,0,0);
			SetPIN(CORTE,ROFF);

			//mando el FIN

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

			//reinicio las variables que use (ver si falta alguna)
			ptr_vector_memoria=ptr_vector_memoria2=flag_fin_dir=flag_fin_cor=0;
			estado_podadora=estado_secuencia=REPOSO;
			estado_direccion=estado_corte=SIN_COMANDO;
		}


	}



}
