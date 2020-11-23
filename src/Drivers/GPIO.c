/*
 * GPIO.c
 *
 *  Created on: 27 de sept. de 2017
 *      Author: Cristian
 */

#include "Aplicacion.h"

/**
 * \fn 		void SetPINSEL( uint8_t port , uint8_t pin , uint8_t sel)
 * \brief 	Elige funcionalidad de pin de GPIO
 * \details
 * \author 	GOS
 * \date   	2014.05.06
 * \param 	[in] uint8_t port, uint8_t pin, uint8_t sel
 * \return 	void
 * */
void SetPINSEL( uint8_t port , uint8_t pin ,uint8_t sel)
{
	port = port * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINSEL[ port ] = PINSEL[ port ] & ( ~ ( 3 << pin ) );
	PINSEL[ port ] = PINSEL[ port ] | ( sel << pin );
}

/**
 * \fn 		void SetPINMODE( uint8_t port , uint8_t pin , uint8_t modo)
 * \brief 	Elige modo de pull de pin de GPIO
 * \details
 * \author 	GOS
 * \date   	2014.05.06
 * \param 	[in] uint8_t port, uint8_t pin, uint8_t modo
 * \return 	void
 * */
void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo)
{
	port = port * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINMODE[ port ] = PINMODE[ port ] & ( ~ ( 3 << pin ) );
	PINMODE[ port ] = PINMODE[ port ] | ( modo << pin );
}


/**
 * \fn 		void SetMODE_OD( uint8_t port , uint8_t pin , uint8_t dir)
 * \brief 	Elige modo de pull de pin de GPIO
 * \details
 * \author 	GOS
 * \date   	2014.05.06
 * \param 	[in] uint8_t port, uint8_t pin, uint8_t dir
 * \return 	void
 * */
void SetMODE_OD( uint8_t port , uint8_t pin , uint8_t dir )
{

	PINMODE_OD[ port ] = PINMODE_OD[ port ] & ( ~ ( 1 << pin ) );
	PINMODE_OD[ port ] = PINMODE_OD[ port ] | ( dir << pin );

}


/**
 * \fn 		void SetDIR( uint8_t port , uint8_t pin , uint8_t dir)
 * \brief 	Elige direccion de pin de GPIO
 * \details
 * \author 	GOS
 * \date   	2014.05.06
 * \param 	[in] uint8_t port, uint8_t pin, uint8_t dir
 * \return 	void
 * */
void SetDIR( uint8_t port , uint8_t pin , uint8_t dir )
{
	port = port * 8;

	GPIOs[ port ] = GPIOs[ port ] & ( ~ ( 1 << pin ) );
	GPIOs[ port ] = GPIOs[ port ] | ( dir << pin );
}


/**
 * \fn 		void SetPIN( uint8_t port , uint8_t pin , uint8_t estado)
 * \brief 	Pone un valor en pin de GPIO
 * \details
 * \author 	GOS
 * \date   	2014.05.06
 * \param 	[in] uint8_t port, uint8_t pin, uint8_t estado
 * \return 	void
 * */
void SetPIN( uint8_t port , uint8_t pin , uint8_t estado )
{
	port = port * 8 + 5;

	GPIOs[ port ] = GPIOs[ port ] & ( ~ ( 1 << pin ) );
	GPIOs[ port ] = GPIOs[ port ] | ( estado << pin );
}

/**
 * \fn 		void GetPIN( uint8_t port , uint8_t pin , uint8_t actividad)
 * \brief 	Lee valor de pin de GPIO, con actividad se indica si es activo bajo o alto
 * \details
 * \author 	GOS
 * \date   	2014.05.06
 * \param 	[in] uint8_t port, uint8_t pin, uint8_t actividad
 * \return 	void
 * */
uint8_t GetPIN( uint8_t port , uint8_t pin , uint8_t actividad )
{
	port = port * 8 + 5;

	return ( ( ( GPIOs[ port ] >> pin ) & 1 ) == actividad ) ? 1 : 0;

}

