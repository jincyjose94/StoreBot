/*
 * lsm303.h
 *
 *  Created on: 07-Feb-2018
 *      Author: jincy
 */

#ifndef LSM303_H_
#define LSM303_H_

//magnetometer registers
#define MAGNETOMETER_ADDR   0x3C
#define CRA_REG_M           0x00
#define CRB_REG_M           0x01
#define MR_REG_M            0x02
#define OUT_X_H_M           0x03
#define OUT_X_L_M           0x04
#define OUT_Z_H_M           0x05
#define OUT_Z_L_M           0x06
#define OUT_Y_H_M           0x07
#define OUT_Y_L_M           0x08

//accelerometer registers
#define ACCELEROMETER_ADDR  0x32
#define CTRL_REG1_A         0x20
#define CTRL_REG2_A         0x21
#define CTRL_REG3_A         0x22
#define CTRL_REG4_A			0x23
#define CTRL_REG5_A			0x24
#define CTRL_REG6_A			0x25
#define STATUS_REG_A		0x27
#define OUT_X_L_A           0x28
#define OUT_X_H_A           0x29
#define OUT_Y_L_A           0x2A
#define OUT_Y_H_A           0x2B
#define OUT_Z_L_A           0x2C
#define OUT_Z_H_A           0x2D
#define FIFO_CTRL_REG_A     0x2E
#define INT1_CFG_A 		    0x30
#define INT1_SRC_A 		    0x31
#define INT1_THS_A 		    0x32
#define INT1_DURATION_A 	0x33
#define INT2_CFG_A 		    0x34
#define INT2_SRC_A 		    0x35
#define INT2_THS_A 		    0x36
#define INT2_DURATION_A		0x37
#define CLICK_CFG_A 		0x38
#define CLICK_SRC_A 		0x39
#define	CLICK_THS_A			0x3A
#define	TIME_LIMIT_A		0x3B
#define	TIME_LATENCY_A		0x3C
#define	TIME_WINDOW_A		0x3D


//for obstacle detetcion
#if 0
//fab lab initialization
#define x_increase 204
#define x_decrease 290
#define y_increase 254
#define y_decrease 326
#endif
#define x_increase 204
#define x_decrease 290
#define y_increase 254
#define y_decrease 326
#define obst_y_dimension 5
#define obst_x_dimension 5
#define ultra_front_border 31
#define ultra_left_border 31
#define ultra_right_border 31
/*#define M_X_MIN
#define M_X_MIN
#define M_X_MIN
#define M_X_MIN*/

#endif /* LSM303_H_ */
