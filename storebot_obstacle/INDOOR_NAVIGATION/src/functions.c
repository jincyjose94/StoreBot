
#include "LPC17xx.h"
#include "functions.h"
#include "string.h"
#include "math.h"

// Function to initialize GPIO to access the user LEDs
void port_init (void)
{
	//LPC_PINCON->PINSEL0=0;
	LPC_PINCON->PINSEL2=0;	//GPIO function for port0

//	LPC_PINCON->PINSEL2=0;
//	LPC_PINCON->PINSEL3=0;	//GPIO function for port1

//	LPC_PINCON->PINSEL4=0;	//GPIO function for port2
//	LPC_PINCON->PINSEL7=0;	//GPIO function for port3
//	LPC_PINCON->PINSEL9=0;	//GPIO function for port4
	LPC_GPIO1->FIODIR=(1<<0);	//P1.0 is output


	//LPC_PINCON->PINSEL0=0;
	//LPC_PINCON->PINSEL1=0;	//GPIO function for port0

}
static LPC_GPIO_TypeDef (* const LPC_GPIO[5]) = { LPC_GPIO0, LPC_GPIO1, LPC_GPIO2, LPC_GPIO3, LPC_GPIO4  };


   void GPIOSetValue( uint32_t portNum, uint32_t bitPosi, uint32_t bitVal )
   {
     if (bitVal == 0)
     {
   	  LPC_GPIO[portNum]->FIOCLR = (1<<bitPosi);
     }
     else if (bitVal >= 1)
     {
   	  LPC_GPIO[portNum]->FIOSET = (1<<bitPosi);
     }
   }

   void GPIOSetDir( uint32_t portNum, uint32_t bitPosi, uint32_t dir )
   {
     if(dir)
   	LPC_GPIO[portNum]->FIODIR |= 1<<bitPosi;
     else
   	LPC_GPIO[portNum]->FIODIR &= ~(1<<bitPosi);
   }

   uint32_t GPIOGetValue (uint32_t portNum, uint32_t bitPosi)
    {
       uint32_t val;
       LPC_GPIO[portNum]->FIOMASK = ~(1<<bitPosi);
       val = LPC_GPIO[portNum]->FIOPIN;
       val = val >> bitPosi;
       LPC_GPIO[portNum]->FIOMASK = 0x00000000;
       return val;
     }

void delay(int cnt)
{
    int i;
    for(i=0;i<cnt;i++);
}


void delay_ms(unsigned int ms)
{
unsigned int i,j;
for(i=0;i<ms;i++)
for(j=0;j<2000;j++);
}
void delay_ms_motor(unsigned int ms)
{
unsigned int i,j;
for(i=0;i<ms;i++)
for(j=0;j<5000;j++);
}
void led_on (void)
{
	LPC_GPIO1->FIOSET = (1<<0);//0
}

void led_off (void)
{
	LPC_GPIO1->FIOCLR= (1<<0);
}


// Function to convert hexadecimal to decimal
int hexadecimalToDecimal(int hex)
{
    // Initializing base value to 1, i.e 16^0

	int16_t  dec=0;
	    int  cnt=0;   /*for power index*/
	    int  dig,i;   /*to store digit*/
   char a[3];
    a[2]=hex&0x00F;
    a[1]=(hex&0x0F0)>>4;
    a[0]=(hex&0xF00)>>8;
    // Extracting characters as digits from last character
    for(i=2;i>=0;i--)
        {
            switch(a[i])
            {
                case 'A':
                    dig=10; break;
                case 'B':
                    dig=11; break;
                case 'C':
                    dig=12; break;
                case 'D':
                    dig=13; break;
                case 'E':
                    dig=14; break;
                case 'F':
                    dig=15; break;
                default:
                    //dig=a[i]-0x30;
                    dig=a[i];
            }
            //dig=dig-24;
            dec= dec+ (dig)*pow((double)16,(double)cnt);
            cnt++;
        }
       return dec;
   // return a[1];
}

/*int acc_by_1000(int y)
{
	int x1,x2,x3,x4,x5,x6,x7,x8;
	char res[5];

	    x1=y/1000;
		x2=y%1000;
		x3=x2/100;
		x4=x2%100;
		x5=x4/10;
		x6=x4%10;
		res[0]=(x1+'0');
		res[1]=('.');
		res[2]=(x3+'0');
		res[3]=(x5+'0');
		res[4]=(x6+'0');
		res[5]='\0';
		return (res);

}*/

void disp_acc(float y)
{
	 int y1,y2,y3,y4,y5,y6,y7,y8,y9,y10;
	// Extract integer part
	    int ipart = (int)y;
	// Extract floating part
	    float fpart = y - (float)ipart;
	// Get the value of fraction part upto given no.
	    int fpart1 = fpart * pow(10, 3);

	      y1=fpart1/100;
	   	y2=fpart1%100;
	   	y3=y2/10;
	   	y4=y2%10;
	   	y5=ipart/1000;
	   	y6=ipart%1000;
	   	y7=y6/100;
	    y8=y6%100;
	    y9=y8/10;
	    y10=y8%10;
	    UART1_Sendchar(y5+'0');
	   	UART1_Sendchar(y7+'0');
	   	UART1_Sendchar(y9+'0');
	   	UART1_Sendchar(y10+'0');
	   	UART1_Sendchar('.');
	   	UART1_Sendchar(y1+'0');
	   	UART1_Sendchar(y3+'0');
	   	UART1_Sendchar(y4+'0');

	   	UART1_Sendchar(' ');
	   	UART1_Sendchar(' ');
	   	UART1_Sendchar(' ');
	   	UART1_Sendchar(' ');
	}

int get_arraylength(int array[100])
{
	int i,length=0;
	for (i=0;i<100;i++)
	{
		if(array[i]!=0) length++;
	}
	return(length);
}
