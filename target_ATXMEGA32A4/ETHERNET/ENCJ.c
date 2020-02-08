


#include "ENCJ.h"



// this is a default initialization structure that may be used to configure the enc28j60
// They are defined as externs to be used 
#if defined(ETH_DEFAULT_STRUCT)
MAC_Config_Struct Mac_Struct_Default = {
									   .FLCTRL_Config       = ETH_NPA_FLCTRL_TRX ,
									   .Frame_Config        = ETH_60PAD_CRCEN    ,
									   .Frame_Length_Config = ETH_HFDEN_CHDEN    ,
									   .Header_Config       = ETH_HEADER_DISABLE ,
									   .Max_Frame_Length    = 256                ,
									   .HLFDPLX_Config      = ETH_HLFDPLX_CTRL0  ,
									   .MAC_Address[0]      = 'A'                ,
									   .MAC_Address[1]      = 'B'                ,
									   .MAC_Address[2]      = 'C'                ,
									   .MAC_Address[3]      = 'D'                ,
									   .MAC_Address[4]      = 'E'                ,
									   .MAC_Address[5]      = 'F'                ,
									};
									
PHY_Config_Struct Phy_Struct_Default = {
										.LEDA               = ETH_LED_MODE_RX_CS,
										.LEDB               = ETH_LED_MODE_TX_CS,
										.LED_Stretch_Config = ETH_TLSTRETCH_140         ,
		
									};
		
Encj_Init_Struct   Encj_Struct_Default= {
										.RX_Buff_Size = 0X0000 + 1024      ,
										.RX_Filter     =  ETH_RXF_NOFILTER ,
										.Power_Config  = 0X00              ,
										.Pattern_Struct_Ptr = NULL         ,
										.Hash_Table  = 0X00                ,
										.ETH_Mode    = ETH_FULL_DPLX       ,
										.PHY_Struct_Ptr = &Phy_Struct_Default      ,
										.MAC_Struct_Ptr = &Mac_Struct_Default      ,
										.Interrupt_Mask = (EIE_PKTIE_BM|EIE_INTIE_BM) ,
									};
									
									
#endif 									

// Current bank
static uint8_t current_bank  = BANK_UNREAD ;
// last register addressed  
static uint8_t register_address = 0        ;
// last command issued by the host 
static uint8_t command          = 0        ;
// Last value that attempted a write 
static uint8_t write_val        = 0        ;
// Value of the last read register 
static uint8_t last_read_val    = 0        ;
// Last fetched status vectors for each transmission and reception 
static uint64_t tx_status_vect  = 0        ;
static uint64_t rx_status_vect  = 0        ;
// This variable will be updated by the End of the Buffer by the init function 
static uint16_t RX_tail         = 0        ;
// this is always the start of the RX Buffer as to ERRATA SHEET OF THE ENC28J60 
static uint16_t RX_head         = RX_BUFF_START_DEFAULT     ;




// This is the reception pointer 
static ETH_Pos  ETH_Position_RX = { .RD_Pos = 0 , 
								    .WR_Pos = 0 ,
							 };
							 
// this is the transmission pointer , it starts out with invalid values , to trigger assertion error if it wasn't initialized 
static ETH_Pos ETH_Position_TX = {
										.RD_Pos = 0XFFFF , 
										.WR_Pos = 0XFFFF , 

} ; 

static int16_t encj_send_byte ( uint8_t cmd ) {
int16_t temp ; 
  
temp = SPI_NB_SendReceive( cmd , &ETHERNET_SPI , TIMEOUT_CMD ) ;
if( temp == -1 ) { return ERRC_TIMEOUT ; } 
 
 return (uint8_t)temp ; 
}


static int16_t encj_bank_switch( uint8_t bank ) {
	
	int16_t temp ; 
	uint8_t val  ; 
	if ( bank > 3UL ) {
		
		return ERRC_ASSERT ; 
	}
	
	ETHERNET_SELECT;
	//CLEAR BANK BITS
	if ( (temp = encj_send_byte( CMD_RCR|(ECON1&ADDR_MASK) ) )  == -1 ) { return ERRC_TIMEOUT ; }
	if ( (temp = encj_send_byte( DUMMY_BYTE ) )  == -1 ) { return ERRC_TIMEOUT ; }
	ETHERNET_DESELECT;
	//MODIFY
	val = (uint8_t) ( temp ) ;
	val &= 0XFC ; 
	val |= bank ; 
	//SET BANK 
	ETHERNET_SELECT;
	if ( (temp = encj_send_byte( CMD_WCR|(ECON1&ADDR_MASK) ) )  == -1 ) { return ERRC_TIMEOUT ; }
	if ( encj_send_byte( val ) == -1 ) { return ERRC_TIMEOUT; }
	ETHERNET_DESELECT;
	//SET BANK GLOBAL VAL 
	current_bank = bank ; 
	
	return ERRC_SUCCESS ; 
	
}

static int16_t Bank_Setup( uint8_t reg_addr ) {
	
	int16_t temp ; 
	
	
	if ( current_bank == BANK_UNREAD ) {
		
		ETHERNET_SELECT ; 
		
		//Read ECON1  
		temp = encj_send_byte( (ECON1&ADDR_MASK)|CMD_RCR ) ;
		
		if ( temp == ERR_TIMEOUT ) { return ERRC_TIMEOUT ; } 
		
		temp = encj_send_byte( DUMMY_BYTE ) ;
		
		if ( temp == ERR_TIMEOUT ) { return ERRC_TIMEOUT ; }
		
		// Set Bank 
		current_bank = temp & ( ECON1_BSEL0_BM | ECON1_BSEL1_BM ) ;
		
		ETHERNET_DESELECT;
		
	}
	
	
	// SWITCH BANKS IF THE DESIRED REGISTER IS OUT OF RANGE -- NOTE BANK SWITCH FUNCTION UPDATES THE GLOBAL VARIABLE 
	
	if ( ( GET_BANK( reg_addr ) != current_bank )  && ( ( reg_addr&ADDR_MASK ) < (EIE&ADDR_MASK) ) ) {
		
		temp = encj_bank_switch( GET_BANK( reg_addr ) ) ;
		
		if ( temp != ERRC_SUCCESS ){ return temp ; } 		
}	
	
return ERR_SUCCESS ; 	
	
	
	
	
	
	
	
	
	
}

static int16_t encj_read_reg( uint8_t reg_addr, REG_LENGTH reg_length ) {
	
	
	int16_t temp ; 
	uint16_t retval = 0 ; 
	//ASSERT PARAMS 
	
	#if defined( ETH_FULL_ASSERT  )
	if ( ((reg_addr&ADDR_MASK) > COMMON_REG_END ) || ( GET_BANK(reg_addr) > 3UL ) ) { return error_handler(ERRC_ASSERT)  ; }
	#endif 
	//UPDATE GLOBALS
	
	register_address = reg_addr & ADDR_MASK ; 
	command          = CMD_RCR              ;
	

	if ( (temp = Bank_Setup( reg_addr ) ) != ERR_SUCCESS ) { return error_handler(temp)  ; } 
	
	// BANK IS SETUP NOW WE READ THE REGISTER 
	
	for( uint8_t i = 0 ; reg_length ; reg_length-- , i++ ) {	
	ETHERNET_SELECT ;
		
	temp = encj_send_byte ( ((reg_addr&ADDR_MASK)+i)|CMD_RCR ) ; 
	
	if ( temp == -1 ) { return error_handler(temp)  ; }
	
	if ( (reg_addr & MAC_MASK) == IS_MAC ){
	// EXTRA DUMMY CYCLE FOR MAC AND MII REGISTERS 
	temp = encj_send_byte ( DUMMY_BYTE ) ; 
	
	if ( temp == -1 ) { return error_handler(temp) ; }
		
	
	}
	 
	temp = encj_send_byte ( DUMMY_BYTE ) ; 
	
	if ( temp == -1 ) { return error_handler(temp)  ; } 
	
	retval |= ( (uint16_t) ( temp << (8*i)  )) ;
	ETHERNET_DESELECT;
}

	//DONE   
	
	last_read_val = (uint8_t) temp ; 
	
	return retval ;  

}



static int16_t encj_write_reg( uint8_t reg_addr  , uint16_t val , REG_LENGTH reg_length ){
		 
	int16_t temp ; 
	uint8_t i ; 
	 //ASSERT PARAMS 
	 #if defined( ETH_FULL_ASSERT ) 
	if ( ((reg_addr&ADDR_MASK) > COMMON_REG_END ) || ( GET_BANK( reg_addr ) > 3UL )  ) { return error_handler(ERRC_ASSERT)  ; }
	#endif 
	//UPDATE GLOBALS 
	
	register_address = reg_addr & ADDR_MASK ; 
	command          = CMD_WCR              ;
	write_val        = val                  ;
	
	
	if ( (temp = Bank_Setup( reg_addr ) ) != ERR_SUCCESS ) { return error_handler(temp) ; }
	  
	// BANK IS SETUP NOW WE WRITE THE REGISTER 
		
		for (  i = 0 ; reg_length ; --reg_length , ++i ){
		ETHERNET_SELECT; 
		
		temp = encj_send_byte( (((reg_addr&ADDR_MASK)+i)|CMD_WCR) ) ;
		
		if ( temp == -1 ) { return error_handler(temp) ;}
			
		temp = encj_send_byte(  (uint8_t) ( val >> (8 * i ) )  ) ; 
		
		if ( temp == -1 ) { return error_handler(temp) ;}
		
		ETHERNET_DESELECT;	
	}
		#if defined( ETH_VERIFY ) 
		//VERIFY
		temp = encj_read_reg( reg_addr , i ) ;		
		if ( IS_ERROR( temp ) ) { return error_handler(temp) ; }
		if ( ( (uint16_t) temp ) != ( val ) ) { return error_handler( ERRC_VERIFY ) ; } 
		#endif 
		
		
		return ERRC_SUCCESS ; 
		
	}
	
	
	
 static int16_t encj_write_buff( uint8_t* val , uint16_t len , ETH_Pos* eth_pos  ) {
	
	int16_t temp ; 
	//ASSERT PARAMS
	#if defined( ETH_FULL_ASSERT ) 
	if ( ( len == 0 ) ||
		 ( val == NULL) ||
		 (eth_pos == NULL ) ) { return error_handler(ERRC_ASSERT ) ; }
		 
	if (  ( ( eth_pos->WR_Pos ) > ETH_BUFF_END )||
		  ( ( eth_pos->RD_Pos ) > ETH_BUFF_END ) ){   return error_handler(ERRC_ASSERT ) ; }
		  
	#endif 
	// first we must set the position of read and write pointers 
	
	encj_write_reg( ERDPTL , eth_pos->RD_Pos , REG16);
	encj_write_reg( EWRPTL , eth_pos->WR_Pos , REG16);
	
	// Check Auto increment 
	
	temp = encj_read_reg( ECON2 , REG8 ) ;
	
	if ( ! ( ( ( uint8_t) temp ) & ( 1 << ECON2_AUTOINC_BP ) ) ) { 
		
		encj_write_reg( ECON2 , (uint8_t)(temp|( 1 << ECON2_AUTOINC_BP ) ) , REG8 ) ;
	}
	
	// Now we update globals
	
	command = CMD_WBM ; 
	
	// START 
	
	ETHERNET_SELECT
	
	// Send Command Word 
	temp = encj_send_byte ( CMD_WBM ) ; 
	if ( IS_ERROR(temp ) ) { return error_handler(temp) ; }
	
	for ( uint16_t i = 0 ; i <= len -1 ; i++ ) {
		
		temp = encj_send_byte( *(val+i) ) ;
		if ( IS_ERROR(temp ) ) { return error_handler(temp) ; }
		uart_print_num( *(val+i) , 16 , 0 , &USARTE0 ) ;
		uart_print("\n", &USARTE0);
		(eth_pos->WR_Pos)++ ; 
		

}

	ETHERNET_DESELECT
	
	
	// Now we verify Written , memory
#if defined( ETH_VERIFY ) 
	ETHERNET_SELECT
	
	// Send Command Word 
	temp = encj_send_byte ( CMD_RBM ) ; 
	if ( IS_ERROR(temp ) ) { return error_handler(temp) ; }
	
	for ( uint16_t i = 0 ; i <= len -1 ; i++ ) {
		
		temp = encj_send_byte( DUMMY_BYTE ) ;
		if ( IS_ERROR(temp ) ) { return error_handler(temp) ; }
		if ( ((uint8_t) temp ) != ( *(val+i ) ) ) { return error_handler(ERRC_VERIFY) ; }
		(eth_pos->RD_Pos)++ ;  

}

	ETHERNET_DESELECT ;
#else 

eth_pos->RD_Pos = eth_pos->WR_Pos ; 	
	 
#endif 
 	return ERRC_SUCCESS ; 

}


static int16_t encj_read_buff( uint8_t * rec_buff , uint16_t read_len , ETH_Pos * eth_pos  ) {
	
int16_t temp ; 
//ASSERT PARAMS 
#if defined( ETH_FULL_ASSERT ) 
if ( ( rec_buff == NULL )||
     ( eth_pos  == NULL )|| ( read_len == 0 ) ) { return error_handler( ERRC_ASSERT ) ; }
     
     
if (  ( ( eth_pos->WR_Pos ) > ETH_BUFF_END )||
	  ( ( eth_pos->RD_Pos ) > ETH_BUFF_END ) ){   return error_handler(ERRC_ASSERT ) ; }    
   
#endif 
	// first we must set the position of read and write pointers 
	
	encj_write_reg( ERDPTL , eth_pos->RD_Pos , REG16);
	encj_write_reg( EWRPTL , eth_pos->WR_Pos , REG16);
	
	// Check Auto increment 
	
	temp = encj_read_reg( ECON2 , REG8 ) ;
	
	if ( ! ( ( ( uint8_t) temp ) & ( 1 << ECON2_AUTOINC_BP ) ) ) { 
		
		encj_write_reg( ECON2 , (uint8_t)(temp|( 1 << ECON2_AUTOINC_BP ) ) , REG8 ) ;
	}
	     
	//Update GLOB 
	
	command = CMD_RBM ; 
	
    // READ
    
    ETHERNET_SELECT; 
    
    // Send Command Word 
	temp = encj_send_byte ( CMD_RBM ) ;
	 
	if ( IS_ERROR(temp ) ) { return error_handler(temp) ; }
	
	for ( uint16_t i = 0 ; i <= read_len -1 ; i++ ) {
		
		temp = encj_send_byte( DUMMY_BYTE ) ;
		if ( IS_ERROR(temp ) ) { return error_handler(temp) ; }
		*(rec_buff+i) =  (uint8_t) temp ;
		uart_print( "\n" , &USARTE0 ) ;
		uart_print_num( (uint8_t) temp , 16 , 0 , &USARTE0);  
		(eth_pos->RD_Pos)++ ;  // read next
		(eth_pos->WR_Pos)++ ; // increment write pointer as well , so that both are equal 

}

	ETHERNET_DESELECT ; 

 	return ERRC_SUCCESS ; 

    
    
	
}
	
	
	
static int16_t encj_bit_set( uint8_t reg_addr , uint8_t bit_mask ) {
	
	int16_t temp ; 
	//ASSERT ADDRESS 
#if defined( ETH_FULL_ASSERT ) 	
	if ( ((reg_addr&ADDR_MASK) > COMMON_REG_END ) ) { return ERRC_ASSERT ; }  
#endif 	
	//Setup bank
	if ( (temp = Bank_Setup( reg_addr ) ) != ERRC_SUCCESS ) { return temp ; }  
	
	ETHERNET_SELECT ; 
	
	temp = encj_send_byte( (reg_addr&ADDR_MASK)|CMD_BFS ) ;
	if ( temp == -1 ) { return ERRC_TIMEOUT ; }
	encj_send_byte( bit_mask ) ;
	if ( temp == -1 ) { return ERRC_TIMEOUT ; }
	
	ETHERNET_DESELECT;
	return ERRC_SUCCESS;
	
}




static int16_t encj_bit_clear( uint8_t reg_addr , uint8_t bit_mask ){
	
		int16_t temp ; 
	//ASSERT ADDRESS 
	#if defined( ETH_FULL_ASSERT ) 
	if ( ((reg_addr&ADDR_MASK) > COMMON_REG_END ) ) { return ERRC_ASSERT ; }  
	#endif
	//Setup bank
	if ( (temp = Bank_Setup( reg_addr ) ) != ERRC_SUCCESS ) { return temp ; }  
	
	ETHERNET_SELECT ; 
	
	temp = encj_send_byte( (reg_addr&ADDR_MASK)|CMD_BFC ) ;
	if ( temp == -1 ) { return ERRC_TIMEOUT ; }
	encj_send_byte( bit_mask ) ;
	if ( temp == -1 ) { return ERRC_TIMEOUT ; }

	ETHERNET_DESELECT;
		
	return ERRC_SUCCESS;

}


static int16_t encj_load_packet ( ETH_Packet * packet , ETH_Pos* position  ){
	
	uint8_t poll_val  , i;
	uint64_t retval = 0 ; 
	//ASSERT PACKET POSITION 
	#if defined( ETH_FULL_ASSERT ) 
	if ( (position == NULL )||( packet == NULL ) ){
		return error_handler( ERRC_ASSERT ) ;
	} 

	if ( ( position->WR_Pos < RX_tail )||
		 ( position->RD_Pos < RX_tail ) ) { return error_handler( ERRC_ASSERT ) ; }
	#endif 
	
	encj_bit_set( ECON1 , ECON1_TXRST_BM ) ;
	encj_bit_clear(ECON1 , ECON1_TXRST_BM ) ; 
	encj_bit_clear(EIR , EIR_TXERIF_BM ) ;
	encj_bit_clear( EIR , EIR_TXIF_BM ) ;
	
	 	 
	//LOAD ETXST 
	uart_print_num(  position->WR_Pos , 10 , '\n' , &USARTE0 ) ;

	encj_write_reg( ETXSTL , position->WR_Pos , REG16 ) ;

	//Start loading the packet 
	
	// load per packet byte 
	encj_write_buff ( &(packet->ppcb) , 1 , position ) ;
	//load Destination address 
	encj_write_buff( packet->dest_address , 6 , position ) ; 
	//load Source address 
	encj_write_buff( packet->src_address , 6 , position ) ;
	//load data length 
	encj_write_buff( (uint8_t*)(&(packet->payload_len)), 2 , position ) ;
	//load data
	encj_write_buff ( packet->payload , packet->payload_len , position ) ; 
	
	// LOAD ETXND 
	encj_write_reg ( ETXNDL  , position->WR_Pos -1  , REG16 ) ;
	
	//Transmit the packet 
	
	encj_bit_set (ECON1 ,  ECON1_TXRTS_BM) ;
	
	// Now WR_POS AND RD_POS are sitting at the next byte
	//wait for RTS to clear
	
	for (  i = 0 ; i <= TXRTS_TIMEOUT_VAL -1  ; i++ ){
		
		//READ ECON1 
		poll_val = encj_read_reg( ECON1 , REG8 ) ;
		
		if ( !(( poll_val ) & ( 1 << ECON1_TXRTS_BP ) ) ){
			break ; 
		}
		else{
			_delay_us( TXRTS_DELAY_VAL ) ;
		}
	}
	
	if ( i == TXRTS_TIMEOUT_VAL ) { return error_handler( ERRC_TX_TIMEOUT ) ; }
	
	// Update status vector 
	
	encj_read_buff( (uint8_t*)(&retval ) , 7UL , position ) ;
	
	tx_status_vect = retval ; 
	
	return ERRC_SUCCESS ;
	
	
}	



static int16_t encj_get_packet ( ETH_Packet * packet_ptr , ETH_Pos* eth_pos  ){
	
	
	int16_t temp ;
	uint16_t next_packet ;  
	uint64_t vector ; 
	//read the next packet pointer , eth_pos is updated to the position of the vector 
	 encj_read_buff ( (uint8_t*)(&next_packet) ,2 , eth_pos ) ;
	
	// get the 7 byte vector , eth_pos is updated to the position of the Destination address 
	encj_read_buff ( (uint8_t*)(&vector ) , 4 , eth_pos ) ; 
	
	//Update the vector 
	rx_status_vect = vector ;
	 
	// Get Destination address 
	encj_read_buff( packet_ptr->dest_address , 6 , eth_pos ) ;
	
	// Get Source address 
	encj_read_buff( packet_ptr->src_address , 6 , eth_pos ) ; 
	
	// Get data length 
	encj_read_buff ( (uint8_t*)(&(packet_ptr->payload_len)) , 2 , eth_pos ) ; 
	
	
	// Get data if there is data 
	if ( (packet_ptr->payload_len) == 0 ) { return ERRC_PAYLOAD_EMPTY ; } 
	
	
	encj_read_buff ( (uint8_t*)(packet_ptr->payload ) , packet_ptr->payload_len , eth_pos ) ; 
	
	
	//update and clear space 
	eth_pos->RD_Pos = next_packet ; // update read position to the next pointer 
	eth_pos->WR_Pos = next_packet ; // for equality 
	
	// free used up space , so that we can loop back into the used space , due to fifo wrapping 
	encj_write_reg( ERXRDPTL , next_packet , REG16 ) ;
	
	// done
	
	return ERRC_SUCCESS ;
	
	
	
} 






 	
	
static int16_t encj_phy_read ( uint8_t reg_addr ) {
	
	int16_t temp ;
	uint8_t i ;
	  
	//READ MICMD 
	temp = encj_read_reg( MICMD , REG8 ) ;
	if ( IS_ERROR ( temp ) ) { return temp ; }
	//CHECK IF MIIRD IS ALREADY SET , CLEAR IT  
	if ( temp & ( 1 << MICMD_MIIRD_BP ) ) {
			temp&= ~( 1 << MICMD_MIIRD_BP ) ;
			temp = encj_write_reg( MICMD , (uint8_t)temp  , REG8 );
			if ( IS_ERROR( temp ) ) { return temp ; }
		}
		  
	//Write PHY Address into MIREGADR
	temp = encj_write_reg(MIREGADR  , (uint8_t) (reg_addr&ADDR_MASK) , REG8 ) ;
	if ( IS_ERROR ( temp ) ) { return temp ; }	
	//SET MIIRD
	temp = encj_read_reg( MICMD , REG8 ) ;
	if ( IS_ERROR ( temp ) ) { return temp ; }
	
	temp |= ( 1 << MICMD_MIIRD_BP ) ;
	//WRITE MICMD 
	temp = encj_write_reg( MICMD  , (uint8_t) temp , REG8 ) ;
	if ( IS_ERROR ( temp ) ) { return temp ; }
	//Wait 10.24 US
	_delay_us( PHY_DELAY ) ;
	//POLL MISTAT
	for (  i = 0 ; i <= PHY_BUSY_NUM_TRY-1 ; i++ ) {
	
	temp = encj_read_reg( MISTAT ,REG8 ) ;
	if ( IS_ERROR ( temp ) ) { return temp ; }
	if ( ( (uint8_t )temp ) & ( 1 << MISTAT_BUSY_BP ) ){
			_delay_us( PHY_BUSY_TIMEOUT ) ;
		}
	else {
		break ;
	}	
	}
	//PHY BUSY TIMEOUT
	if ( i == PHY_BUSY_NUM_TRY ) { return ERRC_PHY_TIMEOUT ; } 
	
	//READ MICMD
	temp = encj_read_reg( MICMD , REG8 ) ; 
	if ( IS_ERROR ( temp ) ) { return temp ; }
	// CLEAR MIIRD
	temp&= ~( 1 << MICMD_MIIRD_BP ) ;
	//WRITE MICMD
	temp = encj_write_reg( MICMD  , (uint8_t ) temp , REG8 ) ; 
	if ( IS_ERROR ( temp ) ) { return temp ; }
	// READ PHY 
	temp = encj_read_reg( MIRDL ,REG16 ); 
	if ( IS_ERROR ( temp ) ) { return temp ; }
	//return PHY
	return temp ; 
	
}	
	 
static int16_t encj_phy_write ( uint8_t reg_addr , uint16_t mask , uint16_t val ) {
	
	
	int16_t temp ; 
	uint8_t i ; 
    //phy write as a RMW Operation 
    temp = encj_phy_read( reg_addr ) ; 	
	if ( IS_ERROR( temp ) ) { return temp ; } 
	//MODIFY 
	temp &= mask ; 
	temp |= val  ; 
	//WRITE
	temp = encj_write_reg( MIWRL  , (uint16_t) temp ,REG16) ;
	if ( IS_ERROR( temp ) ) { return temp ; } 
	//DELAY 
	_delay_us( PHY_DELAY ) ;
	//POLL MISTAT
	for (  i = 0 ; i <= PHY_BUSY_NUM_TRY-1 ; i++ ) {
	
	temp = encj_read_reg( MISTAT  , REG8 ) ;
	if ( IS_ERROR ( temp ) ) { return temp ; }
	if ( ( (uint8_t )temp ) & ( 1 << MISTAT_BUSY_BP ) ){
			_delay_us( PHY_BUSY_TIMEOUT ) ;
		}
	else {
		break ;
	}	
	}
	//PHY BUSY TIMEOUT
	if ( i == PHY_BUSY_NUM_TRY ) { return ERRC_PHY_TIMEOUT ; } 
	
	return ERRC_SUCCESS ; 
}
	 
	 
	 
int16_t Encj_Init ( Encj_Init_Struct encj_struct ) {
	
	
	int16_t temp ; 
	uint8_t val ; 
	uint8_t i;
	#if defined( ETH_FULL_ASSERT ) 
	//PARAMETERS ASSERTION 
	if ( ( encj_struct.RX_Buff_Size > ETH_BUFF_END ) ){
			return ERRC_ASSERT ;  
			  
		  }
	if ( encj_struct.MAC_Struct_Ptr == NULL ){
		return ERRC_ASSERT ;
	}
	
	if( encj_struct.PHY_Struct_Ptr == NULL ){
		return ERRC_ASSERT ;
		
	}
	#endif
		//Done ASSERTION
	// Wait for powerup delay 
	
	_delay_us(300) ;
	
	//Poll for high CLKRDY 
	for ( i = OST_NUMTRY ; i ; i-- ){
		
		temp = encj_read_reg( ESTAT , REG8) ;
		if ( IS_ERROR( temp ) ) { return temp ;}
		
		if ( ((uint8_t)(temp))& ( 1 << ESTAT_CLKRDY_BP ) ) {
			break ; 
		}
		else{
			_delay_us( OST_DELAY ) ;
		}
	}
	
	if ( i == 0 ) { return error_handler( ERRC_STARTUP_TIMEOUT ) ; }
	

	
	//OST Period is Over We Can now access All registers 
	
	//Program ERXST , ERXND 
	
	temp = encj_write_reg( ERXSTL , RX_BUFF_START_DEFAULT , REG16);
	if ( IS_ERROR( temp ) ) { return temp ;}
	temp = encj_write_reg( ERXNDL  , encj_struct.RX_Buff_Size - 1 ,REG16            );
	if ( IS_ERROR( temp ) ) { return temp ;}
	
	
	// Set Size params for the RX buffer 
	RX_tail =  encj_struct.RX_Buff_Size - 1  ;
	RX_head = RX_BUFF_START_DEFAULT          ;
	
	// Set the TX pointers starting position 
	
	ETH_Position_TX.WR_Pos = RX_tail + 1UL; 
	ETH_Position_TX.RD_Pos = RX_tail + 1UL;
	
	//Program Read Pointer at the same location 
	
	temp = encj_write_reg( ERXRDPTL , RX_BUFF_START_DEFAULT , REG16 );
	if ( IS_ERROR( temp ) ) { return temp ;}
	
	//Program Filters 
	
	temp = encj_write_reg( ERXFCON  , encj_struct.RX_Filter , REG8 );
	if ( IS_ERROR( temp ) ) { return temp ;}	
	
	//Mac Config
	
	//MACON1

	temp = encj_read_reg( MACON1  , REG8);
	if ( IS_ERROR( temp ) ) { return temp ;}		
	val = (uint8_t) temp ; 
	val &= MACON1_MASK ; 
	val |= ( ( ( encj_struct.MAC_Struct_Ptr->FLCTRL_Config ) << MACON1_PASSALL_BP ) |
			   ( 1 << MACON1_MARXEN_BP ) ) ;
	
	temp = encj_write_reg( MACON1   , val , REG8);
	if ( IS_ERROR( temp ) ) { return temp ;}			   
	
	// MACON3 
	
	val = ( ( ( encj_struct.MAC_Struct_Ptr->Frame_Config ) << MACON3_TXCRCEN_BP ) |
			( ( encj_struct.MAC_Struct_Ptr->Frame_Length_Config) << MACON3_FRMLNEN_BP)|
			( ( encj_struct.MAC_Struct_Ptr->Header_Config ) << MACON3_PHDREN_BP )|
			( ( encj_struct.ETH_Mode ) << MACON3_FULDPX_BP ) ) ;
	
	temp = encj_write_reg( MACON3  , val  , REG8);
	if ( IS_ERROR( temp ) ) { return temp ;}		
	
	//MACON4 FOR HALF DUPLEX MODE ONLY
	
	if ( encj_struct.ETH_Mode == ETH_HALF_DPLX ) {

		// READ MACON4 
			temp = encj_read_reg( MACON4  , REG8);
			if ( IS_ERROR( temp ) ) { return temp ;}		
			val = (uint8_t) temp ;
			
			val&= MACON4_MASK ; 
			
			val|= ( (encj_struct.MAC_Struct_Ptr->HLFDPLX_Config )  << MACON4_NOBKOFF_BP ) ;
			
		// WRITE MACON4 
			temp = encj_write_reg( MACON4   , val , REG8 );
			if ( IS_ERROR( temp ) ) { return temp ;}	
	
	}		
	
		
		//WRITE MAX PACKET SIZE 
	
	temp = encj_write_reg( MAMXFLL  , encj_struct.MAC_Struct_Ptr->Max_Frame_Length  , REG16 );
	if ( IS_ERROR( temp ) ) { return temp ;}	
		
	
		//WRITE MABBIPG.
		if ( encj_struct.ETH_Mode == ETH_FULL_DPLX ) {
		temp = encj_write_reg( MABBIPG  , MABBIPG_FULLDPLX_VAL , REG8) ;
		if ( IS_ERROR( temp ) ) { return temp ;}	
		temp = encj_write_reg( MAIPGL  , MAIPGL_FULLDPLX_VAL , REG16 ) ;
		if ( IS_ERROR( temp ) ) { return temp ;}
	}
	else if ( encj_struct.ETH_Mode == ETH_HALF_DPLX ) {
		temp = encj_write_reg( MABBIPG  , MABBIPG_HALFDPLX_VAL  , REG8 ) ;
		if ( IS_ERROR( temp ) ) { return temp ;}	
		temp = encj_write_reg( MAIPGL  ,  MAIPGL_HALFDPLX_VAL ,REG16 ) ;
		if ( IS_ERROR( temp ) ) { return temp ;}
	}
	
		
	//WRITE MAC ADDRESS
	
	  	temp = encj_write_reg( MAADR1  , encj_struct.MAC_Struct_Ptr->MAC_Address[0] , REG8 ) ;
		if ( IS_ERROR( temp ) ) { return temp ;}
	  	temp = encj_write_reg( MAADR2  , encj_struct.MAC_Struct_Ptr->MAC_Address[1] , REG8 ) ;
		if ( IS_ERROR( temp ) ) { return temp ;}			
	  	temp = encj_write_reg( MAADR3  , encj_struct.MAC_Struct_Ptr->MAC_Address[2] , REG8 ) ;
		if ( IS_ERROR( temp ) ) { return temp ;}	
	  	temp = encj_write_reg( MAADR4  , encj_struct.MAC_Struct_Ptr->MAC_Address[3] , REG8 ) ;
		if ( IS_ERROR( temp ) ) { return temp ;}	
	  	temp = encj_write_reg( MAADR5  , encj_struct.MAC_Struct_Ptr->MAC_Address[4] , REG8 ) ;
		if ( IS_ERROR( temp ) ) { return temp ;}	
	  	temp = encj_write_reg( MAADR6  , encj_struct.MAC_Struct_Ptr->MAC_Address[5] , REG8 ) ;
		if ( IS_ERROR( temp ) ) { return temp ;}		 
	
		
	//PHY 
	
		if ( encj_struct.ETH_Mode == ETH_FULL_DPLX ) {
			//SET PDPXMD 
		  temp = encj_phy_write( PHCON1 , (PHCON1_MASK  | PHCON1_PPWRSV_BM | PHCON1_PRST_BM) , PHCON1_PDPXMD_BM );
		  if ( IS_ERROR( temp ) ) { return temp ;}		
		  temp = encj_phy_write( PHCON2 , (PHCON2_MASK | PHCON2_TXDIS_BM | PHCON2_JABBER_BM | PHCON2_HDLDIS_BM) , PHCON2_FRCLNK_BM);
		  if ( IS_ERROR( temp ) ) { return temp ;}	 

	}
	else if ( encj_struct.ETH_Mode == ETH_HALF_DPLX ) {
		// CLEAR PDPXMD 
		temp = encj_phy_write( PHCON1 , (PHCON1_MASK | PHCON1_PLOOPBK_BM | PHCON1_PPWRSV_BM | PHCON1_PRST_BM) , 0X00 );
		if ( IS_ERROR( temp ) ) { return temp ;}	
		//SET HDLDIS
		temp = encj_phy_write( PHCON2 , (PHCON2_MASK|PHCON2_FRCLNK_BM|PHCON2_JABBER_BM|PHCON2_TXDIS_BM) , PHCON2_HDLDIS_BM );
		if ( IS_ERROR( temp ) ) { return temp ;}	 
		
	}
	
	// SET LED CONFIGURATION 
		
		temp = 0 ; 
		temp = ( ( ( encj_struct.PHY_Struct_Ptr->LEDA ) << PHILCON_LACFG0_BP ) |
				 ( ( encj_struct.PHY_Struct_Ptr->LEDB ) << PHILCON_LBCFG0_BP ) |
				 ( ( encj_struct.PHY_Struct_Ptr->LED_Stretch_Config ) << PHILCON_STRCH_BP ) ) ;
				 
		temp = encj_phy_write( PHILCON , PHILCON_MASK , temp );
		if ( IS_ERROR( temp ) ) { return temp ;}	
	// ENABLE RXEN INT
	
	encj_write_reg( EIE , encj_struct.Interrupt_Mask  , REG8 ) ;
	
	// ENABLE RXEN 
	encj_bit_set( ECON1 , ECON1_RXEN_BM);
	
	
	uart_print( " here man " , &USARTE0 ) ;
	
	
	return ERRC_SUCCESS ; 
	
	
}



// Main function to be used for sending Packets 


int16_t Encj_SendPacket( ETH_Packet * packet ) {
	
	int16_t temp ; 
	#if defined( ETH_FULL_ASSERT ) 
	//ASSERT TRANSMISSION CONDITIONS 
	if ( ( ETH_Position_TX.WR_Pos <= RX_tail )||
		 ( ETH_Position_TX.RD_Pos <= RX_tail )||
		 ( ETH_Position_TX.WR_Pos > ETH_BUFF_END )||
		 ( ETH_Position_TX.RD_Pos > ETH_BUFF_END )||
		 (	ETH_Position_TX.RD_Pos != ETH_Position_TX.WR_Pos ) ||
		 ( packet == NULL ) ) { return error_handler( ERRC_ASSERT ) ; }
	
	#endif 
	// load pointers 
	
	
	ETH_Position_TX.WR_Pos = RX_tail + 1UL; 
	ETH_Position_TX.RD_Pos = RX_tail + 1UL;
	
		 
	// Check for enough free space 	 
	
	temp = 15UL + packet->payload_len ; 
	
	if ( ( ETH_BUFF_END - ETH_Position_TX.WR_Pos + 1 ) < ( temp + 7UL ) ){
		
		return error_handler ( ERRC_TX_NO_SPACE ) ; 
		
		
	}
	
	// Load the packet 
	
	
	temp = encj_load_packet( packet , &ETH_Position_TX ) ;
	
	if ( IS_ERROR( temp ) ) { return error_handler(temp ) ; }
	
	return ERRC_SUCCESS ; 
	
}
	
	

int16_t Encj_ReceivePacket ( ETH_Packet * packet ) {
	
	int16_t temp ; 
	#if defined( ETH_FULL_ASSERT ) 
	// ASSERT THE POINTERS 
	if ( ( ETH_Position_RX.WR_Pos > RX_tail )||
		 ( ETH_Position_RX.RD_Pos > RX_tail )||
		 ( ETH_Position_RX.WR_Pos > ETH_BUFF_END )||
		 ( ETH_Position_RX.RD_Pos > ETH_BUFF_END )||
		 ( RX_tail == 0 )||
		 (	ETH_Position_RX.RD_Pos != ETH_Position_RX.WR_Pos ) ||
		 ( packet == NULL ) ) { return error_handler( ERRC_ASSERT ) ; }
	#endif 
												
	
	//Check if there are any packets
	
	temp = encj_read_reg( EPKTCNT , REG8 ) ; 
	if ( IS_ERROR(temp) ) { return error_handler(temp) ; }
	
	if ( temp == 0 ) { 
						return error_handler( ERRC_RX_EMPTY ) ; }
						
						
	// Fetch the packet 
	
	temp = encj_get_packet( packet , &ETH_Position_RX ) ;
	if ( IS_ERROR(temp ) ) { return error_handler(temp); }
	
	// Packet fetch done , now we decrement EPKTCNT 
	
	temp = encj_bit_set( ECON2 , ECON2_PKTDEC_BM ) ; 
	if ( IS_ERROR(temp) ) { return error_handler(temp) ; }
	
	
	return ERRC_SUCCESS ;
	

}	 


int16_t Encj_Get_PacketCount ( void ) { 
	
	int16_t temp ; 
	
	//Read Packet Count 
	temp = encj_read_reg( EPKTCNT , REG8 ) ;
	if ( IS_ERROR(temp ) ) { return error_handler( temp ) ;}
	
	return temp ;

}

int16_t Encj_Get_TX_Size ( void ) {
	
	return ( ETH_BUFF_END - ETH_Position_TX.WR_Pos ) ;
	
}

int16_t Encj_Get_RX_Size ( void ) {
	
	return ( RX_tail - ETH_BUFF_START ) ;
} 

int16_t Encj_Get_Status ( void ) {
	
	int16_t temp ; 
	
	temp = encj_read_reg( EIR , REG8) ;
	if ( IS_ERROR(temp ) ) { return error_handler(temp ) ; }
	return (uint8_t) temp ;
	
}

int16_t Encj_Interrupt_Set ( uint8_t interrupt_mask ) {
	
	int16_t temp ;
	
	temp = encj_write_reg ( EIE , interrupt_mask , REG8 ) ;
	if ( IS_ERROR(temp ) ) { return error_handler(temp ) ; }
	return ERRC_SUCCESS ; 
	
}




int16_t Encj_realloc( uint16_t rx_size ) {
	
	int16_t temp ;
	uint8_t i  = TXRTS_TIMEOUT_VAL ;
	//ASSERT NEW SIZE 
	#if defined( ETH_FULL_ASSERT )
	if( rx_size > ETH_BUFF_END ) { return ERRC_ASSERT ; } 
	 #endif 
	 
	 //Note , to reallocate , the receive buffer must be empty , EPTCKNT Must be 0 
	 temp = encj_read_reg(EPKTCNT , REG8 ) ;
	 if ( IS_ERROR ( temp ) ) { return error_handler( temp ) ; } 
	 if ( temp == 0 ) { return error_handler ( ERRC_REALLOC_FAIL ) ; }
	//First we disable the Receive unit 
	encj_bit_clear( ECON1 , ECON1_RXEN_BM ) ;
	//Check for ongoing transmissions
	
	do {
		
		temp = encj_read_reg( ECON1 , REG8 ) ;
		if ( IS_ERROR(temp ) ) { return error_handler( temp ) ; }
		_delay_us( TXRTS_DELAY_VAL ) ;
		--i ;
}while ( ( ( temp ) & ( 1 << ECON1_TXRTS_BP ) ) && ( i ) ) ; 
	
if ( i == 0 ) { return error_handler ( ERRC_TX_TIMEOUT ) ; }
// NO ongoing transmissions , now we modify pointers 

encj_write_reg( ERXNDL , rx_size -1 , REG16 ) ;
encj_write_reg( ERXRDPTL , ETH_BUFF_START , REG16 ) ;
encj_write_reg( ERXWRPTL , ETH_BUFF_START , REG16 ) ;
ETH_Position_RX.RD_Pos = ETH_BUFF_START ;
ETH_Position_RX.WR_Pos = ETH_BUFF_START ;

RX_tail = rx_size -1 ; 


// Modify TX PARAMS 
ETH_Position_TX.RD_Pos = rx_size + 1UL ;
ETH_Position_TX.WR_Pos = rx_size + 1UL ;

//Re-enable RX 
	
encj_bit_set( ECON1 , ECON1_RXEN_BM ) ;	
	

return ERRC_SUCCESS ;	
	
	
}
	 
	 
	 
__attribute__((weak)) int16_t error_handler ( int16_t error_code ) {
	
	
	// For Now the default handler will try to print debug information when it is called 
	
	// Print ERR VAL
	uart_print( " \nERR_CODE : " , &USARTE0 ) ;
	uart_print_num ( error_code , 10 , 0 , &USARTE0 ) ;
	uart_print("\n" , &USARTE0);
	
			
	if ( command == CMD_RCR ) { 
		
		
		uart_print(" \n AT READING COMMAND " ,&USARTE0 ) ;
	}	
	
	else if ( command = CMD_WCR ){
		
				uart_print(" \n AT WRITING COMMAND " ,&USARTE0 ) ;

				
			}
			
	uart_print(" \n WITH VAL :  "         , &USARTE0 );
	uart_print_num ( write_val , 16 , 0 , &USARTE0 ) ;	
	
	uart_print(" \n LAST READ VAL :  "         , &USARTE0 );
	uart_print_num ( last_read_val , 16 , 0 , &USARTE0 ) ;		
			
	uart_print(	"\n AT REGISTER :  " ,&USARTE0 ) ;
	uart_print_num ( register_address , 16 , 0 , &USARTE0 ) ;
	
	uart_print(	"\n AT BANK :  " ,&USARTE0 ) ;
	uart_print_num ( current_bank , 16 , 0 , &USARTE0 ) ;
	
		
		
	return error_code ; 
	

	
	
}	 
 
