/*
 * Aplicacion.h
 *
 *  Created on: 27 de sept. de 2017
 *      Author: Cristian
 */

#ifndef APLICACION_H_
#define APLICACION_H_


	#include "GPIO.h"
	#include "BaseBoard.h"
	#include "RegLPC1769.h"
	#include "I2C.h"
	#include "UART.h"
	#include "iap.h"
	#include "PWM.h"
	#include "Timers.h"


	void InicSysTick(void);
	void InicPLL ( void );
	void cuentoPulsos (void);
	void InicializarKit ( void );
	void inicializar_wifi();




#define ARRANCAR_I2C	I2CONSET=0x60
#define ARRANCAR_I2C0	I2C0ONSET=0x60

											//variables a usar durante el programa

volatile uint8_t delay;						//bandera para hacer un delay y poder dejar un espacio de 100ms entre comandos AT para inicializar el modulo wifi


uint8_t estado_imu, estado_medicion;		//guardan el estado de la maquina de estados de la medicion de los sensores
signed short mediciones[9];					//van a guardar los valores que entregan los sensores de la siguiente forma
											//[ax,ay,az,gx,gy,gz,mx,my,mz]

volatile float prom_gx,prom_gy,prom_gz,prom_ax,prom_ay,prom_az;		//van a guardar los offset del giroscopio y del acelerometro
				//LO CAMBIE DE LONG A FLOAT

float ax,ay,az,gx,gy,gz,hx,hy,hz;								//variables con las cuales voy a trabajar para calcular los angulos
float angulos[3];												//variables que guardaran los angulos actuales de los 3 ejes
float ang_acce[3];												//vector que tiene el calculo del angulo usando la aceleracion solamente

signed short roll_serie,pitch_serie,yaw_serie;

signed short muestra_mx[1500],muestra_my[1500];

volatile uint32_t iser;											//para guardar que interrupciones estan habilitadas



volatile signed short vector[256];								//vector donde se guardan las mediciones de hx y hy
volatile uint8_t grabar;										//variable que uso para indicar que ya llene el vector de mediciones de hx y hy


volatile uint8_t flag_med;


float set_point;    				//antes de arrancar rutina de control, tomo el setpoint del yaw como mi referencia
uint8_t flag_control;
volatile float kp,ki,kd;    				 //subir si reacciona muy lento el robot, no tanto porque es probable que se vuelva inestable si no(recordar el rlocus cuack)
volatile signed short PID;
volatile float duty_der,duty_izq;


#define ARRANCAR_ADELANTE	1
#define ARRANCAR_ATRAS		2
#define STOP				0

#define NONE		0
#define PRIMARIA	1
#define SECUNDARIA	2


#define TOPE_MAX	250				//numero maximo del buffer de recepion a usar
uint8_t IndiceRxIn;					//variable que me sirve para moverme por el buffer ciclico y guardar los datos
uint8_t buffer[TOPE_MAX];			//buffer ciclico donde se guardara lo que se reciba del esp8266
uint8_t mensaje;					//buffer donde guardare los mensajes que vengan de la app


#define PARAR		0
#define AVANZAR		1
#define RETROCEDER  2
//#define IZQUIERDA	3
//#define DERECHA		4

#define RON 0
#define ROFF 1

uint8_t cont_adc,flag_adc;						//contador del adc que uso para tomar 20 muestras y hacer el filtro de mediana
uint16_t vector_adc[20],aux_adc;				//vector adc guarda las muestras y resultado adc contiene el resultado final
uint32_t resultadoADC;
void InicADC();


volatile uint16_t contador_calib;
volatile float xsf,ysf,xoff,yoff,hxmax,hymax,hxmin,hymin;
#define PI 3.14159265

void analizar_mensaje(void);				//este funciona para le app de debug
void analizar_mensaje2(void);				//este serie el que funcione en la app real


/*	Flash sectors to be used for image storage */
#define	IMG_START_SECTOR	0x00010000	/* Sector 16 */
#define	VECTOR				0x10007DD8	/* Sector 20 */

#define		SECTOR		( ( __RW uint32_t  * ) 0x00010000UL )
#define		SECTOR		( ( __RW uint32_t  * ) 0x00010000UL )


volatile uint8_t tomar_muestras;
volatile float medicion_actual,muestras_yaw[12];



volatile float distancia1,distancia2,distancia3;			//las mediciones de los 3 sensores ultrasonicos se guardan aca


//definición de los sectores donde guardare la información de las secuencias

#define		SECTOR1		( ( __RW uint8_t  * ) 0x00010000UL )			//en el sector 16 guardare la secuencia 1
#define		S1_DIR		( ( __RW uint8_t  * ) 0x00011000UL )			//en esta parte del sector 16 guardare las secuencias de direccion
#define		S1_COR		( ( __RW uint8_t  * ) 0x00014000UL )			//en esta parte del sector 16 guardare las secuencias de corte

#define		SECTOR2		( ( __RW uint8_t  * ) 0x00018000UL )			//en el sector 17 guardare la secuencia 2
#define		S2_DIR		( ( __RW uint8_t  * ) 0x00019000UL )			//en esta parte del sector 17 guardare las secuencias de direccion
#define		S2_COR		( ( __RW uint8_t  * ) 0x0001C000UL )			//en esta parte del sector 17 guardare las secuencias de corte

#define		SECTOR3		( ( __RW uint8_t  * ) 0x00020000UL )			//en el sector 18 guardare la secuencia 3
#define		S3_DIR		( ( __RW uint8_t  * ) 0x00021000UL )			//en esta parte del sector 18 guardare las secuencias de direccion
#define		S3_COR		( ( __RW uint8_t  * ) 0x00024000UL )			//en esta parte del sector 18 guardare las secuencias de corte

#define 	SECTOR19		( ( __RW uint8_t  * ) 0x00028000UL )		//en el sector 19 guardare info de usuario y contraseña

#define 	SECTOR10	( ( __RW float  * ) 0x0000A000UL )				//en el sector 10 guardare info de calibracion



#define 	SECTOR8		( ( __RW float  * ) 0x0000A000UL )

#define S1	16				//defino los ID de los sectores
#define S2	17
#define S3	18
#define S19	19
#define S10	10
#define S8	8

volatile char comilla;

uint8_t vector_memoria[256],vector_memoria2[256];		//vectores donde guardare los comandos que vengan

uint16_t ptr_vector_memoria,ptr_vector_memoria2;		//punteros con los cuales me movere por los vectores anteriores

volatile uint8_t estado_podadora;			//esta variable me dice que esta haciendo la podadora. sus opciones son la de abajo

#define ESPERANDO 			0
#define GRABAR_SEC1			1
#define GRABAR_SEC2			2
#define GRABAR_SEC3			3
#define REALIZAR_SEC1		4
#define REALIZAR_SEC2		5
#define REALIZAR_SEC3		6

volatile uint8_t estado_secuencia;			//esta variable me dicen en que estado esta la secuencia. Sus opciones son las de abajo

#define REPOSO		0
#define EN_CURSO	1
#define PAUSADA		2

volatile uint8_t estado_direccion;			//esta variable me dice en que estado estan los comandos de direccion. sus opciones son las de abajo

#define SIN_COMANDO		0
#define AVANZANDO		1
#define DETENIDO		2
#define RETROCEDIENDO	3
#define DERECHA 		4
#define IZQUIERDA		5

volatile uint8_t estado_corte;				//igual que el anterior pero para los comandos de corte. Puede estar en SIN_COMANDO, ON u OFF

volatile uint16_t evento_dir,evento_cor;	//variables que guardan el numero de eventos de los comandos

volatile uint8_t reg_dir,reg_cor;			//variable que guarda cuantos comandos tiene el vector de memoria

volatile uint8_t grabados_dir,grabados_cor;	//variable que guarda cuantas veces grabe en el sector

float vector_calib[11];			//vector que usare para guardar las constantes de calibracion en la memoria



uint16_t contador_eventos_dir,contador_eventos_cor;				//variables que usare para contar cuanto tiempo hare un comando de la secuencia
uint8_t flag_fin_dir,flag_fin_cor;					//flags que me indicaran que ya no hay mas comandos de direccion o corte para repetir

uint8_t comando_dir,comando_corte;

void podadora(void);		//funcion que repetira la secuencia pedida




volatile uint8_t estado_pid;
volatile float error_absoluto;

#define ESPERANDO	0
#define MUESTREANDO	1
#define CALCULANDO 	2

void controlador_PID(void);



//#define DUTY_DRECHA_AVANZAR 366
//#define LIMITE_SUP_DER_AVANZAR	416
//#define LIMITE_INF_DER_AVANZAR	316
//
//
//#define DUTY_IZQUIERDA_AVANZAR 360
//#define LIMITE_SUP_IZQ_AVANZAR	410
//#define LIMITE_INF_IZQ_AVANZAR	310
//
//
//#define DUTY_DRECHA_RETROCEDER 	440
//#define LIMITE_SUP_DER_RETRO	490
//#define LIMITE_INF_DER_RETRO	390
//
//
//#define DUTY_IZQUIERDA_RETROCEDER 434
//#define LIMITE_SUP_IZQ_RETRO	484
//#define LIMITE_INF_IZQ_RETRO	384

//
//#define DUTY_DRECHA_AVANZAR 35
//#define DUTY_DRECHA_RETROCEDER 47
//#define DUTY_IZQUIERDA_AVANZAR 36
//#define DUTY_IZQUIERDA_RETROCEDER 49



#define DUTY_AVANZAR	35
#define DUTY_RETROCEDER	45

#define LIMITE_INFERIOR_AVANZAR 30
#define LIMITE_SUPERIOR_AVANZAR 40
#define LIMITE_INFERIOR_RETROCEDER 40
#define LIMITE_SUPERIOR_RETROCEDER 50


volatile int err_proporcional,err_integral,err_derivativo,salida_pwm;
volatile float error, error_previo;

float vector_pid[250];
uint8_t i_angulos;




#endif /* APLICACION_H_ */
