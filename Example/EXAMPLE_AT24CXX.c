/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: AT24CXX EEPROM
     File Name		: EXAMPLE_AT24CXX.c
     Function		: EXAMPLE_AT24CXX
     Create Date	: 2017/04/29
---------------------------------------------------------------------- */
#ifndef __AT24CXX_EXAMPLE__
#define __AT24CXX_EXAMPLE__

#include <mega32a.h>
#include <stdio.h>
#include <delay.h>
#include <math.h>
#include <i2c.h>
#include "alcd.h"
#include "SENSOR_AT24CXX.h"
#include "Porting_Layer.h"

void  EXAMPLE_AT24CXX(void);


void  EXAMPLE_AT24CXX(void)
{

		CHAR8S check_flag_AT24CXX =0;
              CHAR8U AT_24CXX_DATA;
	       CHAR8U cont_at24cxx_w_data[24]={0};
	       CHAR8U cont_at24cxx_r_data[24]={0},count_temp=0;
		CHAR8U eeprom_id =0;


		/********* very important **********		*/
		/*Continue Read & Write					*/
		/*AT24C01 AT24C02  max 8 byte!!			*/
		/*AT24C04 AT24C08 AT24C16  max 16 byte!!	*/
		/*AT24C32 AT24C64  max 24 byte!!			*/
		/********** very important ***********/
		CHAR8U cnt_rw_max = 8;
		

		/* set eeprom data address */
		INT16U 	eeprom_data_address = 500;
		/* set continue read/write address */
		INT16U	cnt_eeprom_data_address = 550;
		
		printf("-------------------- EEPROM AT24CXX --------------------\r\n");
               /* EEPROM AT24CXX */


		/* display EEPROM ID */
		lcd_gotoxy(0,0);

		eeprom_id=EEPROM_ID;
		switch(eeprom_id)
		{
			case AT24C01: 
						printf("AT2401\r\n");
						lcd_putsf("AT2401");
						break;				
			case AT24C02: 
						printf("AT2402\r\n");
						lcd_putsf("AT2402");				
						break;
			case AT24C04: 
						printf("AT2404\r\n");
						lcd_putsf("AT2404");				
						break;		
			case AT24C08: 
						printf("AT2408\r\n");				
						lcd_putsf("AT2408");				
						break;	
			case AT24C16: 
						printf("AT2416\r\n");			
						lcd_putsf("AT2416");				
						break;
			case AT24C32: 
						printf("AT2432\r\n");				
						lcd_putsf("AT2432");				
						break;			
			case AT24C64: 
						printf("AT2464\r\n");			
						lcd_putsf("AT2464");				
						break;		
			default : 
						printf("ERROR ID\r\n");		
						lcd_putsf("ERROR ID");			
						break;
		}



		delay_ms(20);	/* tiny delay */
			   
		/* release I2C bus */
		i2c_stop_hang();
		i2c_stop_hang();

		/* print the EEPROM data address */ 
		printf("EEPROM data address = 0x%X \r\n",eeprom_data_address);

		/* Read EEPROM data */	   
		check_flag_AT24CXX = EEPROM_READ_1_BYTE(eeprom_data_address,&AT_24CXX_DATA);
		if(check_flag_AT24CXX == 0)
		{
			printf("EEPROM addr =0x%x , READ data = 0x%X \r\n",eeprom_data_address,AT_24CXX_DATA);
		}
		else 
		{
			printf("slave address or register address error!!\r\n");
		}


		/* Set the data value = 0x5A */
		AT_24CXX_DATA = 0x5A;


		/* Write EEPROM data in the eeprom_data_address */	
		check_flag_AT24CXX = EEPROM_WRITE_1_BYTE(eeprom_data_address,AT_24CXX_DATA);
		if(check_flag_AT24CXX == 0)
		{
			printf("WRITE  EEPROM data = 0x%X \r\n",AT_24CXX_DATA);
		}
		else
		{
			printf("slave address or register address error!!\r\n");
		}


		/* Check the data */
		/* Read EEPROM data */	   
		check_flag_AT24CXX = EEPROM_READ_1_BYTE(eeprom_data_address,&AT_24CXX_DATA);
		if(check_flag_AT24CXX == 0)
		{
			printf("Read again EEPROM addr =0x%x , READ data = 0x%X \r\n",eeprom_data_address,AT_24CXX_DATA);
		}
		else 
		{
			printf("slave address or register address error!!\r\n");
		}


		/* create a test data */
		for(count_temp=0;count_temp<cnt_rw_max-1;count_temp++)
		{
			cont_at24cxx_w_data[count_temp] = count_temp * 5;
		}
		for(count_temp=0;count_temp<cnt_rw_max-1;count_temp++)
		{
			printf("test data cont_at24cxx_w_data[%d]=0x%X\r\n",count_temp,cont_at24cxx_w_data[count_temp]);
		}

		/********* very important **********		*/
		/*Continue Read & Write					*/
		/*AT24C01 AT24C02  max 8 byte!!			*/
		/*AT24C04 AT24C08 AT24C16  max 16 byte!!	*/
		/*AT24C32 AT24C64  max 24 byte!!			*/
		/********** very important ***********/

		/* Continue Write EEPROM data */	
		check_flag_AT24CXX = EEPROM_WRITE_N_BYTE(cnt_eeprom_data_address,cnt_rw_max-1,&cont_at24cxx_w_data[0]);
		if(check_flag_AT24CXX != 0 ) 
		{
			printf("Continue write error \r\n");
		}
		
		delay_ms(20);	/* tiny delay */

		/* Continue Read EEPROM data */	
		check_flag_AT24CXX = EEPROM_READ_N_BYTE(cnt_eeprom_data_address,cnt_rw_max-1,&cont_at24cxx_r_data[0]);
		if(check_flag_AT24CXX == 0 )
		{
                 	printf("Continue read data:\r\n");
                 	for(count_temp=0;count_temp<cnt_rw_max-1;count_temp++)\
			{
				printf("cont_at24cxx_r_data[%d]=0x%X\r\n",count_temp,cont_at24cxx_r_data[count_temp]);
                 	}
		}
		else 
		{
			printf("Continue read error \r\n");
		}


		printf("-------------------- EEPROM AT24CXX --------------------\r\n");


		while(1); /* stop here */
			
}
#endif		//#ifndef __AT24CXX_EXAMPLE__
