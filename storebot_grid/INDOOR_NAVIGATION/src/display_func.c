/*
 * display_func.c
 *
 *  Created on: 12-Mar-2018
 *      Author: jincy
 */

#include "LPC17xx.h"
#include "functions.h"
#include "string.h"
#include "math.h"

//decimal to ascii
void print_dec_no_in_ascii(int y)
{
    int x1,x2,x3,x4,x5,x6,x7,x8;

    x1=y/1000;
	x2=y%1000;
	x3=x2/100;
	x4=x2%100;
	x5=x4/10;
	x6=x4%10;

	UART1_Sendchar(x1+'0');
	//UART1_Sendchar('.');
	UART1_Sendchar(x3+'0');
	UART1_Sendchar(x5+'0');
	UART1_Sendchar(x6+'0');
	/*UART1_Sendchar(x1);
	UART1_Sendchar(x3);
	UART1_Sendchar(x5);
	UART1_Sendchar(x6);*/

	UART1_Sendchar(' ');
	UART1_Sendchar(' ');
	UART1_Sendchar(' ');
	UART1_Sendchar(' ');

}

void print_string(char* s)
{
	  while(*s)
	  {
		  UART1_Sendchar(*s);
		  s++;
	  }
}
//convert hex to ascii

void print_hex_in_ascii_16(int x)
{

	int quotient=x,temp,i=3,j;
	char hexadecimalnumber[256];
	if( quotient==0)
		UART1_Sendchar(0+'0'); // adding 48
	while(quotient!=0)
	      {
			temp = quotient % 16;
			//To convert integer into character
 			if( temp < 10)
			temp =temp + 48;
			else
			temp = temp + 55;
			hexadecimalnumber[i]= temp;
			quotient = quotient / 16;
			i--;
   			  }
	for (j = 0 ;j<4;j++)
			  	{
			  		UART1_Sendchar(hexadecimalnumber[j]);
			  	}
	 UART1_Sendchar(' ');
	 UART1_Sendchar(' ');
	 UART1_Sendchar(' ');
	 UART1_Sendchar(' ');
	}
int binary_to_dec (int num)
{
	int binary_val, rem, decimal_val=0,base=1;
	binary_val = num;
    while (num > 0)
    {
        rem = num % 10;
        decimal_val = decimal_val + rem * base;
        num = num / 10 ;
        base = base * 2;

    }
    return(decimal_val);
}

void print_hex_in_ascii(int x)
{

	int quotient=x,temp1,i=1,j;
	char hexadecimalNumber[256];
	if( quotient==0)
		UART1_Sendchar(0+'0');
	while(quotient!=0)
	      {
			temp1 = quotient % 16;
			//To convert integer into character
 			if( temp1 < 10)
			temp1 =temp1 + 48;
			else
			temp1 = temp1 + 55;
			hexadecimalNumber[i++]= temp1;
			quotient = quotient / 16;
   		  }
	for (j = i -1 ;j> 0;j--)
			  	{
			  		UART1_Sendchar(hexadecimalNumber[j]);
			  	}
	 UART1_Sendchar(' ');
	 UART1_Sendchar(' ');
	 UART1_Sendchar(' ');
	 UART1_Sendchar(' ');
	}
/*int dec_to_bin(int dec)
{
	int i,a[9];
	for(i=0;dec>0;i++)
	{
	a[i]=dec%2;
	dec=dec/2;
	}
	for(i=i-1;i>=0;i--)
	{
		return a[i]);
	}

}*/
