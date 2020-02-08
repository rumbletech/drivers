/** @file sysclk.h
 * Author : Mohamed Yousry Mohamed Rashad 
 * 
 * 
 * File Discription : This header file contains externs to basic system startup calls , definitions, and system clock related calls , like enabling and disabling DFLL 
 * or changing PLL prescalers and clock options and so on .
 * 
 * 
 */

#ifndef SYSCLK_TOKEN
#define SYSCLK_TOKEN 1 

#include "../GENERAL/header.h"


/** A prescaler values , can be ored with PSCBC_DIV to generate prescalers for the peipherals
 *  Note : This generates Peripheral CLK4 
 **/
#define PSCA_DIV1   0B00000000
#define PSCA_DIV2   0B00000100
#define PSCA_DIV4   0B00001100
#define PSCA_DIV8	0B00010100
#define PSCA_DIV16  0B00011100
#define PSCA_DIV32  0B00100100
#define PSCA_DIV64  0B00101100
#define PSCA_DIV128 0B00110100
#define PSCA_DIV256 0B00111100
#define PSCA_DIV512 0B01000100

/** B,C prescaler values , can be ored with PSCA_DIV to generate prescalers for the peipherals
 *  Note : B PRESCALER DECIDES PERIPHERAL CLK2 , C PRESCALER DECIDES PERIPHERAL CLK AND CPU CLK 
 **/
 
 #define PSCBC_DIV1_1 0B00000000
 #define PSCBC_DIV1_2 0B00000001
 #define PSCBC_DIV4_1 0B00000010
 #define PSCBC_DIV2_2 0B00000011






#ifndef CCP_IO_PROTECTION_VAL 
#define CCP_IO_PROTECTION_VAL 0XD8 
#endif

#ifndef CCP_SPM_PROTECTION_VAL
#define CCP_SPM_PROTECTION_VAL 0X9D
#endif 


/** Description : Clock select configuration for the system clock , it may be given as a parameter to a startup call 
 * */
typedef enum {
	RC2MHZ   = 0B000 , /**< RC2MHZ : selects the 2 MHZ internal RC oscillator. */
	RC32MHZ  = 0B001 , /**< RC32MHZ: selects the 32 MHZ internal RC oscillator. */
	RC32KHZ  = 0B010 , /**< RC2MHZ : selects the 32.768 KHZ internal RC oscillator. */
	XOSC     = 0B011 , /**< RC2MHZ : selects an external XTAL Crystal oscillator( or an external oscillator */
	PLL      = 0B100 , /**< PLL    : selects the internal PLL as a clock source , when this option is chosen , another sys_clksel parameter must be selected as an input to the pll . */ 
	
} sys_clksel ;


// to do 
//typedef enum{
	
	
	
	
//} xosc_freq ; 



/** Discription : (same as before but this one locks the clock selection )This function starts up the main clock of the controller , it starts it up using internal calibrated oscillators 
 *  it starts it up using internal calibrated RC ( 32.768KHZ , 2MHZ , 32 MHZ ) 
 *  it starts up 32.768KHZ internal oscillator as input to the DFLL.
 *  it starts up DFLL Module with intenral 32.768KHZ as reference.
 *  if no internal clock source is selected it does nothing .  
 *  it doesn't lock the clock selection after its done.
 * 
 * @param clock_source : one of the entities of clksel which is one of the internal clock source (RC2MHZ,RC32MHZ,RC32KHZ)
 * @param prescalers   : OR of one PSCA_DIVX and one of PSCBC_DIVX_Y , it sets the peripheral clks and keeps dividing , division is cascaded .
 * @return : void 
 * */
 
__attribute__((always_inline)) void static inline startup_int_nolock ( sys_clksel clock_source , uint8_t prescalers){
	
	switch ( clock_source ) {
		
		case RC2MHZ :

		// Enable 2MHZ OSCILLATOR 
		OSC.CTRL = ( 1 << OSC_RC2MEN_bp ) | ( 1 << OSC_RC32KEN_bp ) ;
		//Wait for the oscillator to be stable 
		while ( !( OSC.STATUS & ( 1 << OSC_RC2MRDY_bp ) ) ) ;
		// Wait for 32KHZ OSCILLATOR FOR DFLL
		while ( !( OSC.STATUS & ( 1 << OSC_RC32KRDY_bp ) ) ) ;
		//Configuration protection disabled
		CCP = CCP_IOREG_gc ;
		//Write prescalers
		CLK.PSCTRL = prescalers ; 
		//Configuration protection disabled 
		CCP = CCP_IOREG_gc ; 
		//Clock source selection .
		CLK.CTRL = RC2MHZ ;
		//DFLL CKSEL - reference : Internal 32.768 KHZ 
		OSC.DFLLCTRL = 0 ;
		// DFLL Enabled 
		DFLLRC2M.CTRL = 1 ;
		
		break;
		
		case RC32MHZ :
		
		// Enable 2MHZ OSCILLATOR 
		OSC.CTRL = ( 1 << OSC_RC32MEN_bp ) | ( 1 << OSC_RC32KEN_bp );
		//Wait for the oscillator to be stable 
		while ( !( OSC.STATUS & ( 1 << OSC_RC32MRDY_bp ) ) ) ;
		// Wait for 32 KHZ OSCILLATOR FOR DFLL 
		while ( !( OSC.STATUS & ( 1 << OSC_RC32KRDY_bp ) ) ) ;
		//Configuration protection disabled
		CCP = CCP_IOREG_gc ;
		//Write prescalers
		CLK.PSCTRL = prescalers ; 
		//Configuration protection disabled 
		CCP = CCP_IOREG_gc ; 
		//Clock source selection .
		CLK.CTRL = RC32MHZ ;
		//DFLL CKSEL - reference : Internal 32.768 KHZ 
		OSC.DFLLCTRL = 0 ;
		// DFLL Enabled 
		DFLLRC32M.CTRL = 1 ;
		 
		break;
		
		case RC32KHZ : 
		
		// Enable 32 KHZ OSCILLATOR 
		OSC.CTRL =  ( 1 << OSC_RC32KEN_bp ) ;
		// Wait for 32KHZ OSCILLATOR 
		while ( !( OSC.STATUS & ( 1 << OSC_RC32KRDY_bp ) ) ) ;
		//Configuration protection disabled
		CCP = CCP_IOREG_gc ;
		//Write prescalers
		CLK.PSCTRL = prescalers ; 
		//Configuration protection disabled 
		CCP = CCP_IOREG_gc ; 
		//Clock source selection .
		CLK.CTRL = RC32KHZ ;
		break ;
		
	}
	
}


/** Discription : This function starts up the main clock of the controller , it starts it up using internal calibrated oscillators 
 *  it starts it up using internal calibrated RC ( 32.768KHZ , 2MHZ , 32 MHZ ) 
 *  it starts up 32.768KHZ internal oscillator as input to the DFLL.
 *  it starts up DFLL Module with intenral 32.768KHZ as reference.
 *  if no internal clock source is selected it does nothing .  
 *  it locks the clock selection after its done.
 * 
 * @param clock_source : one of the entities of clksel which is one of the internal clock source (RC2MHZ,RC32MHZ,RC32KHZ)
 * @param prescalers   : OR of one PSCA_DIVX and one of PSCBC_DIVX_Y , it sets the peripheral clks and keeps dividing , division is cascaded .
 * @return : void 
 * */


__attribute__((always_inline)) void static inline startup_int_lock ( sys_clksel clock_source , uint8_t prescalers){
	
	switch ( clock_source ) {
		
		case RC2MHZ :

		// Enable 2MHZ OSCILLATOR 
		OSC.CTRL = ( 1 << OSC_RC2MEN_bp ) | ( 1 << OSC_RC32KEN_bp ) ;
		//Wait for the oscillator to be stable 
		while ( !( OSC.STATUS & ( 1 << OSC_RC2MRDY_bp ) ) ) ;
		// Wait for 32KHZ OSCILLATOR FOR DFLL
		while ( !( OSC.STATUS & ( 1 << OSC_RC32KRDY_bp ) ) ) ;
		//Configuration protection disabled
		CCP = CCP_IOREG_gc ;
		//Write prescalers
		CLK.PSCTRL = prescalers ; 
		//Configuration protection disabled 
		CCP = CCP_IOREG_gc ; 
		//Clock source selection .
		CLK.CTRL = RC2MHZ ;
		//DFLL CKSEL - reference : Internal 32.768 KHZ 
		OSC.DFLLCTRL = 0 ;
		// DFLL Enabled 
		DFLLRC2M.CTRL = 1 ;
		// Lock clock selection until next reset 
		CCP = CCP_IOREG_gc;
		CLK.LOCK = 1 ;
		break;
		
		case RC32MHZ :
		
		// Enable 2MHZ OSCILLATOR 
		OSC.CTRL = ( 1 << OSC_RC32MEN_bp ) | ( 1 << OSC_RC32KEN_bp );
		//Wait for the oscillator to be stable 
		while ( !( OSC.STATUS & ( 1 << OSC_RC32MRDY_bp ) ) ) ;
		// Wait for 32 KHZ OSCILLATOR FOR DFLL 
		while ( !( OSC.STATUS & ( 1 << OSC_RC32KRDY_bp ) ) ) ;
		//Configuration protection disabled
		CCP = CCP_IOREG_gc ;
		//Write prescalers
		CLK.PSCTRL = prescalers ;  
		//Configuration protection disabled 
		CCP = CCP_IOREG_gc ; 
		//Clock source selection .
		CLK.CTRL = RC32MHZ ;
		//DFLL CKSEL - reference : Internal 32.768 KHZ 
		OSC.DFLLCTRL = 0 ;
		// DFLL Enabled 
		DFLLRC32M.CTRL = 1 ;
		// Lock clock selection until next reset 
		CCP = CCP_IOREG_gc;
		CLK.LOCK = 1 ; 
		break;
		
		case RC32KHZ : 
		
		// Enable 32 KHZ OSCILLATOR 
		OSC.CTRL =  ( 1 << OSC_RC32KEN_bp ) ;
		// Wait for 32KHZ OSCILLATOR 
		while ( !( OSC.STATUS & ( 1 << OSC_RC32KRDY_bp ) ) ) ;
		//Configuration protection disabled
		CCP = CCP_IOREG_gc ;
		//Write prescalers
		CLK.PSCTRL = prescalers ;  
		//Configuration protection disabled 
		CCP = CCP_IOREG_gc ; 
		//Clock source selection .
		CLK.CTRL = RC32KHZ ;
		// Lock clock selection until next reset 
		CCP = CCP_IOREG_gc;
		CLK.LOCK = 1 ;
		break ;
		
	}
	
}
		
		
		
	


__attribute__((always_inline)) void static inline startup_ext_nolock ( sys_clksel clock_source ) {
	// to be implemented later if needed 
	
	
}  


__attribute__((always_inline)) void static inline startup_ext_lock ( sys_clksel clock_source ) {
	// to be implemented later if needed 
	
	
}  


__attribute__((always_inline)) void static inline startup_pll_nolock ( sys_clksel clock_source ) {
	// to be implemented later if needed 
	
	
}  

__attribute__((always_inline)) void static inline startup_pll_lock ( sys_clksel clock_source ) {
	// to be implemented later if needed 
	
	
}  




#endif 

