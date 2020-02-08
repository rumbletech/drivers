/** @file uart.h
 * Author : Mohamed Yousry Mohamed Rashad 
 * 
 * 
 * File Discription : This header file contains baud rate definitions and externs for calls used for initialization , transmit and receive
 * functions of the usart module . 
 * 
 * 
 */
#ifndef UART_TOKEN 
#define UART_TOKEN 1 



#include "../GENERAL/header.h"


/** Uncomment to activate the ring buffer on any of these uart modules . */
/********************************************************************************************************************************/

#define USARTC0_RING 1
//#define USARTC1_RING 1
//#define USARTD0_RING 1
//#define USARTD1_RING 1
//#define USARTE0_RING 1


/********************************************************************************************************************************/

/** UART RING BUFFER SIZES **/
/********************************************************************************************************************************/

#define USARTC0_TXBUFF_SIZE 256
#define USARTC0_RXBUFF_SIZE 256

#define USARTC1_TXBUFF_SIZE 256
#define USARTC1_RXBUFF_SIZE 256
 
#define USARTD0_TXBUFF_SIZE 256
#define USARTD0_RXBUFF_SIZE 256

#define USARTD1_TXBUFF_SIZE 256
#define USARTD1_RXBUFF_SIZE 256

#define USARTE0_TXBUFF_SIZE 256
#define USARTE0_RXBUFF_SIZE 256


/********************************************************************************************************************************/
// Check for this return value from baud_calc() , it indicates that no suitable baud configuration is found . 

#define BAUD_ERR_VAL (uint16_t)0XFFFF

// bsel , baud equations when bscale > 0
#define bsel_eval_gtz(baud,bscale , f_perph , u2x) ((( f_perph ) / ( pow(2,bscale) * (u2x?8.0:16.0) * baud)) -1.0)
#define baud_eval_gtz(bsel,bscale , f_perph , u2x) (( f_perph ) / ( pow(2,bscale) * (u2x?8.0:16.0) * (bsel +1.0 ) ) )


// bsel , baud equations when bscale < 0 
#define baud_eval_ltz(bsel,bscale , f_perph ,u2x) (( f_perph) / ( (u2x?8.0:16.0) * ( (pow(2,bscale) * bsel ) + 1.0 ) ) )
#define bsel_eval_ltz(baud,bscale , f_perph ,u2x) ( ( 1.0 / pow(2,bscale) ) * ( ( f_perph / ( (u2x?8.0:16.0) * baud ) ) -1.0) )





/** Description : Specifies Frame configuration for the uart , these modes are ignored when the usart module is initiated in master
 * spi mode , and also ignored in ircom .
 * */
typedef enum {
	
	PARITY_DISABLED_2SB_9B = 0B001111 , /**< PARITY_DISABLED_2SB_9B : no parity , 9 bit data , two stop bits. */
	PARITY_ODD_2SB_9B      = 0B101111 , /**< PARITY_ODD_2SB_9B	    : odd parity , 9 bit data , two stop bits. */
	PARITY_EVEN_2SB_9B     = 0B111111 , /**< PARITY_EVEN_2SB_9B     : even parity , 9 bit data , two stop bits. */
	PARITY_DISABLED_1SB_9B = 0B000111 , /**< PARITY_DISABLED_1SB_9B : no parity , 9 bit data , one stop bit. */
	PARITY_ODD_1SB_9B      = 0B100111 , /**< PARITY_ODD_1SB_9B      : odd parity , 9 bit data , one stop bit. */
	PARITY_EVEN_1SB_9B     = 0B110111 , /**< PARITY_EVEN_1SB_9B     : evem parity , 9 bit data , one stop bit. */
	
	PARITY_DISABLED_2SB_8B = 0B001011 , /**< PARITY_DISABLED_2SB_8B : no parity , 8 bit data , two stop bits. */
	PARITY_ODD_2SB_8B      = 0B101011 , /**< PARITY_ODD_2SB_8B      : odd parity , 8 bit data , two stop bits. */
	PARITY_EVEN_2SB_8B     = 0B111011 , /**< PARITY_EVEN_2SB_8B     : even parity , 8 bit data , two stop bits. */
	PARITY_DISABLED_1SB_8B = 0B000011 , /**< PARITY_DISABLED_1SB_8B : no parity , 8 bit data , one stop bit. */
	ODD_PARITY_1SB_8B      = 0B100011 , /**< ODD_PARITY_1SB_8B      : odd parity , 8 bit data , one stop bit. */
	PARITY_EVEN_1SB_8B     = 0B110011 , /**< PARITY_EVEN_1SB_8B     : even parity , 8 bit data , one stop bit. */
	
	PARITY_DISABLED_2SB_7B = 0B001010 , /**< PARITY_DISABLED_2SB_7B : no parity , 7 bit data , two stop bits. */
	PARITY_ODD_2SB_7B      = 0B101010 , /**< PARITY_ODD_2SB_7B      : odd parity , 7 bit data , two stop bits. */
	PARITY_EVEN_2SB_7B     = 0B111010 , /**< PARITY_EVEN_2SB_7B     : even parity , 7 bit data , two stop bits. */
	PARITY_DISABLED_1SB_7B = 0B000010 , /**< PARITY_DISABLED_1SB_7B : no parity , 7 bit data , one stop bit. */
	PARITY_ODD_1SB_7B      = 0B100010 , /**< PARITY_ODD_1SB_7B      : odd parity , 7 bit data , one stop bit. */
	PARITY_EVEN_1SB_7B     = 0B110010 , /**< PARITY_EVEN_1SB_7B     : even parity , 7 bit data , one stop bit. */
	
	PARITY_DISABLED_2SB_6B = 0B001001 , /**< PARITY_DISABLED_2SB_6B : no parity , 6 bit data , two stop bits. */
	PARITY_ODD_2SB_6B      = 0B101001 , /**< PARITY_ODD_2SB_6B      : odd parity , 6 bit data , two stop bits. */
	PARITY_EVEN_2SB_6B     = 0B111001 , /**< PARITY_EVEN_2SB_6B     : even parity , 6 bit data , two stop bits. */
	PARITY_DISABLED_1SB_6B = 0B000001 , /**< PARITY_DISABLED_1SB_6B : no parity , 6 bit data , one stop bit. */
	PARITY_ODD_1SB_6B      = 0B100001 , /**< PARITY_ODD_1SB_6B      : odd parity , 6 bit data , one stop bit. */
	PARITY_EVEN_1SB_6B     = 0B110001 , /**< PARITY_EVEN_1SB_6B     : even parity , 6 bit data , one stop bit. */
	
	PARITY_DISABLED_2SB_5B = 0B001000 , /**< PARITY_DISABLED_2SB_5B : no parity , 5 bit data , two stop bits. */
	ODD_PARITY_2SB_5B      = 0B101000 , /**< ODD_PARITY_2SB_5B      : odd parity , 5 bit data , two stop bits. */
	EVEN_PARITY_2SB_5B     = 0B111000 , /**< EVEN_PARITY_2SB_5B     : even parity , 5 bit data , two stop bits. */
	PARITY_DISABLED_1SB_5B = 0B000000 , /**< PARITY_DISABLED_1SB_5B : no parity , 5 bit data , one stop bit. */
	ODD_PARITY_1SB_5B      = 0B100000 , /**< ODD_PARITY_1SB_5B      : odd parity , 5 bit data , one stop bit. */
	EVEN_PARITY_1SB_5B     = 0B110000 ,	/**< EVEN_PARITY_1SB_5B     : even parity , 5 bit data , one stop bit. */
	
} frame_mode ;

/** Description : Contains enum bit-fields for different configurations of the uart module */

typedef enum{
	
	SERIAL_ASYNCH_UART = 0B00 , /**< SERIAL_ASYNCH_UART : Asynchronous UART mode. */
	SERIAL_SYNCH_UART  = 0B01 , /**< SERIAL_SYNCH_UART  : Synchronous UART mode. */
	SERIAL_IRCOM       = 0B10 , /**< SERIAL_ASYNCH_UART : IRCOM mode. */
	SERIAL_MASTER_SPI  = 0B11 , /**< SERIAL_ASYNCH_UART : Master SPI mode. */
	
} serial_mode ;







/** Description : This function allows the developer to calculate required baud scaler values at COMPILE TIME.
 * @param baud_rate     : the selected baud rate .
 * @param f_perph       : value of the peripheral clock , Note( this is not the same as the system clock ) 
 * @param data_numbits  : number of data bits used ( without the frame ).
 * @param u2x           : u2x used or not .
 * */

__attribute__((always_inline)) static inline uint16_t baud_calc ( uint32_t baud_rate , uint32_t f_perph ,uint8_t data_numbits ,uint8_t u2x ) {
	
	uint16_t bsel[15] ;
	int8_t opt_bscale = 0 ;
	uint16_t opt_bsel = 0 ;
	uint8_t frame_no = data_numbits + 2 ;
	double prev_baud_rate[15] ; 
	double new_baud_rate[15] ;
	double diff_baud_rate[15];
	
	// -7 
	bsel[0] = bsel_eval_ltz( baud_rate , -7 , f_perph , u2x ) ;
	prev_baud_rate[0] = bsel[0] > 4095 ? 0 :baud_eval_ltz( bsel[0] ,-7 , f_perph , u2x ) ;
	// -6 
	bsel[1] = bsel_eval_ltz( baud_rate , -6 , f_perph , u2x ) ;
	prev_baud_rate[1] =  bsel[1] > 4095 ? 0 : baud_eval_ltz( bsel[1] ,-6 , f_perph , u2x ) ;
	//-5
	bsel[2] = bsel_eval_ltz( baud_rate , -5 , f_perph , u2x ) ;
	prev_baud_rate[2] =  bsel[2] > 4095 ? 0 :baud_eval_ltz( bsel[2] ,-5 , f_perph , u2x ) ;	
	//-4
	bsel[3] = bsel_eval_ltz( baud_rate , -4 , f_perph , u2x ) ;
	prev_baud_rate[3] =  bsel[3] > 4095 ? 0 :baud_eval_ltz( bsel[3] ,-4 , f_perph , u2x ) ;	
	//-3
	bsel[4] = bsel_eval_ltz( baud_rate , -3 , f_perph , u2x ) ;
	prev_baud_rate[4] =  bsel[4] > 4095 ? 0 :baud_eval_ltz( bsel[4] ,-3 , f_perph , u2x ) ;	
	//-2
	bsel[5] = bsel_eval_ltz( baud_rate , -2, f_perph , u2x ) ;
	prev_baud_rate[5] =  bsel[5] > 4095 ? 0 :baud_eval_ltz( bsel[5] ,-2 , f_perph , u2x ) ;	
	//-1
	bsel[6] = bsel_eval_ltz( baud_rate , -1 , f_perph , u2x ) ;
	prev_baud_rate[6] =  bsel[6] > 4095 ? 0 :baud_eval_ltz( bsel[6] ,-1 , f_perph , u2x ) ;	
	//0 
	bsel[7] = bsel_eval_gtz( baud_rate , 0 , f_perph , u2x ) ;
	prev_baud_rate[7] =  bsel[7] > 4095 ? 0 :baud_eval_gtz( bsel[7] ,0 , f_perph , u2x ) ;	
	//1
	bsel[8] = bsel_eval_gtz( baud_rate , 1 , f_perph , u2x ) ;
	prev_baud_rate[8] =  bsel[8] > 4095 ? 0 :baud_eval_gtz( bsel[8] ,1 , f_perph , u2x ) ;	
	//2
	bsel[9] = bsel_eval_gtz( baud_rate , 2 , f_perph , u2x ) ;
	prev_baud_rate[9] =  bsel[9] > 4095 ? 0 :baud_eval_gtz( bsel[9] ,2 , f_perph , u2x ) ;	
	//3
	bsel[10] = bsel_eval_gtz( baud_rate , 3 , f_perph , u2x ) ;
	prev_baud_rate[10] =  bsel[10] > 4095 ? 0 :baud_eval_gtz( bsel[10] , 3 , f_perph , u2x ) ;	
	//4
	bsel[11] = bsel_eval_gtz( baud_rate , 4 , f_perph , u2x ) ;
	prev_baud_rate[11] =  bsel[11] > 4095 ? 0 :baud_eval_gtz( bsel[11] , 4 , f_perph , u2x ) ;	
	//5
	bsel[12] = bsel_eval_gtz( baud_rate , 5 , f_perph , u2x ) ;
	prev_baud_rate[12] =  bsel[12] > 4095 ? 0 :baud_eval_gtz( bsel[12] , 5 , f_perph , u2x ) ;	
	//6
	bsel[13] = bsel_eval_gtz( baud_rate , 6 , f_perph , u2x ) ;
	prev_baud_rate[13] =  bsel[13] > 4095 ? 0 :baud_eval_gtz( bsel[13] , 6 , f_perph , u2x ) ;	
	//7
	bsel[14] = bsel_eval_gtz( baud_rate , 7 , f_perph , u2x ) ;
	prev_baud_rate[14] =  bsel[14] > 4095 ? 0 :baud_eval_gtz( bsel[14] ,7 , f_perph , u2x ) ;
	
	diff_baud_rate[0] = fabs(prev_baud_rate[0] - baud_rate * 1.0) ; 
	diff_baud_rate[1] = fabs(prev_baud_rate[1] - baud_rate * 1.0) ;  
	diff_baud_rate[2] = fabs(prev_baud_rate[2] - baud_rate* 1.0) ;  
	diff_baud_rate[3] = fabs(prev_baud_rate[3] - baud_rate* 1.0) ; 
	diff_baud_rate[4] = fabs(prev_baud_rate[4] - baud_rate* 1.0) ;  
	diff_baud_rate[5] = fabs(prev_baud_rate[5] - baud_rate* 1.0) ; 
	diff_baud_rate[6] = fabs(prev_baud_rate[6] - baud_rate* 1.0) ;  
	diff_baud_rate[7] = fabs(prev_baud_rate[7] - baud_rate* 1.0) ;  
	diff_baud_rate[8] = fabs(prev_baud_rate[8] - baud_rate* 1.0) ; 
	diff_baud_rate[9] = fabs(prev_baud_rate[9] - baud_rate* 1.0) ; 
	diff_baud_rate[10] = fabs(prev_baud_rate[10] - baud_rate* 1.0) ;  
	diff_baud_rate[11] = fabs(prev_baud_rate[11] - baud_rate* 1.0) ;  
	diff_baud_rate[12] = fabs(prev_baud_rate[12] - baud_rate* 1.0) ;  
	diff_baud_rate[13] = fabs(prev_baud_rate[13] - baud_rate* 1.0) ;  
	diff_baud_rate[14] = fabs(prev_baud_rate[14] - baud_rate* 1.0) ;  
	
	if( ( baud_rate == ( f_perph / 16 ) ) && !u2x )
	return 0 ;
	
	if ( ( baud_rate == ( f_perph / 8 ) ) && u2x )
	return 0 ; 
	 
	if( ( baud_rate > ( f_perph / 16 ) ) && !u2x )
	return BAUD_ERR_VAL;
	
	if( ( baud_rate > ( f_perph / 8 ) ) && u2x   )
	return BAUD_ERR_VAL;
	
	if (( diff_baud_rate[0] <= diff_baud_rate[1] ) && (diff_baud_rate[0] <= diff_baud_rate[2] )  && (diff_baud_rate[0] <= diff_baud_rate[3] ) && (diff_baud_rate[0] <= diff_baud_rate[4] ) && (diff_baud_rate[0] <= diff_baud_rate[5] )&& (diff_baud_rate[0] <= diff_baud_rate[6] )&& (diff_baud_rate[0] <=diff_baud_rate[7] )&& (diff_baud_rate[0] <=diff_baud_rate[8] )&& (diff_baud_rate[0] <=diff_baud_rate[9] )&& (diff_baud_rate[0] <=diff_baud_rate[10] )&& (diff_baud_rate[0] <=diff_baud_rate[11] )&& (diff_baud_rate[0] <=diff_baud_rate[12] )&& (diff_baud_rate[0] <=diff_baud_rate[13] )&& (diff_baud_rate[0] <=diff_baud_rate[14] ) && ( bsel[0] <= 4095) && ( pow(2,7) <= (frame_no * 8) ) ){
	return ( ((uint16_t)(-7) <<12 ) | bsel[0] );
}
	if (( diff_baud_rate[1] <= diff_baud_rate[0] ) && (diff_baud_rate[1] <= diff_baud_rate[2] )  && (diff_baud_rate[1] <= diff_baud_rate[3] ) && (diff_baud_rate[1] <= diff_baud_rate[4] ) && (diff_baud_rate[1] <= diff_baud_rate[5] )&& (diff_baud_rate[1] <= diff_baud_rate[6] )&& (diff_baud_rate[1] <= diff_baud_rate[7] )&& (diff_baud_rate[1] <= diff_baud_rate[8] )&& (diff_baud_rate[1] <= diff_baud_rate[9] )&& (diff_baud_rate[1] <= diff_baud_rate[10] )&& (diff_baud_rate[1] <= diff_baud_rate[11] )&& (diff_baud_rate[1] <= diff_baud_rate[12] )&& (diff_baud_rate[1] <= diff_baud_rate[13] )&& (diff_baud_rate[1] <= diff_baud_rate[14] ) && ( bsel[1] <= 4095) && ( pow(2,6) <= (frame_no * 8) ) ){
	return ( ((uint16_t)(-6) <<12 ) | bsel[1] );
}
	if (( diff_baud_rate[2] <=diff_baud_rate[0] ) && (diff_baud_rate[2] <=diff_baud_rate[1] )  && (diff_baud_rate[2] <=diff_baud_rate[3] ) && (diff_baud_rate[2] <=diff_baud_rate[4] ) && (diff_baud_rate[2] <=diff_baud_rate[5] )&& (diff_baud_rate[2] <=diff_baud_rate[6] )&& (diff_baud_rate[2] <=diff_baud_rate[7] )&& (diff_baud_rate[2] <=diff_baud_rate[8] )&& (diff_baud_rate[2] <=diff_baud_rate[9] )&& (diff_baud_rate[2] <=diff_baud_rate[10] )&& (diff_baud_rate[2] <=diff_baud_rate[11] )&& (diff_baud_rate[2] <=diff_baud_rate[12] )&& (diff_baud_rate[2] <=diff_baud_rate[13] )&& (diff_baud_rate[2] <=diff_baud_rate[14] ) && ( bsel[2] <= 4095)&& ( pow(2,5) <= (frame_no * 8) )){
	return ( ((uint16_t)(-5) <<12 ) | bsel[2] );
}
	if (( diff_baud_rate[3] <=diff_baud_rate[0] ) && (diff_baud_rate[3] <=diff_baud_rate[1] )  && (diff_baud_rate[3] <=diff_baud_rate[2] ) && (diff_baud_rate[3] <=diff_baud_rate[4] ) && (diff_baud_rate[3] <=diff_baud_rate[5] )&& (diff_baud_rate[3] <=diff_baud_rate[6] )&& (diff_baud_rate[3] <=diff_baud_rate[7] )&& (diff_baud_rate[3] <=diff_baud_rate[8] )&& (diff_baud_rate[3] <=diff_baud_rate[9] )&& (diff_baud_rate[3] <=diff_baud_rate[10] )&& (diff_baud_rate[3] <=diff_baud_rate[11] )&& (diff_baud_rate[3] <=diff_baud_rate[12] )&& (diff_baud_rate[3] <=diff_baud_rate[13] )&& (diff_baud_rate[3] <=diff_baud_rate[14] ) && ( bsel[3] <= 4095)&& ( pow(2,4) <= (frame_no * 8) )){
	return ( ((uint16_t)(-4) <<12 ) | bsel[3] );
}	
	if (( diff_baud_rate[4] <=diff_baud_rate[0] ) && (diff_baud_rate[4] <=diff_baud_rate[1] )  && (diff_baud_rate[4] <=diff_baud_rate[2] ) && (diff_baud_rate[4] <=diff_baud_rate[3] ) && (diff_baud_rate[4] <=diff_baud_rate[5] )&& (diff_baud_rate[4] <=diff_baud_rate[6] )&& (diff_baud_rate[4] <=diff_baud_rate[7] )&& (diff_baud_rate[4] <=diff_baud_rate[8] )&& (diff_baud_rate[4] <=diff_baud_rate[9] )&& (diff_baud_rate[4] <=diff_baud_rate[10] )&& (diff_baud_rate[4] <=diff_baud_rate[11] )&& (diff_baud_rate[4] <=diff_baud_rate[12] )&& (diff_baud_rate[4] <=diff_baud_rate[13] )&& (diff_baud_rate[4] <=diff_baud_rate[14] ) && ( bsel[4] <= 4095)&& ( pow(2,3) <= (frame_no * 8) )){
	return ( ((uint16_t)(-3) <<12 ) | bsel[4] );
}
	if (( diff_baud_rate[5] <=diff_baud_rate[0] ) && (diff_baud_rate[5] <=diff_baud_rate[1] )  && (diff_baud_rate[5] <=diff_baud_rate[2] ) && (diff_baud_rate[5] <=diff_baud_rate[3] ) && (diff_baud_rate[5] <=diff_baud_rate[4] )&& (diff_baud_rate[5] <=diff_baud_rate[6] )&& (diff_baud_rate[5] <=diff_baud_rate[7] )&& (diff_baud_rate[5] <=diff_baud_rate[8] )&& (diff_baud_rate[5] <=diff_baud_rate[9] )&& (diff_baud_rate[5] <=diff_baud_rate[10] )&& (diff_baud_rate[5] <=diff_baud_rate[11] )&& (diff_baud_rate[5] <=diff_baud_rate[12] )&& (diff_baud_rate[5] <=diff_baud_rate[13] )&& (diff_baud_rate[5] <=diff_baud_rate[14] ) && ( bsel[5] <= 4095)&& ( pow(2,2) <= (frame_no * 8) )){
	return ( ((uint16_t)(-2) <<12 ) | bsel[5] );
}
	if (( diff_baud_rate[6] <=diff_baud_rate[0] ) && (diff_baud_rate[6] <=diff_baud_rate[1] )  && (diff_baud_rate[6] <=diff_baud_rate[2] ) && (diff_baud_rate[6] <=diff_baud_rate[3] ) && (diff_baud_rate[6] <=diff_baud_rate[4] )&& (diff_baud_rate[6] <=diff_baud_rate[5] )&& (diff_baud_rate[6] <=diff_baud_rate[7] )&& (diff_baud_rate[6] <=diff_baud_rate[8] )&& (diff_baud_rate[6] <=diff_baud_rate[9] )&& (diff_baud_rate[6] <=diff_baud_rate[10] )&& (diff_baud_rate[6] <=diff_baud_rate[11] )&& (diff_baud_rate[6] <=diff_baud_rate[12] )&& (diff_baud_rate[6] <=diff_baud_rate[13] )&& (diff_baud_rate[6] <=diff_baud_rate[14] ) && ( bsel[6] <= 4095)&& ( pow(2,1) <= (frame_no * 8) )){
	return ( ((uint16_t)(-1) <<12 ) | bsel[6] );
}
	if (( diff_baud_rate[7] <=diff_baud_rate[0] ) && (diff_baud_rate[7] <=diff_baud_rate[1] )  && (diff_baud_rate[7] <=diff_baud_rate[2] ) && (diff_baud_rate[7] <=diff_baud_rate[3] ) && (diff_baud_rate[7] <=diff_baud_rate[4] )&& (diff_baud_rate[7] <=diff_baud_rate[5] )&& (diff_baud_rate[7] <=diff_baud_rate[6] )&& (diff_baud_rate[7] <=diff_baud_rate[8] )&& (diff_baud_rate[7] <=diff_baud_rate[9] )&& (diff_baud_rate[7] <=diff_baud_rate[10] )&& (diff_baud_rate[7] <=diff_baud_rate[11] )&& (diff_baud_rate[7] <=diff_baud_rate[12] )&& (diff_baud_rate[7] <=diff_baud_rate[13] )&& (diff_baud_rate[7] <=diff_baud_rate[14] ) && ( bsel[7] <= 4095)&& ( pow(2,0) <= (frame_no * 8) )){
	return ( ((uint16_t)(0) <<12 ) | bsel[7] );
}
	if (( diff_baud_rate[8] <=diff_baud_rate[0] ) && (diff_baud_rate[8] <=diff_baud_rate[1] )  && (diff_baud_rate[8] <=diff_baud_rate[2] ) && (diff_baud_rate[8] <=diff_baud_rate[3] ) && (diff_baud_rate[8] <=diff_baud_rate[4] )&& (diff_baud_rate[8] <=diff_baud_rate[5] )&& (diff_baud_rate[8] <=diff_baud_rate[6] )&& (diff_baud_rate[8] <=diff_baud_rate[7] )&& (diff_baud_rate[8] <=diff_baud_rate[9] )&& (diff_baud_rate[8] <=diff_baud_rate[10] )&& (diff_baud_rate[8] <=diff_baud_rate[11] )&& (diff_baud_rate[8] <=diff_baud_rate[12] )&& (diff_baud_rate[8] <=diff_baud_rate[13] )&& (diff_baud_rate[8] <=diff_baud_rate[14] ) && ( bsel[8] <= 4095)&& ( pow(2,1) <= (frame_no * 8) )){
	return ( ((uint16_t)(1) <<12 ) | bsel[8] );
}
	if (( diff_baud_rate[9] <=diff_baud_rate[0] ) && (diff_baud_rate[9] <=diff_baud_rate[1] )  && (diff_baud_rate[9] <=diff_baud_rate[2] ) && (diff_baud_rate[9] <=diff_baud_rate[3] ) && (diff_baud_rate[9] <=diff_baud_rate[4] )&& (diff_baud_rate[9] <=diff_baud_rate[5] )&& (diff_baud_rate[9] <=diff_baud_rate[6] )&& (diff_baud_rate[9] <=diff_baud_rate[7] )&& (diff_baud_rate[9] <=diff_baud_rate[8] )&& (diff_baud_rate[9] <=diff_baud_rate[10] )&& (diff_baud_rate[9] <=diff_baud_rate[11] )&& (diff_baud_rate[9] <=diff_baud_rate[12] )&& (diff_baud_rate[9] <=diff_baud_rate[13] )&& (diff_baud_rate[9] <=diff_baud_rate[14] ) && ( bsel[9] <= 4095)&& ( pow(2,2) <= (frame_no * 8) )){
	return ( ((uint16_t)(2) <<12 ) | bsel[9] );
}
	if (( diff_baud_rate[10] <=diff_baud_rate[0] ) && (diff_baud_rate[10] <=diff_baud_rate[1] )  && (diff_baud_rate[10] <=diff_baud_rate[2] ) && (diff_baud_rate[10] <=diff_baud_rate[3] ) && (diff_baud_rate[10] <=diff_baud_rate[4] )&& (diff_baud_rate[10] <=diff_baud_rate[5] )&& (diff_baud_rate[10] <=diff_baud_rate[6] )&& (diff_baud_rate[10] <=diff_baud_rate[7] )&& (diff_baud_rate[10] <=diff_baud_rate[8] )&& (diff_baud_rate[10] <=diff_baud_rate[9] )&& (diff_baud_rate[10] <=diff_baud_rate[11] )&& (diff_baud_rate[10] <=diff_baud_rate[12] )&& (diff_baud_rate[10] <=diff_baud_rate[13] )&& (diff_baud_rate[10] <=diff_baud_rate[14] ) && ( bsel[10] <= 4095)&& ( pow(2,3) <= (frame_no * 8) )){
	return ( ((uint16_t)(3) <<12 ) | bsel[10] );
}
	if (( diff_baud_rate[11] <=diff_baud_rate[0] ) && (diff_baud_rate[11] <=diff_baud_rate[1] )  && (diff_baud_rate[11] <=diff_baud_rate[2] ) && (diff_baud_rate[11] <=diff_baud_rate[3] ) && (diff_baud_rate[11] <=diff_baud_rate[4] )&& (diff_baud_rate[11] <=diff_baud_rate[5] )&& (diff_baud_rate[11] <=diff_baud_rate[6] )&& (diff_baud_rate[11] <=diff_baud_rate[7] )&& (diff_baud_rate[11] <=diff_baud_rate[8] )&& (diff_baud_rate[11] <=diff_baud_rate[9] )&& (diff_baud_rate[11] <=diff_baud_rate[10] )&& (diff_baud_rate[11] <=diff_baud_rate[12] )&& (diff_baud_rate[11] <=diff_baud_rate[13] )&& (diff_baud_rate[11] <=diff_baud_rate[14] ) && ( bsel[11] <= 4095)&& ( pow(2,4) <= (frame_no * 8) )){
	return ( ((uint16_t)(4) <<12 ) | bsel[11] );
}
	if (( diff_baud_rate[12] <=diff_baud_rate[0] ) && (diff_baud_rate[12] <=diff_baud_rate[1] )  && (diff_baud_rate[12] <=diff_baud_rate[2] ) && (diff_baud_rate[12] <=diff_baud_rate[3] ) && (diff_baud_rate[12] <=diff_baud_rate[4] )&& (diff_baud_rate[12] <=diff_baud_rate[5] )&& (diff_baud_rate[12] <=diff_baud_rate[6] )&& (diff_baud_rate[12] <=diff_baud_rate[7] )&& (diff_baud_rate[12] <=diff_baud_rate[8] )&& (diff_baud_rate[12] <=diff_baud_rate[9] )&& (diff_baud_rate[12] <=diff_baud_rate[10] )&& (diff_baud_rate[12] <=diff_baud_rate[11] )&& (diff_baud_rate[12] <=diff_baud_rate[13] )&& (diff_baud_rate[12] <=diff_baud_rate[14] ) && ( bsel[12] <= 4095)&& ( pow(2,5) <= (frame_no * 8) )){
	return ( ((uint16_t)(5) <<12 ) | bsel[12] );
}				
	if (( diff_baud_rate[13] <=diff_baud_rate[0] ) && (diff_baud_rate[13] <=diff_baud_rate[1] )  && (diff_baud_rate[13] <=diff_baud_rate[2] ) && (diff_baud_rate[13] <=diff_baud_rate[3] ) && (diff_baud_rate[13] <=diff_baud_rate[4] )&& (diff_baud_rate[13] <=diff_baud_rate[5] )&& (diff_baud_rate[13] <=diff_baud_rate[6] )&& (diff_baud_rate[13] <=diff_baud_rate[7] )&& (diff_baud_rate[13] <=diff_baud_rate[8] )&& (diff_baud_rate[13] <=diff_baud_rate[9] )&& (diff_baud_rate[13] <=diff_baud_rate[10] )&& (diff_baud_rate[13] <=diff_baud_rate[11] )&& (diff_baud_rate[13] <=diff_baud_rate[12] )&& (diff_baud_rate[13] <=diff_baud_rate[14] ) && ( bsel[13] <= 4095)&& ( pow(2,6) <= (frame_no * 8) )){
	return ( ((uint16_t)(6) <<12 ) | bsel[13] );
}		
	if (( diff_baud_rate[14] <=diff_baud_rate[0] ) && (diff_baud_rate[14] <=diff_baud_rate[1] )  && (diff_baud_rate[14] <=diff_baud_rate[2] ) && (diff_baud_rate[14] <=diff_baud_rate[3] ) && (diff_baud_rate[14] <=diff_baud_rate[4] )&& (diff_baud_rate[14] <=diff_baud_rate[5] )&& (diff_baud_rate[14] <=diff_baud_rate[6] )&& (diff_baud_rate[14] <=diff_baud_rate[7] )&& (diff_baud_rate[14] <=diff_baud_rate[8] )&& (diff_baud_rate[14] <=diff_baud_rate[9] )&& (diff_baud_rate[14] <=diff_baud_rate[10] )&& (diff_baud_rate[14] <=diff_baud_rate[11] )&& (diff_baud_rate[14] <=diff_baud_rate[12] )&& (diff_baud_rate[14] <=diff_baud_rate[13] ) && ( bsel[14] <= 4095)&& ( pow(2,7) <= (frame_no * 8) )){
	return ( ((uint16_t)(7) <<12 ) | bsel[14] );		
}
	return BAUD_ERR_VAL ;
}


// Protos 

/**Description : UART pin initialization for the atxmega32a4 , this is not compatible with other micros ,
 * this function will initialize and set the pins directions for the uart module chosen.
 * this function doesn't initialize XCK pins as it is meant for asynchronous usage of the module.
 * * Note : Use this USART asynch modes .
 * 
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void.
 * */
 
void uart_port_asynch_xmega32a4 ( USART_t* usart_port ) ; 

/**Description : UART pin initialization for the atxmega32a4 , this is not compatible with other micros ,
 * this function will initialize and set the pins directions for the uart module chosen.
 * this function initializes XCK pins as it is meant for synchronous usage of the module.
 * Note : Use this in SPI or USART synch modes .
 * 
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void.
 * */


void uart_port_synch_xmega32a4 ( USART_t* usart_port );

/** Description : Initializes the uart module pointed to by usart_port , with the frame configuartion in frame_config
 * and the baud rate given by baud_select , in double speed or normal speed , u2x = 1 , u2x = 0 , respectively.
 * The module is initialized as an asynchronous full duplex transceiver.
 * 
 * @param baud_select : 16 bit prescaler values obtained from baud_calc.
 * @param u2x : double speed selection (u2x = 1 ) , normal speed ( u2x = 0 ) , must match the u2x in baud_calc() function.
 * @param frame_config : one of the many frame configuration available in frame_mode enum.
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void.
 * */

void uart_asynch_init ( uint16_t baud_select ,  uint8_t u2x, frame_mode frame_config , USART_t * usart_port ) ;

/** Description : Initializes the uart module pointed to by usart_port , with the frame configuartion in frame_config
 * and the baud rate given by baud_select , in double speed or normal speed , u2x = 1 , u2x = 0 , respectively.
 * The module is initialized as a Synchronous full duplex transceiver.
 * 
 * @param baud_select : 16 bit prescaler values obtained from baud_calc.
 * @param u2x : double speed selection (u2x = 1 ) , normal speed ( u2x = 0 ) , must match the u2x in baud_calc() function.
 * @param frame_config : one of the many frame configuration available in frame_mode enum.
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void.
 * */

void uart_synch_init (uint16_t baud_select ,  uint8_t u2x, frame_mode frame_config , USART_t * usart_port );

/** Description : Initializes the uart module pointed to by usart_port with (MOSI/MISO/XCK ) lines are used.
 * the baud rate given by baud_select , in double speed or normal speed , u2x = 1 , u2x = 0 , respectively.
 * The module is initialized in FULL DUPLEX MASTER SPI MODE ( 8 BITS - MSB FIRST - POSITIVE CLOCK POLARITY ).
 * 
 * @param baud_select : 16 bit prescaler values obtained from baud_calc.
 * @param u2x : double speed selection (u2x = 1 ) , normal speed ( u2x = 0 ) , must match the u2x in baud_calc() function.
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void.
 * */

void uart_mspi_init( uint16_t baud_select ,  uint8_t u2x , USART_t * usart_port ) ;


/** Description : Initializes the uart module pointed to by usart_port with ONLY ( MOSI / XCK ) lines are used.
 * the baud rate given by baud_select , in double speed or normal speed , u2x = 1 , u2x = 0 , respectively.
 * The module is initialized in HALF SIMPLEX MASTER SPI MODE ( 8 BITS - MSB FIRST - POSITIVE CLOCK POLARITY ).
 * 
 * @param baud_select : 16 bit prescaler values obtained from baud_calc.
 * @param u2x : double speed selection (u2x = 1 ) , normal speed ( u2x = 0 ) , must match the u2x in baud_calc() function.
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void.
 * */

void uart_mspi_2wire_init( uint16_t baud_select ,  uint8_t u2x , USART_t * usart_port ) ;

/** Description : Completely Disables UART Module pointed to by usart_port .
 * 
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void.
 * */
 
void uart_disable ( USART_t* usart_port ) ;

/** Description : Sets the interrupt for the USART Module , RXC interrupt level is given by rxc_int , same for TXC , DRE interrupts.
 * 
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * @param txc_int    : TXC interrupt level .
 * @param rxc_int    : RXC interrupt level .
 * @param dre_in     : DRE interrupt level .
 * 
 * @retval : void.
 * */

void uart_interrupt_set( int_level txc_int , int_level rxc_int , int_level dre_int , USART_t* usart_port );

/** Description : This function transmits a byte given by argument 'byte' , using USART module given by usart_port
 * This Transmit function is blocking .
 * 
 * @param byte : data to be transmitted.
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void 
 * */

void uartb_transmit ( uint8_t byte , USART_t* usart_port )  ;

/** Description : This function BLOCKS until a byte is read from the usart module pointed to by usart_port .
 * 
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval uint8_t : byte read from the receive buffer. 
 * 
 * */

uint8_t uartb_receive ( USART_t* usart_port ) ;

/** Description : This function transmits a byte and receives a byte  This should be used in MASTER SPI MODE only .
 * NOTE : this function should only be used when in MASTER SPI Mode 
 * 
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * @param byte : 8 bit value to be transmitted.
 * 
 * @retval uint8_t : byte read from the receive buffer. 
 * 
 * */

uint8_t uartb_transceive ( uint8_t byte ,USART_t* usart_port );

/** Description : This function transmits a byte given by argument 'byte' , using USART module given by usart_port
 * This Transmit function is NON BLOCKING.
 * 
 * @param byte : data to be transmitted.
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void 
 * */
uint8_t uartnb_transmit( uint8_t byte , USART_t* usart_port ) ;

/** Description : This function  reads a byte from the usart module pointed to by usart_port .
 * NOTE : This function is NON-BLOCKING.
 * 
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval -1 : Receive buffer is empty.
 * @retval any value other than -1 : take the 8 LS bits , this is the received byte .
 * 
 * */

int16_t uartnb_receive ( USART_t* usart_port );


/** Description : prints a null terminated string , using BLOCKING CALLS.
 * 
 * @param buff : pointer to the buffer .
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void.
 * 
 * */

void uart_print ( uint8_t* buff  , USART_t* usart_port );

/** Description : sends an array , byte by byte from 0 >> len , using BLOCKING CALLS.
 * 
 * @param buff : pointer to the buffer .
 * @param len  : number of bytes to write from the buffer.
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void.
 * 
 * */


void uart_transmit_array ( uint8_t* buff , uint16_t len , USART_t* usart_port ) ;

/** Description : prints a Numeric value by converting into ASCII first.
 * 
 * @param val : numeric value to be printed.
 * @param base: base of the format you want printed , 2 binary , `16 hex  and so on .
 * @param termination : character to be printed at the end of the value printed , use 0 if no terminating character is wanted.
 * @param usart_port : pointer to the usart module used ex : ( USARTE0 , USARTC0 , USARTC1 ... ).
 * 
 * @retval : void.
 * 
 * */

void uart_print_num ( int32_t val  , uint8_t base  , uint8_t termination , USART_t* usart_port );


/** Description : This call completely intializes USARTE0 for debugging .
 * NOTE : it is Initialized at 9600 BPS , 8 BIT DATA , 10 BIT FRAME , NO PARITY , 1 STOP BIT .
 * NOTE : this call also initializes the pins needed to be initialized and prints a debug message so you can test your micro.
 * NOTE : this function assumes no prescalers are used , and assumes its CLOCK to be the default internal 2MHZ RC oscillator.
 * */
 
void uart_debug_9600 ( void );

/** Description : The following calls are used on the module that has its ring buffer enabled 
 * to Enable a ring buffer simple #define USARTXX_RING anywhere the header file can see it , mainly in the uart.h , or header.h .
 */
 
 
 /** Description : writes data pointed to by data_ptr , with length of len , on the ring buffer given by ring_buff
  * @param ring_buff : can be one of the following ( USARTC0_RING, USARTC1_RING , USARTD0_RING , USARTD1_RING , USARTE0_RING ).
  * @param data_ptr  : pointer to the data to be transmitted .
  * @param len       : number of bytes to write .
  * @retval -2       : ring buffer is not enabled for the module .
  * @retval -1       : buffer doesn't have free ( len ) of bytes or the buffer is full .
  * @retval  1       : successfully written to the fifo.
  * */

int16_t uart_write( uint8_t ring_buff , uint8_t* data_ptr , uint16_t len  );

 /** Description : this function returns a single byte from the fifo buffer .
  * @param ring_buff : can be one of the following ( USARTC0_RING, USARTC1_RING , USARTD0_RING , USARTD1_RING , USARTE0_RING ).
  * @retval -2       : ring buffer is not enabled for the module .
  * @retval -1       : buffer is empty .
  * @retval  bytes   : returns the byte from the fifo.
  * */


int16_t uart_get( uint8_t ring_buff );

 /** Description : this function returns len' length bytes from the fifo buffer .
  * @param ring_buff : can be one of the following ( USARTC0_RING, USARTC1_RING , USARTD0_RING , USARTD1_RING , USARTE0_RING ).
  * @param ptr       : pointer to a buffer that will store the data.
  * @param len       : number of bytes to wait for .
  * @retval -2       : ring buffer is not enabled for the module .
  * @retval -1       : buffer is empty .
  * @retval  1       : successfully written (len) bytes into ptr.
  * */


int16_t uart_bget ( uint8_t ring_buff , uint8_t * ptr , uint16_t len );

 /** Description : writes data pointed to by data_ptr , with length of len , on the ring buffer given by ring_buff
  * NOTE : this function is the same as uart_write() but this one blocks until the data is completely shifted out of the buffer.
  * @param ring_buff : can be one of the following ( USARTC0_RING, USARTC1_RING , USARTD0_RING , USARTD1_RING , USARTE0_RING ).
  * @param data_ptr  : pointer to the data to be transmitted .
  * @param len       : number of bytes to write .
  * @retval -2       : ring buffer is not enabled for the module .
  * @retval -1       : buffer doesn't have free ( len ) of bytes or the buffer is empty.
  * @retval  1       : successfully written to the fifo.
  * */

int16_t uart_bwrite( uint8_t ring_buff , uint8_t* data_ptr , uint16_t len  );

/** Description : This function returns the number of bytes currently in the receive buffer ( received bytes number ).
  * @param ring_buff : can be one of the following ( USARTC0_RING, USARTC1_RING , USARTD0_RING , USARTD1_RING , USARTE0_RING ).
  * @retval -2       : no ring buffer is enabled for the module chosen.
  * @retval byte_num : returns the number of bytes in the receive buffer. 
*/

int16_t get_rx_numbytes ( uint8_t ring_buff );

/** Description : This function returns the number of free bytes ( free space ) in the tx buffer.
  * @param ring_buff : can be one of the following ( USARTC0_RING, USARTC1_RING , USARTD0_RING , USARTD1_RING , USARTE0_RING ).
  * @retval -2       : no ring buffer is enabled for the module chosen.
  * @retval byte_num : returns the number of free bytes in the tx buffer. 
*/

int16_t get_tx_numbytes ( uint8_t ring_buff );


int16_t flush_rx_buff ( uint8_t ring_buff );

#endif
