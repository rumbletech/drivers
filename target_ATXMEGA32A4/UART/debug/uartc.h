/** @file uart.h
 * Author : Mohamed Yousry Mohamed Rashad 
 * 
 * 
 * File Discription : This header file contains baud rate definitions and externs for calls used for initialization , transmit and receive
 * functions of the usart module . 
 * 
 * 
 */

//#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
//#include "../GPIO/GPIO.h"


#ifndef F_CPU 
#error " F_CPU is not defined for the uart module for baud rate settings "
#endif

#define BAUD_ERR_VAL (uint16_t)0XFFFF


#define bsel_eval_gtz(baud,bscale , f_perph , u2x) (( f_perph ) / ( pow(2,bscale) * (u2x?8.0:16.0) * baud)) -1
#define baud_eval_gtz(bsel,bscale , f_perph , u2x) (( f_perph ) / ( pow(2,bscale) * (u2x?8.0:16.0) * (bsel +1 ) ) )



#define baud_eval_ltz(bsel,bscale , f_perph ,u2x) (( f_perph) / ( (u2x?8.0:16.0) * ( (pow(2,bscale) * bsel ) + 1 ) ) )
#define bsel_eval_ltz(baud,bscale , f_perph ,u2x) ( ( 1.0 / pow(2,bscale) ) * ( ( f_perph / ( (u2x?8.0:16.0) * baud ) ) -1) )




static inline uint16_t baud_calc ( uint32_t baud_rate , uint32_t f_perph ,uint8_t data_numbits ,uint8_t u2x ) {
	
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
	
	diff_baud_rate[0] = abs(prev_baud_rate[0] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[0] ); 
	diff_baud_rate[1] = abs(prev_baud_rate[1] - baud_rate) ;  
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[1] ); 
	diff_baud_rate[2] = abs(prev_baud_rate[2] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[2] );   
	diff_baud_rate[3] = abs(prev_baud_rate[3] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[3] );  
	diff_baud_rate[4] = abs(prev_baud_rate[4] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[4] );   
	diff_baud_rate[5] = abs(prev_baud_rate[5] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[5] );  
	diff_baud_rate[6] = abs(prev_baud_rate[6] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[6] );   
	diff_baud_rate[7] = abs(prev_baud_rate[7] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[7] );   
	diff_baud_rate[8] = abs(prev_baud_rate[8] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[8] );  
	diff_baud_rate[9] = abs(prev_baud_rate[9] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[9] );  
	diff_baud_rate[10] = abs(prev_baud_rate[10] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[10] );   
	diff_baud_rate[11] = abs(prev_baud_rate[11] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[11] );   
	diff_baud_rate[12] = abs(prev_baud_rate[12] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[12] );   
	diff_baud_rate[13] = abs(prev_baud_rate[13] - baud_rate) ;
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[13] );   
	diff_baud_rate[14] = abs(prev_baud_rate[14] - baud_rate) ;  
	printf("baud_diff_0 : %lf\n" , diff_baud_rate[14] ); 
	
	if( ( baud_rate == ( f_perph / 16 ) ) && !u2x )
	return 0 ;
	if ( ( baud_rate == ( f_perph / 8 ) ) && u2x )
	return 0 ;  
	if( ( baud_rate > ( f_perph / 16 ) ) && !u2x )
	return BAUD_ERR_VAL;
	if( ( baud_rate > ( f_perph / 8 ) ) && u2x   )
	return BAUD_ERR_VAL;
	if (( diff_baud_rate[0] <= diff_baud_rate[1] ) && (diff_baud_rate[0] <= diff_baud_rate[2] )  && (diff_baud_rate[0] <= diff_baud_rate[3] ) && (diff_baud_rate[0] <= diff_baud_rate[4] ) && (diff_baud_rate[0] <= diff_baud_rate[5] )&& (diff_baud_rate[0] <= diff_baud_rate[6] )&& (diff_baud_rate[0] <=diff_baud_rate[7] )&& (diff_baud_rate[0] <=diff_baud_rate[8] )&& (diff_baud_rate[0] <=diff_baud_rate[9] )&& (diff_baud_rate[0] <=diff_baud_rate[10] )&& (diff_baud_rate[0] <=diff_baud_rate[11] )&& (diff_baud_rate[0] <=diff_baud_rate[12] )&& (diff_baud_rate[0] <=diff_baud_rate[13] )&& (diff_baud_rate[0] <=diff_baud_rate[14] ) && ( bsel[0] <= 4095) ){
	return ( ((uint16_t)(-7) <<12 ) | bsel[0] );
}
	if (( diff_baud_rate[1] <= diff_baud_rate[0] ) && (diff_baud_rate[1] <= diff_baud_rate[2] )  && (diff_baud_rate[1] <= diff_baud_rate[3] ) && (diff_baud_rate[1] <= diff_baud_rate[4] ) && (diff_baud_rate[1] <= diff_baud_rate[5] )&& (diff_baud_rate[1] <= diff_baud_rate[6] )&& (diff_baud_rate[1] <= diff_baud_rate[7] )&& (diff_baud_rate[1] <= diff_baud_rate[8] )&& (diff_baud_rate[1] <= diff_baud_rate[9] )&& (diff_baud_rate[1] <= diff_baud_rate[10] )&& (diff_baud_rate[1] <= diff_baud_rate[11] )&& (diff_baud_rate[1] <= diff_baud_rate[12] )&& (diff_baud_rate[1] <= diff_baud_rate[13] )&& (diff_baud_rate[1] <= diff_baud_rate[14] ) && ( bsel[1] <= 4095)) {
	return ( ((uint16_t)(-6) <<12 ) | bsel[1] );
}
	if (( diff_baud_rate[2] <=diff_baud_rate[0] ) && (diff_baud_rate[2] <=diff_baud_rate[1] )  && (diff_baud_rate[2] <=diff_baud_rate[3] ) && (diff_baud_rate[2] <=diff_baud_rate[4] ) && (diff_baud_rate[2] <=diff_baud_rate[5] )&& (diff_baud_rate[2] <=diff_baud_rate[6] )&& (diff_baud_rate[2] <=diff_baud_rate[7] )&& (diff_baud_rate[2] <=diff_baud_rate[8] )&& (diff_baud_rate[2] <=diff_baud_rate[9] )&& (diff_baud_rate[2] <=diff_baud_rate[10] )&& (diff_baud_rate[2] <=diff_baud_rate[11] )&& (diff_baud_rate[2] <=diff_baud_rate[12] )&& (diff_baud_rate[2] <=diff_baud_rate[13] )&& (diff_baud_rate[2] <=diff_baud_rate[14] ) && ( bsel[2] <= 4095)){
	return ( ((uint16_t)(-5) <<12 ) | bsel[2] );
}
	if (( diff_baud_rate[3] <=diff_baud_rate[0] ) && (diff_baud_rate[3] <=diff_baud_rate[1] )  && (diff_baud_rate[3] <=diff_baud_rate[2] ) && (diff_baud_rate[3] <=diff_baud_rate[4] ) && (diff_baud_rate[3] <=diff_baud_rate[5] )&& (diff_baud_rate[3] <=diff_baud_rate[6] )&& (diff_baud_rate[3] <=diff_baud_rate[7] )&& (diff_baud_rate[3] <=diff_baud_rate[8] )&& (diff_baud_rate[3] <=diff_baud_rate[9] )&& (diff_baud_rate[3] <=diff_baud_rate[10] )&& (diff_baud_rate[3] <=diff_baud_rate[11] )&& (diff_baud_rate[3] <=diff_baud_rate[12] )&& (diff_baud_rate[3] <=diff_baud_rate[13] )&& (diff_baud_rate[3] <=diff_baud_rate[14] ) && ( bsel[3] <= 4095)){
	return ( ((uint16_t)(-4) <<12 ) | bsel[3] );
}	
	if (( diff_baud_rate[4] <=diff_baud_rate[0] ) && (diff_baud_rate[4] <=diff_baud_rate[1] )  && (diff_baud_rate[4] <=diff_baud_rate[2] ) && (diff_baud_rate[4] <=diff_baud_rate[3] ) && (diff_baud_rate[4] <=diff_baud_rate[5] )&& (diff_baud_rate[4] <=diff_baud_rate[6] )&& (diff_baud_rate[4] <=diff_baud_rate[7] )&& (diff_baud_rate[4] <=diff_baud_rate[8] )&& (diff_baud_rate[4] <=diff_baud_rate[9] )&& (diff_baud_rate[4] <=diff_baud_rate[10] )&& (diff_baud_rate[4] <=diff_baud_rate[11] )&& (diff_baud_rate[4] <=diff_baud_rate[12] )&& (diff_baud_rate[4] <=diff_baud_rate[13] )&& (diff_baud_rate[4] <=diff_baud_rate[14] ) && ( bsel[4] <= 4095)){
	return ( ((uint16_t)(-3) <<12 ) | bsel[4] );
}
	if (( diff_baud_rate[5] <=diff_baud_rate[0] ) && (diff_baud_rate[5] <=diff_baud_rate[1] )  && (diff_baud_rate[5] <=diff_baud_rate[2] ) && (diff_baud_rate[5] <=diff_baud_rate[3] ) && (diff_baud_rate[5] <=diff_baud_rate[4] )&& (diff_baud_rate[5] <=diff_baud_rate[6] )&& (diff_baud_rate[5] <=diff_baud_rate[7] )&& (diff_baud_rate[5] <=diff_baud_rate[8] )&& (diff_baud_rate[5] <=diff_baud_rate[9] )&& (diff_baud_rate[5] <=diff_baud_rate[10] )&& (diff_baud_rate[5] <=diff_baud_rate[11] )&& (diff_baud_rate[5] <=diff_baud_rate[12] )&& (diff_baud_rate[5] <=diff_baud_rate[13] )&& (diff_baud_rate[5] <=diff_baud_rate[14] ) && ( bsel[5] <= 4095)){
	return ( ((uint16_t)(-2) <<12 ) | bsel[5] );
}
	if (( diff_baud_rate[6] <=diff_baud_rate[0] ) && (diff_baud_rate[6] <=diff_baud_rate[1] )  && (diff_baud_rate[6] <=diff_baud_rate[2] ) && (diff_baud_rate[6] <=diff_baud_rate[3] ) && (diff_baud_rate[6] <=diff_baud_rate[4] )&& (diff_baud_rate[6] <=diff_baud_rate[5] )&& (diff_baud_rate[6] <=diff_baud_rate[7] )&& (diff_baud_rate[6] <=diff_baud_rate[8] )&& (diff_baud_rate[6] <=diff_baud_rate[9] )&& (diff_baud_rate[6] <=diff_baud_rate[10] )&& (diff_baud_rate[6] <=diff_baud_rate[11] )&& (diff_baud_rate[6] <=diff_baud_rate[12] )&& (diff_baud_rate[6] <=diff_baud_rate[13] )&& (diff_baud_rate[6] <=diff_baud_rate[14] ) && ( bsel[6] <= 4095)){
	return ( ((uint16_t)(-1) <<12 ) | bsel[6] );
}
	if (( diff_baud_rate[7] <=diff_baud_rate[0] ) && (diff_baud_rate[7] <=diff_baud_rate[1] )  && (diff_baud_rate[7] <=diff_baud_rate[2] ) && (diff_baud_rate[7] <=diff_baud_rate[3] ) && (diff_baud_rate[7] <=diff_baud_rate[4] )&& (diff_baud_rate[7] <=diff_baud_rate[5] )&& (diff_baud_rate[7] <=diff_baud_rate[6] )&& (diff_baud_rate[7] <=diff_baud_rate[8] )&& (diff_baud_rate[7] <=diff_baud_rate[9] )&& (diff_baud_rate[7] <=diff_baud_rate[10] )&& (diff_baud_rate[7] <=diff_baud_rate[11] )&& (diff_baud_rate[7] <=diff_baud_rate[12] )&& (diff_baud_rate[7] <=diff_baud_rate[13] )&& (diff_baud_rate[7] <=diff_baud_rate[14] ) && ( bsel[7] <= 4095)){
	return ( ((uint16_t)(0) <<12 ) | bsel[7] );
}
	if (( diff_baud_rate[8] <=diff_baud_rate[0] ) && (diff_baud_rate[8] <=diff_baud_rate[1] )  && (diff_baud_rate[8] <=diff_baud_rate[2] ) && (diff_baud_rate[8] <=diff_baud_rate[3] ) && (diff_baud_rate[8] <=diff_baud_rate[4] )&& (diff_baud_rate[8] <=diff_baud_rate[5] )&& (diff_baud_rate[8] <=diff_baud_rate[6] )&& (diff_baud_rate[8] <=diff_baud_rate[7] )&& (diff_baud_rate[8] <=diff_baud_rate[9] )&& (diff_baud_rate[8] <=diff_baud_rate[10] )&& (diff_baud_rate[8] <=diff_baud_rate[11] )&& (diff_baud_rate[8] <=diff_baud_rate[12] )&& (diff_baud_rate[8] <=diff_baud_rate[13] )&& (diff_baud_rate[8] <=diff_baud_rate[14] ) && ( bsel[8] <= 4095)){
	return ( ((uint16_t)(1) <<12 ) | bsel[8] );
}
	if (( diff_baud_rate[9] <=diff_baud_rate[0] ) && (diff_baud_rate[9] <=diff_baud_rate[1] )  && (diff_baud_rate[9] <=diff_baud_rate[2] ) && (diff_baud_rate[9] <=diff_baud_rate[3] ) && (diff_baud_rate[9] <=diff_baud_rate[4] )&& (diff_baud_rate[9] <=diff_baud_rate[5] )&& (diff_baud_rate[9] <=diff_baud_rate[6] )&& (diff_baud_rate[9] <=diff_baud_rate[7] )&& (diff_baud_rate[9] <=diff_baud_rate[8] )&& (diff_baud_rate[9] <=diff_baud_rate[10] )&& (diff_baud_rate[9] <=diff_baud_rate[11] )&& (diff_baud_rate[9] <=diff_baud_rate[12] )&& (diff_baud_rate[9] <=diff_baud_rate[13] )&& (diff_baud_rate[9] <=diff_baud_rate[14] ) && ( bsel[9] <= 4095)){
	return ( ((uint16_t)(2) <<12 ) | bsel[9] );
}
	if (( diff_baud_rate[10] <=diff_baud_rate[0] ) && (diff_baud_rate[10] <=diff_baud_rate[1] )  && (diff_baud_rate[10] <=diff_baud_rate[2] ) && (diff_baud_rate[10] <=diff_baud_rate[3] ) && (diff_baud_rate[10] <=diff_baud_rate[4] )&& (diff_baud_rate[10] <=diff_baud_rate[5] )&& (diff_baud_rate[10] <=diff_baud_rate[6] )&& (diff_baud_rate[10] <=diff_baud_rate[7] )&& (diff_baud_rate[10] <=diff_baud_rate[8] )&& (diff_baud_rate[10] <=diff_baud_rate[9] )&& (diff_baud_rate[10] <=diff_baud_rate[11] )&& (diff_baud_rate[10] <=diff_baud_rate[12] )&& (diff_baud_rate[10] <=diff_baud_rate[13] )&& (diff_baud_rate[10] <=diff_baud_rate[14] ) && ( bsel[10] <= 4095)){
	return ( ((uint16_t)(3) <<12 ) | bsel[10] );
}
	if (( diff_baud_rate[11] <=diff_baud_rate[0] ) && (diff_baud_rate[11] <=diff_baud_rate[1] )  && (diff_baud_rate[11] <=diff_baud_rate[2] ) && (diff_baud_rate[11] <=diff_baud_rate[3] ) && (diff_baud_rate[11] <=diff_baud_rate[4] )&& (diff_baud_rate[11] <=diff_baud_rate[5] )&& (diff_baud_rate[11] <=diff_baud_rate[6] )&& (diff_baud_rate[11] <=diff_baud_rate[7] )&& (diff_baud_rate[11] <=diff_baud_rate[8] )&& (diff_baud_rate[11] <=diff_baud_rate[9] )&& (diff_baud_rate[11] <=diff_baud_rate[10] )&& (diff_baud_rate[11] <=diff_baud_rate[12] )&& (diff_baud_rate[11] <=diff_baud_rate[13] )&& (diff_baud_rate[11] <=diff_baud_rate[14] ) && ( bsel[11] <= 4095)){
	return ( ((uint16_t)(4) <<12 ) | bsel[11] );
}
	if (( diff_baud_rate[12] <=diff_baud_rate[0] ) && (diff_baud_rate[12] <=diff_baud_rate[1] )  && (diff_baud_rate[12] <=diff_baud_rate[2] ) && (diff_baud_rate[12] <=diff_baud_rate[3] ) && (diff_baud_rate[12] <=diff_baud_rate[4] )&& (diff_baud_rate[12] <=diff_baud_rate[5] )&& (diff_baud_rate[12] <=diff_baud_rate[6] )&& (diff_baud_rate[12] <=diff_baud_rate[7] )&& (diff_baud_rate[12] <=diff_baud_rate[8] )&& (diff_baud_rate[12] <=diff_baud_rate[9] )&& (diff_baud_rate[12] <=diff_baud_rate[10] )&& (diff_baud_rate[12] <=diff_baud_rate[11] )&& (diff_baud_rate[12] <=diff_baud_rate[13] )&& (diff_baud_rate[12] <=diff_baud_rate[14] ) && ( bsel[12] <= 4095)){
	return ( ((uint16_t)(5) <<12 ) | bsel[12] );
}				
	if (( diff_baud_rate[13] <=diff_baud_rate[0] ) && (diff_baud_rate[13] <=diff_baud_rate[1] )  && (diff_baud_rate[13] <=diff_baud_rate[2] ) && (diff_baud_rate[13] <=diff_baud_rate[3] ) && (diff_baud_rate[13] <=diff_baud_rate[4] )&& (diff_baud_rate[13] <=diff_baud_rate[5] )&& (diff_baud_rate[13] <=diff_baud_rate[6] )&& (diff_baud_rate[13] <=diff_baud_rate[7] )&& (diff_baud_rate[13] <=diff_baud_rate[8] )&& (diff_baud_rate[13] <=diff_baud_rate[9] )&& (diff_baud_rate[13] <=diff_baud_rate[10] )&& (diff_baud_rate[13] <=diff_baud_rate[11] )&& (diff_baud_rate[13] <=diff_baud_rate[12] )&& (diff_baud_rate[13] <=diff_baud_rate[14] ) && ( bsel[13] <= 4095)){
	return ( ((uint16_t)(6) <<12 ) | bsel[13] );
}		
	if (( diff_baud_rate[14] <=diff_baud_rate[0] ) && (diff_baud_rate[14] <=diff_baud_rate[1] )  && (diff_baud_rate[14] <=diff_baud_rate[2] ) && (diff_baud_rate[14] <=diff_baud_rate[3] ) && (diff_baud_rate[14] <=diff_baud_rate[4] )&& (diff_baud_rate[14] <=diff_baud_rate[5] )&& (diff_baud_rate[14] <=diff_baud_rate[6] )&& (diff_baud_rate[14] <=diff_baud_rate[7] )&& (diff_baud_rate[14] <=diff_baud_rate[8] )&& (diff_baud_rate[14] <=diff_baud_rate[9] )&& (diff_baud_rate[14] <=diff_baud_rate[10] )&& (diff_baud_rate[14] <=diff_baud_rate[11] )&& (diff_baud_rate[14] <=diff_baud_rate[12] )&& (diff_baud_rate[14] <=diff_baud_rate[13] ) && ( bsel[14] <= 4095)){
	return ( ((uint16_t)(7) <<12 ) | bsel[14] );		
}
	return BAUD_ERR_VAL ;
}







//#if defined(F_CPU == 32000000UL)

//#define 

