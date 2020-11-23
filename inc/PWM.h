/*
 * PWM.h
 *
 *  Created on: 11 de nov. de 2017
 *      Author: Cristian
 */

#ifndef PWM_H_
#define PWM_H_

#include "aplicacion.h"

//registros del periferico PWM

	#define		PWM		( ( __RW uint32_t  * ) 0x40018000UL )

	#define		PWM1IR		PWM[0]
	#define		PWM1TCR		PWM[1]
	#define		PWM1TC		PWM[2]
	#define		PWM1PR		PWM[3]
	#define		PWM1PC		PWM[4]
	#define		PWM1MCR		PWM[5]
	#define 	PWM1M0		PWM[6]
	#define 	PWM1M1		PWM[7]
	#define 	PWM1M2		PWM[8]
	#define 	PWM1M3		PWM[9]
	#define 	PWM1CCR		PWM[10]
	#define 	PWM1CR0		PWM[11]
	#define 	PWM1CR1		PWM[12]
	#define 	PWM1CR2		PWM[13]
	#define 	PWM1CR3		PWM[14]
	#define 	PWM1M4		PWM[16]
	#define 	PWM1M5		PWM[17]
	#define 	PWM1M6		PWM[18]
	#define 	PWM1PCR		PWM[19]
	#define 	PWM1LER		PWM[20]
	#define 	PWM1CTCR	PWM[21]

//GPIOs que controlaran la direccion de los motores

#define	INAT1	PORT2,1
#define INBT1	PORT2,2
#define INAT2	PORT2,6
#define INBT2	PORT2,5

//puertos que mandaran la señal PWM a los motores
#define	TRACK2	5			//PORT2,4
#define TRACK1	4			//PORT2,3
#define CORTE	PORT2,0

//funcion que inicializa los pines del motor y parte del PWM
void inicializar_pwm();
//funcion con la que manejaremos el PWM
void motores(uint8_t,uint16_t,uint16_t);

#endif /* PWM_H_ */
