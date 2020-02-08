


#ifndef HEADER_TOKEN
#define HEADER_TOKEN 1  

#define F_CPU   32000000UL
#define F_PERPH 32000000UL


/** Uncomment to activate the ring buffer on any of these uart modules . */
/********************************************************************************************************************************/

#define USARTC0_RING 1
//#define USARTC1_RING 2
//#define USARTD0_RING 3
//#define USARTD1_RING 4
//#define USARTE0_RING 5


/*************************************************************************************************************************************/

/*****************************************************        A7 MODULE   ************************************************************/
#define A7_UART_RING USARTC0_RING 
#define A7_PWR_PORT  PORTE
#define A7_PWR_PIN   1
/*************************************************************************************************************************************/

#define UART_E0_RX  2
#define UART_E0_TX  3 
#define UART_E0_XCK 1

#define UART_C0_RX  2
#define UART_C0_TX  3
#define UART_C0_XCK 1

#define UART_C1_RX  6
#define UART_C1_TX  7
#define UART_C1_XCK 5

#define UART_D0_RX  2
#define UART_D0_TX  3
#define UART_D0_XCK 1

#define UART_D1_RX  6
#define UART_D1_TX  7
#define UART_D1_XCK 5

#ifndef UNUSED 
#define UNUSED -1 
#endif 

typedef enum{
	
	INT_DISABLED        = 0B00 ,
	INT_LOW_PRIORITY    = 0B01 ,
	INT_MEDIUM_PRIORITY = 0B10 ,
	INT_HIGH_PRIORITY   = 0B11 ,
	
} int_level ;




#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../GPIO/GPIO.h"
#include "../SYSCLK/sysclk.h"
#include "../UART/uart.h"
#include "../A7/GPRS.h"
#include "../SPI/SPI.h"
#include "../ETHERNET/ENCJ.h"


#endif 
