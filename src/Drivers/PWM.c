/*
 * PWM.c
 */

#include "aplicacion.h"

#define DUTY_MAX 100

void inicializar_pwm()
{
    PCONP|=(1<<6);         		//Habilito el PWM1 en el control de consumo de los periféricos
    //el clock del periferico esta en 25 MHz (PCLKSEL0 tiene 00 en los bits 12 y 13)

    //la frecuencia PWM será	f= Frecuancia_periferico/(Preescaler*1000)
    //como f_periferico=25 MHz y f_pwm no debe superar los 20 KHz el preescaler deberá ser mayor o igual a 13

    PWM1PR=0xD;

    //SetPINSEL(INAC,PINSEL_GPIO);
    SetPINSEL(INAT1,PINSEL_GPIO);
    SetPINSEL(INAT2,PINSEL_GPIO);
    SetPINSEL(INBT1,PINSEL_GPIO);
    SetPINSEL(INBT2,PINSEL_GPIO);

    SetDIR(INAT1,SALIDA);
    SetDIR(INAT2,SALIDA);
    SetDIR(INBT1,SALIDA);
    SetDIR(INBT2,SALIDA);

    SetDIR(PORT0,22,SALIDA);
    SetPIN(PORT0,22,1);

    SetPINSEL(PORT2,7,PINSEL_GPIO);			//POR EL P2.7 SE LE AVISARA AL MICRO QUE HUBO LEVANTAMIENTO
    SetDIR(PORT2,7,ENTRADA);

    //TRACK1 se usa con el P2.4. el cual usa el canal 5
    PINSEL4&=~((3<<8));				//limpio la parte del registro que quiero atacar
    PINSEL4|=(1<<8);            	//le elijo la opcion 01 (PWM1.5) al P2.4
    PINMODE4&=~((3<<8));    		//pongo al P2.4 como Pull-up

    //Idem TRACK2. usa el P2.3, el cual usa el canal 4
    PINSEL4&=~((3<<6));
    PINSEL4|=(1<<6);
    PINMODE4&=~((3<<6));


    //El corte se controla por el P2.0

    SetPINSEL(CORTE,PINSEL_GPIO);
    SetDIR(CORTE,SALIDA);
    SetPIN(CORTE,ROFF);


}



void motores(uint8_t comando,uint16_t dizq,uint16_t dder)
{
	switch(comando)
	{
		case AVANZAR:

			if((flag_control==STOP)&&(caracteres==1))
				set_point=angulos[2];				//tomo el setpoint para realizar el control

//			if(flag_control==STOP)
			if((flag_control==STOP)&&(estado_direccion!=AVANZANDO))
			{
				vector_pid[i_angulos]=set_point=angulos[2];
				estado_direccion=AVANZANDO;
			}

			flag_control=ARRANCAR_ADELANTE;

			//SI INA esta en 1 y INB esta en 0, las ruedas giran horariamente
			SetPIN(INAT1,ROFF);
			SetPIN(INAT2,ROFF);
			SetPIN(INBT1,RON);
			SetPIN(INBT2,RON);

			PWM1M4=DUTY_MAX-dder;
			PWM1M5=DUTY_MAX-dizq;

		    PWM1M0=DUTY_MAX;    // Máximo valor del duty -> 100%
		    PWM1LER=(1<<4)|(1<<5)|(1<<0);

		    PWM1MCR|=(1<<1);    //Reseteo el contador cuando llega MR0

		    PWM1CTCR=0;    //Funciona por matcheo , no por captura.
		    PWM1TCR=(1<<3)|(1<<0);    //Habilito la cuenta y el modo PWM

		    PWM1PCR&=~(0x3<<4);    //Deshabilito el flanco doble en el canal seleccionado
		    PWM1PCR|=(0x3<<(8+4));    //Habilito salida PWM por flanco simple
	    	break;

		case RETROCEDER:

			if((flag_control==STOP)&&(caracteres==1))
				set_point=angulos[2];				//tomo el setpoint para realizar el control

//			if(flag_control==STOP)
			if((flag_control==STOP)&&(estado_direccion!=RETROCEDIENDO))
			{
				vector_pid[i_angulos]=set_point=angulos[2];
				estado_direccion=RETROCEDIENDO;
			}

			flag_control=ARRANCAR_ATRAS;


			//SI INA esta en 0 y INB esta en 1, las ruedas giran anti-horariamente
			SetPIN(INAT1,RON);
			SetPIN(INAT2,RON);
			SetPIN(INBT1,ROFF);
			SetPIN(INBT2,ROFF);

			PWM1M4=DUTY_MAX-dder;
			PWM1M5=DUTY_MAX-dizq;

			PWM1M0=DUTY_MAX;    // Máximo valor del duty -> 100%
		    PWM1LER=(1<<4)|(1<<5)|(1<<0);

		    PWM1MCR|=(1<<1);    //Reseteo el contador cuando llega MR0

		    PWM1CTCR=0;    //Funciona por matcheo , no por captura.
		    PWM1TCR=(1<<3)|(1<<0);    //Habilito la cuenta y el modo PWM

		    PWM1PCR&=~(0x3<<4);    //Deshabilito el flanco doble en el canal seleccionado
		    PWM1PCR|=(0x3<<(8+4));    //Habilito salida PWM por flanco simple
	    	break;

		case PARAR:

			flag_control=STOP;

			//SI INA esta en 0 y INB esta en 0, las ruedas frenan
			SetPIN(INAT1,ROFF);
			SetPIN(INAT2,ROFF);
			SetPIN(INBT1,ROFF);
			SetPIN(INBT2,ROFF);

			PWM1M4=PWM1M5=DUTY_MAX;

			PWM1M0=DUTY_MAX;    // Máximo valor del duty -> 100%
		    PWM1LER=(1<<4)|(1<<5)|(1<<0);

		    PWM1MCR|=(1<<1);    //Reseteo el contador cuando llega MR0

		    PWM1CTCR=0;    //Funciona por matcheo , no por captura.
		    PWM1TCR=(1<<3)|(1<<0);    //Habilito la cuenta y el modo PWM

		    PWM1PCR&=~(0x3<<4);    //Deshabilito el flanco doble en el canal seleccionado
		    PWM1PCR|=(0x3<<(8+4));    //Habilito salida PWM por flanco simple
	    	break;

		case IZQUIERDA:
			flag_control=STOP;

			//SI INA esta en 1 y INB esta en 0, las ruedas giran horariamente
			SetPIN(INAT1,RON);
			SetPIN(INAT2,ROFF);
			SetPIN(INBT1,ROFF);
			SetPIN(INBT2,RON);

			PWM1M4=DUTY_MAX-47;
			PWM1M5=DUTY_MAX-37;

			PWM1M0=DUTY_MAX;    // Máximo valor del duty -> 100%
		    PWM1LER=(1<<4)|(1<<5)|(1<<0);

		    PWM1MCR|=(1<<1);    //Reseteo el contador cuando llega MR0

		    PWM1CTCR=0;    //Funciona por matcheo , no por captura.
		    PWM1TCR=(1<<3)|(1<<0);    //Habilito la cuenta y el modo PWM

		    PWM1PCR&=~(0x3<<4);    //Deshabilito el flanco doble en el canal seleccionado
		    PWM1PCR|=(0x3<<(8+4));    //Habilito salida PWM por flanco simple
	    	break;

		case DERECHA:
			flag_control=STOP;

			//SI INA esta en 1 y INB esta en 0, las ruedas giran horariamente
			SetPIN(INAT1,ROFF);
			SetPIN(INAT2,RON);
			SetPIN(INBT1,RON);
			SetPIN(INBT2,ROFF);


			PWM1M4=DUTY_MAX-37;
			PWM1M5=DUTY_MAX-47;

			PWM1M0=DUTY_MAX;    // Máximo valor del duty -> 100%
		    PWM1LER=(1<<4)|(1<<5)|(1<<0);

		    PWM1MCR|=(1<<1);    //Reseteo el contador cuando llega MR0

		    PWM1CTCR=0;    //Funciona por matcheo , no por captura.
		    PWM1TCR=(1<<3)|(1<<0);    //Habilito la cuenta y el modo PWM

		    PWM1PCR&=~(0x3<<4);    //Deshabilito el flanco doble en el canal seleccionado
		    PWM1PCR|=(0x3<<(8+4));    //Habilito salida PWM por flanco simple
	    	break;


	}
}

