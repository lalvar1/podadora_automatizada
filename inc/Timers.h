/*
 * Timers.h
 *
 *  Created on: 22 de feb. de 2018
 *      Author: Cristian
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "RegLPC1769.h"

#define TRIG1	PORT0,21
#define TRIG2	PORT2,10
#define TRIG3	PORT2,12
#define ECHO1	PORT0,22
#define ECHO2	PORT2,8
#define ECHO3	PORT2,11


// Timer 0
#define		TIMER0 		( ( __RW uint32_t  * ) 0x40004000UL )
#define		T0IR		TIMER0[0]
#define		T0TCR		TIMER0[1]
#define		T0TC		TIMER0[2]
#define		T0PR		TIMER0[3]
#define		T0PC		TIMER0[4]
#define		T0MCR		TIMER0[5]
#define		T0MR0		TIMER0[6]
#define		T0MR1		TIMER0[7]
#define		T0MR2		TIMER0[8]
#define		T0MR3		TIMER0[9]
#define		T0CCR		TIMER0[10]
#define		T0CR0		TIMER0[11]
#define		T0CR1		TIMER0[12]

#define		TIMER0EMR	( ( __RW uint32_t  * ) 0x4000403CUL )

#define		TIMER0CTCR	( ( __RW uint32_t  * ) 0x40004070UL )

// Timer 1
#define		TIMER1 		( ( __RW uint32_t  * ) 0x40008000UL )
#define		T1IR		TIMER1[0]
#define		T1TCR		TIMER1[1]
#define		T1TC		TIMER1[2]
#define		T1PR		TIMER1[3]
#define		T1PC		TIMER1[4]
#define		T1MCR		TIMER1[5]
#define		T1MR0		TIMER1[6]
#define		T1MR1		TIMER1[7]
#define		T1MR2		TIMER1[8]
#define		T1MR3		TIMER1[9]
#define		T1CCR		TIMER1[10]
#define		T1CR0		TIMER1[11]
#define		T1CR1		TIMER1[12]

#define		TIMER1EMR	( ( __RW uint32_t  * ) 0x4000803CUL )

#define		TIMER1CTCR	( ( __RW uint32_t  * ) 0x40008070UL )



void Inic_timer(void);

#endif /* TIMERS_H_ */
