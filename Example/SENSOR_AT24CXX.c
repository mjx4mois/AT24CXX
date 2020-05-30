/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: EEPROM
     File Name		: SENSOR_AT24CXX.c
     Function		: SENSOR_AT24CXX
     Create Date	: 2017/05/02
---------------------------------------------------------------------- */

#include <stdio.h>
#include <delay.h>
#include <datatype_Layer.h>
#include <swi2c_Layer.h>
#include <SENSOR_AT24CXX.h>


/*--------------------------------------------------------------------------------------------------*/
CHAR8S EEPROM_WRITE_1_BYTE(INT16U reg_address,CHAR8U data)
{

	CHAR8U I2C_FLAG,temp_data;

		/*------------------------------ AT24C01 --------------------------------------*/
		#if (EEPROM_ID == AT24C01) || (EEPROM_ID == AT24C02)

       	/* check AT24C01 or AT24C02  Max Register range */
		if(reg_address<=255 && reg_address>=0)
		{
			I2C_FLAG = i2c_write_1_byte_data(EEPROM_SLAVE_ADDRESS,reg_address,data);

			if(I2C_FLAG == 1)
			{
				return 0;
			}
        		else 
			{
				return -1;
        		}
		}
       	else
       	{
 			//printf("register address error!!\r\n");
        		return -1;
       	}
		/*------------------------------ AT24C01 --------------------------------------*/

		/*------------------------------ AT24C04 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C04)


	CHAR8U AT24C04_SLAVE_ADDRESS;
       /* SET SLAVE ADDRESS & REGISTER ADDRESS */
	union AT24CXX_ADDRESS_DATA AT24C04_DATA;

       	/* check AT24C04  Max Register range */
		if(reg_address<=511 && reg_address>=0)
       	{
			AT24C04_DATA.BIT16_DATA = reg_address ;
			AT24C04_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C04_DATA.BYTE[1] & 0X01)<<1);

			I2C_FLAG = i2c_write_1_byte_data(AT24C04_SLAVE_ADDRESS,AT24C04_DATA.BYTE[0],data);

			if(I2C_FLAG == 1)
          		{
            			return 0;
			}
			else
			{
				return -1;
			}
       	}	
       	else  	
       	{
			// printf("register address error!!\r\n");
        		return -1;
       	}
		/*------------------------------ AT24C04 --------------------------------------*/

		/*------------------------------ AT24C08 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C08)

       CHAR8U AT24C08_SLAVE_ADDRESS;
        /*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C08_DATA;

		 /*check AT24C08  Max Register range*/
		if(reg_address<=1023 && reg_address>=0)
		{
			AT24C08_DATA.BIT16_DATA = reg_address ;
			AT24C08_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C08_DATA.BYTE[1] & 0X03)<<1);

			I2C_FLAG = i2c_write_1_byte_data(AT24C08_SLAVE_ADDRESS,AT24C08_DATA.BYTE[0],data);

	       	 if(I2C_FLAG == 1)
	          	{
	            		return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }
		/*------------------------------ AT24C08 --------------------------------------*/

		/*------------------------------ AT24C16 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C16)

	CHAR8U AT24C16_SLAVE_ADDRESS;
        /*SET SLAVE ADDRESS & REGISTER ADDRESS*/
        union AT24CXX_ADDRESS_DATA AT24C16_DATA;

		/*check AT24C16  Max Register range*/
	       if(reg_address<=2047 && reg_address>=0)
	       {
			AT24C16_DATA.BIT16_DATA = reg_address ;
			AT24C16_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C16_DATA.BYTE[1] & 0X07)<<1);

			I2C_FLAG = i2c_write_1_byte_data(AT24C16_SLAVE_ADDRESS,AT24C16_DATA.BYTE[0],data);

			if(I2C_FLAG == 1)
			{
				return 0;
			}
			else
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }
		/*------------------------------ AT24C16 --------------------------------------*/

		/*------------------------------ AT24C32 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C32)

        /*SET SLAVE ADDRESS & REGISTER ADDRESS*/
        union AT24CXX_ADDRESS_DATA AT24C32_DATA;

		/*check AT24C32  Max Register range*/
	       if(reg_address<=4095 && reg_address>=0)
	       {
			AT24C32_DATA.BIT16_DATA = reg_address ;

			I2C_FLAG = i2c_write_1_byte_data_two_reg_addr(EEPROM_SLAVE_ADDRESS,AT24C32_DATA.BYTE[1],AT24C32_DATA.BYTE[0],data);

			if(I2C_FLAG == 1)
	          	{
	            		return 0;
	          	}
	        	else 
			{		
				return -1;
	        	}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }
		/*------------------------------ AT24C32 --------------------------------------*/

		/*------------------------------ AT24C64 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C64)

        /*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C64_DATA;

		/*check AT24C64  Max Register range*/
		if(reg_address<=8191 && reg_address>=0)
	       {
			AT24C64_DATA.BIT16_DATA = reg_address ;

			I2C_FLAG = i2c_write_1_byte_data_two_reg_addr(EEPROM_SLAVE_ADDRESS,AT24C64_DATA.BYTE[1],AT24C64_DATA.BYTE[0],data);

			if(I2C_FLAG == 1)
			{
				return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
		        return -1;
	       }
		/*------------------------------ AT24C64 --------------------------------------*/

#else
	 //printf("AT24CXX type define error\r\n");
        while(1);
#endif

}
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
CHAR8S EEPROM_WRITE_N_BYTE(INT16U reg_address,CHAR8U n_byte,CHAR8U *w_data_stream)
{

	CHAR8U I2C_FLAG,temp_data;

		/*------------------------------ AT24C01 --------------------------------------*/
		#if (EEPROM_ID == AT24C01) || (EEPROM_ID == AT24C02)

	CHAR8U start_addr;

	       /*check AT24C01 or AT24C02  Max Register range*/
	       if(reg_address<=255 && reg_address>=0)
	       {
			start_addr = (CHAR8U)reg_address;
			if( (reg_address + (INT16U)n_byte) > 255)  return -1; /* overflow.*/
			
			I2C_FLAG = i2c_write_n_byte_data(EEPROM_SLAVE_ADDRESS,start_addr,n_byte,&w_data_stream[0]);
			
			delay_ms(10);   /* after write must delay !!*/
			
			if(I2C_FLAG == 1)
			{
				return 0;
			}
	        	else 
			{
				return -1;
	        	}
	       }
	       else
	       {
		 	//printf("register address error!!\r\n");
		        return -1;
	       }
		/*------------------------------ AT24C01 --------------------------------------*/

		/*------------------------------ AT24C04 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C04)

	CHAR8U AT24C04_SLAVE_ADDRESS;

	/*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C04_DATA;

		/*check AT24C04  Max Register range*/
	       if(reg_address<=511 && reg_address>=0)
	       {
			if( (reg_address + (INT16U)n_byte) >511)  return -1; /* overflow.*/

			AT24C04_DATA.BIT16_DATA = reg_address;
			AT24C04_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C04_DATA.BYTE[1] & 0X01)<<1);

			I2C_FLAG = i2c_write_n_byte_data(AT24C04_SLAVE_ADDRESS,AT24C04_DATA.BYTE[0],n_byte,&w_data_stream[0]);
			
			delay_ms(10); /* a little delay.*/
			
	        	if(I2C_FLAG == 1)
	          	{
				return 0;
			}
			else
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }
	 	/*------------------------------ AT24C04 --------------------------------------*/

		/*------------------------------ AT24C08 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C08)

       CHAR8U AT24C08_SLAVE_ADDRESS;

	/* SET SLAVE ADDRESS & REGISTER ADDRESS */
	union AT24CXX_ADDRESS_DATA AT24C08_DATA;

		/* check AT24C08  Max Register range */
	       if(reg_address<=1023 && reg_address>=0)
		{
			if( (reg_address + (INT16U)n_byte) >1023)  return -1; /* overflow.*/

			AT24C08_DATA.BIT16_DATA = reg_address ;
			AT24C08_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C08_DATA.BYTE[1] & 0X03)<<1);

			I2C_FLAG = i2c_write_n_byte_data(AT24C08_SLAVE_ADDRESS,AT24C08_DATA.BYTE[0],n_byte,&w_data_stream[0]);
			
			delay_ms(10); /* a little delay. */
	          
			if(I2C_FLAG == 1)
			{
				return 0;
			}
	        	else 
			{
				return -1;
	        	}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }
	 	/*------------------------------ AT24C08 --------------------------------------*/

		/*------------------------------ AT24C16 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C16)

	CHAR8U AT24C16_SLAVE_ADDRESS;

	/* SET SLAVE ADDRESS & REGISTER ADDRESS */
	union AT24CXX_ADDRESS_DATA AT24C16_DATA;

		/* check AT24C16  Max Register range */
	       if(reg_address<=2047 && reg_address>=0)
	       {
			if( (reg_address + (INT16U)n_byte) >2047)  return -1; /* overflow.*/

			AT24C16_DATA.BIT16_DATA = reg_address ;
			AT24C16_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C16_DATA.BYTE[1] & 0X07)<<1);

			I2C_FLAG = i2c_write_n_byte_data(AT24C16_SLAVE_ADDRESS,AT24C16_DATA.BYTE[0],n_byte,&w_data_stream[0]);
			
			delay_ms(10); /* a little delay.*/
			
			if(I2C_FLAG == 1)
			{
				return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }
		/*------------------------------ AT24C16 --------------------------------------*/

		/*------------------------------ AT24C32 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C32)

	/*SET SLAVE ADDRESS & REGISTER ADDRESS*/
        union AT24CXX_ADDRESS_DATA AT24C32_DATA;

		/*check AT24C32  Max Register range*/
	       if(reg_address<=4095 && reg_address>=0)
	       {
			if( (reg_address + (INT16U)n_byte) >4095)  return -1;/* overflow.*/

			AT24C32_DATA.BIT16_DATA = reg_address;
			I2C_FLAG =  i2c_write_n_byte_data_two_reg_addr(EEPROM_SLAVE_ADDRESS,AT24C32_DATA.BYTE[1],AT24C32_DATA.BYTE[0],n_byte,&w_data_stream[0]);
			
			delay_ms(10); /* a little delay.*/
			
			if(I2C_FLAG == 1)
			{
				return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
			return -1;
	       }
		/*------------------------------ AT24C32 --------------------------------------*/

		/*------------------------------ AT24C64 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C64)

        /*SET SLAVE ADDRESS & REGISTER ADDRESS*/
        union AT24CXX_ADDRESS_DATA AT24C64_DATA;

		/*check AT24C64  Max Register range*/
	       if(reg_address<=8191 && reg_address>=0)
	       {
			if( (reg_address + (INT16U)n_byte) >8191)  return -1; /* overflow.*/

			AT24C64_DATA.BIT16_DATA = reg_address ;
	  		I2C_FLAG = i2c_write_n_byte_data_two_reg_addr(EEPROM_SLAVE_ADDRESS,AT24C64_DATA.BYTE[1],AT24C64_DATA.BYTE[0],n_byte,&w_data_stream[0]);
			
	          	delay_ms(10);  /* a little delay.*/
	          	
			if(I2C_FLAG == 1)
			{
				return 0;
			}
		        else 
			{
				return -1;
		        }
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }

		/*------------------------------ AT24C64 --------------------------------------*/
#else
	//printf("AT24CXX type define error\r\n");
        while(1);
#endif

}
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
CHAR8S EEPROM_READ_1_BYTE(INT16U reg_address,CHAR8U *data)
{

	CHAR8U I2C_FLAG,temp_data;

		/*------------------------------ AT24C01 --------------------------------------*/
	   	#if (EEPROM_ID == AT24C01) || (EEPROM_ID == AT24C02)

		/*check AT24C01 or AT24C02  Max Register range*/
	       if(reg_address<=255 && reg_address>=0)
	       {

	        	I2C_FLAG = i2c_read_1_byte_data(EEPROM_SLAVE_ADDRESS,reg_address,&temp_data);

	        	if(I2C_FLAG == 1)
	          	{
				*data = temp_data;
				return 0;
			}
	        	else
			{
				return -1;
	        	}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
			return -1;
	       }
	 	/*------------------------------ AT24C01 --------------------------------------*/

	 	/*------------------------------ AT24C04 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C04)

       CHAR8U AT24C04_SLAVE_ADDRESS;

	/*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C04_DATA;

		if(reg_address<=511 && reg_address>=0)
	       {

			AT24C04_DATA.BIT16_DATA = reg_address ;
	        	AT24C04_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C04_DATA.BYTE[1] & 0X01)<<1);

	        	I2C_FLAG = i2c_read_1_byte_data(AT24C04_SLAVE_ADDRESS,AT24C04_DATA.BYTE[0],&temp_data);

	        	if(I2C_FLAG == 1)
	          	{
	            		*data = temp_data;
	            		return 0;
	          	}
			else
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }

	 	/*------------------------------ AT24C04 --------------------------------------*/

	 	/*------------------------------ AT24C08 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C08)

       CHAR8U AT24C08_SLAVE_ADDRESS;

	/*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C08_DATA;

	       if(reg_address<=1023 && reg_address>=0)
	       {

			AT24C08_DATA.BIT16_DATA = reg_address ;
			AT24C08_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C08_DATA.BYTE[1] & 0X03)<<1);

			I2C_FLAG = i2c_read_1_byte_data(AT24C08_SLAVE_ADDRESS,AT24C08_DATA.BYTE[0],&temp_data);

			if(I2C_FLAG == 1)
			{
				*data = temp_data;
	 			return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }
	 	/*------------------------------ AT24C08 --------------------------------------*/

	 	/*------------------------------ AT24C16 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C16)

	CHAR8U AT24C16_SLAVE_ADDRESS;

	/*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C16_DATA;

	       if(reg_address<=2047 && reg_address>=0)
	       {

			AT24C16_DATA.BIT16_DATA = reg_address ;
			AT24C16_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C16_DATA.BYTE[1] & 0X07)<<1);

			I2C_FLAG = i2c_read_1_byte_data(AT24C16_SLAVE_ADDRESS,AT24C16_DATA.BYTE[0],&temp_data);

			if(I2C_FLAG == 1)
			{
				*data = temp_data;
				return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }
	 	/*------------------------------ AT24C16 --------------------------------------*/

	  	/*------------------------------ AT24C32 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C32)

	/*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C32_DATA;

		if(reg_address<=4095 && reg_address>=0)
	       {

			AT24C32_DATA.BIT16_DATA = reg_address ;

			I2C_FLAG = i2c_read_1_byte_data_two_reg_addr(EEPROM_SLAVE_ADDRESS,AT24C32_DATA.BYTE[1],AT24C32_DATA.BYTE[0],&temp_data);

			if(I2C_FLAG == 1)
			{
		            *data = temp_data;
		            return 0;
			}
		        else 
			{
				return -1;
		        }
	       }
	       else
	       {
			//printf("register address error!!\r\n");
			return -1;
	       }
	 	/*------------------------------ AT24C32 --------------------------------------*/

	 	/*------------------------------ AT24C64 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C64)

	/*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C64_DATA;

		if(reg_address<=8191 && reg_address>=0)
	       {

	        	AT24C64_DATA.BIT16_DATA = reg_address ;

	        	I2C_FLAG = i2c_read_1_byte_data_two_reg_addr(EEPROM_SLAVE_ADDRESS,AT24C64_DATA.BYTE[1],AT24C64_DATA.BYTE[0],&temp_data);

			if(I2C_FLAG == 1)
			{
		            	*data = temp_data;
		            	return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
			return -1;
	       }
	  	/*------------------------------ AT24C64 --------------------------------------*/

	#else
	//printf("AT24CXX type define error\r\n");
        while(1);
#endif
}
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
CHAR8S EEPROM_READ_N_BYTE(INT16U reg_address,CHAR8U n_byte,CHAR8U *r_data_stream)
{

	CHAR8U I2C_FLAG,temp_data;


	  	/*------------------------------ AT24C01 --------------------------------------*/
		#if (EEPROM_ID == AT24C01) || (EEPROM_ID == AT24C02)

	CHAR8U start_addr;

		/*check AT24C01 or AT24C02  Max Register range*/
	       if(reg_address<=255 && reg_address>=0)
	       {
			start_addr = (CHAR8U)reg_address;
			if( (reg_address + (INT16U)n_byte) > 255)  return -1; /* overflow.*/
			I2C_FLAG = i2c_read_n_byte_data(EEPROM_SLAVE_ADDRESS,start_addr,n_byte,&r_data_stream[0]);

			if(I2C_FLAG == 1)
			{
				return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }
	  	/*------------------------------ AT24C01 --------------------------------------*/

	  	/*------------------------------ AT24C04 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C04)

       CHAR8U AT24C04_SLAVE_ADDRESS;

       /*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C04_DATA;

	       if(reg_address<=511 && reg_address>=0)
	       {
			if( (reg_address + (INT16U)n_byte) > 511)  return -1; /* overflow.*/

			AT24C04_DATA.BIT16_DATA = reg_address ;
			AT24C04_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C04_DATA.BYTE[1] & 0X01)<<1);

			I2C_FLAG = i2c_read_n_byte_data(AT24C04_SLAVE_ADDRESS,AT24C04_DATA.BYTE[0],n_byte,&r_data_stream[0]);

			if(I2C_FLAG == 1)
	          	{
				return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }

	  	/*------------------------------ AT24C04 --------------------------------------*/

	  	/*------------------------------ AT24C08 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C08)

	CHAR8U AT24C08_SLAVE_ADDRESS;

	 /*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C08_DATA;

		if(reg_address<=1023 && reg_address>=0)
	       {
			if( (reg_address + (INT16U)n_byte) > 1023)  return -1;  /* overflow.*/

			AT24C08_DATA.BIT16_DATA = reg_address ;
			AT24C08_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C08_DATA.BYTE[1] & 0X03)<<1);

			I2C_FLAG = i2c_read_n_byte_data(AT24C08_SLAVE_ADDRESS,AT24C08_DATA.BYTE[0],n_byte,&r_data_stream[0]);

			if(I2C_FLAG == 1)
			{
				return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
	        	return -1;
	       }
	  	/*------------------------------ AT24C08 --------------------------------------*/

	  	/*------------------------------ AT24C16 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C16)

	CHAR8U AT24C16_SLAVE_ADDRESS;

	/*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C16_DATA;

	       if(reg_address<=2047 && reg_address>=0)
		{
			if( (reg_address + (INT16U)n_byte) > 2047)  return -1;  /* overflow.*/

			AT24C16_DATA.BIT16_DATA = reg_address ;
			AT24C16_SLAVE_ADDRESS = EEPROM_SLAVE_ADDRESS | ((AT24C16_DATA.BYTE[1] & 0X07)<<1);

			I2C_FLAG = i2c_read_n_byte_data(AT24C16_SLAVE_ADDRESS,AT24C16_DATA.BYTE[0],n_byte,&r_data_stream[0]);

			if(I2C_FLAG == 1)
			{
				return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
			return -1;
	       }
	  	/*------------------------------ AT24C16 --------------------------------------*/

	  	/*------------------------------ AT24C32 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C32)

	/*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C32_DATA;

		if(reg_address<=4095 && reg_address>=0)
	       {
			if( (reg_address + (INT16U)n_byte) > 4095)  return -1;  /*overflow.*/

			AT24C32_DATA.BIT16_DATA = reg_address ;

			I2C_FLAG = i2c_read_n_byte_data_two_reg_addr(EEPROM_SLAVE_ADDRESS,AT24C32_DATA.BYTE[1],AT24C32_DATA.BYTE[0],n_byte,&r_data_stream[0]);

			if(I2C_FLAG == 1)
			{
				return 0;
			}
			else 
			{
				return -1;
			}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
			return -1;
	       }
	  	/*------------------------------ AT24C32 --------------------------------------*/

	  	/*------------------------------ AT24C64 --------------------------------------*/
		#elif  (EEPROM_ID == AT24C64)

	/*SET SLAVE ADDRESS & REGISTER ADDRESS*/
	union AT24CXX_ADDRESS_DATA AT24C64_DATA;

	       if(reg_address<=8191 && reg_address>=0)
	       {
	       
			if( (reg_address + (INT16U)n_byte) > 8191)  return -1;  /* overflow.*/

	        	AT24C64_DATA.BIT16_DATA = reg_address ;

	        	I2C_FLAG = i2c_read_n_byte_data_two_reg_addr(EEPROM_SLAVE_ADDRESS,AT24C64_DATA.BYTE[1],AT24C64_DATA.BYTE[0],n_byte,&r_data_stream[0]);

	        	if(I2C_FLAG == 1)
	          	{
	            		return 0;
	          	}
	       	else 
			{
				return -1;
	       	}
	       }
	       else
	       {
			//printf("register address error!!\r\n");
			return -1;
	       }
	  	/*------------------------------ AT24C64 --------------------------------------*/

#else
	//printf("AT24CXX type define error\r\n");
        while(1);
#endif

}
/*------------------------------------------------------------------------------------------------*/
