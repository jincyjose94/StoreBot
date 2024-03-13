/*
 * lsm303.c
 *
 *  Created on: 08-Feb-2018
 *      Author: jincy
 */

#include "lpc17xx.h"
#include "lpc_types.h"
#include "i2c.h"
#include "functions.h"
#include "lsm303.h"
#include "string.h"
#include "math.h"
#include <stdlib.h>

#define I2C_PORT_USED 1
int i;


/*////////////////////single write////////////////////////*/
//ACCELEROMETER WRITE
uint8_t  EX_LSM303A_WRITE(uint8_t adres, uint8_t veri)
{
		//I2CStart( I2C_PORT_USED );
	  for ( i = 0; i < BUFSIZE; i++ )	/* clear buffer */
	  {
		I2CMasterBuffer[I2C_PORT_USED][i] = 0;
	  }
	  I2CWriteLength[I2C_PORT_USED] = 3;
	  I2CReadLength[I2C_PORT_USED]  = 0;
	  I2CMasterBuffer[I2C_PORT_USED][0] = ACCELEROMETER_ADDR;
	  I2CMasterBuffer[I2C_PORT_USED][1] = adres;
	  I2CMasterBuffer[I2C_PORT_USED][2] = veri;
	  if(I2CEngine(I2C_PORT_USED))
	  return 1;
	  else
	  return 0;
	 // I2CStop(I2C_PORT_USED);
}


/*////////////////////////////////////single read////////////////////////////*/
//ACCELEROMETER READ
uint8_t  EX_LSM303A_READ(uint8_t adres)
{
		//I2CStart( I2C_PORT_USED );
	   for ( i = 0; i < BUFSIZE; i++ )	  	/* clear buffer */
	   {
		I2CMasterBuffer[I2C_PORT_USED][i] = 0;
		I2CSlaveBuffer[I2C_PORT_USED][i] = 0;

	   }

	  I2CWriteLength[I2C_PORT_USED] = 2;
	  I2CReadLength[I2C_PORT_USED] = 1;
	  I2CMasterBuffer[I2C_PORT_USED][0] = ACCELEROMETER_ADDR;
	  I2CMasterBuffer[I2C_PORT_USED][1] = adres;
	  I2CMasterBuffer[I2C_PORT_USED][2] = ACCELEROMETER_ADDR|RD_BIT;
	  I2CEngine(I2C_PORT_USED);
	  I2CStop(I2C_PORT_USED);
	 //return (I2CMasterBuffer[I2C_PORT_USED][3]);

	  return (I2CSlaveBuffer[I2C_PORT_USED][0]);
  }

/*/////////////////////////////////single write mag///////////////////////////////////*/
//MAGNETOMETER WRITE
uint8_t  EX_LSM303M_WRITE(uint8_t adres, uint8_t veri)
{
		//I2CStart( I2C_PORT_USED );
	  for ( i = 0; i < BUFSIZE; i++ )	/* clear buffer */
	  {
		I2CMasterBuffer[I2C_PORT_USED][i] = 0;
	  }
	  I2CWriteLength[I2C_PORT_USED] = 3;
	  I2CReadLength[I2C_PORT_USED]  = 0;
	  I2CMasterBuffer[I2C_PORT_USED][0] = MAGNETOMETER_ADDR;
	  I2CMasterBuffer[I2C_PORT_USED][1] = adres;
	  I2CMasterBuffer[I2C_PORT_USED][2] = veri;
	  if(I2CEngine(I2C_PORT_USED))
	  return 1;
	  else
	  return 0;
	 // I2CStop(I2C_PORT_USED);
}

/*/////////////////////////////single read mag///////////////////////////////*/
//MAGNETOMETER READ
uint8_t  EX_LSM303M_READ(uint8_t adres)
{
		//I2CStart( I2C_PORT_USED );
	   for ( i = 0; i < BUFSIZE; i++ )	  	/* clear buffer */
	   {
		I2CMasterBuffer[I2C_PORT_USED][i] = 0;
		I2CSlaveBuffer[I2C_PORT_USED][i] = 0;

	   }

	  I2CWriteLength[I2C_PORT_USED] = 2;
	  I2CReadLength[I2C_PORT_USED] = 1;
	  I2CMasterBuffer[I2C_PORT_USED][0] = MAGNETOMETER_ADDR;
	  I2CMasterBuffer[I2C_PORT_USED][1] = adres;
	  I2CMasterBuffer[I2C_PORT_USED][2] = MAGNETOMETER_ADDR|RD_BIT;
	  I2CEngine(I2C_PORT_USED);
	  I2CStop(I2C_PORT_USED);
	 //return (I2CMasterBuffer[I2C_PORT_USED][3]);

	  return (I2CSlaveBuffer[I2C_PORT_USED][0]);
  }


void LSM303_init (void)
{
	//CONFIGURE ACCELEROMETER
	//EX_LSM303A_WRITE(CTRL_REG5_A,0x40);
	EX_LSM303A_WRITE(CTRL_REG1_A,0x57);		//data rate=100Hz and enable x,y,z axis
	//EX_LSM303A_WRITE(CTRL_REG2_A,0x08);		//hp filter disabled
	EX_LSM303A_WRITE(CTRL_REG4_A,0x08);		//2g acceleration+MSB @ high byte=10, 08=high resolution=1 bit, else only 10 bit
	//EX_LSM303A_WRITE(CTRL_REG5_A,0x40);		//fifo enable, reboot disable
	//EX_LSM303A_WRITE(FIFO_CTRL_REG_A,0x40);	//FIFO mode
	//EX_LSM303A_WRITE(0x26,0x00);
	//CONFIGURE MAGNETOMETER
	EX_LSM303M_WRITE(CRA_REG_M,0x18);  //data rate configurations in CRA_REG_M register, 15hz default value= 100 for D2 D1 D0
	EX_LSM303M_WRITE(CRB_REG_M,0x20);  //gain configuration
	EX_LSM303M_WRITE(MR_REG_M,0x00);   //mode selection


}

	/*reading magnetometer registers and angle calculation*/
int magnetometer_reading(void)
//void magnetometer_reading(void)
	{
		int16_t x_mag_m,y_mag_m;
		float heading;
		float Pi = 3.14159;
		int16_t mag_x_h=EX_LSM303M_READ(OUT_X_H_M);
		int16_t mag_x_l=EX_LSM303M_READ(OUT_X_L_M);
		int16_t mag_y_h=EX_LSM303M_READ(OUT_Y_H_M);
		int16_t mag_y_l=EX_LSM303M_READ(OUT_Y_L_M);
		x_mag_m = (int16_t)(((int16_t)mag_x_h<<8) | mag_x_l);  // Turn the MSB LSB into signed 16-bit value
		y_mag_m = (int16_t)(((int16_t)mag_y_h<<8) | mag_y_l);  // MAG_Y
		heading = (atan2(y_mag_m,x_mag_m) * 180) / Pi;
		if(heading < 0)
		   	{
		        heading = 360 + heading;
		   	}
		return(heading);
	}

double accelerometer_reading(void)
{
	int i;
	float acc[100];
	float x_org;
	float thousand=1000;
	float hundred=100;
	float sum;
	int16_t acc_x_h=(EX_LSM303A_READ(OUT_X_H_A));
	int acc_x_l=(EX_LSM303A_READ(OUT_X_L_A));
	int16_t x_16bit = ((int16_t)((int16_t)acc_x_h<<7 | acc_x_l>>1))/8;
	signed int x_ac= hexadecimalToDecimal(x_16bit);
	float x_acc=x_ac;

	if(x_acc>2047)
			{
				x_org = x_acc - 4096;
			}
	else x_org = x_acc;
	float x_value=x_org/thousand;
	return(x_value);
}

float callibrate_acc(void)
{
	  float sstatex=0, Sample_X;
	  unsigned int count1;
	  float offset_pos, offset_neg;
	  count1 = 0;
	  do{
	  Sample_X = accelerometer_reading();
	  sstatex = sstatex + Sample_X;              // Accumulate Samples
	  count1++;
	  }while(count1!=100);                    // 100 times
	  sstatex=sstatex/100;                       // division between 100
	  	  /* calibration */
	  	  if(sstatex>=0)
	  	  {
	  		sstatex=(sstatex+0.003)*9.8;
	  	  }
	  	  else
	  	  {
	  		sstatex=(sstatex+0.065)*9.8;
	  	  }
	  	  /* calibration over */

	  return(sstatex);
	  /*if(sstatex >= 0)
		  {
		   offset_pos= 1-sstatex; //calculate positive acceleration offset

		  }
	  else
		  {
		   offset_neg=1-(2+sstatex); //calculate positive acceleration offset
		  }*/
	 //print offset values to callibrate
	  /*print_string("offsetpositive");
	  disp_acc(offset_pos);
	  print_string("offsetnegative");
	  disp_acc(offset_neg);*/
}
float motion_check(void)
{
	float s,a[200];
	int i;
	for (i=0;i<200;i++)
	{
		a[i]=callibrate_acc();
		s=s+a[i];
	}
	s=s/200;
	return(s);
}
