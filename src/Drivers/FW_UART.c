/*
 * FW_UART.c
 */

#include "aplicacion.h"

extern volatile char BufferRx[TOPE],BufferTx[TOPE],TxStart;


	void UART0_IRQHandler (void)
	{
	    uint8_t iir,dato;
	    do
	    {
	        iir = U0IIR;
	        if (iir & 0x04) {
	        	dato=U0RBR;				// data ready
	        	guardar_dato(dato);
	        	//PushRx(dato);
	        }
	        if (iir & 0x02) { // THRE disponible

	        	dato=PopTx();

	        	if(dato==0xFF)
	        		TxStart=0;
	        	else
	        		U0THR=dato;
	        }


	     } while ( !(iir & 0x01) ); // pendiente
	}

