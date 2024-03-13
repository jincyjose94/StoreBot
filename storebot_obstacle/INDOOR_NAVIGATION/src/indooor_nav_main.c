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
#include "i2c.h"
#include "lsm303.h"
#include "string.h"
#include "math.h"


// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;


#define I2C_PORT_USED 1

//uint8_t  j,i;
int x_loc[100]={0}, y_loc[100]={0};
int breadth=5;
int xy_global[2]={0};
int main(void)
{
	UART1_Init(9600);
	int x_max,y_max;
	int loop=0,ob_loc=0;
    int i,pulses,c=0;
   // int a[20]={1,2,3,4,5,6,7,8,9,10,11,12,13};
   // int b[20];
    double acc_x[2]={0,0};
    double vel_x[2]={0,0};
    double disp_x[2]={0,0};
    int countx=12;
    float deltaTime=1;
    int xy[2]={0,0};
    int *p;
    uint32_t ultrafront, ultraleft, ultraright;
    //int count1,count2, count3, xy_temp_1, xy_temp_2, 2xy_temp_3, axis, area_finding,x_i,y_i;
    char ch;
    uint32_t ultraf,ultrar,ultral,ultra_rl;
    uint32_t front_obst=200;
    uint32_t right_obst=200;
    int r_l,not_r_l,r=0,l=1;
    uint32_t side=220;
    char flag=0;
    uint32_t zero=0;
    SystemInit();
	port_init();
	ultra_init();
	hc020k_init();
    I2C1Init(0);     // Initialize I2C
    I2CStart(I2C_PORT_USED);
    I2CEngine( I2C_PORT_USED );
	LSM303_init ();
	motor_init();
	roboticarm_init();
	int count1=0, traverse_i=0;
	int w1,w2;
	int x_length=0,y_length=0;
	int x_loc_i=0,y_loc_i=0;
	//volatile int dist_travelled_old;
	int distance_travelled_new=0, distance_travelled_old=0, dist_travelled=0;
	int turn_direction[100]={0};
	//float check_zero_acc = motion_check()+0.045;
	// if(UART1_Getchar()=='A')
    while(1)
    {
    	UART1_Init(9600);
		//ultra_init();
    	//hc020k_init();
    	I2CEngine( I2C_PORT_USED );  // Communicate with I2c
		LSM303_init ();
		print_string("starting:");

		//print_string("check_zero_acc:");
		//disp_acc(check_zero_acc);
		//read values
/*	print_string("ANGLE:");
		print_dec_no_in_ascii(magnetometer_reading());
		//int angle=magnetometer_reading();
		//print_dec_no_in_ascii(angle);
		print_string("Acc:");
		acc_x[1]=callibrate_acc();
	    if ((acc_x[1] <=2)&&(acc_x[1] >= -2)) //Discrimination window applied to the X axis acceleration
	      	  	 {acc_x[1] = 0;}
		if (((acc_x[1]<=check_zero_acc)&&(acc_x[1]>=0))||(acc_x[1]>=(-check_zero_acc)&&(acc_x[1]<=0)))  //we count the number of acceleration samples that equals zero
			     { countx++;}
		else { countx =0;}

		if (countx>=4)          //if this number exceeds 25, we can assume that velocity is cero
					 {
					 vel_x[1]=0;
					 vel_x[0]=0;
					 }
		else
		vel_x[1]= vel_x[0]+ ((acc_x[1] +acc_x[0])/2);//first integration
		disp_x[1]= disp_x[0] + ((vel_x[1] + vel_x[0])/2);//second integration
			print_string("Acc1:");
			disp_acc(acc_x[1]);
			print_string("Acc0:");
			disp_acc(acc_x[0]);
			print_string("vel1:");
			disp_acc(vel_x[1]);
			print_string("vel0:");
			disp_acc(vel_x[0]);
			print_string("disp1:");
			disp_acc(disp_x[1]);
			print_string("disp0:");
			disp_acc(disp_x[0]);
			print_string("countx:");
			disp_acc(countx);
	    acc_x[0] = acc_x[1];  //The current acceleration value must be sent to the previous acceleration
	    vel_x[0] = vel_x[1];          //Same done for the velocity variable
	    disp_x[0] = disp_x[1]; */

		delay_ms_motor(10);

		ultraf=ultrasonic_front();
		ultral=ultrasonic_left();
		ultrar=ultrasonic_right();
#if 0
left();
stop();
stop();
stop();
#endif

#if 0
		print_string("front_before_loop:");
		print_dec_no_in_ascii(ultraf);
		print_string("left_b4_loop:");
		print_dec_no_in_ascii(ultral);
		print_string("right_b4_loop:");
		print_dec_no_in_ascii(ultrar);
#endif
/*if(loop==0)
{
	stop();
}*/
 		if (ultraf>=front_obst)  //FWD MOTION
		{
 			dist_travelled=front();
			distance_travelled_new=dist_travelled-distance_travelled_old;
			if((traverse_i==0)||((traverse_i%2)==0))
			{
			print_string("traverse_i=0: \n");
			print_string("traverse_i:");
			print_dec_no_in_ascii(traverse_i);

			xy_global[0]=xy_global[0]+distance_travelled_new;
			x_max=breadth;
			}
			else if((traverse_i%2)==1)
			{
			print_string("\n traverse_i=1:");
			print_string("traverse_i=0:");
			print_dec_no_in_ascii(traverse_i);

			xy_global[0]=xy_global[0]-distance_travelled_new;
			x_max=0;
			}
			distance_travelled_old=dist_travelled;
#if 0
			//checking

			print_string("front_before:");
			print_dec_no_in_ascii(ultraf);
			print_string("left:");
			print_dec_no_in_ascii(ultral);
			print_string("right:");
			print_dec_no_in_ascii(ultrar);
#endif
			print_string("xy[0]:");
			print_dec_no_in_ascii(xy_global[0]);
			print_string("xy[1]:");
			print_dec_no_in_ascii(xy_global[1]);
			print_string("\n");

//#endif
		}
		//else stop();


		else
		{
			if(ultraf<=front_obst)
			{
				stop();

//#if 0
				print_string("front_in_stop:");
				print_dec_no_in_ascii(ultraf);
//#endif
				if(traverse_i==0)
				{
					if(ultrar>=ultral)
					{
						r_l=r; //in r_l, (r=0;means turn right)
					}
					else if(ultral>=ultrar)
					{
						r_l=l;//r_l=l means turn left;l=1;i
					}
					turn_direction[traverse_i]=r_l;
					print_string("r_l:");
					print_dec_no_in_ascii(r_l);

				}
				else
				{
					turn_direction[traverse_i]=r_l;
					r_l=!(turn_direction[traverse_i-1]);
				}
				not_r_l=!r_l;

				x_loc[ob_loc]=xy_global[0];
				y_loc[ob_loc]=xy_global[1];
				ob_loc++;

				robot_turn(r_l);    //FIRST TURN OF 4
				print_string("first turn excecuted:");
			}



				ultraf=ultrasonic_front();
				ultra_rl=ultra_leftright_check(not_r_l);

#if 0
				/**checking **/
				print_string("\n");

				print_string("front_after1:");
				print_dec_no_in_ascii(ultraf);
				print_string("ultra_rl_after1:");
				print_dec_no_in_ascii(ultra_rl);
				/**checking**/
#endif

				//while((ultraf>=front_obst)&&(ultra_rl<=right_obst))
				while((xy_global[0]<=(x_max-5))&&(ultra_rl<=right_obst))
				{
		 			dist_travelled=front();
					distance_travelled_new=dist_travelled-distance_travelled_old;
					xy_global[1]=xy_global[1]+distance_travelled_new;
					distance_travelled_old=dist_travelled;

					ultraf=ultrasonic_front();
					ultra_rl=ultra_leftright_check(not_r_l);
					print_string("front after first turn:");
					print_string("\n");

#if 0
					/**checking **/
					print_string("front_after1inloop:");
					print_dec_no_in_ascii(ultraf);
					print_string("ultra_rl_after1inloop:");
					print_dec_no_in_ascii(ultra_rl);
					print_string("\n");
					/**checking**/
#endif

					//if((xy_global[1]>=(y_max-5))||(ultra_rl>=right_obst))  //extra added here
					if((ultra_rl>=right_obst))  //extra added here
					break;
					else continue;
				}

				//if((ultraf<=front_obst)||(ultra_rl>=right_obst))
				if((xy_global[0]<=(x_max-5))&&(ultra_rl>=right_obst))
				{
					stop();
					x_loc[ob_loc]=xy_global[0];
					y_loc[ob_loc]=xy_global[1];
					ob_loc++;

						robot_turn(not_r_l);   //2ND TURN OF 4
						print_string("2nd turn excecuted:");

						//print_string("2nd_turn_executed");
						ultraf=ultrasonic_front();
						ultra_rl=ultra_leftright_check(not_r_l);
#if 0
						/**checking **/
						print_string("front_after2:");
						print_dec_no_in_ascii(ultraf);
						print_string("ultra_rl_after2:");
						print_dec_no_in_ascii(ultra_rl);
						print_string("\n");

						/**checking**/
#endif
						while((ultraf>=front_obst)&&(ultra_rl<=right_obst))
						{
							print_string("while after 2nd turn");
							print_string("\n");

				 			dist_travelled=front();
							distance_travelled_new=dist_travelled-distance_travelled_old;
							if((traverse_i==0)||((traverse_i%2)==0))
							xy_global[0]=xy_global[0]+distance_travelled_new;
							else if((traverse_i%2)==1)
							xy_global[0]=xy_global[0]-distance_travelled_new;
							distance_travelled_old=dist_travelled;
							ultraf=ultrasonic_front();
							ultra_rl=ultra_leftright_check(not_r_l);
							if((ultraf<=front_obst)||(ultra_rl>=right_obst)) //extra 3 lines
							break;
							else continue;
						}
						if(ultra_rl>=right_obst)
						{
							stop();

							x_loc[ob_loc]=xy_global[0];
							y_loc[ob_loc]=xy_global[1];
							ob_loc++;

							robot_turn(not_r_l);   //3RD TURN OF 4
							print_string("3rdturn_executed");
							ultraf=ultrasonic_front();//..
							ultra_rl=ultra_leftright_check(not_r_l);

#if 0
							print_string("front_after3:");
							print_dec_no_in_ascii(ultraf);
							print_string("ultra_rl_after3:");
							print_dec_no_in_ascii(ultra_rl);
							print_string("\n");
#endif

							while((ultraf>=front_obst)&&(ultra_rl<=right_obst))
							{
#if 0
								print_string("front_after2 in loop:");
								print_dec_no_in_ascii(ultraf);
								print_string("ultra_rl_after2 in loop:");
								print_dec_no_in_ascii(ultra_rl);
#endif

								print_string("while after 3rd turn:");
								print_string("\n");

					 			dist_travelled=front();
								distance_travelled_new=dist_travelled-distance_travelled_old;
								xy_global[1]=xy_global[1]-distance_travelled_new;
								distance_travelled_old=dist_travelled;
								ultraf=ultrasonic_front();
								ultra_rl=ultra_leftright_check(not_r_l);
								if((ultraf<=front_obst)||(ultra_rl>=right_obst))  //extra 3 lines
								break;
								else continue;
							}
							if((ultraf<=front_obst)||(ultra_rl>=right_obst))
							{
								stop();
								x_loc[ob_loc]=xy_global[0];
								y_loc[ob_loc]=xy_global[1];
								ob_loc++;

								robot_turn(r_l);    //LAST TURN OF 4
								print_string("4thturn_executed");
							}

						}
					}
				if(xy_global[0]>=(x_max))
				{
						print_string("corner_reached");
						//continue; //not obstacle; corner confirmed
						traverse_i++;
					robot_turn(r_l);    //AFTER CORNER DETECTED, TURN AT CORNER
					print_string("cornerturn_executed");
		 			dist_travelled=front();
					distance_travelled_new=dist_travelled-distance_travelled_old;
					xy_global[1]=xy_global[1]+distance_travelled_new;
					distance_travelled_old=dist_travelled;
					delay_ms_motor(2500);
					robot_turn(r_l);    //AFTER CORNER DETECTED, 2nd TURN AT CORNER
				}
			}
loop++;
x_length=get_arraylength(x_loc);
y_length=get_arraylength(y_loc);
print_string("\n x_length ");
print_dec_no_in_ascii(x_length);

print_string(" \n y_length ");
print_dec_no_in_ascii(y_length);

print_string("x_loc: ");

for(x_loc_i=0;x_loc_i<x_length;x_loc_i++)
{
	print_dec_no_in_ascii(x_loc[x_loc_i]);
	print_string(", ");
}
print_string("\n");
print_string("y_loc: ");

for(y_loc_i=0;y_loc_i<x_length;y_loc_i++)
{
	print_dec_no_in_ascii(y_loc[y_loc_i]);
	print_string(", ");
}
	/*	print_string("front:");
		print_dec_no_in_ascii(ultraf);
		print_string("left:");
		print_dec_no_in_ascii(ultral);
		print_string("right:");
		print_dec_no_in_ascii(ultrar);
	/*	pulses = speed_encoder_start();

    	    	print_string("count:");
    	    	print_dec_no_in_ascii(pulses);*/

	/*	ch=UART1_Getchar();
		switch(ch)
		{
		case 'F' :front();
					break;
					//OBSTACLE LOCATION FINDING
		case 'L' :left();break;
		case 'R' :right();break;
		case 'S': stop();break;
					}
*/
		//front();
		//right();




			//dist_travelled=front();

  	UART1_Sendchar('\n');
}

}
