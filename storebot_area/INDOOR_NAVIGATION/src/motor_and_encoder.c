/*
 * hc020kencoder.c
 *
 *  Created on: 05-Apr-2018
 *      Author: jincy
 */
#include "functions.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "LPC17xx.h"

#include "lpc_types.h"
#include "i2c.h"
#include "lsm303.h"
#include "string.h"
#include "math.h"

//pwm functions
#define SBIT_CNTEN     0
#define SBIT_PWMEN     2

#define SBIT_PWMMR0R   1

#define SBIT_LEN0      0
#define SBIT_LEN1      1
#define SBIT_LEN2      2
#define SBIT_LEN3      3
#define SBIT_LEN4      4

#define SBIT_PWMENA1   9
#define SBIT_PWMENA2   10
#define SBIT_PWMENA3   11
#define SBIT_PWMENA4   12


void hc020k_init(void)
{
	//LPC_GPIO1->FIODIR |= (0<<18);	//P0.18 is input
    GPIOSetDir(1, 18, 0 );
	LPC_PINCON->PINSEL3 |= (1<<4);
	LPC_PINCON->PINSEL3 |= (1<<5);
	LPC_SC->PCONP |= 1 << 2; //Power up TimerCounter1
}

int speed_encoder_start(void)
{
	int pulses;
	LPC_TIM1->TCR |= 1 << 0; // Counter mode
	LPC_TIM1->PR |= 60; // COUNT AT 60th cycle

	LPC_TIM1->CTCR |= 1; // Count on falling edges
	LPC_TIM1->CTCR |= 0 << 2; // CAP1.0 is the input pin for which the input signal needs to be connected.
	pulses=(LPC_TIM1->TC)/20;
	return(pulses);
}


void motor_init(void)
{
    GPIOSetDir(1, 23, 1 );
    GPIOSetDir(1, 21, 1 );
    LPC_PINCON->PINSEL3 = (0<<11) | (0<<15) | (0<<10) | (0<<14); //	P1.21 (PWM1.3) and P1.23 (PWM1.4)
    GPIOSetDir(1, 19, 1 );
    GPIOSetDir(1, 25, 1 );
    LPC_PINCON->PINSEL3 = (0<<7) | (0<<6) | (0<<19) | (0<<18); //	P1.21 (PWM1.3) and P1.23 (PWM1.4)
    GPIOSetDir(2, 11, 1 );
    GPIOSetDir(2, 12, 1 );
    LPC_PINCON->PINSEL4 = (0<<22) | (0<<23) | (0<<24) | (0<<25); //	P2.11 (PWM1.3) and P2.12 (PWM1.4)
    GPIOSetDir(0, 21, 1 );
    GPIOSetDir(0, 22, 1 );
    LPC_PINCON->PINSEL1 = (0<<12) | (0<<13) | (0<<14) | (0<<15); //	P0.21 (PWM1.3) and P0.22 (PWM1.4)

/*	LPC_GPIO1->FIOMASK |= (0<<21)|(0<<23);
	LPC_GPIO1->FIOMASK |= (0<<19)|(0<<25);
	LPC_GPIO2->FIOMASK |= (0<<11)|(0<<12);
	LPC_GPIO0->FIOMASK |= (0<<22)|(0<<21);*/
}

void roboticarm_init(void)
{
	LPC_GPIO1->FIODIR|=(1<<24);//updown motor left
    LPC_PINCON->PINSEL3 = (0<<18) | (0<<19) ; //	P1.21 (PWM1.3) and P1.23 (PWM1.4)
	LPC_GPIO0->FIODIR|=(1<<19);//pick n place
    LPC_PINCON->PINSEL1 = (0<<8) | (0<<9) ; //	P1.21 (PWM1.3) and P1.23 (PWM1.4)
	LPC_GPIO1->FIODIR|=(1<<27);//updown motor right
    LPC_PINCON->PINSEL3 = (0<<24) | (0<<25) ; //	P1.21 (PWM1.3) and P1.23 (PWM1.4)
	LPC_GPIO1->FIODIR|=(1<<29);//bottom motor
    LPC_PINCON->PINSEL3 = (0<<28) | (0<<29) ; //	P1.21 (PWM1.3) and P1.23 (PWM1.4)

}


int *forward(int xy[2])
{
	int distance;
	int direction;
	direction=magnetometer_reading();
	//dc back1
	//dc back2
	distance=speed_encoder_start();
	if((direction<=x_increase+10)&&(direction>=x_increase-10))
		xy[0]=xy[0]+distance;
	else if(direction==y_increase)
		xy[1]=xy[1]+distance;
	else if(direction==x_decrease)
		xy[0]=xy[0]-distance;
	else if(direction==y_decrease)
		xy[1]=xy[1]-distance;
	return(xy);
}

/*
int obstacle_traverse(int xy[2])
{
	int count2,x_temp_1;
	right();
	xy=forward(xy);
	if(ultraright>=50)
		stop();
	right();
	while(count2<=obst_dimension_x)
	{
		x_temp_1=xy[1];
		xy=forward(xy);
		count2=xy[0]-x_temp_1;
	}
	stop();
	left();
	//xy=forward(xy);

	return(xy);

}*/

void back(void)
{
	   GPIOSetValue( 1, 21, 0 );
	   GPIOSetValue( 1, 23, 1 );
	   GPIOSetValue( 1, 19, 1 );
	   GPIOSetValue( 1, 25, 0 );
	   GPIOSetValue( 2, 12, 0 );
	   GPIOSetValue( 2, 11, 1 );
	   GPIOSetValue( 0, 21, 0 );
	   GPIOSetValue( 0, 22, 1 );
		delay_ms_motor(1000);
		   GPIOSetValue( 1, 21, 1 );
		   GPIOSetValue( 1, 23, 1 );
		   GPIOSetValue( 1, 19, 1 );
		   GPIOSetValue( 1, 25, 1 );
		   GPIOSetValue( 2, 12, 1 );
		   GPIOSetValue( 2, 11, 1 );
		   GPIOSetValue( 0, 21, 1 );
		   GPIOSetValue( 0, 22, 1 );


}


void front(void)
{
	int pulses;
	   GPIOSetValue( 1, 21, 1 );
	   GPIOSetValue( 1, 23, 0 );
	   GPIOSetValue( 1, 19, 0 );
	   GPIOSetValue( 1, 25, 1 );
	   GPIOSetValue( 2, 12, 1);
	   GPIOSetValue( 2, 11, 0 );
	   GPIOSetValue( 0, 21, 1 );
	   GPIOSetValue( 0, 22, 0 );

	 //  pulses = speed_encoder_start();
	   print_string("count:");
	   print_dec_no_in_ascii(10);

}

void stop(void)
{
	   	   	   GPIOSetValue( 1, 21, 1 );
			   GPIOSetValue( 1, 23, 1 );
			   GPIOSetValue( 1, 19, 1 );
			   GPIOSetValue( 1, 25, 1 );
			   GPIOSetValue( 2, 12, 1 );
			   GPIOSetValue( 2, 11, 1 );
			   GPIOSetValue( 0, 21, 1 );
			   GPIOSetValue( 0, 22, 1 );
			   print_string("stop_executed"); //delete

	delay_ms_motor(3000);
	//ultra_init();

	//print_dec_no_in_ascii(10);
}

void right(void)
{

	   GPIOSetValue( 1, 19, 0 );
	   GPIOSetValue( 1, 25, 1 );
	   GPIOSetValue( 2, 12, 1);
	   GPIOSetValue( 2, 11, 0 );
	   GPIOSetValue( 1, 21, 1 );
	   GPIOSetValue( 1, 23, 1 );
	   GPIOSetValue( 0, 21, 1 );
	   GPIOSetValue( 0, 22, 1 );

	   delay_ms_motor(1960);

	   GPIOSetValue( 1, 21, 1 );
	   GPIOSetValue( 1, 23, 1 );
	   GPIOSetValue( 1, 19, 1 );
	   GPIOSetValue( 1, 25, 1 );
	   GPIOSetValue( 2, 12, 1 );
	   GPIOSetValue( 2, 11, 1 );
	   GPIOSetValue( 0, 21, 1 );
	   GPIOSetValue( 0, 22, 1 );




}
void left(void)
{
	   GPIOSetValue( 1, 21, 1 );
	   GPIOSetValue( 1, 23, 0 );
	   GPIOSetValue( 0, 21, 1 );
	   GPIOSetValue( 0, 22, 0 );
		GPIOSetValue( 1, 19, 1 );
		GPIOSetValue( 1, 25, 1 );
		GPIOSetValue( 2, 12, 1 );
		GPIOSetValue( 2, 11, 1 );

	delay_ms_motor(2200);

	GPIOSetValue( 1, 21, 1 );
	GPIOSetValue( 1, 23, 1 );
	GPIOSetValue( 1, 19, 1 );
	GPIOSetValue( 1, 25, 1 );
	GPIOSetValue( 2, 12, 1 );
	GPIOSetValue( 2, 11, 1 );
	GPIOSetValue( 0, 21, 1 );
	GPIOSetValue( 0, 22, 1 );


	//print_dec_no_in_ascii(30);
}

void robot_turn(int turn)
{
	if (turn==0)
	{
		right();
	}
	else
	{
		left();
	}
}
int ultra_leftright_check(int side)
{
	int border;
	if (side==1) //CHECK LEFT SIDE #OBSTACLE PRESENT AT LEFT SIDE
	{
		border=ultrasonic_left();
	}
	else //CHECKING RIGHT SIDE #OBSTACLE AT RIGHT SIDE
	{
		border=ultrasonic_right();
	}
	return(border);
}

void updownleft (unsigned int ms)
{
	int x;
for (x=0;x<5;x++)
{
	int i,j;
	LPC_GPIO1->FIOSET = (1<<24);//0
	for(i=0;i<ms;i++)
	for(j=0;j<2000;j++);
	LPC_GPIO1->FIOCLR= (1<<24);
	for(i=0;i<(300-ms);i++)
	for(j=0;j<2000;j++);
}

}

void updownright (unsigned int ms)
{
	int x;
for (x=0;x<10;x++)
{
	int i,j;
	LPC_GPIO1->FIOSET = (1<<27);//0
	for(i=0;i<ms;i++)
	for(j=0;j<2000;j++);
	LPC_GPIO1->FIOCLR= (1<<27);
	for(i=0;i<(300-ms);i++)
	for(j=0;j<2000;j++);
}

}

void bottom (unsigned int ms)
{
	int x;
for (x=0;x<7;x++)
{
	int i,j;
	LPC_GPIO1->FIOSET = (1<<29);//0
	for(i=0;i<ms;i++)
	for(j=0;j<2000;j++);
	LPC_GPIO1->FIOCLR= (1<<29);
	for(i=0;i<(300-ms);i++)
	for(j=0;j<2000;j++);
}

}

void pick (unsigned int ms)
{
	int x;
for (x=0;x<3;x++)
{
	int i,j;
	LPC_GPIO0->FIOSET = (1<<19);//0
	for(i=0;i<ms;i++)
	for(j=0;j<2000;j++);
	LPC_GPIO0->FIOCLR= (1<<19);
	for(i=0;i<(300-ms);i++)
	for(j=0;j<2000;j++);
}

}
