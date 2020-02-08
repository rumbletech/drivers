/** @file uart_intd.c 
 * 
 * Description : this is a light weight uart ring buffer , that uses interrupts provided by the xmega , to write to or read from 
 * TX and RX and then store or fetch from the RX_buff or TX_buff .
 * 
 * Note : to activate the ring buffer on one of the usart modules you need to follow the following steps :
 * 
 * STEP0 : Choose the wanted ring buffer SIZES from uart.h
 * STEP1 : Define UARTXX_RING in uart.h 
 * STEP2 : initialize your USART using calls from uart.c to enable interrupt driven operation 
 * STEP3 : add uart_intd.c in your list of dependencies to be compiled.
 */


#include "../uart.h"



typedef enum {
	
	BUFF_EMPTY      = 0X00 ,
	BUFF_NOT_EMPTY  = 0X01 , 
	BUFF_FULL       = 0X02 ,
	
	
} buff_state ; 

//**********************************************************************************************************************************
//****************************************************USARTC0 - ISR*****************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

#ifdef USARTC0_RING


uint8_t USARTC0_tx_buff[USARTC0_TXBUFF_SIZE] ; 
uint8_t USARTC0_rx_buff[USARTC0_RXBUFF_SIZE] ;  

volatile uint16_t USARTC0_tx_tail = 0 ;
volatile uint16_t USARTC0_tx_head = 0 ;
volatile buff_state USARTC0_tx_state = BUFF_EMPTY; 

volatile uint16_t USARTC0_rx_tail = 0 ;
volatile uint16_t USARTC0_rx_head = 0 ;
volatile buff_state USARTC0_rx_state = BUFF_EMPTY; 




ISR( USARTC0_RXC_vect ){
	
	if ( USARTC0_rx_state != BUFF_FULL )
	{
		
		USARTC0_rx_buff[USARTC0_rx_head++] = USARTC0_DATA ; 
		
		if ( USARTC0_rx_head >= USARTC0_RXBUFF_SIZE )
		{
			
			USARTC0_rx_head = 0 ; 
	
	    }
		if ( USARTC0_rx_head == USARTC0_rx_tail )
		{
			
			USARTC0_rx_state = BUFF_FULL ; 
		}
		else
		{
			
			USARTC0_rx_state = BUFF_NOT_EMPTY ;
			
		}	
	
	
	}
	
	else
	{
		
	}
	
}
		

 


ISR( USARTC0_TXC_vect ) {

//Increment 

USARTC0_tx_tail++; 

// Check for overflow

if ( USARTC0_tx_tail >= USARTC0_TXBUFF_SIZE )
{
		
		USARTC0_tx_tail = 0 ; 
		
}


//Update status 
	
	
if(  USARTC0_tx_tail == USARTC0_tx_head )
{
		
	USARTC0_tx_state = BUFF_EMPTY ;

		
}

else
{
	
	USARTC0_tx_state = BUFF_NOT_EMPTY ; 
	
}	
	
	
// Check if there is something to send 

if ( USARTC0_tx_state != BUFF_EMPTY )
{
	
	// Reload the transmit buffer .	
	USARTC0_DATA = USARTC0_tx_buff[USARTC0_tx_tail];
	
}

}


#endif

//**********************************************************************************************************************************
//****************************************************USARTC1 - ISR*****************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

#ifdef USARTC1_RING


uint8_t USARTC1_tx_buff[USARTC1_TXBUFF_SIZE] ; 
uint8_t USARTC1_rx_buff[USARTC1_RXBUFF_SIZE] ;  

volatile uint16_t USARTC1_tx_tail = 0 ;
volatile uint16_t USARTC1_tx_head = 0 ;
volatile buff_state USARTC1_tx_state = BUFF_EMPTY; 

volatile uint16_t USARTC1_rx_tail = 0 ;
volatile uint16_t USARTC1_rx_head = 0 ;
volatile buff_state USARTC1_rx_state = BUFF_EMPTY; 




ISR( USARTC1_RXC_vect ){
	
	if ( USARTC1_rx_state != BUFF_FULL )
	{
		
		USARTC1_rx_buff[USARTC1_rx_head++] = USARTC1_DATA ; 
		
		if ( USARTC1_rx_head >= USARTC1_RXBUFF_SIZE )
		{
			
			USARTC1_rx_head = 0 ; 
	
	    }
		if ( USARTC1_rx_head == USARTC1_rx_tail )
		{
			
			USARTC1_rx_state = BUFF_FULL ; 
		}
		else
		{
			
			USARTC1_rx_state = BUFF_NOT_EMPTY ;
			
		}	
	
	
	}
	
	else
	{
		
	}
	
}
		

 


ISR( USARTC1_TXC_vect ) {

//Increment 

USARTC1_tx_tail++; 

// Check for overflow

if ( USARTC1_tx_tail >= USARTC1_TXBUFF_SIZE )
{
		
		USARTC1_tx_tail = 0 ; 
		
}


//Update status 
	
	
if(  USARTC1_tx_tail == USARTC1_tx_head )
{
		
	USARTC1_tx_state = BUFF_EMPTY ;

		
}

else
{
	
	USARTC1_tx_state = BUFF_NOT_EMPTY ; 
	
}	
	
	
// Check if there is something to send 

if ( USARTC1_tx_state != BUFF_EMPTY )
{
	
	// Reload the transmit buffer .	
	USARTC1_DATA = USARTC1_tx_buff[USARTC1_tx_tail];
	
}

}


#endif

//**********************************************************************************************************************************
//****************************************************USARTD0 - ISR*****************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

#ifdef USARTD0_RING


uint8_t USARTD0_tx_buff[USARTD0_TXBUFF_SIZE] ; 
uint8_t USARTD0_rx_buff[USARTD0_RXBUFF_SIZE] ;  

volatile uint16_t USARTD0_tx_tail = 0 ;
volatile uint16_t USARTD0_tx_head = 0 ;
volatile buff_state USARTD0_tx_state = BUFF_EMPTY; 

volatile uint16_t USARTD0_rx_tail = 0 ;
volatile uint16_t USARTD0_rx_head = 0 ;
volatile buff_state USARTD0_rx_state = BUFF_EMPTY; 




ISR( USARTD0_RXC_vect ){
	
	if ( USARTD0_rx_state != BUFF_FULL )
	{
		
		USARTD0_rx_buff[USARTD0_rx_head++] = USARTD0_DATA ; 
		
		if ( USARTD0_rx_head >= USARTD0_RXBUFF_SIZE )
		{
			
			USARTD0_rx_head = 0 ; 
	
	    }
		if ( USARTD0_rx_head == USARTD0_rx_tail )
		{
			
			USARTD0_rx_state = BUFF_FULL ; 
		}
		else
		{
			
			USARTD0_rx_state = BUFF_NOT_EMPTY ;
			
		}	
	
	
	}
	
	else
	{
		
	}
	
}
		

 


ISR( USARTD0_TXC_vect ) {

//Increment 

USARTD0_tx_tail++; 

// Check for overflow

if ( USARTD0_tx_tail >= USARTD0_TXBUFF_SIZE )
{
		
		USARTD0_tx_tail = 0 ; 
		
}


//Update status 
	
	
if(  USARTD0_tx_tail == USARTD0_tx_head )
{
		
	USARTD0_tx_state = BUFF_EMPTY ;

		
}

else
{
	
	USARTD0_tx_state = BUFF_NOT_EMPTY ; 
	
}	
	
	
// Check if there is something to send 

if ( USARTD0_tx_state != BUFF_EMPTY )
{
	
	// Reload the transmit buffer .	
	USARTD0_DATA = USARTD0_tx_buff[USARTD0_tx_tail];
	
}

}


#endif

//**********************************************************************************************************************************
//****************************************************USARTD1 - ISR*****************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

#ifdef USARTD1_RING


uint8_t USARTD1_tx_buff[USARTD1_TXBUFF_SIZE] ; 
uint8_t USARTD1_rx_buff[USARTD1_RXBUFF_SIZE] ;  

volatile uint16_t USARTD1_tx_tail = 0 ;
volatile uint16_t USARTD1_tx_head = 0 ;
volatile buff_state USARTD1_tx_state = BUFF_EMPTY; 

volatile uint16_t USARTD1_rx_tail = 0 ;
volatile uint16_t USARTD1_rx_head = 0 ;
volatile buff_state USARTD1_rx_state = BUFF_EMPTY; 




ISR( USARTD1_RXC_vect ){
	
	if ( USARTD1_rx_state != BUFF_FULL )
	{
		
		USARTD1_rx_buff[USARTD1_rx_head++] = USARTD1_DATA ; 
		
		if ( USARTD1_rx_head >= USARTD1_RXBUFF_SIZE )
		{
			
			USARTD1_rx_head = 0 ; 
	
	    }
		if ( USARTD1_rx_head == USARTD1_rx_tail )
		{
			
			USARTD1_rx_state = BUFF_FULL ; 
		}
		else
		{
			
			USARTD1_rx_state = BUFF_NOT_EMPTY ;
			
		}	
	
	
	}
	
	else
	{
		
	}
	
}
		

 


ISR( USARTD1_TXC_vect ) {

//Increment 

USARTD1_tx_tail++; 

// Check for overflow

if ( USARTD1_tx_tail >= USARTD1_TXBUFF_SIZE )
{
		
		USARTD1_tx_tail = 0 ; 
		
}


//Update status 
	
	
if(  USARTD1_tx_tail == USARTD1_tx_head )
{
		
	USARTD1_tx_state = BUFF_EMPTY ;

		
}

else
{
	
	USARTD1_tx_state = BUFF_NOT_EMPTY ; 
	
}	
	
	
// Check if there is something to send 

if ( USARTD1_tx_state != BUFF_EMPTY )
{
	
	// Reload the transmit buffer .	
	USARTD1_DATA = USARTD1_tx_buff[USARTD1_tx_tail];
	
}

}


#endif

//**********************************************************************************************************************************
//****************************************************USARTE0 - ISR*****************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

#ifdef USARTE0_RING


uint8_t USARTE0_tx_buff[USARTE0_TXBUFF_SIZE] ; 
uint8_t USARTE0_rx_buff[USARTE0_RXBUFF_SIZE] ;  

volatile uint16_t USARTE0_tx_tail = 0 ;
volatile uint16_t USARTE0_tx_head = 0 ;
volatile buff_state USARTE0_tx_state = BUFF_EMPTY; 

volatile uint16_t USARTE0_rx_tail = 0 ;
volatile uint16_t USARTE0_rx_head = 0 ;
volatile buff_state USARTE0_rx_state = BUFF_EMPTY; 




ISR( USARTE0_RXC_vect ){
	
	if ( USARTE0_rx_state != BUFF_FULL )
	{
		
		USARTE0_rx_buff[USARTE0_rx_head++] = USARTE0_DATA ; 
		
		if ( USARTE0_rx_head >= USARTE0_RXBUFF_SIZE )
		{
			
			USARTE0_rx_head = 0 ; 
	
	    }
		if ( USARTE0_rx_head == USARTE0_rx_tail )
		{
			
			USARTE0_rx_state = BUFF_FULL ; 
		}
		else
		{
			
			USARTE0_rx_state = BUFF_NOT_EMPTY ;
			
		}	
	
	
	}
	
	else
	{
		
	}
	
}
		

 


ISR( USARTE0_TXC_vect ) {

//Increment 

USARTE0_tx_tail++; 

// Check for overflow

if ( USARTE0_tx_tail >= USARTE0_TXBUFF_SIZE )
{
		
		USARTE0_tx_tail = 0 ; 
		
}


//Update status 
	
	
if(  USARTE0_tx_tail == USARTE0_tx_head )
{
		
	USARTE0_tx_state = BUFF_EMPTY ;

		
}

else
{
	
	USARTE0_tx_state = BUFF_NOT_EMPTY ; 
	
}	
	
	
// Check if there is something to send 

if ( USARTE0_tx_state != BUFF_EMPTY )
{
	
	// Reload the transmit buffer .	
	USARTE0_DATA = USARTE0_tx_buff[USARTE0_tx_tail];
	
}

}


#endif
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************


static uint16_t ar_mod ( int16_t diff , uint16_t N ) {
	if ( diff <= 0 )
	{
		return diff + N ; 
	}
	else
	{
		return diff ;
		
	}	
	
}

int16_t uart_get( uint8_t ring_buff ) {
	
	uint8_t * buff ; 
	uint16_t* head ;
	uint16_t* tail ; 
	uint8_t* state ;
	int16_t retval ;
	uint16_t buff_size ;   
	
// Resolve The Buffer starting address 

switch ( ring_buff ) {
	
	#ifdef USARTC0_RING 
	case USARTC0_RING :
	
	buff  = USARTC0_rx_buff ;
	head = &USARTC0_rx_head ;
	tail = &USARTC0_rx_tail ;
	state= &USARTC0_rx_state;
	buff_size = USARTC0_RXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTC1_RING 
	case USARTC1_RING :
	
	buff  = USARTC1_rx_buff ;
	head = &USARTC1_rx_head ;
	tail = &USARTC1_rx_tail ;
	state= &USARTC1_rx_state;
	buff_size = USARTC1_RXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTD0_RING 
	case USARTD0_RING :
	
	buff  = USARTD0_rx_buff ;
	head = &USARTD0_rx_head ;
	tail = &USARTD0_rx_tail ;
	state= &USARTD0_rx_state;
	buff_size = USARTD0_RXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTD1_RING 
	case USARTD1_RING :
	
	buff  = USARTD1_rx_buff ;
	head = &USARTD1_rx_head ;
	tail = &USARTD1_rx_tail ;
	state= &USARTD1_rx_state;
	buff_size = USARTD1_RXBUFF_SIZE;
	
	break;
	#endif 		
	
	#ifdef USARTE0_RING 
	case USARTE0_RING :
	
	buff  = USARTE0_rx_buff ;
	head = &USARTE0_rx_head ;
	tail = &USARTE0_rx_tail ;
	state= &USARTE0_rx_state;
	buff_size = USARTE0_RXBUFF_SIZE;
	
	break;
	#endif 
	
	default:
	
	return -2 ;    // no ring buffer is active or input doesn't match an active ring buffer . 
	
}


 // Variable addresses are resolved , now we operate
 
 if ( *(state) == BUFF_EMPTY ){
	 return -1 ; 
 } 

 retval = *( buff + *(tail) ) ;    // READ VAL 
 *(tail)+= 1;                      // INCREMENT TAIL
 
 // Overflow check
 
 if ( *(tail) >= buff_size ){
	 
	 *(tail) = 0 ;   
 }

// Update buff state

if ( *(tail ) == *(head ) )
{
		
*(state) = BUFF_EMPTY ; 
	
}

else
{
	
*(state) = BUFF_NOT_EMPTY;

}
		


	
	
return retval ; 	
	
	
}




int16_t uart_write( uint8_t ring_buff , uint8_t* data_ptr , uint16_t len  ){
	

	uint8_t * buff ; 
	uint16_t* head ;
	uint16_t* tail ; 
	uint8_t* state ;
	uint8_t prev_state ;
	uint16_t buff_size ;
	int16_t armod ;    
	
// Resolve The Buffer starting address 

switch ( ring_buff ) {
	
	#ifdef USARTC0_RING 
	case USARTC0_RING :
	
	buff  = USARTC0_tx_buff ;
	head = &USARTC0_tx_head ;
	tail = &USARTC0_tx_tail ;
	state= &USARTC0_tx_state;
	buff_size = USARTC0_TXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTC1_RING 
	case USARTC1_RING :
	
	buff  = USARTC1_tx_buff ;
	head = &USARTC1_tx_head ;
	tail = &USARTC1_tx_tail ;
	state= &USARTC1_tx_state;
	buff_size = USARTC1_TXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTD0_RING 
	case USARTD0_RING :
	
	buff  = USARTD0_tx_buff ;
	head = &USARTD0_tx_head ;
	tail = &USARTD0_tx_tail ;
	state= &USARTD0_tx_state;
	buff_size = USARTD0_TXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTD1_RING 
	case USARTD1_RING :
	
	buff  = USARTD1_tx_buff ;
	head = &USARTD1_tx_head ;
	tail = &USARTD1_tx_tail ;
	state= &USARTD1_tx_state;
	buff_size = USARTD1_TXBUFF_SIZE;
	
	break;
	#endif 		
	
	#ifdef USARTE0_RING 
	case USARTE0_RING :
	
	buff  = USARTE0_tx_buff ;
	head = &USARTE0_tx_head ;
	tail = &USARTE0_tx_tail ;
	state= &USARTE0_tx_state;
	buff_size = USARTE0_TXBUFF_SIZE;
	
	break;
	#endif 
	
	default:
	
	return -2 ;    // no ring buffer is active or input doesn't match an active ring buffer . 
	
}
	
	
	// Addresses are resolved  , now we make some checking
	
	//If the TX BUFF is full we cant write to it , if the space is less than len we cant write to it 
	
	if( ( *(state) == BUFF_FULL ) || ( ar_mod( (int16_t)(*tail) - (int16_t)(*head) , buff_size ) < len ) ) {
		return -1 ;
	}
	
	
	
	// write and increment 
	
	for ( uint16_t i = 0 ; i <= len -1 ; i++ )
	{
		//write
		*( buff + *(head)  ) = *( data_ptr + i ) ; 
		//increment
		*(head)+= 1 ;
		//check for overflow 
		
		if ( *(head) >= buff_size /2 ){
			
			*(head) = 0 ;
		}
		 
	}
		
	
	// save previous state to check for an empty buff
	
	prev_state = *(state) ; 
	
	//Update status 

	
	if ( *(head) == *(tail) )
	{
		
		*(state) = BUFF_FULL ; 
		
	}
	else
	{
		*(state) = BUFF_NOT_EMPTY;
	}
		
	
	
	if ( prev_state == BUFF_EMPTY ){
		
		// Trigger Transmission 
		 
		
		switch ( ring_buff ) {
	
	#ifdef USARTC0_RING 
	case USARTC0_RING :
	
	USARTC0_DATA = *(buff + *(tail) ) ; 
	
	break;
	#endif 
	
	#ifdef USARTC1_RING 
	case USARTC1_RING :
	
	USARTC1_DATA = *(buff + *(tail) ) ; 
	
	break;
	#endif 
	
	#ifdef USARTD0_RING 
	case USARTD0_RING :
	
	USARTD0_DATA = *(buff + *(tail) ) ; 
	
	break;
	#endif 
	
	#ifdef USARTD1_RING 
	case USARTD1_RING :
	
	USARTD1_DATA = *(buff + *(tail) ) ; 
	
	break;
	#endif 		
	
	#ifdef USARTE0_RING 
	case USARTE0_RING :
	
	USARTE0_DATA = *(buff + *(tail) ) ; 
	
	break;
	#endif 
	
	default:
	break;
}


		
			
	}
	
else
{
		//Transmission of some bytes is already in progress
	
	
}			 	
	
	return 1 ; 
	
	
} 



int16_t flush_rx_buff ( uint8_t ring_buff ) {
	
	

	uint16_t* head ;
	uint16_t* tail ; 
	uint8_t* state ;  
	
// Resolve The Buffer starting address 

switch ( ring_buff ) {
	
	#ifdef USARTC0_RING 
	case USARTC0_RING :
	
	head = &USARTC0_rx_head ;
	tail = &USARTC0_rx_tail ;
	state= &USARTC0_rx_state;

	
	break;
	#endif 
	
	#ifdef USARTC1_RING 
	case USARTC1_RING :
	
	head = &USARTC1_rx_head ;
	tail = &USARTC1_rx_tail ;
	state= &USARTC1_rx_state;
	
	break;
	#endif 
	
	#ifdef USARTD0_RING 
	case USARTD0_RING :
	
	head = &USARTD0_rx_head ;
	tail = &USARTD0_rx_tail ;
	state= &USARTD0_rx_state;
	
	break;
	#endif 
	
	#ifdef USARTD1_RING 
	case USARTD1_RING :
	
	head = &USARTD1_rx_head ;
	tail = &USARTD1_rx_tail ;
	state= &USARTD1_rx_state;
	
	break;
	#endif 		
	
	#ifdef USARTE0_RING 
	case USARTE0_RING :
	
	head = &USARTE0_rx_head ;
	tail = &USARTE0_rx_tail ;
	state= &USARTE0_rx_state;
	
	break;
	#endif 
	default :
	return -2;
	
}
	
*tail = 0;
*head = 0;
*state = BUFF_EMPTY;
	
	return 1 ; 
}


int16_t get_tx_numbytes ( uint8_t ring_buff ){
	
	

	uint16_t* head ;
	uint16_t* tail ; 
	uint16_t buff_size ;
	
// Resolve The Buffer starting address 

switch ( ring_buff ) {
	
	#ifdef USARTC0_RING 
	case USARTC0_RING :
	

	head = &USARTC0_tx_head ;
	tail = &USARTC0_tx_tail ;
	buff_size = USARTC0_TXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTC1_RING 
	case USARTC1_RING :

	head = &USARTC1_tx_head ;
	tail = &USARTC1_tx_tail ;
	buff_size = USARTC1_TXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTD0_RING 
	case USARTD0_RING :
	

	head = &USARTD0_tx_head ;
	tail = &USARTD0_tx_tail ;
	buff_size = USARTD0_TXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTD1_RING 
	case USARTD1_RING :
	

	head = &USARTD1_tx_head ;
	tail = &USARTD1_tx_tail ;
	buff_size = USARTD1_TXBUFF_SIZE;
	
	break;
	#endif 		
	
	#ifdef USARTE0_RING 
	case USARTE0_RING :
	
	head = &USARTE0_tx_head ;
	tail = &USARTE0_tx_tail ;
	buff_size = USARTE0_TXBUFF_SIZE;
	
	break;
	#endif 
	
	default:
	
	return -2 ;    // no ring buffer is active or input doesn't match an active ring buffer . 
	
}


return ar_mod( (int16_t)(*tail) - (int16_t)(*head) , buff_size ) ; 


}



int16_t get_rx_numbytes ( uint8_t ring_buff ) {
	
	

	uint16_t* head ;
	uint16_t* tail ; 
	uint16_t buff_size ;   
	
// Resolve The Buffer starting address 

switch ( ring_buff ) {
	
	#ifdef USARTC0_RING 
	case USARTC0_RING :
	

	head = &USARTC0_rx_head ;
	tail = &USARTC0_rx_tail ;
	buff_size = USARTC0_RXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTC1_RING 
	case USARTC1_RING :
	

	head = &USARTC1_rx_head ;
	tail = &USARTC1_rx_tail ;
	buff_size = USARTC1_RXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTD0_RING 
	case USARTD0_RING :
	
	head = &USARTD0_rx_head ;
	tail = &USARTD0_rx_tail ;
	buff_size = USARTD0_RXBUFF_SIZE;
	
	break;
	#endif 
	
	#ifdef USARTD1_RING 
	case USARTD1_RING :
	

	head = &USARTD1_rx_head ;
	tail = &USARTD1_rx_tail ;
	buff_size = USARTD1_RXBUFF_SIZE;
	
	break;
	#endif 		
	
	#ifdef USARTE0_RING 
	case USARTE0_RING :

	head = &USARTE0_rx_head ;
	tail = &USARTE0_rx_tail ;
	buff_size = USARTE0_RXBUFF_SIZE;
	
	break;
	#endif 
	
	default:
	
	return -2 ;    // no ring buffer is active or input doesn't match an active ring buffer . 
	
}


return ar_mod( (int16_t)(*head) - (int16_t)(*tail) , buff_size ) ; 


}




int16_t uart_bwrite( uint8_t ring_buff , uint8_t* data_ptr , uint16_t len  ){
	
	int16_t ret = uart_write(ring_buff , data_ptr , len ) ;
	uint8_t * state ; 
	switch ( ring_buff ) {
	
	#ifdef USARTC0_RING 
	case USARTC0_RING :


	state= &USARTC0_tx_state;

	
	break;
	#endif 
	
	#ifdef USARTC1_RING 
	case USARTC1_RING :
	

	state= &USARTC1_tx_state;

	
	break;
	#endif 
	
	#ifdef USARTD0_RING 
	case USARTD0_RING :
	

	state= &USARTD0_tx_state;

	break;
	#endif 
	
	#ifdef USARTD1_RING 
	case USARTD1_RING :
	

	state= &USARTD1_tx_state;

	
	break;
	#endif 		
	
	#ifdef USARTE0_RING 
	case USARTE0_RING :
	

	state= &USARTE0_tx_state;

	
	break;
	#endif 
	
	default:
	
	return -2 ;    // no ring buffer is active or input doesn't match an active ring buffer . 
	
}
	
	if ( ret == -1 ) { return -1 ; }
	else if ( ret == -2 ) { return -2 ; }
	else if ( ret == 1 ) { 
		//wait for the buffer to empty which means the entire array is shifted out and done 
		while ( (*state) != BUFF_EMPTY ) ; 
		return ret ; 
		
	}
	
	
}



int16_t uart_bget ( uint8_t ring_buff , uint8_t * ptr , uint16_t len ) {
	
	int16_t val ;
	int16_t i = 0 ; 
	
	while ( len ) {
		
		val = uart_get( ring_buff ) ; // fetch a value 
		
		if ( val == -2 ) { return -2 ; }
		
		else if ( val != -1 ){
			
			
			*(ptr + i ) = (uint8_t ) val ; 
			++i ;
			--len ;
		} 
				
		} 
		
		return 1 ; 
		
		
		
	}




	
	












