





//Prevent Recursive Inclusion 
#ifndef ETHERNET_TOKEN 
#define ETHERNET_TOKEN 1 

#include "../GENERAL/header.h"
// CODE MODS

#define ETH_FULL_ASSERT    1 
#define ETH_VERIFY         1 
#define ETH_DEFAULT_STRUCT 1

//Hardware Params 

#define ETHERNET_SPI  SPID
#define ETHERNET_CS   SPID_SS 
#define ETHERNET_PORT PORTD
#define ETHERNET_RESET 2
#define ETHERNET_INT   3

// TIMEOUT PARAMS
#define TIMEOUT_CMD    255UL
#define PHY_DELAY      11UL
#define PHY_BUSY_TIMEOUT 50UL
#define PHY_BUSY_NUM_TRY  100UL
#define OST_DELAY         100UL
#define OST_NUMTRY        20UL

//MACROS  
#define ETHERNET_SELECT        pin_clear( ETHERNET_CS , &ETHERNET_PORT );
#define ETHERNET_DESELECT      pin_set( ETHERNET_CS , &ETHERNET_PORT ); 
#define ETHERNET_ABORT         pin_set( ETHERNET_CS , &ETHERNET_PORT );
#define ETHERNET_HARD_RESET    pin_clear( ETHERNET_RESET , &ETHERNET_PORT ) ;
#define ETHERNET_GET_INT_STATE pin_read( ETHERNET_INT , &ETHERNET_PORT );   
#define IS_ERROR(X)        ((X < 0) ? (1UL) : (0UL)) 
#define GET_BANK(ADDR) ( (ADDR&BANK_MASK) >> 5 ) 
#define IS_PACKET_RECEIVED(X)  ((X&(1<<EIR_PKTIF_BP))? (1UL):(0UL))
#define IS_TX_COMPLETE(X)      ((X&(1<<EIR_TXIF_BP))? (1UL):(0UL))
#define IS_RX_ERROR(X)         ((X&(1<<EIR_RXERIF_BP_BP))? (1UL):(0UL)) 
#define IS_TX_ERROR(X)         ((X&(1<<EIR_TXERIF_BP_BP))? (1UL):(0UL))


//BASIC DEFINES 
#define BANK0_BASE (0X00)
#define BANK1_BASE (0X20)
#define BANK2_BASE (0X40)
#define BANK3_BASE (0X60)

#define BANK_MASK  (0X60)
#define ADDR_MASK  (0X1F)
#define MAC_MASK   (0X80)
#define IS_MAC     (0X80)
#define DUMMY_BYTE (0X00)
#define BANK_UNREAD (0XFF)
#define COMMON_REG_START (0X1B)
#define COMMON_REG_END   (0X1F)
#define ETH_BUFF_END     (0X1FFF)
#define ETH_BUFF_START   (0X0000)
#define ETX_BUFF_START   (0X0000)
#define ETX_BUFF_END     (0X1FFF)
#define RX_BUFF_START_DEFAULT (0x0000)

#define MABBIPG_FULLDPLX_VAL  0X15
#define MABBIPG_HALFDPLX_VAL  0X12
#define MAIPGL_FULLDPLX_VAL   0X0C12
#define MAIPGL_HALFDPLX_VAL   0X12
#define MAIPGH_HALFDPLX_VAL   0X0C
#define TXRTS_DELAY_VAL       5UL
#define TXRTS_TIMEOUT_VAL     20UL



// START OF THE REGISTER MAP DEFINES 


//BANK0_REGISTERS

#define ERDPTL   (uint8_t)(0X00|BANK0_BASE) 
#define ERDPTH   (uint8_t)(0X01|BANK0_BASE)
#define EWRPTL   (uint8_t)(0X02|BANK0_BASE)
#define EWRPTH   (uint8_t)(0X03|BANK0_BASE)
#define ETXSTL   (uint8_t)(0X04|BANK0_BASE)
#define ETXSTH   (uint8_t)(0X05|BANK0_BASE)
#define ETXNDL   (uint8_t)(0X06|BANK0_BASE)
#define ETXNDH   (uint8_t)(0X07|BANK0_BASE)
#define ERXSTL   (uint8_t)(0X08|BANK0_BASE)
#define ERXSTH   (uint8_t)(0X09|BANK0_BASE)
#define ERXNDL   (uint8_t)(0X0A|BANK0_BASE)
#define ERXNDH   (uint8_t)(0X0B|BANK0_BASE)
#define ERXRDPTL (uint8_t)(0X0C|BANK0_BASE)
#define ERXRDPTH (uint8_t)(0x0D|BANK0_BASE)
#define ERXWRPTL (uint8_t)(0X0E|BANK0_BASE)
#define ERXWRPTH (uint8_t)(0x0F|BANK0_BASE)
#define EDMASTL  (uint8_t)(0X10|BANK0_BASE)
#define EDMASTH  (uint8_t)(0X11|BANK0_BASE)
#define EDMANDL  (uint8_t)(0X12|BANK0_BASE)
#define EDMANDH  (uint8_t)(0X13|BANK0_BASE)
#define EDMADSTL (uint8_t)(0x14|BANK0_BASE)
#define EDMADSTH (uint8_t)(0x15|BANK0_BASE)
#define EDMACSL  (uint8_t)(0X16|BANK0_BASE)
#define EDMACSH  (uint8_t)(0x17|BANK0_BASE)



//BANK1_REGISTERS


#define EHT0    (uint8_t)(0X00|BANK1_BASE)
#define EHT1    (uint8_t)(0X01|BANK1_BASE)
#define EHT2    (uint8_t)(0X02|BANK1_BASE)
#define EHT3    (uint8_t)(0x03|BANK1_BASE)
#define EHT4    (uint8_t)(0X04|BANK1_BASE)
#define EHT5    (uint8_t)(0X05|BANK1_BASE)
#define EHT6    (uint8_t)(0x06|BANK1_BASE)
#define EHT7    (uint8_t)(0X07|BANK1_BASE)
#define EPMM0   (uint8_t)(0x08|BANK1_BASE)
#define EPMM1   (uint8_t)(0X09|BANK1_BASE)
#define EPMM2   (uint8_t)(0X0A|BANK1_BASE)
#define EPMM3   (uint8_t)(0X0B|BANK1_BASE)
#define EPMM4   (uint8_t)(0X0C|BANK1_BASE)
#define EPMM5   (uint8_t)(0X0D|BANK1_BASE)
#define EPMM6   (uint8_t)(0X0E|BANK1_BASE)
#define EPMM7   (uint8_t)(0X0F|BANK1_BASE)
#define EPMCSL  (uint8_t)(0X10|BANK1_BASE)
#define EPMCSH  (uint8_t)(0X11|BANK1_BASE)
#define EPMOL   (uint8_t)(0X14|BANK1_BASE)
#define EPMOH   (uint8_t)(0X15|BANK1_BASE)
#define ERXFCON (uint8_t)(0X18|BANK1_BASE)
#define EPKTCNT (uint8_t)(0X19|BANK1_BASE)


//BANK2_REGISTERS



#define MACON1   (uint8_t)(0X00|BANK2_BASE|IS_MAC)
#define MACON3   (uint8_t)(0X02|BANK2_BASE|IS_MAC)
#define MACON4   (uint8_t)(0X03|BANK2_BASE|IS_MAC)
#define MABBIPG  (uint8_t)(0X04|BANK2_BASE|IS_MAC)
#define MAIPGL   (uint8_t)(0X06|BANK2_BASE|IS_MAC)
#define MAIPGH   (uint8_t)(0X07|BANK2_BASE|IS_MAC)
#define MACLCON1 (uint8_t)(0X08|BANK2_BASE|IS_MAC)
#define MACLCON2 (uint8_t)(0X09|BANK2_BASE|IS_MAC)
#define MAMXFLL  (uint8_t)(0X0A|BANK2_BASE|IS_MAC)
#define MAMXFLH  (uint8_t)(0X0B|BANK2_BASE|IS_MAC)
#define MICMD    (uint8_t)(0X12|BANK2_BASE|IS_MAC)
#define MIREGADR (uint8_t)(0X14|BANK2_BASE|IS_MAC)
#define MIWRL    (uint8_t)(0X16|BANK2_BASE|IS_MAC)
#define MIWRH    (uint8_t)(0X17|BANK2_BASE|IS_MAC)
#define MIRDL    (uint8_t)(0X18|BANK2_BASE|IS_MAC)
#define MIRDH    (uint8_t)(0X19|BANK2_BASE|IS_MAC)



//BANK3_REGISTERS 

#define MAADR5  (uint8_t)(0X00|BANK3_BASE|IS_MAC)
#define MAADR6  (uint8_t)(0X01|BANK3_BASE|IS_MAC)
#define MAADR3  (uint8_t)(0X02|BANK3_BASE|IS_MAC)
#define MAADR4  (uint8_t)(0X03|BANK3_BASE|IS_MAC)
#define MAADR1  (uint8_t)(0X04|BANK3_BASE|IS_MAC)
#define MAADR2  (uint8_t)(0X05|BANK3_BASE|IS_MAC)
#define EBSTSD  (uint8_t)(0X06|BANK3_BASE)
#define EBSTCON (uint8_t)(0X07|BANK3_BASE)
#define EBSTCSL (uint8_t)(0X08|BANK3_BASE)
#define EBSTCSH (uint8_t)(0X09|BANK3_BASE)
#define MISTAT  (uint8_t)(0X0A|BANK3_BASE|IS_MAC)
#define EREVID  (uint8_t)(0X12|BANK3_BASE)
#define ECOCON  (uint8_t)(0X15|BANK3_BASE)
#define EFLOCON (uint8_t)(0X17|BANK3_BASE)
#define EPAUSL  (uint8_t)(0X18|BANK3_BASE)
#define EPAUSH  (uint8_t)(0X19|BANK3_BASE)


//PHY REGISTERS

#define PHCON1  (uint8_t)(0X00)
#define PHSTAT1 (uint8_t)(0X01)
#define PHID1   (uint8_t)(0X02)
#define PHID2   (uint8_t)(0X03)
#define PHCON2  (uint8_t)(0X10)
#define PHSTAT2 (uint8_t)(0X11)
#define PHIE    (uint8_t)(0X12)
#define PHIR    (uint8_t)(0X13)
#define PHILCON (uint8_t)(0X14)


//COMMON_REGISTERS

#define EIE   (uint8_t)(0X1B)
#define EIR   (uint8_t)(0X1C)
#define ESTAT (uint8_t)(0X1D)
#define ECON2 (uint8_t)(0X1E)
#define ECON1 (uint8_t)(0X1F)


//Bit Fields

//ECON1

#define ECON1_BSEL0_BP (0UL)
#define ECON1_BSEL0_BM  ( 1UL << ECON1_BSEL0_BP )
#define ECON1_BSEL1_BP (1UL)
#define ECON1_BSEL1_BM  ( 1UL << ECON1_BSEL1_BP )
#define ECON1_RXEN_BP  (2UL)
#define ECON1_RXEN_BM   ( 1UL << ECON1_RXEN_BP  )
#define ECON1_TXRTS_BP (3UL)
#define ECON1_TXRTS_BM  ( 1UL << ECON1_TXRTS_BP )
#define ECON1_CSUMEN_BP (4UL)
#define ECON1_CSUMEN_BM ( 1UL << ECON1_CSUMEN_BP)
#define ECON1_DMAST_BP  (5UL)
#define ECON1_DMAST_BM  ( 1UL << ECON1_DMAST_BP )
#define ECON1_RXRST_BP  (6UL)
#define ECON1_RXRST_BM  ( 1UL << ECON1_RXRST_BP )
#define ECON1_TXRST_BP  (7UL)
#define ECON1_TXRST_BM  ( 1UL << ECON1_TXRST_BP )


//ECON2

#define ECON2_VRPS_BP (3UL)
#define ECON2_VRPS_BM ( 1UL << ECON2_VRPS_BP ) 
#define ECON2_PWRSV_BP (5UL)
#define ECON2_PWRSV_BM ( 1UL << ECON2_PWRSV_BP)
#define ECON2_PKTDEC_BP (6UL)
#define ECON2_PKTDEC_BM ( 1UL << ECON2_PKTDEC_BP)
#define ECON2_AUTOINC_BP (7UL)
#define ECON2_AUTOINC_BM ( 1UL << ECON2_AUTOINC_BP )

//ESTAT

#define ESTAT_CLKRDY_BP (0UL)
#define ESTAT_CLKRDY_BM ( 1UL << ESTAT_CLKRDY_BP )
#define ESTAT_TXABRT_BP (1UL)
#define ESTAT_TXABRT_BM ( 1UL << ESTAT_TXABRT_BP )
#define ESTAT_RXBUSY_BP (2UL)
#define ESTAT_RXBUSY_BM ( 1UL << ESTAT_RXBUSY_BP )
#define ESTAT_LATECOL_BP (4UL)
#define ESTAT_LATECOL_BM ( 1UL << ESTAT_LATECOL_BP )
#define ESTAT_BUFER_BP   (6UL)
#define ESTAT_BUFER_BM ( 1UL << ESTAT_BUFER_BP )
#define ESTAT_INT_BP  (7UL)
#define ESTAT_INT_BM   ( 1UL << ESTAT_INT_BP )



//EIR

#define EIR_RXERIF_BP (0UL)
#define EIR_RXERIF_BM ( 1 << EIR_RXERIF_BP ) 
#define EIR_TXERIF_BP (1UL)
#define EIR_TXERIF_BM ( 1 << EIR_TXERIF_BP )
#define EIR_TXIF_BP   (3UL)
#define EIR_TXIF_BM   ( 1 << EIR_TXIF_BP   )
#define EIR_LINKIF_BP (4UL)
#define EIR_LINKIF_BM ( 1 << EIR_LINKIF_BP )
#define EIR_DMAIF_BP  (5UL)
#define EIR_DMAIF_BM  ( 1 << EIR_DMAIF_BP  )
#define EIR_PKTIF_BP  (6UL)
#define EIR_PKTIF_BM  ( 1 << EIR_PKTIF_BP  )


//EIE

#define EIE_RXERIE_BP    (0UL)
#define EIE_RXERIE_BM   ( 1 << EIE_RXERIE_BP ) 
#define EIE_TXERIE_BP    (1UL)
#define EIE_TXERIE_BM   ( 1 << EIE_TXERIE_BP )
#define EIE_TXIE_BP      (3UL)
#define EIE_TXIE_BM     ( 1 << EIE_TXIE_BP   )
#define EIE_LINKIE_BP    (4UL)
#define EIE_LINKIE_BM   ( 1 << EIE_LINKIE_BP )
#define EIE_DMAIE_BP     (5UL)
#define EIE_DMAIE_BM    ( 1 << EIE_DMAIE_BP  )
#define EIE_PKTIE_BP     (6UL)
#define EIE_PKTIE_BM    ( 1 << EIE_PKTIE_BP  )
#define EIE_INTIE_BP     (7UL)
#define EIE_INTIE_BM    ( 1 << EIE_INTIE_BP  )


//ERXFCON

#define ERXFCON_BCEN_BP (0UL)
#define ERXFCON_BCEN_BM ( 1UL << ERXFCON_BCEN_BP ) 
#define ERXFCON_MCEN_BP (1UL)
#define ERXFCON_MCEN_BM ( 1UL << ERXFCON_MCEN_BP )
#define ERXFCON_HTEN_BP (2UL)
#define ERXFCON_HTEN_BM ( 1UL << ERXFCON_HTEN_BP )
#define ERXFCON_MPEN_BP (3UL)
#define ERXFCON_MPEN_BM ( 1UL << ERXFCON_MPEN_BP )
#define ERXFCON_PMEN_BP (4UL)
#define ERXFCON_PMEN_BM ( 1UL << ERXFCON_PMEN_BP )
#define ERXFCON_CRCEN_BP (5UL)
#define ERXFCON_CRCEN_BM ( 1UL << ERXFCON_CRCEN_BP )
#define ERXFCON_ANDOR_BP (6UL)
#define ERXFCON_ANDOR_BM ( 1UL << ERXFCON_ANDOR_BP ) 
#define ERXFCON_UCEN_BP  (7UL)
#define ERXFCON_UCEN_BM  ( 1UL << ERXFCON_UCEN_BP ) 

//MACON1 

#define MACON1_MASK (0XF0)
#define MACON1_MARXEN_BP  (0UL)
#define MACON1_MARXEN_BM  ( 1UL << MACON1_MARXEN_BP ) 
#define MACON1_PASSALL_BP (1UL)
#define MACON1_PASSALL_BM ( 1UL << MACON1_PASSALL_BP )
#define MACON1_RXPAUS_BP  (2UL)
#define MACON1_RXPAUS_BM  ( 1UL << MACON1_RXPAUS_BP )
#define MACON1_TXPAUS_BP  (3UL)
#define MACON1_TXPAUS_BM  ( 1UL << MACON1_TXPAUS_BP )

//MACON3

#define MACON3_MASK        (0X00)
#define MACON3_FULDPX_BP   (0UL)
#define MACON3_FULDPX_BM   ( 1UL << MACON3_FULDPX_BP )
#define MACON3_FRMLNEN_BP  (1UL)
#define MACON3_FRMLNEN_BM  ( 1UL << MACON3_FRMLNEN_BP )
#define MACON3_HFRMEN_BP   (2UL)
#define MACON3_HFRMEN_BM   ( 1UL << MACON3_HFRMEN_BP  )
#define MACON3_PHDREN_BP   (3UL)
#define MACON3_PHDREN_BM   ( 1UL << MACON3_PHDREN_BP  )
#define MACON3_TXCRCEN_BP  (4UL)
#define MACON3_TXCRCEN_BM  ( 1UL << MACON3_TXCRCEN_BP )
#define MACON3_PADCFG0_BP  (5UL)
#define MACON3_PADCFG0_BM  ( 1UL`<< MACON3_PADCFG0_BP )
#define MACON3_PADCFG1_BP  (6UL)
#define MACON3_PADCFG1_BM  ( 1UL << MACON3_PADCFG1_BP )
#define MACON3_PADCFG2_BP  (7UL)
#define MACON3_PADCFG2_BM  ( 1UL << MACON3_PADCFG2_BP )

//MACON4_

#define MACON4_MASK       (0X8F)
#define MACON4_NOBKOFF_BP (4UL)
#define MACON4_NOBKOFF_BM ( 1UL << MACON4_NOBKOFF_BP )
#define MACON4_BPEN_BP    (5UL)
#define MACON4_BPEN_BM    ( 1UL << MACON4_BPEN_BP    )
#define MACON4_DEFER_BP   (6UL)
#define MACON4_DEFER_BM   ( 1UL << MACON4_DEFER_BP   )


//MICMD

#define MICMD_MASK       (0XFC)
#define MICMD_MIIRD_BP   (0UL)
#define MICMD_MIIRD_BM   ( 1UL << MICMD_MIIRD_BP )
#define MICMD_MIISCAN_BP (1UL)
#define MICMD_MIISCAN_BM ( 1UL << MICMD_MIISCAN_BP ) 


//EBSTCON


#define EBSTCON_MASK       (0X00)
#define EBSTCON_BISTST_BP  (0UL)
#define EBSTCON_BISTST_BM  ( 1UL << EBSTCON_BISTST_BP )
#define EBSTCON_TME_BP     (1UL)
#define EBSTCON_TME_BM     ( 1UL << EBSTCON_TME_BP    )
#define EBSTCON_TMSEL0_BP  (2UL)
#define EBSTCON_TMSEL0_BM  ( 1UL << EBSTCON_TMSEL0_BP )
#define EBSTCON_TMSEL1_BP  (3UL)
#define EBSTCON_TMSEL1_BM  ( 1UL << EBSTCON_TMSEL1_BP )
#define EBSTCON_PSEL_BP    (4UL)
#define EBSTCON_PSEL_BM    ( 1UL << EBSTCON_PSEL_BP   )
#define EBSTCON_PSV0_BP    (5UL)
#define EBSTCON_PSV0_BM    ( 1UL << EBSTCON_PSV0_BP   ) 
#define EBSTCON_PSV1_BP    (6UL)
#define EBSTCON_PSV1_BM    ( 1UL << EBSTCON_PSV1_BP   )
#define EBSTCON_PSV2_BP    (7UL)
#define EBSTCON_PSV2_BM    ( 1UL << EBSTCON_PSV2_BP   )



//MISTAT

#define MISTAT_MASK       (0XF8)
#define MISTAT_BUSY_BP    (0UL)
#define MISTAT_BUSY_BM    ( 1UL << MISTAT_BUSY_BP    )
#define MISTAT_SCAN_BP    (1UL)
#define MISTAT_SCAN_BM    ( 1UL << MISTAT_SCAN_BP    )
#define MISTAT_INVALID_BP (2UL) 
#define MISTAT_INVALID_BM ( 1UL << MISTAT_INVALID_BP )


//ECOCON

#define ECOCON_MASK       (0XF8)
#define ECOCON_COCON0_BP  (0UL)
#define ECOCON_COCON0_BM  ( 1UL << ECOCON_COCON0_BP )
#define ECOCON_COCON1_BP  (1UL)
#define ECOCON_COCON1_BM  ( 1UL << ECOCON_COCON1_BP )
#define ECOCON_COCON2_BP  (2UL)
#define ECOCON_COCON2_BM  ( 1UL << ECOCON_COCON2_BP )

//EFLOCON

#define EFLOCON_MASK     (0XF8)
#define EFLOCON_FCEN0_BP   (0UL)
#define EFLOCON_FCEN0_BM   ( 1UL << EFLOCON_FCEN0_BP   )
#define EFLOCON_FCEN1_BP   (1UL)
#define EFLOCON_FCEN1_BM   ( 1UL << EFLOCON_FCEN1_BP   )
#define EFLOCON_FULDPXS_BP (2UL)
#define EFLOCON_FULDPXS_BM ( 1UL << EFLOCON_FULDPXS_BP )

//PHCON1 

#define PHCON1_MASK  (0X36FF)
#define PHCON1_PDPXMD_BP (8UL)
#define PHCON1_PDPXMD_BM ( 1UL << PHCON1_PDPXMD_BP )
#define PHCON1_PPWRSV_BP (11UL)
#define PHCON1_PPWRSV_BM ( 1UL << PHCON1_PPWRSV_BP )
#define PHCON1_PLOOPBK_BP (14UL)
#define PHCON1_PLOOPBK_BM ( 1UL << PHCON1_PLOOPBK_BP )
#define PHCON1_PRST_BP    (15UL)
#define PHCON1_PRST_BM    ( 1UL << PHCON1_PRST_BP    )


// PHSTAT1

#define PHSTAT1_MASK (0XE7F9)
#define PHSTAT1_JBSTAT_BP (1UL)
#define PHSTAT1_JBSTAT_BM ( 1UL << PHSTAT1_JBSTAT_BP )
#define PHSTAT1_LLSTAT_BP (2UL)
#define PHSTAT1_LLSTAT_BM ( 1UL << PHSTAT1_LLSTAT_BP )
#define PHSTAT1_PHDPX_BP  (11UL)
#define PHSTAT1_PHDPX_BM  ( 1UL << PHSTAT1_PHDPX_BP  )
#define PHSTAT1_PFDPX_BP  (12UL)
#define PHSTAT1_PFDPX_BM  ( 1UL << PHSTAT1_PFDPX_BP  )


//PHID1
#define PHID1_MASK   (0X0000)
#define PHID1_OUI3_BP (0UL)
#define PHID1_OUI3_BM ( 1UL << PHID1_OUI3_BP )


//PHID2
#define PHID2_MASK   (0X0000)
#define PHID2_OUI19_BP (10UL)
#define PHID2_OUI19_BM ( 1UL << PHID2_OUI19_BP )
#define PHID2_OUI20_BP (11UL)
#define PHID2_OUI20_BM ( 1UL << PHID2_OUI20_BP )
#define PHID2_OUI21_BP (12UL)
#define PHID2_OUI21_BM ( 1UL << PHID2_OUI21_BP )
#define PHID2_OUI22_BP (13UL)
#define PHID2_OUI22_BM ( 1UL << PHID2_OUI22_BP )
#define PHID2_OUI23_BP (14UL)
#define PHID2_OUI23_BM ( 1UL << PHID2_OUI23_BP )
#define PHID2_OUI24_BP (15UL)
#define PHID2_OUI24_BM ( 1UL << PHID2_OUI24_BP )
#define PHID2_PPN0_BP  (4UL)
#define PHID2_PPN0_BM  ( 1UL << PHID2_PPN0_BP) 
#define PHID2_PPN1_BP  (5UL)
#define PHID2_PPN1_BM  ( 1UL << PHID2_PPN1_BP) 
#define PHID2_PPN2_BP  (6UL)
#define PHID2_PPN2_BM  ( 1UL << PHID2_PPN2_BP) 
#define PHID2_PPN3_BP  (7UL)
#define PHID2_PPN3_BM  ( 1UL << PHID2_PPN3_BP) 
#define PHID2_PPN4_BP  (8UL)
#define PHID2_PPN4_BM  ( 1UL << PHID2_PPN4_BP) 
#define PHID2_PPN5_BP  (9UL)
#define PHID2_PPN5_BM  ( 1UL << PHID2_PPN5_BP) 
#define PHID2_PREV0_BP (0UL)
#define PHID2_PREV0_BM ( 1UL << PHID2_PREV0_BP)
#define PHID2_PREV1_BP (1UL)
#define PHID2_PREV1_BM ( 1UL << PHID2_PREV1_BP)
#define PHID2_PREV2_BP (2UL)
#define PHID2_PREV2_BM ( 1UL << PHID2_PREV2_BP)
#define PHID2_PREV3_BP (3UL)
#define PHID2_PREV3_BM ( 1UL << PHID2_PREV3_BP)



//PHCON2

#define PHCON2_MASK  (0X9AFF)
#define PHCON2_HDLDIS_BP   (8UL)
#define PHCON2_HDLDIS_BM   ( 1UL << PHCON2_HDLDIS_BP )
#define PHCON2_JABBER_BP   (10UL)
#define PHCON2_JABBER_BM   ( 1UL << PHCON2_JABBER_BP )
#define PHCON2_TXDIS_BP    (13UL)
#define PHCON2_TXDIS_BM    ( 1UL << PHCON2_TXDIS_BP  )
#define PHCON2_FRCLNK_BP   (14UL)
#define PHCON2_FRCLNK_BM   ( 1UL << PHCON2_FRCLNK_BP )

//PHSTAT2

#define PHSTAT2_MASK (0XC1DF)
#define PHSTAT2_PLRITY_BP   (5UL)
#define PHSTAT2_PLRITY_BM   ( 1UL << PHSTAT2_PLRITY_BP  )
#define PHSTAT2_DPXSTAT_BP  (9UL)
#define PHSTAT2_DPXSTAT_BM  ( 1UL << PHSTAT2_DPXSTAT_BP )
#define PHSTAT2_LSTAT_BP    (10UL)
#define PHSTAT2_LSTAT_BM    ( 1UL << PHSTAT2_LSTAT_BP   )
#define PHSTAT2_COLSTAT_BP  (11UL)
#define PHSTAT2_COLSTAT_BM  ( 1UL << PHSTAT2_COLSTAT_BP )
#define PHSTAT2_RXSTAT_BP   (12UL)
#define PHSTAT2_RXSTAT_BM   ( 1UL << PHSTAT2_RXSTAT_BP  )
#define PHSTAT2_TXSTAT_BP   (13UL)
#define PHSTAT2_TXSTAT_BM   ( 1UL << PHSTAT2_TXSTAT_BP  )




//PHIE

#define PHIE_MASK    (0XFFED)
#define PHIE_PGEIE_BP   (1UL)
#define PHIE_PGEIE_BM   ( 1UL << PHIE_PGEIE_BP  )
#define PHIE_PLNKIE_BP  (4UL)
#define PHIE_PLNKIE_BM  ( 1UL << PHIE_PLNKIE_BP )


//PHIR

#define PHIR_MASK    (0XFFEB)
#define PHIR_PGIF_BP   (2UL)
#define PHIR_PGIF_BM   ( 1 << PHIR_PGIF_BP   )
#define PHIR_PLNKIF_BP (4UL)
#define PHIR_PLNKIF_BM ( 1 << PHIR_PLNKIF_BP )

//PHILCON
 
#define PHILCON_MASK (0XF001)
#define PHILCON_STRCH_BP      (1UL)
#define PHILCON_STRCH_BM      ( 1UL << PHILCON_STRCH_BP  ) 
#define PHILCON_LFRQ0_BP      (2UL) 
#define PHILCON_LFRQ0_BM      ( 1UL << PHILCON_LFRQ0_BP  )
#define PHILCON_LFRQ1_BP      (3UL) 
#define PHILCON_LFRQ1_BM      ( 1UL << PHILCON_LFRQ1_BP  )
#define PHILCON_LBCFG0_BP     (4UL)
#define PHILCON_LBCFG0_BM     ( 1UL << PHILCON_LBCFG0_BP )
#define PHILCON_LBCFG1_BP     (5UL)
#define PHILCON_LBCFG1_BM     ( 1UL << PHILCON_LBCFG1_BP )
#define PHILCON_LBCFG2_BP     (6UL)
#define PHILCON_LBCFG2_BM     ( 1UL << PHILCON_LBCFG2_BP )
#define PHILCON_LBCFG3_BP     (7UL)
#define PHILCON_LBCFG3_BM     ( 1UL << PHILCON_LBCFG3_BP )
#define PHILCON_LACFG0_BP     (8UL)
#define PHILCON_LACFG0_BM     ( 1UL << PHILCON_LACFG0_BP )
#define PHILCON_LACFG1_BP     (9UL)
#define PHILCON_LACFG1_BM     ( 1UL << PHILCON_LACFG1_BP )
#define PHILCON_LACFG2_BP     (10UL)
#define PHILCON_LACFG2_BM     ( 1UL << PHILCON_LACFG2_BP )
#define PHILCON_LACFG3_BP     (11UL)
#define PHILCON_LACFG3_BM     ( 1UL << PHILCON_LACFG3_BP )

//COMMANDS 

#define CMD_RCR (0X00)
#define CMD_WCR (0X40)
#define CMD_RBM (0X3A)
#define CMD_WBM (0X7A)
#define CMD_BFS (0X80)
#define CMD_BFC (0XA0)
#define CMD_SRC (0XFF)


typedef enum {
	
	REG8  = 1 , 
	REG16 = 2 , 

} REG_LENGTH ;

typedef enum {
	
	WRITE_REG = 1 , 
	READ_REG  = 0 , 
	
} REG_OP ; 

typedef enum {
	
	ERRC_SUCCESS        =  0  ,
	ERRC_TIMEOUT        = -1  , 
	ERRC_ASSERT         = -2  ,
	ERRC_PHY_TIMEOUT    = -3  ,
	ERRC_CLKRDY_TIMEOUT = -4  ,
	ERRC_VERIFY         = -5  , 
	ERRC_TX_TIMEOUT     = -6  , 
	ERRC_PAYLOAD_EMPTY  = -7  ,
	ERRC_TX_NO_SPACE    = -8  ,
	ERRC_RX_EMPTY       = -9  ,
	ERRC_REALLOC_FAIL   = -10 , 
	ERRC_STARTUP_TIMEOUT= -11 ,
	
} ETH_ERR ;


typedef enum {
	
	ETH_LED_MODE_DPX_COL_S   = 0B1110 ,
	ETH_LED_MODE_LS_TRX_S    = 0B1101 ,
	ETH_LED_MODE_LS_RX_S     = 0B1100 ,
	ETH_LED_MODE_BLK_SLOW    = 0B1011 ,
	ETH_LED_MODE_BLK_FAST    = 0B1010 ,
	ETH_LED_MODE_OFF         = 0B1001 ,
	ETH_LED_MODE_ON          = 0B1000 , 
	ETH_LED_MODE_TRX_CS      = 0B0111 ,
	ETH_LED_MODE_DPX         = 0B0101 ,
	ETH_LED_MODE_LS          = 0B0100 ,
	ETH_LED_COL_CS           = 0B0011 ,
	ETH_LED_MODE_RX_CS            = 0B0010 ,
	ETH_LED_MODE_TX_CS            = 0B0001 ,
	
} ETH_LED_MODE ;


typedef enum {
	
	ETH_NOSTRETCH      = 0B000 ,
	ETH_TNSTRETCH_40   = 0B001 ,
	ETH_TMSTRETCH_70   = 0B011 ,
	ETH_TLSTRETCH_140  = 0B101 ,
	
	
} ETH_LED_STRETCH ; 

typedef struct {
	
	ETH_LED_MODE    LED_A ;
	ETH_LED_MODE    LED_B ;
	ETH_LED_STRETCH LED_Stretch ;
	
	
} ETH_LED_CONFIG ;  





typedef enum {
	ETH_RXF_NOFILTER      =  0X00              ,
	ETH_RXF_UNICAST       =  ERXFCON_UCEN_BM   ,  
	ETH_RXF_AND           =  ERXFCON_ANDOR_BM  ,
	ETH_RXF_CRC           =  ERXFCON_CRCEN_BM  ,
	ETH_RXF_PATTERN_MATCH =  ERXFCON_PMEN_BM   ,
	ETH_RXF_MAGIC_PACKET  =  ERXFCON_MPEN_BM   ,
	ETH_RXF_HASH_TABLE    =  ERXFCON_HTEN_BM   ,
	ETH_RXF_MULTICAST     =  ERXFCON_MCEN_BM   ,
	ETH_RXF_BROADCAST     =  ERXFCON_BCEN_BM   ,
	
} RX_FILTER ; 












typedef enum {
	
	ETH_PWRSV_REGSV  = 0B101  ,
	ETH_PWRSV_REGNSV = 0B100  ,   
	ETH_PWRNSV       = 0B000  ,
	
	
} POWER_CONFIG ; 




typedef struct {
	
	uint16_t Pattern_Offset ; 
	uint16_t Pattern_Checksum ;
	uint64_t Pattern_Mask     ;
	
} Pattern_Match_Struct ; 



typedef enum {
	
	ETH_FULL_DPLX = 1 , 
	ETH_HALF_DPLX = 0 ,

} ETH_MODE ;

typedef enum {
	
	ETH_CRC_ENABLED  = 1 ,
	ETH_CRC_DISABLED = 0 ,
	
} CRC_CONFIG ; 

typedef enum {
	
	ETH_NPA_FLCTRL_TRX = 0B110 , 
	ETH_NPA_FLCTRL_TX  = 0B100 ,
	ETH_NPA_FLCTRL_RX  = 0B010 ,
	ETH_NPA_NFCTRL     = 0B000 ,
	ETH_PA_FLCTRL_TRX  = 0B111 , 
	ETH_PA_FLCTRL_TX   = 0B101 ,
	ETH_PA_FLCTRL_RX   = 0B011 ,
	ETH_PA_NFCTRL      = 0B001 ,

} FLOW_CONTROL_CONFIG ;



typedef enum {
	
	ETH_NOPAD_NOCRCEN      = 0B0000 ,
	ETH_64PAD_CRCEN        = 0B0111 ,
	ETH_60PAD_CRCEN        = 0B0011 ,
	ETH_64VLAN_60PAD_CRCEN = 0B1011 ,
	
} FRAME_CONFIG ;  

typedef enum {
	
	ETH_HEADER_ENABLE  = 1 , 
	ETH_HEADER_DISABLE = 0 ,
	
} HEADER_CONFIG ;

typedef enum {
	
	ETH_HFEN_CHEN   = 0B11 , 
	ETH_HFEN_CHDEN  = 0B10 ,
	ETH_HFDEN_CHEN  = 0B01 ,
	ETH_HFDEN_CHDEN = 0B00 ,
	
} FRMLEN_CONFIG ;

typedef enum {
	
	ETH_HLFDPLX_CTRL0 = 0B000 ,
	ETH_HLFDPLX_CTRL1 = 0B001 ,
	ETH_HLFDPLX_CTRL2 = 0B010 ,
	ETH_HLFDPLX_CTRL3 = 0B011 ,
	ETH_HLFDPLX_CTRL4 = 0B100 ,
	ETH_HLFDPLX_CTRL5 = 0B101 ,
	ETH_HLFDPLX_CTRL6 = 0B110 ,
	ETH_HLFDPLX_CTRL7 = 0B111 ,
	
} HLFDPLX_CONFIG ;  

typedef struct {
	
	
	FLOW_CONTROL_CONFIG FLCTRL_Config       ; 
	FRAME_CONFIG        Frame_Config        ;
	FRMLEN_CONFIG       Frame_Length_Config ;
	HEADER_CONFIG       Header_Config       ;
	uint16_t            Max_Frame_Length    ;
	HLFDPLX_CONFIG      HLFDPLX_Config      ;
	uint8_t             MAC_Address[6]      ;
	
} MAC_Config_Struct ;


typedef struct {
	
	ETH_LED_MODE LEDA                  ;
	ETH_LED_MODE LEDB                  ;
	ETH_LED_STRETCH LED_Stretch_Config ;
	
	
}PHY_Config_Struct ; 

typedef struct {
	
	uint16_t RX_Buff_Size                    ;
	RX_FILTER    RX_Filter                   ;
	POWER_CONFIG Power_Config                ;
	Pattern_Match_Struct* Pattern_Struct_Ptr ; 
	uint64_t Hash_Table                      ;
	ETH_MODE   ETH_Mode                      ;
	MAC_Config_Struct*   MAC_Struct_Ptr      ;
	PHY_Config_Struct*   PHY_Struct_Ptr      ;
	uint8_t Interrupt_Mask                   ;
	
} Encj_Init_Struct ; 
 
typedef struct {
	
	uint16_t RD_Pos ; 
	uint16_t WR_Pos ;
	
	
} ETH_Pos ;  

typedef struct {
	
	uint8_t ppcb             ;
	uint8_t * dest_address   ;
	uint8_t * src_address    ;
	uint16_t payload_len     ;
	uint8_t * payload        ; 
	
} ETH_Packet ; 



// External Default variables ,  that may be altered . 

#if defined(ETH_DEFAULT_STRUCT)
extern MAC_Config_Struct Mac_Struct_Default   ;
extern PHY_Config_Struct Phy_Struct_Default   ;
extern Encj_Init_Struct   Encj_Struct_Default ;
#endif 

 
int16_t Encj_ReceivePacket ( ETH_Packet * packet ) ;
int16_t Encj_SendPacket( ETH_Packet * packet );
int16_t Encj_Init ( Encj_Init_Struct encj_struct );
int16_t Encj_realloc( uint16_t rx_size );
int16_t Encj_Get_PacketCount ( void ) ;
int16_t Encj_Get_RX_Size ( void );
int16_t Encj_Get_TX_Size ( void ); 
int16_t Encj_Get_Status( void ) ;
int16_t Encj_Interrupt_Set ( uint8_t interrupt_mask );

#endif 
