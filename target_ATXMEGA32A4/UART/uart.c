/** @file uart.c
 * Author : Mohamed Yousry Mohamed Rashad 
 * 
 * 
 * File Discription : This file contains function implementations for uart module , spi master mode as well as initialization and value 
 * calculations for the xmega series . 
 * 
 * 
 */


#include "uart.h"
#include <stdio.h>




void uart_port_asynch_xmega32a4 ( USART_t* usart_port ) {
	
		
		
		if( usart_port ==  &USARTC0 ){
		
		pin_config( UART_C0_RX , &PORTC , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_C0_TX , &PORTC , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		
	}
		
		else if ( usart_port == &USARTC1 ){
		
		pin_config( UART_C1_RX , &PORTC , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_C1_TX , &PORTC , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );		
		
	}
		
		else if ( usart_port == &USARTD0 ){
		
		pin_config( UART_D0_RX , &PORTD , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_D0_TX , &PORTD , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		
	}
		else if ( usart_port == &USARTD1 ){
		
		pin_config( UART_D1_RX , &PORTD , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_D1_TX , &PORTD , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );		
		
	}
		
		else if ( usart_port == &USARTE0 ){
		
		pin_config( UART_E0_RX , &PORTE , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_E0_TX , &PORTE , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		
	}
	
	
		
	}
	
	
	void uart_port_synch_xmega32a4 ( USART_t* usart_port ) {

	
		
		
		if( usart_port ==  &USARTC0 ){
		
		pin_config( UART_C0_RX , &PORTC , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_C0_TX , &PORTC , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_C0_XCK , &PORTC , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		
	}
		else if ( usart_port == &USARTC1 ){
		
		pin_config( UART_C1_RX , &PORTC , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_C1_TX , &PORTC , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_C1_XCK , &PORTC , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );		
		
	}	
		
		else if ( usart_port ==  &USARTD0 ) { 
		
		pin_config( UART_D0_RX , &PORTD , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_D0_TX , &PORTD , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_D0_XCK , &PORTD , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		
	}
		else if ( usart_port == &USARTD1 ){
		
		pin_config( UART_D1_RX , &PORTD , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_D1_TX , &PORTD , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_D1_XCK , &PORTD , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );		
		
	}
		
		else if ( usart_port == &USARTE0 ){
		
		pin_config( UART_E0_RX , &PORTE , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_E0_TX , &PORTE , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		pin_config( UART_E0_XCK , &PORTE , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
		
		
}
		
	}
	


void uart_asynch_init ( uint16_t baud_select ,  uint8_t u2x, frame_mode frame_config , USART_t * usart_port ) {
	
	// Set the baud rate 
	usart_port->BAUDCTRLA = (uint8_t) baud_select ;
	usart_port->BAUDCTRLB = (uint8_t)( baud_select >> 8 );
	
	
	// serial control
	
	usart_port->CTRLC = ( frame_config << USART_CHSIZE0_bp ) | ( SERIAL_ASYNCH_UART << USART_CMODE0_bp) ;
	usart_port->CTRLB = ( 1 << USART_RXEN_bp ) | ( 1 << USART_TXEN_bp ) | ( (u2x?1:0) << USART_CLK2X_bp ) ;	
}

void uart_synch_init (uint16_t baud_select ,  uint8_t u2x, frame_mode frame_config , USART_t * usart_port ) {


	// Set the baud rate 
	usart_port->BAUDCTRLA = (uint8_t) baud_select ;
	usart_port->BAUDCTRLB = (uint8_t)( baud_select >> 8 );
	
	
	// serial control
	
	usart_port->CTRLC = ( frame_config << USART_CHSIZE0_bp ) | ( SERIAL_SYNCH_UART << USART_CMODE0_bp) ;
	usart_port->CTRLB = ( 1 << USART_RXEN_bp ) | ( 1 << USART_TXEN_bp ) | ( (u2x?1:0) << USART_CLK2X_bp ) ;	



}


void uart_mspi_init( uint16_t baud_select ,  uint8_t u2x , USART_t * usart_port ) {
	
	
	// Set the baud rate 
	usart_port->BAUDCTRLA = (uint8_t) baud_select ;
	usart_port->BAUDCTRLB = (uint8_t)( baud_select << 8 );
	
	//serial control , no need for frame configuration 
	
	usart_port->CTRLC = ( SERIAL_MASTER_SPI << USART_CMODE0_bp ) ; 
	usart_port->CTRLB = ( 1 << USART_RXEN_bp ) | ( 1 << USART_TXEN_bp ) | ( (u2x?1:0) << USART_CLK2X_bp ) ;	


}


void uart_mspi_2wire_init( uint16_t baud_select ,  uint8_t u2x , USART_t * usart_port ) {
	
	
	// Set the baud rate 
	usart_port->BAUDCTRLA = (uint8_t) baud_select ;
	usart_port->BAUDCTRLB = (uint8_t)( baud_select << 8 );
	
	//serial control , no need for frame configuration // Transmitter only is active no RX
	
	usart_port->CTRLC = ( SERIAL_MASTER_SPI << USART_CMODE0_bp ) ; 
	usart_port->CTRLB =  ( 1 << USART_TXEN_bp ) | ( (u2x?1:0) << USART_CLK2X_bp ) ;	


}



void uart_disable ( USART_t* usart_port ) {
	
	usart_port->CTRLB = 0 ; 
}


void uart_interrupt_set( int_level txc_int , int_level rxc_int , int_level dre_int , USART_t* usart_port ) {
	
	usart_port->CTRLA = ( txc_int << USART_TXCINTLVL0_bp ) | ( rxc_int << USART_RXCINTLVL0_bp ) | ( dre_int << USART_DREINTLVL0_bp );
	
	
}


void uartb_transmit ( uint8_t byte , USART_t* usart_port )  {
	
	
	usart_port->DATA = byte ;
	while ( !(usart_port->STATUS & ( 1 << USART_DREIF_bp ) ));
	
}
	

uint8_t uartb_receive ( USART_t* usart_port ) {
	
	while( !( usart_port->STATUS * ( 1 << USART_RXCIF_bp ) ) ); 
	
	return usart_port->DATA ; 
	
	
}

uint8_t uartb_transceive ( uint8_t byte ,USART_t* usart_port ) { 
	
	while ( !(usart_port->STATUS & ( 1 << USART_TXCIF_bp ) ));  // wait for transmit to complete
		
	usart_port->DATA = byte; 
	
	while( !( usart_port->STATUS * ( 1 << USART_RXCIF_bp ) ) ); // receiver should have also finished

return usart_port->DATA ; // Return received byte 
	
}
 
	

uint8_t uartnb_transmit( uint8_t byte , USART_t* usart_port ) {
		
		if ( ( usart_port->STATUS * ( 1 << USART_DREIF_bp ) ) ){
			
		usart_port->DATA = byte ;
		return 1 ; 
	}
	
	return 0 ; 
	
}


int16_t uartnb_receive ( USART_t* usart_port ){
	
	if ( ( usart_port->STATUS * ( 1 << USART_RXCIF_bp ) ) ){
	return usart_port->DATA ;
}

return -1 ;    // no data
}




void uart_print ( uint8_t* buff  , USART_t* usart_port ) {
	
	for ( uint8_t i = 0 ; *(buff+i) != 0  ; i++){
		
		uartb_transmit( *(buff+i) , usart_port ) ;

	
}
}

void uart_print_num ( int32_t val  , uint8_t base  , uint8_t termination , USART_t* usart_port ) {
	
	uint8_t itoa_buff[11] ;
	
	itoa( val , itoa_buff , base ) ;
	
	for ( uint8_t i = 0 ; itoa_buff[i] != 0 ; i++ ) {
		
		uartb_transmit( itoa_buff[i] , usart_port ) ;
}

if ( termination ) {  uartb_transmit ( termination , usart_port ) ; } 


}

void uart_transmit_array ( uint8_t* buff , uint16_t len , USART_t* usart_port ) {
	
	for ( uint16_t i = 0 ; i <= len -1 ; i++ ) {
		
		uartb_transmit ( *(buff+i) , usart_port ) ;
	}
}



void uart_debug_9600 ( void ) { 
	
	uint8_t debug_word[] = "UART Debug Mode : ------------------------------\n" ; 
	// init port pins ;
	
	uart_port_asynch_xmega32a4 ( &USARTE0 ) ;   
	
	// init UARTE0 module for debug 9600 bps , 1 stop bit , 8 bit data , no parity , u2x off , 10 bit frame , fperph = F_CPU Default NO SCALERS
	
	uart_asynch_init( baud_calc(9600 , 2000000UL , 8 , 0 ) , 0 , PARITY_DISABLED_1SB_8B , &USARTE0 ) ;
	
	
	//transmit on sentence
	
	uart_print( debug_word  ,&USARTE0 ) ;
	
	// MORE STUFF LATER ---- REGISTER READ / TRANSMISSION OF RECEIVED WORDS AND SO ON 
	
} 












