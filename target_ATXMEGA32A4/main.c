



#include "GENERAL/header.h"








int main( void ) {
	
	int16_t word ,bord;
	uint8_t c; 
	uint8_t arar[6] = "abcdew" ; 
	
	uint8_t daddr[7] ;
	daddr[6] = 0 ; 
	uint8_t saddr[7] ;
	saddr[7] = 0 ;
	uint8_t payload[30];
	payload[29]= 0 ;
	
	SPI_Init_Struct spi_init_struct1 = {
										.SPI_module     = &SPIC            ,    
										.SPI_mode       = SPI_MASTER       ,
										.SPI_dor        = SPI_MSB_FIRST    ,
										.SPI_prescale   = SPI_PRESCALE_2  , 
										.SPI_clk_config = SPI_CPOL_L_PHA_F ,
										.INT_level      = UNUSED           ,
																					};

	SPI_Init_Struct spi_init_struct2 = {
										.SPI_module     = &SPID            ,    
										.SPI_mode       = SPI_MASTER       ,
										.SPI_dor        = SPI_MSB_FIRST    ,
										.SPI_prescale   = SPI_PRESCALE_2 , 
										.SPI_clk_config = SPI_CPOL_L_PHA_F ,
										.INT_level      = UNUSED           ,
																					};

	ETH_Packet my_packet1 = {
								.ppcb = 0x00 ,
								.dest_address = Mac_Struct_Default.MAC_Address ,
								.src_address  = Mac_Struct_Default.MAC_Address , 
								.payload_len  = 6                      ,
								.payload      = &arar ,
	}				;
	
		ETH_Packet my_packet2 = {
								.ppcb = 0x00 ,
								.dest_address = daddr ,
								.src_address  = saddr , 
								.payload_len  = 1                      ,
								.payload      = payload ,
	}				;
		
																																											
	// clock startup at 32 MHZ DFLL ENABLED 
	
	startup_int_nolock( RC32MHZ , PSCA_DIV1 | PSCBC_DIV1_1 ) ;
	
	// Initialize Port 
	
	//uart_port_asynch_xmega32a4( &USARTC0 ) ;  
	uart_port_asynch_xmega32a4( &USARTE0 ) ;
	 //INITIALIZE UART MODULE AT 115200 BAUD 
	//uart_asynch_init( baud_calc( 115200 , F_PERPH , 8 , 0 )  , 0 , PARITY_DISABLED_1SB_8B , &USARTC0 ) ; // init at 115200 
	uart_asynch_init( baud_calc( 9600 , F_PERPH   , 8 , 0 )  , 0 , PARITY_DISABLED_1SB_8B , &USARTE0 ) ; // init at 115200 
	//INIT SPI
	//SPI_Init( spi_init_struct1 ) ;
	SPI_Init( spi_init_struct2 ) ; 
	//GLOBAL INT SETTINGS ENABLE LOWLEVEL INTERRUPTS
	//PMIC_CTRL = PMIC_LOLVLEN_bm ;
	
//	Enable interrupts
	//uart_interrupt_set( INT_LOW_PRIORITY , INT_LOW_PRIORITY ,INT_DISABLED , &USARTC0);
	
	//pin_config( 2 ,  &PORTD ,OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
	//pin_config( 3 ,  &PORTD ,OUTPUT , TOTEMPOLE_Z , SENSE_BOTH_EDGES );
	pin_config( 4 ,  &PORTD , OUTPUT , TOTEMPOLE_Z, SENSE_BOTH_EDGES ); //SS
	pin_set(4,&PORTD);
	
	pin_config( 3 , &PORTD , INPUT , TOTEMPOLE_PULLUP , SENSE_FALLING_EDGE ) ;
	
	
Encj_Init( Encj_Struct_Default );


while(1){
if ( uartb_receive( &USARTE0 ) == 'A' ) {
Encj_SendPacket( &my_packet1 );
arar[0]++;
_delay_ms(2000);
uart_print( "\nRECEIVED" , &USARTE0 ) ;
Encj_ReceivePacket( &my_packet2);
uart_print( daddr , &USARTE0 ) ;
uart_print("\n\n",&USARTE0); 
uart_print( saddr , &USARTE0 ) ;
uart_print("\n\n",&USARTE0); 
uart_print( payload , &USARTE0 ) ;
uart_print("\n\n",&USARTE0); 

}
}


	while(1){
		


	


	
}

}

