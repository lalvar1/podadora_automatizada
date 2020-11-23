/*
 * I2C.c
 */

#include "Aplicacion.h"


void INIC_I2C1(void)
{

	IPR2 |= (0x1<<19);				//le pongo prioridad 1 al I2C0


	PCONP |= (1 << 7); 						// Habilitar I2C0 que esta en el bit 7 del registro PCONP
	PCLKSEL0 &=~(11<< 14);
	SetPINSEL(PORT0,27,PINSEL_FUNC1);		//la funcion 10 es la correspondiente al SDA0
	SetPINSEL(PORT0,28,PINSEL_FUNC1);		//la funcion 10 es la correspondiente al SCL0
	SetPINMODE(PORT0,27,PINMODE_NONE);		//los pines no deben ser ni pull up ni pull down (pagina 428)
	SetPINMODE(PORT0,28,PINMODE_NONE);
	SetMODE_OD(PORT0,27,OPEN_DRAIN);		//deben ser open drain (pagina 428)
	SetMODE_OD(PORT0,28,OPEN_DRAIN);
	ISER0 |= 0x01<<10;						//habilito interrupcion del NVIC del I2C0

	//idem I2C0
	I2C0SCLH=0x7D;
	I2C0SCLL=0x7D;
	I2C0ONSET=0x40;

	//seteo las constantes que se tienen en la podadora
	prom_gx=SECTOR10[0];
	prom_gy=SECTOR10[1];
	prom_gz=SECTOR10[2];
	prom_ax=SECTOR10[3];
	prom_ay=SECTOR10[4];
	prom_az=SECTOR10[5];
	xsf=SECTOR10[6];
	ysf=SECTOR10[7];
	xoff=SECTOR10[8];
	yoff=SECTOR10[9];

	estado_imu=INICIANDO_MAGNETO;			//lo cambie por la imu para probar

	estado_medicion=MIDIENDO;				//LO PASE DE CALIBRANDO_MPU a MIDIENDO

	ARRANCAR_I2C0;

	//en este momento el systick se va a dar cuenta de que estado_imu esta en acelerometro y empieza a arrancar el i2c

	angulos[0]=angulos[1]=0;


}


