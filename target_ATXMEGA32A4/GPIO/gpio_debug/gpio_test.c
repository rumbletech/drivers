


#include "../GPIO.h"
#include <util/delay.h>
#include "../../SYSCLK/sysclk.h"


//avr-gcc -Os -mmcu=atxmega32a4 -o gpio_test.o gpio_test.c; avr-objcopy -O ihex gpio_test.o gpio_test.hex; sudo avrdude -p ATXMEGA32A4 -c avrispmkII -P usb -U flash:w:gpio_test.hex




int main (void) { 
	
	//system clock startup with dfll , nolock , no prescalers , internal 32 MHZ
	startup_int_nolock( RC32MHZ , PSCA_DIV1 | PSCBC_DIV1_1 );
	// pin 2 output , totempole
	pin_config( 2 ,&PORTD , OUTPUT, TOTEMPOLE_Z , SENSE_BOTH_EDGES ) ;
	
	
	
	
	while(1){
	
	pin_set( 2 , &PORTD ) ;
	_delay_ms(5000);
	pin_clear( 2 , &PORTD ) ;
	_delay_ms(5000);
	

	
}

}
