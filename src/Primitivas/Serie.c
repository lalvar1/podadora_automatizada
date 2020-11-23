/*
 * Serie.c
 */

#include "aplicacion.h"
#include <stdlib.h>

volatile char BufferRx[TOPE],BufferTx[TOPE];
volatile uint8_t Rxin=0,Rxout=0,Txin=0,Txout=0,TxStart=0;



void PushTx(char dato){
	BufferTx[Txin]=dato;
	Txin++;
	Txin%=TOPE;

	if(!TxStart)	{
		U0THR=PopTx();
		TxStart=0;
	}

}

uint16_t PopTx(void){			//saca el dato del buffer y trabajo con el dato en la interrupcion
	uint8_t aux_serie=0xFF;

	if(Txout!=Txin)	{
		aux_serie=BufferTx[Txout];
		Txout++;
		Txout%=TOPE;
	}
	return aux_serie;
}



void enviar_datos()
{
	uint16_t vector_mensaje[23],k,aux_serie2,dummy;

////envio del roll
//	if(angulos[0]<0)			//roll_serie lo ponemos entre -18000 y +18000. Por ejemplo -165,7° (-1657°)
//	{
//		vector_mensaje[0]=45;			//mando el signo si es negativo
//		aux_serie2=roll_serie*-1;		//aux=1657
//	}
//	else
//	{
		vector_mensaje[0]=' ';
		aux_serie2=roll_serie;			//aux=1657
//	}

	dummy=(aux_serie2/1000)+48;		//dummy=1+48(para pasar a ascii)
	vector_mensaje[1]=dummy;
	aux_serie2%=1000;					//aux=657
	dummy=(aux_serie2/100)+48;			//dummy=6+48
	vector_mensaje[2]=dummy;
	aux_serie2%=100;					//aux=57;
	dummy=(aux_serie2/10)+48;			//dummy=5
	vector_mensaje[3]=dummy;
	vector_mensaje[4]=',';				//envio la coma
	aux_serie2%=10;					//aux=7
	vector_mensaje[5]=(aux_serie2+48);
	vector_mensaje[6]='|';
	vector_mensaje[7]='|';

////envio del pitch
//	if(angulos[1]<0)			//roll_serie lo ponemos entre -9000 y +9000. Por ejemplo -857 (-85,7°)
//	{
//		vector_mensaje[8]=45;			//primero mando el signo si es negativo
//		aux_serie2=pitch_serie*-1;		//aux=857
//	}
//	else
//	{
		vector_mensaje[8]=' ';
		aux_serie2=pitch_serie;			//aux=857
//	}




	dummy=(aux_serie2/100)+48;			//dummy=8+48 (el 48 es para pasarlo a ascii)
	vector_mensaje[9]=dummy;
	aux_serie2%=100;					//aux=57
	dummy=(aux_serie2/10)+48;			//dummy=5+48
	vector_mensaje[10]=dummy;
	vector_mensaje[11]=',';				//envio la coma
	aux_serie2%=10;					//aux=7;
	vector_mensaje[12]=(aux_serie2+48);

	vector_mensaje[13]='|';
	vector_mensaje[14]='|';




//envio del yaw
	if(angulos[2]<0)			//roll_serie lo ponemos entre -18000 y +18000. Por ejemplo -165,7° (-1657°)
	{
		vector_mensaje[15]=45;			//mando el signo si es negativo
		aux_serie2=yaw_serie*-1;		//aux=1657
	}
	else
	{
		vector_mensaje[15]=' ';
		aux_serie2=yaw_serie;			//aux=1657
	}

	dummy=(aux_serie2/1000)+48;		//dummy=1+48(para pasar a ascii)
	vector_mensaje[16]=dummy;
	aux_serie2%=1000;					//aux=657
	dummy=(aux_serie2/100)+48;			//dummy=6+48
	vector_mensaje[17]=dummy;
	aux_serie2%=100;					//aux=57;
	dummy=(aux_serie2/10)+48;			//dummy=5
	vector_mensaje[18]=dummy;
	vector_mensaje[19]=',';				//envio la coma
	aux_serie2%=10;					//aux=7
	vector_mensaje[20]=(aux_serie2+48);

	Enviar_Parametros("AT+CIPSEND=");
	PushTx(numero_id+48);
	PushTx(',');
	PushTx(2+48);			//envio 22 caracteres para enviar el vector (MANDALO EN CUOTAS QUE SINO SE PIERDE EL MENSAJE)
	PushTx(1+48);			//envio 22 caracteres para enviar el vector
	PushTx(0x0D);
	PushTx(0x0A);
	while(flag_okey!=1);
	flag_okey=0;
	delay=1;				//hago un delay para establecer al esp8266
	while(delay);

	for(k=0;k<12;k++)
		PushTx(vector_mensaje[k]);

	for(k=0;k<65000;k++);

	for(k=12;k<21;k++)
		PushTx(vector_mensaje[k]);

	PushTx(0x0D);
	PushTx(0x0A);
	delay=1;				//hago un delay para establecer al esp8266
	while(delay);

}

void Enviar_Parametros(char* dato){

	uint8_t i;

	for(i=0;dato[i]!='\0';i++){
		PushTx(dato[i]);
	}

}

uint8_t debugger[25];

void guardar_dato(uint8_t dato)
{
	buffer[IndiceRxIn]=dato;			//guardo el dato en un buffer
	IndiceRxIn++;
	IndiceRxIn%=TOPE_MAX;				//esto se hace para que el buffer sea ciclico

	switch(estado_lectura)
	{
	case ESPERA:
		if(dato=='r')
			estado_lectura=READY_1;
		if(dato=='O')
			estado_lectura=OKEY_1;
		if(dato=='E')
			estado_lectura=ERROR_1;
		if(dato=='+')
			estado_lectura=MSG_1;
		break;

	case READY_1:
		if(dato!='e')
			estado_lectura=ESPERA;
		if(dato=='e')
			estado_lectura=READY_2;
		if(dato=='r')
			estado_lectura=READY_1;
		break;

	case READY_2:
		if(dato!='a')
			estado_lectura=ESPERA;
		if(dato=='a')
		{
			estado_lectura=READY_3;
			contador_mensaje=2;
		}
		break;

	case READY_3:
		contador_mensaje--;
		if(!contador_mensaje)
		{
			for(k=0;k<TOPE_MAX;k++)
			{
				buffer[k]=0;
				IndiceRxIn=0;
			}
			estado_lectura=ESPERA;
			k=0;
		}
		break;

	case OKEY_1:
		if(dato=='K')
			flag_okey=1;
		estado_lectura=ESPERA;
		break;

	case ERROR_1:
		if(dato!='R')
			estado_lectura=ESPERA;
		if(dato=='R')
			estado_lectura=ERROR_2;
		if(dato=='E')
			estado_lectura=ERROR_1;
		break;

	case ERROR_2:
		if(dato!='R')
			estado_lectura=ESPERA;
		if(dato=='R')
		{
			estado_lectura=ERROR_3;
			contador_mensaje=2;
		}
		break;

	case ERROR_3:
		contador_mensaje--;
		if(!contador_mensaje)
		{
			estado_lectura=ESPERA;
			flag_error=1;
		}
		break;

	case MSG_1:
		if(dato!='I')
			estado_lectura=ESPERA;
		if(dato=='I')
			estado_lectura=MSG_2;
		if(dato=='+')
			estado_lectura=MSG_1;
		break;

	case MSG_2:
		if(dato!='P')
			estado_lectura=ESPERA;
		else
		{
			estado_lectura=MSG_3;
			contador_mensaje=6;
		}
		break;

	case MSG_3:
		data[6-contador_mensaje]=dato;
		contador_mensaje--;
		if(!contador_mensaje)
		{
			if(dato==':')
			{
				caracteres=contador_mensaje=(data[4]-48);
				estado_lectura=MSG_4A;
			}
			else
			{
				caracteres=(data[4]-48)*10+(data[5]-48);
				estado_lectura=MSG_4B;
			}

			numero_id=(data[2]-48);
		}
		break;

	case MSG_4A:
		if(contador_mensaje==1)
		{
			receptor[caracteres-contador_mensaje]=dato;
			flag_msg=1;
			estado_lectura=ESPERA;
			contador_mensaje=0;
		}
		else
		{
			receptor[caracteres-contador_mensaje]=dato;
			contador_mensaje--;
		}

		break;

	case MSG_4B:
		if(dato==':')
		{
			data[6]=dato;
			contador_mensaje=caracteres;
			estado_lectura=MSG_5;
		}
		else
		{
			contador_mensaje=0;
			estado_lectura=ESPERA;
		}
		break;

	case MSG_5:
		receptor[caracteres-contador_mensaje]=dato;
		contador_mensaje--;
		if(!contador_mensaje)
		{
			flag_msg=1;
			estado_lectura=ESPERA;
		}
		break;


	}


}







