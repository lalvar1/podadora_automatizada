/*
===============================================================================
 Name        : Plantilla.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include "aplicacion.h"

/*	Flash sectors to be used for image storage */
#define	IMG_START_SECTOR	0x00010000	/* Sector 16 */
#define	VECTOR				0x10007DD8	/* Sector 20 */

#define		SECTOR		( ( __RW uint32_t  * ) 0x00010000UL )
#define		SECTOR		( ( __RW uint32_t  * ) 0x00010000UL )



// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

uint8_t opq;

	InicializarKit();



    while(1)
    {

    	if (((estado_podadora==REALIZAR_SEC1)||(estado_podadora==REALIZAR_SEC2)||(estado_podadora==REALIZAR_SEC3))&&(estado_secuencia==EN_CURSO))
    	{
        	//if( (distancia1<10) || (distancia2<10)|| (distancia3<10) )
        	if( ((distancia1<20) && (distancia1>10)) || ((distancia2<20) && (distancia2>10))|| ((distancia3<20) && (distancia3>10)) )
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
    			PushTx(3+48);			//envio 9 caracteres para enviar AVANZANDO
    			PushTx(0x0D);
    			PushTx(0x0A);
    			for(opq=0;opq<5;opq++)
    			{
    				delay=1;
    				while(delay);
    			}
    			Enviar_Parametros("PRO");
        	}


			if(GetPIN(PORT2,7,0))				//SI RECIBO UN 0 del pin del microswitch, significa que se levanto el equipo
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
				PushTx(3+48);			//envio 9 caracteres para enviar AVANZANDO
				PushTx(0x0D);
				PushTx(0x0A);
				for(opq=0;opq<5;opq++)
				{
					delay=1;
					while(delay);
				}
				Enviar_Parametros("LEV");
			}

    	}

    	if(flag_msg)
    	{
			if(caracteres==1)
				analizar_mensaje();
			else
				analizar_mensaje2();
			flag_msg=0;
    	}

    	podadora();			//función que repite la secuencia



    	if( (estado_pid==CALCULANDO) && ( (estado_direccion==AVANZANDO) || (estado_direccion==RETROCEDIENDO) ) )
    	{
    		controlador_PID();
    		estado_pid=ESPERANDO;


    	}
    }




}
