/* 
 * File:   i2c.h
 * Author: Nurul Syuhada @ Cytron Technologies Sdn. Bhd.
 *
 * Created on July 3, 2015, 1:41 PM
*/
#ifndef _I2C_H
#define _I2C_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Define i2c pins
#define SDA			RC4				// Data pin for i2c
#define SCK			RC3				// Clock pin for i2c
#define SDA_DIR		TRISC4			// Data pin direction
#define SCK_DIR		TRISC3			// Clock pin direction

// Define i2c speed
#define I2C_SPEED	100				// kbps

#define _XTAL_FREQ 20000000

 
//Function Declarations
void InitI2C(void);
unsigned char b_i2c_check_error_flag(void);
void I2C_Start(void);
void I2C_ReStart(void);
void I2C_Stop(void);
void I2C_Send_ACK(void);
void I2C_Send_NACK(void);
void I2C_Write_Byte(unsigned char);
unsigned char I2C_Read_Byte(void);

#endif



