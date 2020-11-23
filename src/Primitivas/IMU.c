/*
 * IMU.c
 *
 *  Created on: 27 de sept. de 2017
 *      Author: Cristian
 */

#include "Aplicacion.h"
#include <math.h>



volatile uint16_t j=0;


void calcular_angulosxy(){


		float auxiliar;
		uint8_t n=0;

		mediciones[0]-=prom_ax;		//resto los offset
		mediciones[1]-=prom_ay;
		//mediciones[2]-=prom_az;
		mediciones[3]-=prom_gx;
		mediciones[4]-=prom_gy;
		mediciones[5]-=prom_gz;

		gx=mediciones[3]/G_R;		//convierto al rango de las mediciones, dividiendo la muestra por el factor de escala
		gy=mediciones[4]/G_R;
		gz=mediciones[5]/G_R;

		ax=mediciones[0]/A_R;
		ay=mediciones[1]/A_R;
		az=mediciones[2]/A_R;

		hx=mediciones[6];
		hy=mediciones[7];
		hz=mediciones[8];

		//calculo del angulo usando los valores del acelerometro
		ang_acce[0]=atan2(ay,sqrt(pow((ax),2) + pow((az),2)))*RAD_TO_DEG;


		//ang_acce[0]=atan2((ay),sqrt(pow((ax),2) + pow((az),2)))*RAD_TO_DEG;
		ang_acce[1]=atan(-1*(ax/A_R)/sqrt(pow((ay/A_R),2) + pow((az/A_R),2)))*RAD_TO_DEG;


		//fusion de las medidas del acelerometro y el giroscopio mediante filtro complementario
		angulos[0]=0.98*(angulos[0]+gx*0.015)+0.02*ang_acce[0];
		angulos[1]=0.98*(angulos[1]+gy*0.015)+0.02*ang_acce[1];

		roll_serie=duty_der*10;
		pitch_serie=duty_izq*10;


		if((xsf!=0)&&(ysf!=0))			//si son distintos de 0 es porque ya hubo una calibraciòn previa
		{
			//compensacion de inclinacion

			//Xh= X*cos(pitch)+Y*sin(pitch)*sin(roll)-Z*cos(roll)*sin(pitch)
			auxiliar=0;
			auxiliar=mediciones[6]*cos(angulos[1]*PI/180);
			auxiliar+=mediciones[7]*sin(angulos[0]*PI/180)*sin(angulos[1]*PI/180);
			auxiliar-=mediciones[8]*cos(angulos[0]*PI/180)*sin(angulos[1]*PI/180);
			hx=auxiliar;		//guardo las mediciones

			//Yh= Y*cos(roll)+Z*sin(roll)
			auxiliar=0;
			auxiliar=mediciones[7]*cos(angulos[0]*PI/180);
			auxiliar+=mediciones[8]*sin(angulos[0]*PI/180);
			hy=auxiliar;

			//Compenacion por efectos Magnéticos
			hx=hx*xsf+xoff;
			hy=hy*ysf+yoff;

			//calculo del yaw

			ang_acce[2]=atan2(hy,hx)*RAD_TO_DEG;

			//filtro complementario

			angulos[2]=0.98*(angulos[2]+gz*0.015)+0.02*ang_acce[2];
			yaw_serie=angulos[2]*10;
		}

}


signed short make_word(uint8_t high,uint8_t low)
{
	uint16_t aux_data;
	signed short aux2;
	aux_data= (high<<8|low);

	aux2= (signed short)aux_data;
	return aux2;
}


signed short buscar_max(signed short vector[])
{
	signed short max=0;
	uint16_t i=0;

	for(i=0;i<1500;i++)
	{
		if(vector[i]>max)
			max=vector[i];
	}

	return max;
}

signed short buscar_min(signed short vector[])
{
	signed short min=0;
	uint16_t i=0;

	for(i=0;i<1500;i++)
	{
		if(vector[i]<min)
			min=vector[i];
	}

	return min;
}

