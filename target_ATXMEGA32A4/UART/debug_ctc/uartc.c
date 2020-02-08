/** @file uart.c
 * Author : Mohamed Yousry Mohamed Rashad 
 * 
 * 
 * File Discription : This file contains function implementations for uart module , spi master mode as well as initialization and value 
 * calculations for the xmega series . 
 * 
 * 
 */

#define F_CPU 32000000
#include "uartc.h"
#include <stdio.h>










int main( void ) {
	
	uint32_t baud_rate ; 
	uint32_t f_cpu ;
	
	while(1){
	printf("Enter baud rate :\n ");
	scanf("%d" , &baud_rate );
	printf("Enter frequency of cpu :\n ");
	scanf("%d" , &f_cpu );
	
	
	printf("%x",baud_calc( baud_rate , f_cpu , 8 , 0)) ;
}
}


/*int main ( void ) {
	
	
uint16_t x ; x= baud_calc( 9600 , 32000000 , 10 , 0 ) ;
port_write( (uint8_t)x , &PORTD ) ;
	while(1){}
	
}
*/
