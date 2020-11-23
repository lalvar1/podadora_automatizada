/*
 * FW_IMU.c
 */

#include "aplicacion.h"
#include <math.h>



volatile uint8_t counter=0,hb,lb;
volatile uint16_t count=0;
volatile float aux_calib=0;


void I2C0_IRQHandler(void) {

	switch(I2C0STAT){

        case 0x08:
        	if((estado_imu==INICIANDO_MAGNETO)||(estado_imu==MAGNETOMETRO))
        		I2C0DAT=0x3C;
        	else
        		I2C0DAT=0xD0;

        	I2C0ONCLR=0x18;				//STO=SI=0;		AA=STA=X;
        	break;


        case 0x20:
			I2C0ONSET=0x30;			//STO=STA=1	   mando un STOP seguido de un START para pasar a medir el giroscopio
			I2C0ONCLR=0x08;			//SI=0			//STO=SI=0;		AA=STA=X;
        		break;

        case 0x10:
        	if((estado_imu==INICIANDO_MAGNETO)||(estado_imu==MAGNETOMETRO))
        		I2C0DAT=0x3D;
        	else
        		I2C0DAT=0xD1;

        	I2C0ONCLR=0x18;				//STO=SI=0;		AA=STA=X;
            break;

        case 0x18:
         	if(estado_imu==INICIANDO_MAGNETO)
         		I2C0DAT=0x00;			//cargo direccion del registro de configuracion del hmc5883
         	if(estado_imu==INICIANDO_MPU)
         		I2C0DAT=0x6B;			//cargo direccion del registro de configuracion del mpu
         	if(estado_imu==ACELEROMETRO)
         		I2C0DAT=0x3B;			//cargo primer direccion de los registros de aceleracion
         	if(estado_imu==GYROSCOPIO)
         		I2C0DAT=0x43;			//cargo primer direccion de los registros de giroscopio
         	if(estado_imu==MAGNETOMETRO)
           		I2C0DAT=0x03;			//cargo primer direccion de los registros del magnetometro

         	I2C0ONCLR=0x38;			//STO=STA=SI=0		AA=X

        	break;

        case 0x28:
            if(estado_imu==INICIANDO_MAGNETO)
            {
              switch(counter)
              {
              case 0:
              	I2C0DAT=0x78;			//Registro A: 8 muestras promediadas, 75Hz de DOR y medicion normal
              	I2C0ONCLR=0x38;			//STO=STA=SI=0		AA=X
              	counter++;
              	break;

              case 1:
              	I2C0DAT=0x20;			//Registro B: Rango de +-1.3Ga y ganancia de 1090 LSB/Ga. Resolucion de 0.92mGa/LSB
              	I2C0ONCLR=0x38;			//STO=STA=SI=0		AA=X
              	counter++;
              	break;

              case 2:
              	I2C0DAT=0x00;			//Registro MODE: medicion continua
              	I2C0ONCLR=0x38;
              	counter++;
              	break;

              case 3:
              	I2C0ONSET=0x30;			//STO=STA=1		//mando un STOP seguido de un START para iniciar la IMU
              	I2C0ONCLR=0x08;			//SI=0
              	counter=0;
              	estado_imu=INICIANDO_MPU;
              	break;
              }
            break;
            }

            if(estado_imu==INICIANDO_MPU)
            {
            	if(!counter)
              	{
              	I2C0DAT=0x00;			//escribo un 0 en el registro de control para prender el sensor (espero)
              	I2C0ONCLR=0x38;			//STO=STA=SI=0		AA=X
              	counter++;
              	}
              	else
              	{
              	I2C0ONSET=0x10;			//STO=1;  //termino la inicializacion
              	I2C0ONCLR=0x28;			//STA=SI=0;
              	counter=0;
              	estado_imu=ACELEROMETRO;
              	break;
              	}
            }

            if((estado_imu==ACELEROMETRO)||(estado_imu==GYROSCOPIO)||(estado_imu==MAGNETOMETRO))
            {
            	I2C0ONSET=0x20;		//STA=1
              	I2C0ONCLR=0x18;		//STO=SI=0  y AA=X
            }

          	break;


        case 0x40 :
        	I2C0ONCLR=0x38;		//STA=STO=SI=0
            I2C0ONSET=0x04;		//AA=1
            break;

        case 0x50:
         	switch(counter)
         	{
         		case 0:
         			hb=I2C0DAT;
         			counter++;
         			I2C0ONCLR=0x38;			//STA=STO=SI=0
         			I2C0ONSET=0x04;			//AA=1
         			break;

         		case 1:
         			lb=I2C0DAT;
         			if(estado_imu==ACELEROMETRO)
         				mediciones[0]=make_word(hb,lb);				//guardo acele_x
         			if(estado_imu==GYROSCOPIO)
         				mediciones[3]=make_word(hb,lb);				//guardo gyro_x
         			if(estado_imu==MAGNETOMETRO)
         				mediciones[6]=make_word(hb,lb);				//guardo magne_x

         			counter++;
        			I2C0ONCLR=0x38;			//STA=STO=SI=0
        			I2C0ONSET=0x04;			//AA=1
        			break;

         		case 2:
         			hb=I2C0DAT;
         			counter++;
         			I2C0ONCLR=0x38;			//STA=STO=SI=0
         			I2C0ONSET=0x04;			//AA=1
         			break;
         		case 3:
         			lb=I2C0DAT;
         			if(estado_imu==ACELEROMETRO)
         				mediciones[1]=make_word(hb,lb);				//guardo acele_y
         			if(estado_imu==GYROSCOPIO)
         				mediciones[4]=make_word(hb,lb);				//guardo gyro_y
         			if(estado_imu==MAGNETOMETRO)
         				mediciones[8]=make_word(hb,lb);				//guardo magne_z

         			counter++;
         			I2C0ONCLR=0x38;			//STA=STO=SI=0
         			I2C0ONSET=0x04;			//AA=1
         			break;
 				case 4:
 					hb=I2C0DAT;
 					counter=0;
 					I2C0ONCLR=0x3C;			//STA=STO=SI=AA=0
 					break;
         	}
         	break;

            case 0x58:
             	lb=I2C0DAT;
     			if(estado_imu==ACELEROMETRO)
     				mediciones[2]=make_word(hb,lb);				//guardo acele_z
     			if(estado_imu==GYROSCOPIO)
     				mediciones[5]=make_word(hb,lb);				//guardo gyro_z
     			if(estado_imu==MAGNETOMETRO)
     				mediciones[7]=make_word(hb,lb);				//guardo magne_y


     			switch(estado_medicion)
     			{
     				case CALIBRANDO_MPU:
     					if(estado_imu==ACELEROMETRO)
     					{
							estado_imu=GYROSCOPIO;
							I2C0ONSET=0x30;			//STO=STA=1	   mando un STOP seguido de un START para pasar a medir el giroscopio
							I2C0ONCLR=0x08;			//SI=0
						}
						else
						{
							estado_imu=ACELEROMETRO;
							prom_gx+=mediciones[3];
							prom_gy+=mediciones[4];
							prom_gz+=mediciones[5];
							prom_ax+=mediciones[0];
							prom_ay+=mediciones[1];
							prom_az+=mediciones[2];
							count++;

							if(count==3000)					//cuando tengo el numero de muestras que quiero divido para tener el offset
							{
							   prom_gx/=count;
							   prom_gy/=count;
							   prom_gz/=count;
							   prom_ax/=count;
							   prom_ay/=count;
							   prom_az/=count;
							   prom_az-=A_R;
							   count=0;
							   estado_medicion=MIDIENDO;				//paso a calibrar el magnetometro
							}

							I2C0ONSET=0x10;			//STO=0;
							I2C0ONCLR=0x28;			//STA=SI=0;
						}
     					break;

     				case MIDIENDO:
     					if(estado_imu==ACELEROMETRO)
     					{
     						estado_imu=GYROSCOPIO;
     						I2C0ONSET=0x30;			//STO=STA=1	   mando un STOP seguido de un START para pasar a medir el giroscopio
     						I2C0ONCLR=0x08;			//SI=0
     					}
						else
						{
							if(estado_imu==GYROSCOPIO)
							{
								estado_imu=MAGNETOMETRO;
	     						I2C0ONSET=0x30;			//STO=STA=1	   mando un STOP seguido de un START para pasar a medir el giroscopio
	     						I2C0ONCLR=0x08;			//SI=
							}
							else
							{
								estado_imu=ACELEROMETRO;
								calcular_angulosxy();
								I2C0ONSET=0x10;			//STO=0;
								I2C0ONCLR=0x28;			//STA=SI=0;
							}

						}
     					break;

     				case CALIBRANDO_MAGNETO:
     					if(estado_imu==ACELEROMETRO)
     					{
     						estado_imu=GYROSCOPIO;
     					    I2C0ONSET=0x30;			//STO=STA=1	   mando un STOP seguido de un START para pasar a medir el giroscopio
     					    I2C0ONCLR=0x08;			//SI=0
     					}
     					else
     					{
     						if(estado_imu==GYROSCOPIO)
     						{
     							estado_imu=MAGNETOMETRO;
     						    I2C0ONSET=0x30;			//STO=STA=1	   mando un STOP seguido de un START para pasar a medir el magnetometro
     						    I2C0ONCLR=0x08;			//SI=
     						}
     						else
     						{
     							estado_imu=ACELEROMETRO;

//     							vector[contador_calib]=mediciones[6];
//     							vector[128+contador_calib]=mediciones[7];
//     							contador_calib++;

     							calcular_angulosxy();				//saco el roll (ang[0]) y el pitch (ang[1])

     							//Xh= X*cos(pitch)+Y*sin(pitch)*sin(roll)-Z*cos(roll)*sin(pitch)

     							aux_calib=0;
     							aux_calib=mediciones[6]*cos(angulos[1]*PI/180);
     							aux_calib+=mediciones[7]*sin(angulos[0]*PI/180)*sin(angulos[1]*PI/180);
     							aux_calib-=mediciones[8]*cos(angulos[0]*PI/180)*sin(angulos[1]*PI/180);
     							vector[contador_calib]=aux_calib;		//guardo las mediciones

     							//Yh= Y*cos(roll)+Z*sin(roll)
     							aux_calib=0;
     							aux_calib=mediciones[7]*cos(angulos[0]*PI/180);
     							aux_calib+=mediciones[8]*sin(angulos[0]*PI/180);

     							vector[128+contador_calib]=aux_calib;
     							contador_calib++;

     							if(contador_calib==127)
     							{

         							hxmax=hxmin=vector[0];
         							hymax=hymin=vector[128];
         							ysf=xsf=xoff=yoff=0;

     								for(contador_calib=0;contador_calib<127;contador_calib++)
     								{
     									if(vector[contador_calib]>hxmax)
     										hxmax=vector[contador_calib];

     									if(vector[contador_calib]<hxmin)
     										hxmin=vector[contador_calib];
     								}

     								for(contador_calib=128;contador_calib<255;contador_calib++)
     								{
     									if(vector[contador_calib]>hymax)
     										hymax=vector[contador_calib];

     									if(vector[contador_calib]<hymin)
     										hymin=vector[contador_calib];
     								}

     								aux_calib=(hxmax-hxmin)/(hymax-hymin);

     								if(aux_calib>1)
     									ysf=aux_calib;
     								else
     									ysf=1;

     								aux_calib=(hymax-hymin)/(hxmax-hxmin);

     								if(aux_calib>1)
     									xsf=aux_calib;
     								else
     									xsf=1;

     								xoff=(((hxmax-hxmin)/2)-hxmax)*xsf;
     								yoff=(((hymax-hymin)/2)-hymax)*ysf;

     								contador_calib=0;
     								grabar=1;
     								estado_medicion=MIDIENDO;
     							}

     							I2C0ONSET=0x10;			//STO=0;
     							I2C0ONCLR=0x28;			//STA=SI=0;
     						}

     					}
     					break;

     			}
     		    break;
	}
}





