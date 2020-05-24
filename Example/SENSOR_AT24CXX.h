/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: EEPROM
     File Name		: SENSOR_AT24CXX.c
     Function		: SENSOR_AT24CXX
     Create Date	: 2017/05/02

     HAL Layer : SWI2C function
---------------------------------------------------------------------- */

#ifndef __AT24CXX_HEADER__
#define __AT24CXX_HEADER__

/*
    support IC :
				1.AT24C01
				2.AT24C02
				3.AT24C04
				4.AT24C08
				5.AT24C16
				6.AT24C32 * note 1
				7.AT24C64 * note 1

note 1: add this item on 2017/05/04
*/

/* SELECT AT24CXX */
#define AT24C01  	1
#define AT24C02  	2
#define AT24C04  	4
#define AT24C08  	8
#define AT24C16  	16
#define AT24C32	32
#define AT24C64	64

/* SELECT AT24CXX */
#define EEPROM_ID  	AT24C32

/* PIN ADDRESS */
/* SET THE ADDRESS PIN*/
/* ground -> set "0" , vcc -> set "1"  ,*/
#define EEP_A2	0
#define EEP_A1	0
#define EEP_A0	0

//"x" -> don't care , "o" -> must be set 0 or 1
/*--------------------------------
	IC	      |   A2   |	   A1	   |    A0    |
-----------+----- +------+-------|
 AT24C01      |    o    |    o      |     o     |
-----------+----- +------+-------|
 AT24C02      |    o    |    o      |     o     |
-----------+----- +------+-------|
 AT24C04      |    o    |    o     |      x     |
-----------+----- +------+-------|
 AT24C08      |    o    |    x     |      x     |
-----------+----- +------+-------|
 AT24C16      |    x    |    x      |     x     |
-----------+----- +------+-------|
 AT24C32      |    o    |    o      |     o     |
-----------+----- +------+-------|
 AT24C64      |    o    |    o      |     o     |
----------------------------------*/


/********* very important **********		*/
/*Continue Read & Write					*/
/*AT24C01 AT24C02  max 8 byte!!			*/
/*AT24C04 AT24C08 AT24C16  max 16 byte!!	*/
/*AT24C32 AT24C64  max 24 byte!!			*/
/********** very important ***********/
#if (EEPROM_ID == AT24C01) ||(EEPROM_ID == AT24C02)
/* define EEPROM_max continue read / write */
#define EERPOM_CNT_MAX	8
#elif (EEPROM_ID == AT24C04) ||(EEPROM_ID == AT24C08) ||(EEPROM_ID == AT24C16)
#define EERPOM_CNT_MAX	16
#elif (EEPROM_ID == AT24C32) ||(EEPROM_ID == AT24C64) 
#define EERPOM_CNT_MAX	24
#endif



/*--------------------------------- Define SLAVE ADDRESS -------------------------------------*/
#if (EEPROM_ID == AT24C01) || (EEPROM_ID == AT24C02)

	/*DEFINE AT24C01 or AT24C02 address*/
	#define EEPROM_SLAVE_ADDRESS ( 0xA0 |(EEP_A2<<3) | (EEP_A1<<2) | (EEP_A0<<1) )

#elif  (EEPROM_ID == AT24C04)

	/*DEFINE AT24C04 address*/
	#define EEPROM_SLAVE_ADDRESS ( 0xA0 | (EEP_A2<<3) | (EEP_A1<<2) )

#elif  (EEPROM_ID == AT24C08)

	/*DEFINE AT24C08 address*/
	#define EEPROM_SLAVE_ADDRESS ( 0xA0 | (EEP_A2<<3) )

#elif  (EEPROM_ID == AT24C16)

	/*DEFINE AT24C16 address*/
	#define EEPROM_SLAVE_ADDRESS (0xA0)

#elif  (EEPROM_ID == AT24C32)

	/*DEFINE AT24C32 address*/
	#define EEPROM_SLAVE_ADDRESS ( 0xA0 |(EEP_A2<<3) | (EEP_A1<<2) | (EEP_A0<<1) )

#elif  (EEPROM_ID == AT24C64)

	/*DEFINE AT24C64 address*/
	#define EEPROM_SLAVE_ADDRESS ( 0xA0 |(EEP_A2<<3) | (EEP_A1<<2) | (EEP_A0<<1) )

#endif
/*--------------------------------- Define SLAVE ADDRESS -------------------------------------*/


/*--------------------------------- Define Union -------------------------------------*/
union AT24CXX_ADDRESS_DATA
{
        CHAR8U BYTE[2];
        INT16U BIT16_DATA;
};
/*--------------------------------- Define Union -------------------------------------*/

/********* very important **********		*/
/*Continue Read & Write					*/
/*AT24C01 AT24C02  max 8 byte!!			*/
/*AT24C04 AT24C08 AT24C16  max 16 byte!!	*/
/*AT24C32 AT24C64  max 24 byte!!			*/
/********** very important ***********/

/*----------------------------------- Function --------------------------------------*/
CHAR8S EEPROM_WRITE_1_BYTE(INT16U reg_address,CHAR8U data);
CHAR8S EEPROM_WRITE_N_BYTE(INT16U reg_address,CHAR8U n_byte,CHAR8U *w_data_stream);
CHAR8S EEPROM_READ_1_BYTE(INT16U reg_address,CHAR8U *data);
CHAR8S EEPROM_READ_N_BYTE(INT16U reg_address,CHAR8U n_byte,CHAR8U *r_data_stream);

#if (EEPROM_ID == AT24C32) || (EEPROM_ID == AT24C64)
CHAR8S EEPROM_WRITE_1_BYTE_REG_ADDR_FOR_2BYTE_REG_ADDR(INT16U reg_address,CHAR8U data);
CHAR8S EEPROM_WRITE_N_BYTE_REG_ADDR_FOR_2BYTE_REG_ADDR(INT16U reg_address,CHAR8U n_byte,CHAR8U *w_data_stream);
CHAR8S EEPROM_READ_1_BYTE_REG_ADDR_FOR_2BYTE_REG_ADDR(INT16U reg_address,CHAR8U *data);
CHAR8S EEPROM_READ_N_BYTE_REG_ADDR_FOR_2BYTE_REG_ADDR(INT16U reg_address,CHAR8U n_byte,CHAR8U *r_data_stream);
#endif
/*----------------------------------- Function --------------------------------------*/

#endif		//#ifndef __AT24CXX_HEADER__
