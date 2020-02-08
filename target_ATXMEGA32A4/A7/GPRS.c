




#include "GPRS.h"


struct pwr_datastruct {
	
	uint8_t _CINIT1[PWR_ON_STRLEN] ;
	uint8_t _CINIT2[PWR_ON_STRLEN] ;
	uint8_t _STN[PWR_ON_STRLEN] ;
	uint8_t _CINIT3[PWR_ON_STRLEN] ;
	uint8_t _CINIT4[PWR_ON_STRLEN] ;
	uint8_t _CINIT5[PWR_ON_STRLEN] ;
	uint8_t _CINIT6[PWR_ON_STRLEN] ;
	uint8_t _CTZV[PWR_ON_STRLEN] ;
	uint8_t _CIEV1[PWR_ON_STRLEN] ;
	uint8_t _CIEV2[PWR_ON_STRLEN] ;
	uint8_t _CREG1[PWR_ON_STRLEN] ;
	uint8_t _CREG2[PWR_ON_STRLEN] ;	
	
	
} init_struct ; 




uint8_t * cmd_buff[] = { "AT&F0\r\n" , "ATE0\r\n" , "ATV1\r\n" , "AT+IPR=115200\r\n" ,"AT+ICF=3,3\r\n" , "AT&W0\r\n" , "AT+CPOF\r\n" ,"ATD" } ; 
uint8_t ** ok_resp_buff[] = { {"|OK|", "|AT&F0|OK|" , "|AT&F0|" } ,  {"|OK|", "|ATE0|OK|" , "|ATE0|" } , {"|OK|", "|ATV1|OK|" , "|ATV1|" } , {"|OK|", "|AT+IPR|OK|" , "|AT+IPR|" } , {"|OK|", "|AT+ICF|OK|" , "|AT+ICF|" } , {"|OK|", "|AT&W0|OK|" , "|AT&W0|" } ,{"|OK|" , "|AT+CPOF|OK|" , "|AT+CPOF|" }, {"|OK|" ,"|ATD|OK|" , "|ATD|" } };


static void string_divider( uint8_t * src_buff , uint8_t* dist_buff  , uint8_t element_num ) {
	
	uint16_t i , j , l  ;
	
for ( i = 0 , j = 0 , l = 0  ; ( *(src_buff + i ) != 0 ) && ( j <= element_num + 1 ) ; i++ ){
	
	//increment column number if it is found 
	if( *(src_buff + i ) == '|' ) {
		
	++j ;  
}

// copy string 
	if ( ( j == element_num+1 ) && ( *(src_buff + i ) != '|' ) ) {
	
		*(dist_buff + l ) = *( src_buff + i ) ;
		++l;
}
	
		
	}
	//Terminate the string
	
	*(dist_buff + l ) = 0 ;  
	
}



// Empty error handler 
static int16_t error_handler ( uint8_t cmd , uint8_t * tokenized_resp ){
	return ERR_SUCCESS ; 
	
}



static int16_t A7_get_response ( uint8_t * resp_buff , to_delay timeout_delay ) {
	
	uint16_t buff_size ;    
	uint16_t i , j , prevchar = 0  ;   
	int16_t word ;    
	uint8_t temp ; 
	
	
		// wait for an amount timeout delay which is the response window for the gsm module 
		
		switch( timeout_delay ){
			
			case DELAY_INIT :
			
			_delay_ms( DELAY_INIT );
			break;

			case DELAY_PWRON :
			
			_delay_ms( DELAY_PWRON );
			break;			
			 
			case DELAY_CALL :
			
			_delay_ms( DELAY_CALL );
			break;
			
			case DELAY_GPS :
			
			_delay_ms( DELAY_GPS );
			break;						
	
		}
		
		*(resp_buff + 0 ) = '|' ; 
		
		// Receive an unknown number of bytes , during the time timeout_delay 
		
		for( buff_size = 0 ; (word = uart_get( A7_UART_RING ) ) != -1 ; ++buff_size ){
			
			*( resp_buff + buff_size + 1 ) = ( uint8_t ) word;
		}
		
		// Timeout error 
		if ( !buff_size ) {
			
			return 0 ; 
		}
		
		// Null terminate the response buffer 
		
		*(resp_buff + buff_size ) = 0 ; 
		
		//filter  ( REMOVE \R \N from the message ) 
		
		for (  i = 0 , j = 0 ; i < buff_size ; i++ ){
			
			temp = *(resp_buff+i ) ;
			 
			// Shift non formatting characters to the start of the buffer 
			if ( (temp != '\r') && (temp != '\n' ) ){
				*(resp_buff + j ) = temp ;
				++j;
				prevchar = 1 ; 
			}
			else{
				// Handling of case |\n\rOK  or any similar situation when we get | followed by \r or \n
				if ( i ==1 ) { prevchar = 0 ; }
				
				if ( prevchar  ) {
					
					*(resp_buff + j ) = '|' ;
					++j;
					prevchar = 0 ;
				}
			}
			
			// Null terminate the modified response buffer 
			if ( i == buff_size - 1 ){
				*( resp_buff+ j ) = 0 ;
				buff_size = j - 1  ;  
			}
			
		}
	
	// return the new size of the buffer 
	
	return buff_size  ; 
	
	
}



int16_t A7_send_cmd ( uint8_t cmd  , to_delay timeout_delay , ... ){
	
	uint8_t raw_resp[MAX_RESP_SIZE] ; 
	uint8_t i ; 
	uint8_t* arg_holder ; 
	uint8_t* varg_cmd[CMD_LENGTH];
	
	// parse the arguments******************************************** 
	
	// this type is used to iterate over the given argument list 
	va_list arg ; 
	// initializes arg to give timeout_delay , last argument given before the vargs
	va_start( arg , timeout_delay ) ;
	
	switch ( cmd ) {
		
		
	case CMD_ATD : 
	
	// advance arg to give the next argument type is uint8_t * 
	
	arg_holder = va_arg( arg , uint8_t* ) ;
	//COPY ATD COMMAND 
	strcpy(varg_cmd , cmd_buff[cmd] ) ;
	
	//INSERT PHONE NUMBER
	strcat( varg_cmd , arg_holder ) ;
	
	//Terminate
	
	strcat( varg_cmd , "\r\n" ) ;
	
	break;
	
	
	default:
	strcpy( varg_cmd , cmd_buff[cmd] ) ;
	break ;
	
}
	
	//****************************************************************
	//clear RX BUFF
	flush_rx_buff( A7_UART_RING ) ;
	//send cmd 
	uart_write( A7_UART_RING , varg_cmd , strlen( varg_cmd ) ); 
	//wait for response 
	if ( A7_get_response( raw_resp , timeout_delay ) == 0 ) { return ERR_TIMEOUT ; }	
	//debug
	uart_print( raw_resp , & USARTE0 ) ;
	uartb_transmit( '\n', &USARTE0);
	// check return against known responses
	for ( i = 0 ; i <= MAX_RESP_NUM -1  ; i++){
		
		if ( !strcmp( raw_resp , *(*(ok_resp_buff + cmd ) + i ) ) ){
			// found a good response 
			return ERR_SUCCESS ; 
		}
		
	}
	
	// calculate command number
	
	
	
	// no good response found 
	// call error handler 
	
	return ( error_handler( cmd , raw_resp ) ) ; 
	
		
	}
	
	








int16_t A7_Init( void ) {
	
	uint8_t init_row[ PWR_ON_STRLEN * 20] ;
	uint8_t i ;  
/*	const uint8_t* init_cmds[6] = {"AT&F0\r\n" , "ATE0\r\n" , "ATV1\r\n" , "AT+IPR=115200\r\n" ,"AT+ICF=3,3\r\n" , "AT&W0\r\n"};
	const uint8_t* resp1_cmds[6] = {"|AT&F0|OK|", "|ATE0|OK|","|ATV|OK|" , "|AT+IPR|OK|" , "|AT+ICF|OK|" , "|AT&W|OK" };
	const uint8_t* resp2_cmds[6] = {"|AT&F0|"  , "|ATE0|"   ,"|ATV|"    , "|AT+IPR|"      "|AT+ICF|"      "|AT&W|" };
	*/
	
	// PUSHPULL OUTPUT , LOW 
	pin_config(  A7_PWR_PIN , &A7_PWR_PORT , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES ) ;
	pin_clear( A7_PWR_PIN , &A7_PWR_PORT ) ; 
	//WAIT FOR POWERUP
	_delay_ms(50);
	// PULL THE PWRPIN HIGH
	pin_set( A7_PWR_PIN , &A7_PWR_PORT ) ; 
	// WAIT FOR HOLD_TIME
	_delay_ms( A7_HOLD_TIME ) ;
	//RELEASE
	pin_clear( A7_PWR_PIN , &A7_PWR_PORT);
	
	_delay_ms(DELAY_PWRON);
	//*******************************************************************************************************************************
	//                                         Here you can add code for capturing data on powerup
	//*******************************************************************************************************************************
	int16_t error_check = 0 ;
	
	//SETTING PARAMETERS
	
	for ( i = CMD_ATF ; i <= 6  ; i++ ) {
	
	error_check+= A7_send_cmd( i , DELAY_INIT ) ; 
	
}
	
	if ( !error_check ) { return ERR_SUCCESS ; }
	
	return error_check ; 
	
	 
}






















