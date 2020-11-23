/*
 * I2C.h
 *
 *  Created on: 27 de sept. de 2017
 *      Author: Cristian
 */

#ifndef I2C_H_
#define I2C_H_

#include "aplicacion.h"

#define 	I2C0		( ( __RW uint32_t  * ) 0x4001C000UL )
#define		I2C1		( ( __RW uint32_t  * ) 0x4005C000UL )


#define I2C0ONSET		I2C0[0]
#define I2C0STAT   		I2C0[1]				 // bits 3 al 7 indican el estado actual de la interfaz. los demas estan reservados
#define I2C0DAT			I2C0[2]				 // solo los primeros 8 bits, contiene el dato actual que se enviara o que llega
#define I2C0SCLH		I2C0[4]	 			 // maxima frecuencia de trabajo (bit 0 al 15)	(CREO)
#define I2C0SCLL		I2C0[5]				 //minima frecuencia de trabajo (bit 0 al 15)	(CREO)
#define I2C0ONCLR		I2C0[6]


#define I2CONSET		I2C1[0]
#define I2C1STAT   		I2C1[1]				 // bits 3 al 7 indican el estado actual de la interfaz. los demas estan reservados
#define I2C1DAT			I2C1[2]				 // solo los primeros 8 bits, contiene el dato actual que se enviara o que llega
#define I2C1SCLH		I2C1[4]	 			// maxima frecuencia de trabajo (bit 0 al 15)	(CREO)
#define I2C1SCLL		I2C1[5]				 //minima frecuencia de trabajo (bit 0 al 15)	(CREO)
#define I2CONCLR		I2C1[6]


#define ULTRA_LOW_POWER			0
#define STANDARD				1
#define HIGH_RESOLUTION			2
#define ULTRA_HIGH_RESOLUTION	3

//estados de estado_imu

#define INICIANDO_MAGNETO	0
#define INICIANDO_MPU		1
#define ACELEROMETRO 		2
#define GYROSCOPIO 			3
#define MAGNETOMETRO 		4

#define REPOSO				0
#define CALIBRANDO_MPU		1
#define CALIBRANDO_MAGNETO 	2
#define MIDIENDO			3

//Ratios de conversion especificados por la IMU	 (factor de escala)
#define A_R 16384.0		//antes estaba el 16384 solo
#define G_R 131			//antes era 131
#define M_R 1090.0

#define RAD_TO_DEG 57.295779
#define DEG_TO_RAD 0.0174444

//prototipos de funciones

void INIC_I2C1(void);


//funciones de la IMU
void calcular_angulosxy();
signed short make_word(uint8_t,uint8_t);
signed short buscar_max(signed short vector[]);
signed short buscar_min(signed short vector[]);



#endif /* I2C_H_ */
