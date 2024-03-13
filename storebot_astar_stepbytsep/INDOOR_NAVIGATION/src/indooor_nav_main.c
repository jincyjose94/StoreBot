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
#include "astar.h"

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

//uint8_t  j,i;


int main(void)
{
    int i,k;
    int *astar;
    int x[100]={10, 10,15,15,35,35,30,30,20,20,15,15,30,30,25,25,15,15,10,10,20,20,25,25};
    int y[100]={0,5,5,0,5,10,10,5,5,10,10,5,15,20,20,15,15,20,20,15,20,25,25,20};
    int grid[10][10]={{0,0,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,1,0,0,1,0,0,0,0},{0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
    int d_x=31,d_y=27;
    int g_x,g_y,gx_disp,gy_disp;
    int top,c=0;
    int command;
    int parent[40]={0};
    SystemInit();
	port_init();
	UART1_Init(9600);
int array[40]={1,2};
int length=2;
	//float check_zero_acc = motion_check()+0.045;
	// if(UART1_Getchar()=='A')
    while(1)
    {
	astar=astarpath(grid, 0, 0, 6, 5);
   	for (i=0;i<40;i++)
	{
		parent[i]=*(astar+i);
	}

	print_string("x:");
	for (k=0;k<40;k++)
		print_dec_no_in_ascii(parent[k]);


 /*  	command=astarpath(grid, 0, 0, 3, 2);
		print_dec_no_in_ascii(command);

    	if(UART1_Getchar()=='A')
    	{
    		print_string("x:");
    		push(array, 1);
    		for (i=0;i<size_array;i++)
    		{
    			top=array[i];
    		    if(top!=0) c++;
    		}
    			array[c]=2;


    	}
    	else if (UART1_Getchar()=='B')
    	{
    		for (k=0;k<20;k++)
    		    			    		print_dec_no_in_ascii(array[k]);
    	}*/
    	//push(array[20], 1);
    		//array[1]=1;

    	UART1_Sendchar('\n');

}
//}
}
