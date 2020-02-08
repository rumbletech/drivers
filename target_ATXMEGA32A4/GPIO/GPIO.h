/** @file GPIO.h
 * Author : Mohamed Yousry Mohamed Rashad 
 * 
 * 
 * File Discription : This is a header file that will include , most Port IO operation calls on the target mcu = ATXMEGA32A4
 * 					  if another microcontroller is chosen in the the same family ATXMEGAXXA4 then the file is probably compatible ,
 * 					  just change the gcc command -mmcu = ATXMEGAXXXA4 , and hopefully it will compile . 
 * 
 * 
 */
 
 #ifndef GPIO_TOKEN
 #define GPIO_TOKEN 1 


#include "../GENERAL/header.h"



#define OUTPUT_INVERT_MASK 0B01000000  /** Output inversion mask , must be logically or-ed with the opconfig of the pin .*/
#define OUTPUT_SRL_MASK    0B10000000  /** Slew Rate limit mask  , must be logically or-ed with the opconfig of the pin .*/
#define INT0_CLEAR_MASK    0B11111100
#define INT1_CLEAR_MASK    0B11110011
#define VPORTA 0
#define VPORTB 1
#define VPORTC 2
#define VPORTD 3

#ifndef VPORT0_MAP 
#define VPORT0_MAP VPORTA
#warning "'VPORT0_MAP' not defined ,PORTA is by default mapped to VPORT0 , in init function " 
#endif

#ifndef VPORT1_MAP
#define VPORT1_MAP VPORTB
#warning "'VPORT1_MAP' not defined ,PORTB is by default mapped to VPORT1 , in init function " 
#endif

#ifndef VPORT2_MAP
#define VPORT2_MAP VPORTC
#warning "'VPORT2_MAP' not defined ,PORTC is by default mapped to VPORT2 , in init function " 
#endif

#ifndef VPORT3_MAP
#define VPORT3_MAP VPORTD
#warning "'VPORT3_MAP' not defined , PORTD is by default mapped to VPORT3 , in init function " 
#endif 



/**
 * Description : Specifies the output/pull configuration for port pins when output and input as such output_input.
 */
 
typedef enum {
	
	TOTEMPOLE_Z         =  0B000 << PORT_OPC0_bp, /**< TOTEMPOLE_Z : OUTPUT is TOTEMPOLE , when input it is in Z state. */
	TOTEMPOLE_BUSKEEPER =  0B001 << PORT_OPC0_bp, /**< TOTEMPOLE_Z : OUTPUT is TOTEMPOLE , when input it is in Z state. */
	TOTEMPOLE_PULLDOWN  =  0B010 << PORT_OPC0_bp, /**< TOTEMPOLE_BUSKEEPER : OUTPUT is TOTEMPOLE , When input it is in buskeeper mode which preserves the last input on the pin. */
	TOTEMPOLE_PULLUP    =  0B011 << PORT_OPC0_bp, /**< TOTEMPOLE_PULLUP    : OUTPUT is TOTEMPOLE , When input it is pulled up by an active resistor. */
	WIREDOR_Z           =  0B100 << PORT_OPC0_bp, /**< WIREDOR_Z           : OUTPUT is ORWIRED ( when OUTPUT is High , the pin is high . when OUTPUT is low , it is open drain(Z) ) , when input it is open drain / Z. */
	WIREDAND_Z          =  0B101 << PORT_OPC0_bp, /**< WIREDAND_Z          : OUTPUT IS ANDWIRED( when OUTPUT is low  , the pin is low  . when OUTPUT is high , it is Z ) , When input , its is in Z state. */
	WIREDOR_PULLDOWN    =  0B110 << PORT_OPC0_bp, /**< WIREDOR_PULLDOWN    : Same as WIREDOR_Z but instead of Z states in the output and input it is pulled low internally instead. */
	WIREDAND_PULLUP     =  0B111 << PORT_OPC0_bp, /** WIREDAND_PULLUP     : Same as WIREDAND_Z but instead of Z states in the output and input it is pulled high internally instead. */
	
} opcconfig ; 


/** Description : Input sense configuration for pin n , this will determine the interrupt event sensed on the pin . */

typedef enum {
	
     SENSE_BOTH_EDGES     = 0B000 , /**< The pin will get event triggered by any edge in the input. */
     SENSE_RISING_EDGE    = 0B001 , /**< The pin will get event triggered by a rising edge in the input. */
	 SENSE_FALLING_EDGE   = 0B010 , /**< The pin will get event triggered by a falling edge in the input. */
	 SENSE_LEVEL          = 0B011 , /**< The pin will get event triggered by any level change in the input. */
	 SENSE_INPUT_DISABLED = 0B100 , /**< Digital input is disabled completely on this pin */
	 
} iscconfig ; 

/** Description : Describes the direction of port pins .*/

typedef enum {
	
	OUTPUT = 1 , /**< The pin is in OUTPUT direction */
	INPUT  = 0 , /**< The pin is in INPUT  direction */
} pindir ; 








/** Description :
 *  Configures a port pin with an output/pull configuration and sets its direction 
 *  @param pin_num : number of the port pin .
 *  @param port_t  : Pointer to a PORT , ex ( &PORTA , &PORTB ...  . 
 *  @param pin_dir : Direction of the pin ( OUTPUT , INPUT ) .
 *  @param opcconfig : Output/pull configuration for the pin .
 *  @param iscconfig : input sense configuration for the pin .
 * 
 *  @return void : returns nothing 
 */


__attribute__((always_inline)) void static inline pin_config ( uint8_t pin_num , PORT_t* port_t , pindir pin_dir , opcconfig output_config , iscconfig sense_config ) {
	
	*( (uint8_t*) port_t + 0x10 + pin_num ) = ( output_config  ) | ( sense_config) ;
    pin_dir ?( port_t->DIRSET = ( 1 << pin_num ) ): ( port_t->DIRCLR = ( 1 << pin_num ) ) ; 
    
}



/** Description :
 *  Configures a port pin with an output/pull configuration and sets its direction 
 *  @param pin_mask : mask that contains the pins with the same configuration .
 *  @param port_t  : Pointer to a PORT , ex ( &PORTA , &PORTB ...  . 
 *  @param port_dir : Direction of the port pins ( OUTPUT , INPUT ) .
 *  @param opcconfig : Output/pull configuration for the pin .
 *  @param iscconfig : input sense configuration for the pin .
 * 
 *  @return void : returns nothing 
 */

	
__attribute__((always_inline)) void static inline pin_group_config ( uint8_t pin_mask , PORT_t* port_t , pindir port_dir , opcconfig output_config , iscconfig sense_config ){
	 uint8_t i = 0 ; 
	PORTCFG_MPCMASK = pin_mask ; 
	
	if ( pin_mask%2 == 1 ) { i = 0 ; } 
	else if ( pin_mask >= 128 ) { i = 7 ; }
	else if ( pin_mask >= 64  ) { i = 6 ; }
	else if ( pin_mask >= 32  ) { i = 5 ; }
	else if ( pin_mask >= 16  ) { i = 4 ; }
	else if ( pin_mask >= 4   ) { i = 3 ; }
	else if ( pin_mask >= 2   ) { i = 2 ; }
	else { i = 1 ; }
	 
	*( (uint8_t*) port_t + 0x10 + i ) = ( output_config  ) | ( sense_config ) ;
	port_dir ?( port_t->DIRSET = ( pin_mask ) ): ( port_t->DIRCLR = ( pin_mask ) ) ; 

}

	 
	

/** Description : Sets a pin ( non rmw ).
 * @param pin_num : pin number .
 * @param port_t  : pointer to a PORT
 * @return void : no return . .
 */
 

__attribute__((always_inline)) void static inline pin_set ( uint8_t pin_num , PORT_t* port_t ) {
	
	port_t->OUTSET = ( 1 << pin_num ) ; 
	
	}
	
	
/** Description : Clears a pin ( non rmw ).
 * @param pin_num : pin number .
 * @param port_t  : pointer to a PORT
 * @return void : no return .
 */	
	
__attribute__((always_inline)) void static inline pin_clear ( uint8_t pin_num , PORT_t* port_t ) {
	
	port_t->OUTCLR = ( 1 << pin_num ) ; 
	
	}
	

/** Description : toggles a pin ( non rmw ).
 * @param pin_num : pin number .
 * @param port_t  : pointer to a PORT
 * @return void : no return . 
 */	
	
__attribute__((always_inline)) void static inline pin_toggle ( uint8_t pin_num , PORT_t* port_t ) {
	
	port_t->OUTTGL = ( 1 << pin_num ) ; 
	
	}		
	
	
/** Description : returns a pin value either high or low .
 * @param pin_num : pin number .
 * @param port_t  : pointer to a PORT.
 * @return : returns pin value ( 1 for high ) ( 0 for low ). */	
	
__attribute__((always_inline)) uint8_t static inline pin_read( uint8_t pin_num , PORT_t* port_t ){
	
	return ( ( ( port_t->IN ) & ( 1 << pin_num ) ) ? 1 : 0 ) ;
}	

/** Description : writes an 8 bit val to a port ( rmw ).
 * @param port_val : value of the PORT to be written.
 * @param port_t  : pointer to a PORT
 * @return void : no return . 
 */

__attribute__((always_inline)) void static inline port_write ( uint8_t port_val , PORT_t* port_t ) {
	
	port_t->OUT = port_val ; 
	
	}
	
	/** Description : reads an input port value .
 * @param port_t  : pointer to a PORT
 * @return : returns the value of the PORT read from the IN register. 
 */
	
__attribute__((always_inline)) uint8_t static inline port_read (  PORT_t* port_t ) {
	
	return ( port_t->IN ); 
	
	}
	
/** Description : sets bit in an 8 bit val (non rmw ) , bits that are not specified in port_val are not affected .
 * @param port_val : value of the PORT to be written.
 * @param port_t  : pointer to a PORT
 * @return void : no return . 
 */
	
__attribute__((always_inline)) void static inline port_set( uint8_t port_val , PORT_t* port_t ) {
	
	port_t->OUTSET = port_val ; 
	
	}	
	
/** Description : clears bits in an 8 bit val (non rmw ) , bits that are not specified in port_val are not affected .
 * @param port_val : value of the PORT to be written.
 * @param port_t  : pointer to a PORT
 * @return void : no return . 
 */	
	
__attribute__((always_inline)) void static inline port_clear( uint8_t port_val , PORT_t* port_t ) {
	
	port_t->OUTCLR = port_val ; 
	
	}	
	
	
/** Description : toggles bits in an 8 bit val (non rmw ) , bits that are not specified in port_val are not affected .
 * @param port_val : value of the PORT to be written.
 * @param port_t  : pointer to a PORT
 * @return void : no return . 
 */	
	
__attribute__((always_inline)) void static inline port_toggle( uint8_t port_val , PORT_t* port_t ) {
	
	port_t->OUTTGL= port_val ; 
	
	}
	
/** Description : Changes the direction of the port pin , it doesn't affect other pins.
 * @param pin_num : pin number.
 * @param pin_dir : direction of the pin .
 * @param port_t  : pointer to a PORT
 * @return void : no return . 
 */	

__attribute__((always_inline)) void static inline pin_chdir( uint8_t pin_num ,pindir pin_dir , PORT_t* port_t ) {
	
	pin_dir ? ( port_t->DIRSET = ( 1 << pin_num ) ) : ( port_t->DIRCLR = ( 1 << pin_num ) ) ;
	
}

/** Description : Changes the direction of multiple pins , pins written to 1 are changed , others are unaffected.
 * @param port_val : mask that specifies bits to change direction.
 * @param pin_dir  : direction of the pins.
 * @param port_t   : pointer to a PORT
 * @return void : no return . 
 */	

__attribute__((always_inline)) void static inline port_chdir( uint8_t port_val ,pindir pin_dir , PORT_t* port_t ) {

	pin_dir ? ( port_t->DIRSET = ( port_val ) ) : ( port_t->DIRCLR = ( port_val ) ) ;

}

/** Description : Changes the direction of multiple pins , pins written to 1 are outputes , THE REST ARE INPUTS..
 * @param port_val : mask that specifies bits to change direction , 1 >> OUTPUT , 0 >> INPUT .
 * @param port_t   : pointer to a PORT
 * @return void : no return . 
 */	


__attribute__((always_inline)) void static inline port_wrdir( uint8_t port_val , PORT_t* port_t ) {

	port_t->DIR = ( port_val ) ; 

}


/** Description : Writes Interrupt0 and Interrupt1 masks , INT0 is triggered by pins that correspond to written 1's in the mask .
 *  same is for INT1 .  
 * @param int0mask : mask that specifies bits that trigger int0.
 * @param int1mask : mask that specifies bits that trigger in1.
 * @param port_t   : pointer to a PORT
 * @return void : no return . 
 */	
__attribute__((always_inline)) void static inline port_INT_write( uint8_t int0mask , uint8_t int1mask , PORT_t* port_t ) {
	
	port_t->INT0MASK = int0mask ; 
	port_t->INT1MASK = int1mask ;
	
}

/** Descriptions : Activates INT0 OR DISABLES , interrupt for port_t at a specified priority level .
 * @param pr_level : specifies the priority level for INT0 .
 * @param port_t   : pointer to a port .
 * @return void    : no return 
 * */

__attribute__((always_inline)) void static inline port_INT0_set( int_level pr_level , PORT_t* port_t ) {
	
	uint8_t temp ;
	temp  = port_t->INTCTRL ; 
	temp &= INT0_CLEAR_MASK ;
	port_t->INTCTRL = temp | pr_level ; 
	
}

/** Descriptions : Activates INT1 / OR DISABLES , interrupt for port_t at a specified priority level .
 * @param pr_level : specifies the priority level for INT1 .
 * @param port_t   : pointer to a port .
 * @return void    : no return 
 * */

__attribute__((always_inline)) void static inline port_INT1_set( int_level pr_level , PORT_t* port_t ) {
	
	uint8_t temp ;
	temp  = port_t->INTCTRL ; 
	temp &= INT1_CLEAR_MASK ;
	port_t->INTCTRL = temp | ( pr_level << 2 ) ; 
	
}

/** Description : gives int0 and int1 flags for the specified port.
 * @param port_t : pointer to the port .
 * @return       : returns a uint8_t , which gives the interrupt flags ( first 2 bits ) .
 * */
 
__attribute__((always_inline)) uint8_t static inline port_rflags( PORT_t* port_t ) {
	
	return ( port_t->INTFLAGS ) ;
	
}
	
	
/** Description : Initializes Virtual ports by mapping actual ports into memory mapped IO , to 0x3F ,
 *  this function must be called before using VPORT Macros.
 * NOTE :
 * 			VPORT0_MAP : is the mapping of VPORT0 , it can be mapped to any ( PORTA,PORTB,PORTC,PORTD ) by using appropriate defines.
 *          VPORT1_MAP : is the mapping of VPORT1 , it can be mapped to any ( PORTA,PORTB,PORTC,PORTD ) by using appropriate defines.
 *          VPORT2_MAP : is the mapping of VPORT2 , it can be mapped to any ( PORTA,PORTB,PORTC,PORTD ) by using appropriate defines.
 *          VPORT3_MAP : is the mapping of VPORT3 , it can be mapped to any ( PORTA,PORTB,PORTC,PORTD ) by using appropriate defines.
 * */
__attribute__((always_inline)) void static inline vport_map_init ( void ) {

			PORTCFG_VPCTRLA = ( VPORT1_MAP << 4 )|( VPORT0_MAP );
			PORTCFG_VPCTRLB = ( VPORT3_MAP << 4 )|( VPORT2_MAP );
					
		}
	
	
	
	

/** VIRTUAL PORTS **/	
/**
 * The following inlines should be used when vport_map_init() is called , because the vports use memory mapped i/o , it uses IN/OUT instrcutions
 * and is faster than normal calls that use LDI/STS  commands .
 * However they do not suppport bit sit and bit clear like normal ports 
 * so the calls are made as macros to distinguish .
 */
 
 /** DESCRIPTION : FOR THESE FUNCTIONS USE 
  * @param : PORT : ( VPORT0,VPORT1,VPORT2,VPORT3 ) OR USE ANY OF THE NON VIRTUAL PORTS .
  * @param : VAL  : UINT8_T .
  * */
  
 #define vport_write( PORT , VAL ) PORT.OUT = VAL   /** RMW , WRITES VAL TO VPORT SPECIFIED BY PORT */
 #define vport_read( PORT ) PORT.IN 			    /** RETURNS 8 BIT INPUT PORT VALUE READ FROM VPORT SPECIFIED BY PORT */
 #define vport_wrdir(PORT, VAL ) PORT.DIR = VAL  	/** RMW , WRITES VAL TO VPORT DIRECTION REGISTER , SPECIFIED BY PORT */
 #define vport_rflags( PORT ) PORT.INTFLAGS         /** RETURNS INTERRUPT FLAGS OF VPORT SPECIFIED BY PORT THE 2 LSBS ARE VITAL , THE REST ARE RESERVED */
 #define vport_set_pin( PORT , pin_num ) PORT.OUT |= ( 1 << pin_num ) /** RMW , setsa pin */	 
 #define vport_clear_pin(PORT , pin_num ) PORT.OUT &= ~ ( 1 << pin_num ) /**RMW , clears a pin*/
	
	
	
				
	
	
#endif  
	
	
	
	
	
	


























