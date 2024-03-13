//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2009-11 Code Red Technologies Ltd.
//
// main_ledflash.c demonstrates the use of the "user LEDs" on the
// RDB1768 development board (LEDs 2-5).
//
//
// Software License Agreement
// 
// The software is owned by Code Red Technologies and/or its suppliers, and is 
// protected under applicable copyright laws.  All rights are reserved.  Any 
// use in violation of the foregoing restrictions may subject the user to criminal 
// sanctions under applicable laws, as well as to civil liability for the breach 
// of the terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
// TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
// CODE RED TECHNOLOGIES LTD. 

#include "functions.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "LPC17xx.h"

#include "lpc_types.h"

#include "string.h"
#include "math.h"


// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;



#define I2C_PORT_USED 1
int x[100]={10, 10,15,15,35,35,30,30,20,20,15,15,30,30,25,25,15,15,10,10,20,20,25,25};
int y[100]={0,5,5,0,5,10,10,5,5,10,10,5,15,20,20,15,15,20,20,15,20,25,25,20};

uint8_t  j,i;


int main(void)
{
    int i,k;
    char grid[10][10];
    int d_x=31,d_y=27;
    int g_x,g_y,gx_disp,gy_disp;
    int command;
    SystemInit();
	port_init();
	UART1_Init(9600);

	//float check_zero_acc = motion_check()+0.045;
	// if(UART1_Getchar()=='A')
    while(1)
    {
    	print_string("xoriginal:");
    	    	for (j=0;j<50;j++)
    	    	{
    	    		print_dec_no_in_ascii(x[j]);

    	    		UART1_Sendchar(' ');
    	    	}
    	    	UART1_Sendchar('\n');

    	//obstacle location modified
  	for (i=0;i<100;i++)
    	{
    		if(x[i]>x[i+2])
    		{
    			x[i]=x[i]+x[i+2];
    			x[i+2]=x[i]-x[i+2];
    			x[i]=x[i]-x[i+2];
    			x[i+1]=x[i+1]+x[i+3];
    			x[i+3]=x[i+1]-x[i+3];
    			x[i+1]=x[i+1]-x[i+3];
    		}
    		y[i]=y[i+3];
    		i=i+3;
    	}
    	int temp1[4];
    	for (k=0;k<100;k++)
    	{
    		if(y[k]==y[k+4])
    		{
    			if(x[k]>x[k+4])
    			{
    				temp1[0]=x[k];
    				temp1[1]=x[k+1];
    				temp1[2]=x[k+2];
    				temp1[3]=x[k+3];
    				x[k]=x[k+4];
    				x[k+1]=x[k+5];
    				x[k+2]=x[k+6];
    				x[k+3]=x[k+7];
    				x[k+4]=temp1[0];
    				x[k+5]=temp1[1];
    				x[k+6]=temp1[2];
    				x[k+7]=temp1[3];

    			}
    		}
    		k=k+3;
    		//temp1={0};
    	}
int j=0;
int x_init=0,y_init=0;
    	//obstacles into grid
    	for (g_y=0;g_y<10;g_y++)
    	{
    		for(g_x=0;g_x<10;g_x++)
    		{
    			if((x[j]>=(x_init))&&(x[j+3]<=(x_init+6))&&(y[j]>=y_init)&&(y[j+1]<=(y_init+6)))
    				{
    			    	grid[g_y][g_x]=1;
    			    	j=j+4;
     			    }
    			else if((d_x>=(x_init))&&(d_x<=(x_init+5))&&(d_y>=y_init)&&(d_y<=(y_init+6)))
					{
						grid[g_y][g_x]='d';
					}
    			else grid[g_y][g_x]=0;
    			x_init=x_init+5;
    		}
    		if(x_init==50)
    		{
    			x_init=0;
    		}
    		y_init=y_init+5;
    	}
    		if(y_init==50)
    		{
    		    y_init=0;
    		}

 /*  	for (g_y=0;g_y<10;g_y++)
    	{
    		for (g_x=0;g_x<10;g_x++)
    		{
    			//print_dec_no_in_ascii(grid[gy_disp][gx_disp]);
    			UART1_Sendchar(grid[g_y][g_x]+'0');
    			UART1_Sendchar(' ');
    		}
    		UART1_Sendchar('\n');
    	}
*/


    	UART1_Sendchar('\n');


}
//}
}
