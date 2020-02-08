

#include "../uart.h"
#define F_CPU 2000000
#include <util/delay.h>




int main( void ) {
	
	
	//startup_int_nolock( RC32MHZ , PSCA_DIV1 | PSCBC_DIV1_1 ) ; // init system clock
	//uart_port_asynch_xmega32a4( &USARTE0 );
	//uart_asynch_init ( baud_calc(19200,32000000,8,0) , 0 ,PARITY_DISABLED_1SB_8B , &USARTE0); 
	uart_debug_9600();
	
	while(1){
		
		uart_print_num( 128 , 10 ,'\n'  , &USARTE0 ) ;
		_delay_ms(3000);
		uart_print("my  nigga\n"  , &USARTE0 ) ;
		_delay_ms(3000);		
		}
	
	
	
	
	
}
