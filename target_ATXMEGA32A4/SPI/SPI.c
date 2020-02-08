










#include "SPI.h"






int16_t SPI_Init( SPI_Init_Struct spi_struct ) {
	
	
	//Assert checking should be put here
	 
	// end here
	
	//Check SPI Module 
	
	#if defined(__AVR_ATxmega32A4__)
	
	if ( spi_struct.SPI_module == &SPIC && spi_struct.SPI_mode == SPI_MASTER ){
		
		
		pin_config( SPIC_MOSI , &PORTC , OUTPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES);
		pin_config( SPIC_SCK, &PORTC , OUTPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES  );
		pin_config( SPIC_MISO,&PORTC , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES ) ;

		
	}
	else if ( spi_struct.SPI_module == &SPIC && spi_struct.SPI_mode == SPI_SLAVE ){
		
		pin_config( SPIC_MOSI , &PORTC , INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES);
		pin_config( SPIC_SCK, &PORTC , INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES  );
		pin_config( SPIC_MISO,&PORTC , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES ) ;
		pin_config( SPIC_SS , &PORTC , INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES);
		
		
	}
	
	
	else if (spi_struct.SPI_module == &SPID && spi_struct.SPI_mode == SPI_MASTER){
		
		pin_config( SPID_MOSI , &PORTD , OUTPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES);
		pin_config( SPID_SCK, &PORTD , OUTPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES  );
		pin_config( SPID_MISO,&PORTD , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES ) ;
		
		
	}
	
	
	
	else if ( spi_struct.SPI_module ==&SPID && spi_struct.SPI_mode == SPI_SLAVE) {
		
		
		pin_config( SPID_MOSI , &PORTD , INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES);
		pin_config( SPID_SCK, &PORTD , INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES  );
		pin_config( SPID_MISO,&PORTD , OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES ) ;
		pin_config( SPID_SS , &PORTD , INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES);		
		
		
		
	}
	
	else {
		
		// assert fail 
		return 0 ;  
	}
	
	#endif 
	
	//Check if interrupts are enabled 
	if ( spi_struct.INT_level != UNUSED && spi_struct.INT_level <= INT_HIGH_PRIORITY ) {
		
		spi_struct.SPI_module->INTCTRL = spi_struct.INT_level ; 
		
	}
	else{
		
		spi_struct.SPI_module->INTCTRL = INT_DISABLED ; 
	}
	
	// Configure and Enable 
	spi_struct.SPI_module->CTRL = ( spi_struct.SPI_prescale << SPI_PRESCALER0_bp ) | ( spi_struct.SPI_clk_config << SPI_MODE0_bp)|
								  ( spi_struct.SPI_dor << SPI_DORD_bp ) | ( spi_struct.SPI_mode << SPI_MASTER_bp ) |
								  ( 1 << SPI_ENABLE_bp ) ; 
	
		
	return 1 ; 							  
								  
}





int16_t SPI_Deinit( SPI_Init_Struct spi_struct  ) {
	
	
#if defined(__AVR_ATxmega32A4__)

	
	//DeInit Pins 
	if ( spi_struct.SPI_module == &SPIC  ){
		
		
		pin_config( SPIC_MOSI , &PORTC,INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES);
		pin_config( SPIC_SCK, &PORTC , INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES  );
		pin_config( SPIC_MISO,&PORTC , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES ) ;
		pin_config( SPIC_SS , &PORTC , INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES);	
		
		
	}
	
	else if ( spi_struct.SPI_module == &SPID){
		
		pin_config( SPID_MOSI,&PORTD,INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES);
		pin_config( SPID_SCK ,&PORTD , INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES  );
		pin_config( SPID_MISO,&PORTD , INPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES ) ;
		pin_config( SPID_SS  ,&PORTD , INPUT , TOTEMPOLE_Z,SENSE_BOTH_EDGES);	
		
		
		
	}
	
	else {
		
		return 0 ; 
		
		
	}
	
#endif 
	
	// Disable SPI
	spi_struct.SPI_module->INTCTRL = INT_DISABLED ; 
	spi_struct.SPI_module->CTRL = 0x00UL ; 
	
return 1 ; 
	
}		
		
	
					  
								  

int16_t SPI_NB_SendReceive (  uint8_t val , SPI_t * spi_module , uint16_t timeout ) {
	
	 
	spi_module->DATA = val ; 
	
	for ( ; timeout && ( !(spi_module->STATUS & ( 1 << SPI_IF_bp ) ) ); timeout-- ){
		
		_delay_us(1); 
	}
	
	if ( timeout == 0 ) { return -1 ; }
	
	
	return spi_module->DATA ; 

		
	}
	


uint8_t SPI_B_SendReceive (  uint8_t val , SPI_t * spi_module , uint16_t timeout ) {
	//write
	spi_module->DATA = val ; 
	//block
	while( ( !(spi_module->STATUS & ( 1 << SPI_IF_bp ) ) ) ) ;
	//return val 
	return spi_module->DATA ;
		
	}	
	
	
	
void SPI_Int_Send( uint8_t val  ,SPI_t * spi_module  ) {

spi_module->DATA = val ; 

}




uint8_t SPI_Int_Receive ( SPI_t * spi_module  ) {

	return spi_module->DATA ; 
	
}


	
	
	
	
	
	
	
	
	
	

