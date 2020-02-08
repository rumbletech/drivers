/** @file GPRS.h
 * 
 * Author : Mohamed yousry mohamed rashad .
 * 
 * Description : This file contains basic command definitions and commands , for the GPRS.C module , NOTE  the GPRS module will use one
 * of the UARTS on your micro , this is confiugrable from the application header , you may want to enable ring buffers or not enable them
 * on the uart module of your choosing .
 * 
 * */

#ifndef A7_TOKEN 
#define A7_TOKEN 1

// Include the main header  , Include stdarg.h for variadic functions 

#include "../GENERAL/header.h"
#include <stdarg.h>


#define CMD_LENGTH 50
#define A7_HOLD_TIME 2500
#define PWR_ON_STRLEN 30
#define MAX_RESP_SIZE 100
#define MAX_RESP_NUM  3

#ifndef A7_UART_RING  
#warning " Both A7_UART_RING and A7_UART are not defined for the A7 Module "
#endif


typedef enum { 
	
	DELAY_INIT  = 200  , 
	DELAY_PWRON = 12000, 
	DELAY_CALL  = 120000,
	DELAY_GPS   = 5000 , 
	
} to_delay ;

typedef enum {
	CMD_ATF    = 0 ,
	CMD_ATE    = 1 ,
	CMD_ATV    = 2 ,
	CMD_ATIPR  = 3 ,
	CMD_ATICF  = 4 ,
	CMD_ATW    = 5 ,  
	CMD_ATCPOF = 6 ,
	CMD_ATD    = 7 ,
	
} cmds ;

typedef enum {
	
	ERR_SUCCESS = 0 , 
	ERR_TIMEOUT = ( 1 << 0 ) ,
		
} errc ; 



extern int16_t A7_Init( void ) ; 
extern int16_t A7_send_cmd ( uint8_t cmd  , to_delay timeout_delay , ... );



#endif
