







#ifndef SPI_TOKEN 
#define SPI_TOKEN 1

#include "../GENERAL/header.h"


#if defined(__AVR_ATxmega32A4__)

#define SPID_SS   4
#define SPID_MOSI 5
#define SPID_MISO 6
#define SPID_SCK  7

#define SPIC_SS   4
#define SPIC_MOSI 5
#define SPIC_MISO 6
#define SPIC_SCK  7

#endif 

typedef enum { 
	
	SPI_CPOL_L_PHA_F = 0B00 ,
	SPI_CPOL_L_PHA_S = 0B01 ,
	SPI_CPOL_H_PHA_F = 0B10 ,
	SPI_CPOL_H_PHA_S = 0B11 , 
	
	
} SPI_Clk_Config ; 


typedef enum {
	
	SPI_PRESCALE_2   = 0X80UL ,
	SPI_PRESCALE_4   = 0x00UL ,
	SPI_PRESCALE_8   = 0X81UL ,
	SPI_PRESCALE_16  = 0X01UL ,
	SPI_PRESCALE_32  = 0X82UL ,
	SPI_PRESCALE_64  = 0X02UL ,
	SPI_PRESCALE_128 = 0X03UL ,
	
	
} SPI_Clk_Prescale ; 


typedef enum{
	
	SPI_MASTER = 1 , 
	SPI_SLAVE  = 0 ,
	
	
} SPI_Mode ; 


typedef enum {
	
	SPI_MSB_FIRST = 0 ,
	SPI_LSB_FIRST = 1 , 
	
} SPI_Data_Order ; 


typedef struct {

SPI_t*           SPI_module     ; 	
SPI_Mode         SPI_mode       ;
SPI_Data_Order   SPI_dor        ; 
SPI_Clk_Prescale SPI_prescale   ;
SPI_Clk_Config   SPI_clk_config ; 
int16_t INT_level               ; 

} SPI_Init_Struct ; 



int16_t SPI_Init( SPI_Init_Struct spi_struct ) ;
int16_t SPI_Deinit( SPI_Init_Struct spi_struct  );
int16_t SPI_NB_SendReceive (  uint8_t val , SPI_t * spi_module , uint16_t timeout ) ;
uint8_t SPI_B_SendReceive (  uint8_t val , SPI_t * spi_module , uint16_t timeout ) ;
void SPI_Int_Send( uint8_t val  ,SPI_t * spi_module  );
uint8_t SPI_Int_Receive ( SPI_t * spi_module  );


#endif 
