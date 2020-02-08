


//include eeprom.h for EEMEM definitions 

#include "GENERAL/header.h"

#define VAL         0X8000   
#define PARAM       0X4000
#define NO_PARAM    0X2000

      

#define AT_CMD      0X0000
#define ATCPOF_CMD  0X0001 | NO_PARAM
#define ATS0_CMD    0X0002 | PARAM
#define ATS3_CMD    0X0003 | PARAM
#define ATS4_CMD    0X0004 | PARAM
#define ATS5_CMD    0X0005 | PARAM 
#define SWITCH_CMD  0X0006 | NO_PARAM
#define ATO_CMD     0X0007 | VAL
#define ATF_CMD     0X0008 | VAL
#define ATV_CMD     0X0009 | VAL
#define ATE_CMD     0X000A | VAL
#define ATW_CMD     0X000B | VAL
#define ATQ_CMD     0X000C | VAL

#define AT     "AT"
#define ATCPOF "AT+CPOF"                           //Power-off cmd 
#define ATS0   "ATS0"                              //Automatic Answering ( 0 Disabled ) , 0-255 , answers after n rings 
#define ATS3   "ATS3"							   //Response Formatting character /r  ( DECIMAL)
#define ATS4   "ATS4"                              //Response Formatting character /n  ( DECIMAL)
#define ATS5   "ATS5"                              //Respone  Formatting character ( indicates character that is recognized to delete the preceding character )
#define SWITCH "+++"                               //Switch back to command mode from online data mode.
#define ATO    "ATO"                               //Switch to online data mode from command mode.
#define ATF    "AT&F"                              //Set all parameters to default value ( which is indicated by val , if val =0 >> factory reset)    
#define ATV    "ATV"                               //Set Response code format mode , 0 = NUMERIC FORM SHORT FORMAT , 1 = LONG VERBOSE FORMAT
#define ATE    "ATE"                               //ECHO MODE ON = 1 , ECHO MODE OFF = 0 
#define ATW    "AT&W"                              //Stores the current configuration in non-volatile memory  VAL = USER PROFILE NUMBER
#define ATQ    "ATQ"                               //Suppresses Response code transmission , VAL = 0 NOT SUPPRESSED , VAL = 1 SUPPRESSED
#define ATX    "ATX"                               //    
