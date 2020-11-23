/*
 * FW_ADC.c
 */


//--------------------------------------- ADC ----------------------------------------//

#include "aplicacion.h"




#define PCADC             12
#define CLKDIV            8
#define PDN               21
#define ADC_START         24
#define ADCOFFS           4
#define ADGINTEN          8


#define 	ADC		( ( __RW uint32_t  * ) 0x40034000UL )

#define ADCR		ADC[0]
#define ADGDR   	ADC[1]
#define ADINTEN		ADC[2]
#define ADDR0		ADC[3]
#define ADDR1		ADC[4]
#define ADDR2		ADC[5]
#define ADDR3		ADC[6]
#define ADDR4		ADC[7]
#define ADDR5		ADC[8]
#define ADDR6		ADC[9]
#define ADDR7		ADC[10]
#define ADSTAT		ADC[11]
#define ADTRM		ADC[12]




/**
 * void InicADC(void)
 *
 * Rutina de inicializacion del ADC
 * */
void InicADC(void){

	IPR5 |= (0x1<<19);			//LE PONGO PRIORIDAD 1 AL ADC

	//1.- Activo la alimentacion del dispositivo desde el registro PCONP:
	PCONP |= 1<<12;
	//2.- Selecciono el clock del ADC como 25MHz:
	PCLKSEL0 &= ~(0x03<<24);
	//3.- Y el divisor como 1, para muestrear a 200kHz:
	ADCR |= 0x00000100;
	//4.- Configuro los pines del ADC0
//	//ADC0.5 : P1[31]->PINSEL3: 30:31
//	PINSEL3 |= PINSEL_FUNC3 << 30;

	//ADC0.0 : P0[23]->PINSEL1: 14:15
	PINSEL1 |= PINSEL_FUNC1 << 14;

	//5.- ACTIVO LAS INTERRUPCIONES GLOBALES Y ADC0CH5:
//	ADINTEN &= 0xFFFFFF20;
	ADINTEN &= 0xFFFFFF01;

	// HABILITO INT DEL ADC EN NVIC
	ISER0 |= (0x01 << 22);
	//6.- Selecciono que voy a tomar muestras del canal AD0.5:
//	ADCR |= 0x00000020;
	ADCR |= 0x00000001;

	//7.- Activo el ADC (PDN = 1):
	ADCR |= 1<<21;
	//8.- Disparo el ADC para que muestree solo, con BURST = 1 y START = 000:
	ADCR &= ~(0x0F<<24);
	ADCR |= 1<<16;
}

/**
 * void ADC_IRQHandler(void)
 * */
void ADC_IRQHandler(void){
	static uint8_t contador = 0;
	static uint16_t resultadoParcial = 0;
	static uint32_t acumulador = 0;

	resultadoParcial = (ADGDR >> 4) & (0x0000FFFF);
	acumulador += resultadoParcial;
	contador ++;

	if(contador == 128){
		resultadoADC = acumulador >> 7;
		contador = 0;
		acumulador = 0;
	}

}


