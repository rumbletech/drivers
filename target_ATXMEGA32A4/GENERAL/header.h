


#ifndef HEADER_TOKEN
#define HEADER_TOKEN 1  

#define F_CPU   32000000UL
#define F_PERPH 32000000UL


#define UART_E0_RX  2
#define UART_E0_TX  3 
#define UART_E0_XCK 1

#define UART_C0_RX  2
#define UART_C0_TX  3
#define UART_C0_XCK 1

#define UART_C1_RX  6
#define UART_C1_TX  7
#define UART_C1_XCK 5

#define UART_D0_RX  2
#define UART_D0_TX  3
#define UART_D0_XCK 1

#define UART_D1_RX  6
#define UART_D1_TX  7
#define UART_D1_XCK 5

typedef enum{
	
	INT_DISABLED        = 0B00 ,
	INT_LOW_PRIORITY    = 0B01 ,
	INT_MEDIUM_PRIORITY = 0B10 ,
	INT_HIGH_PRIORITY   = 0B11 ,
	
} int_level ;


#endif 
