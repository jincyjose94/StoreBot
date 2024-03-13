/*
 * ultrasonic.c
 *
 *  Created on: 20-Mar-2018
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

void ultra_init(void)
{
	LPC_PINCON->PINSEL3|=(0<<20)&(0<<21)&(0<<24)&(0<<25);	//GPIO function for P1.26, P1.28
	LPC_PINCON->PINSEL4|=(0<<0)&(0<<1)&(0<<2)&(0<<3);	//GPIO function for P2.0, P2.1
	LPC_PINCON->PINSEL4|=(0<<14)&(0<<15)&(0<<16)&(0<<17);	//GPIO function for 92.7, P2.8
	LPC_SC->PCONP |= 1 << 1;                                         //Power up Timer 0

}

#if 0
using  J1_18 and J1_19 free
J!_18=p0.30
J1_19=p0.29
#endif

long int getPulseWidth_usfront()
    {
		uint32_t i=0,result;
			   //Wait for the rising edge
			   for(i=0;i<600000;i++)
			   {
				  if(!(LPC_GPIO1->FIOPIN & (1<<28))) continue; else break;// if(!x) is same as if(x==0)
			   }
			   if(i==600000)
				  return 0xffff; //Indicates time out
       //High Edge Found
       //Setup Timer1
       LPC_TIM0->TC=0x00000000; // init counter
       //LPC_TIM0->PR=1; // prescale=1
       LPC_TIM0->TCR |= 1 << 1;       // reset timer
       LPC_TIM0->TCR &= ~(1 << 1);   // stop resetting the timer.
       LPC_TIM0->TCR |= 1 << 0;                                      // Start timer
			   //Now wait for the falling edge
			   for(i=0;i<600000;i++)
			   {
				  if(LPC_GPIO1->FIOPIN & (1<<28))
				  {
					 if((LPC_TIM0->TC) > 600000) break; else continue;
				  }
				  else
				   break;
			   }

			   if(i==600000)
				  return 0xffff; //Indicates time out
       //Falling edge found
       result=(LPC_TIM0->TC); //STORE COUNT IN RESULT
       //Stop Timer
       LPC_TIM0->TCR |= 0 << 0;
       if(result > 600000)
       { return 0xfffe;} //No obstacle
       else
          return (result/2);
    }

long int ultrasonic_front(void)
{
		uint32_t d;
		LPC_SC->PCLKSEL0 |= ( 1 << 2)|(1<<3);                        // Clock for timer = CCLK /4 -->12000000/4hz
    	//Set Ultra Sonic Port as out
		LPC_GPIO1->FIODIR|=(1<<26);
			delay_us(10);
		//Give the US pin a 15us High Pulse
		LPC_GPIO1->FIOSET|=(1<<26);   //High
			delay_us(15);
		LPC_GPIO1->FIOCLR|=(1<<26);//Low
			delay_us(20);
		//Now make the pin input
		LPC_GPIO1->FIODIR&=(~(1<<28));
		//Measure the width of pulse
		int r=getPulseWidth_usfront();
		//print_string("rf: ");
		//print_dec_no_in_ascii(r);
		//Handle Errors
		if(r==0xffff)
			//print_string("error");
			return(0);
		else  if(r==0xfffe)
			//print_string("clear");
			//return('h');
			d=(r/58.0); //Convert to cm
		else
		  {
			d=(r/58.0); //Convert to cm
		  }
		return(d);
}

long int getPulseWidth_usright()
    {
		uint32_t i=0,result;
		//Wait for the rising edge
		for(i=0;i<600000;i++)
		{
			if(!(LPC_GPIO2->FIOPIN & (1<<8))) continue; else break;// if(!x) is same as if(x==0)
		}
		 if(i==600000)
				  return 0xffff; //Indicates time out
       //High Edge Found
       //Setup Timer1
       LPC_TIM0->TC=0x00000000; // init counter
       //LPC_TIM0->PR=1; // prescale=1
       LPC_TIM0->TCR |= 1 << 1;       // reset timer
       LPC_TIM0->TCR &= ~(1 << 1);   // stop resetting the timer.
       LPC_TIM0->TCR |= 1 << 0;                                      // Start timer
			   //Now wait for the falling edge
			   for(i=0;i<600000;i++)
			   {
				  if(LPC_GPIO2->FIOPIN & (1<<8))
				  {
					 if((LPC_TIM0->TC) > 600000) break; else continue;
				  }
				  else
				   break;
			   }

			   if(i==600000)
				  return 0xffff; //Indicates time out
       //Falling edge found
       result=(LPC_TIM0->TC); //STORE COUNT IN RESULT
       //Stop Timer
       LPC_TIM0->TCR |= 0 << 0;
       if(result > 600000)
       { return 0xfffe;} //No obstacle
       else
          return (result/2);
    }

long int ultrasonic_right(void)
{
		uint32_t d;
		LPC_SC->PCLKSEL0 |= ( 1 << 2)|(1<<3);                        // Clock for timer = CCLK /4 -->12000000/4hz
    	//Set Ultra Sonic Port as out
		LPC_GPIO2->FIODIR|=(1<<7);
			delay_us(10);
		//Give the US pin a 15us High Pulse
		LPC_GPIO2->FIOSET|=(1<<7);   //High
			delay_us(15);
		LPC_GPIO2->FIOCLR|=(1<<7);//Low
			delay_us(20);
		//Now make the pin input
		LPC_GPIO2->FIODIR&=(~(1<<8));
		//Measure the width of pulse
		int r=getPulseWidth_usright();
		//print_string("r_r8: ");
		//print_dec_no_in_ascii(r);
		//Handle Errors
		if(r==0xffff)
			//print_string("error");
			return('h');
		else  if(r==0xfffe)
			//print_string("clear");
			//return(0);
			d=(r/58.0); //Convert to cm
		else
		  {
			d=(r/58.0); //Convert to cm
		  }
		return(d);
}

long int getPulseWidth_usleft()
    {
		uint32_t i=0,result;
			   //Wait for the rising edge
			   for(i=0;i<600000;i++)
			   {
				  if(!(LPC_GPIO2->FIOPIN & (1<<1))) continue; else break;// if(!x) is same as if(x==0)
			   }
			   if(i==600000)
				  return 0xffff; //Indicates time out
       //High Edge Found
       //Setup Timer1
       LPC_TIM0->TC=0x00000000; // init counter
       //LPC_TIM0->PR=1; // prescale=1
       LPC_TIM0->TCR |= 1 << 1;       // reset timer
       LPC_TIM0->TCR &= ~(1 << 1);   // stop resetting the timer.
       LPC_TIM0->TCR |= 1 << 0;                                      // Start timer
			   //Now wait for the falling edge
			   for(i=0;i<600000;i++)
			   {
				  if(LPC_GPIO2->FIOPIN & (1<<1))
				  {
					 if((LPC_TIM0->TC) > 600000) break; else continue;
				  }
				  else
				   break;
			   }

			   if(i==600000)
				  return 0xffff; //Indicates time out
       //Falling edge found
       result=(LPC_TIM0->TC); //STORE COUNT IN RESULT
       //Stop Timer
       LPC_TIM0->TCR |= 0 << 0;
       if(result > 600000)
       { return 0xfffe;} //No obstacle
       else
          return (result/2);
    }

long int ultrasonic_left(void)
{
		uint32_t d;
		LPC_SC->PCLKSEL0 |= ( 1 << 2)|(1<<3);                        // Clock for timer = CCLK /4 -->12000000/4hz
    	//Set Ultra Sonic Port as out
		LPC_GPIO2->FIODIR|=(1<<0);
			delay_us(10);
		//Give the US pin a 15us High Pulse
		LPC_GPIO2->FIOSET|=(1<<0);   //High
			delay_us(15);
		LPC_GPIO2->FIOCLR|=(1<<0);//Low
			delay_us(20);
		//Now make the pin input
		LPC_GPIO2->FIODIR&=(~(1<<1));
		//Measure the width of pulse
		int r=getPulseWidth_usleft();
		//print_string("rleft: ");
		//print_dec_no_in_ascii(r);
		//Handle Errors
		if(r==0xffff)
			//print_string("error");
			return('h');
		else  if(r==0xfffe)
			//print_string("clear");
			//return(0);
			d=(r/58.0); //Convert to cm
		else
		  {
			d=(r/58.0); //Convert to cm
		  }
		return(d);
}


void delay_us(int delay)
{
	int i,j;
 for(i=0;i<delay;i++)
 for(j=0;j<15;j++);
}
