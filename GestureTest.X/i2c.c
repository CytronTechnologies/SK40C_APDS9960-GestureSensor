/* I2C library*/

#include <xc.h>
#include "i2c.h"


// The flag to indicate whether an I2C error has occured.
unsigned char b_i2c_error_flag = 0;

// Function Purpose: Configure I2C module
void InitI2C(void)
{	
        
  SDA_DIR = 1;		// Make SDA and
	SCK_DIR = 1;		// SCK pins input
    
	SSPADD  = ((_XTAL_FREQ/4000)/I2C_SPEED) - 1;	
	SSPSTAT = 0x80;		// Slew Rate control is disabled
	SSPCON  = 0x28;		// Select and enable I2C in master mode
  
}

unsigned char b_i2c_check_error_flag(void)
{
	return b_i2c_error_flag;	
}

// Function Purpose: I2C_Start sends start bit sequence
void I2C_Start(void)
{
	SEN = 1;			// Send start bit
	while( SEN == 1);		// Wait for it to complete	
}

// Function Purpose: I2C_ReStart sends start bit sequence
void I2C_ReStart(void)
{
	RSEN = 1;			// Send Restart bit
	while(RSEN == 1);		// Wait for it to complete
}

//Function : I2C_Stop sends stop bit sequence
void I2C_Stop(void)
{
	PEN=1;      // Enable the Stop bit  
  while (PEN == 1); // waits till stob bit is enable
}

//Function : I2C_Send_ACK sends ACK bit sequence
void I2C_Send_ACK(void)
{
	ACKDT = 0;			// 0 means ACK
	ACKEN = 1;			// Send ACKDT value
	while(ACKEN == 1);		// Wait for it to complete			
}

//Function : I2C_Send_NACK sends NACK bit sequence
void I2C_Send_NACK(void)
{
	 ACKDT=1;    // Acknowledge the operation (Send NACK)    
   ACKEN=1;    // Acknowledge sequence on SDA & SCL pins  
   while (ACKEN == 1);
}

// Function Purpose: I2C_Write_Byte transfers one byte
void I2C_Write_Byte(unsigned char Byte)
{
  // Clear the error flag before we start a new I2C operation.
	b_i2c_error_flag = 0;
	SSPBUF = Byte;		// Send Byte value
	while (SSPSTATbits.R_W == 1);// Wait for slave to acknowledge.
  
	// If slave does not acknowledge...
	if (ACKSTAT == 1) {
		// Send stop bit.
		PEN = 1;
		while (PEN == 1);
		
		// Set the error flag and exit.
		b_i2c_error_flag = 1;
		return;
	}
	
}

// Function Purpose: I2C_Read_Byte reads one byte
unsigned char I2C_Read_Byte(void )
{
  RCEN=1;        // Enable to receive data    
        
    // Wait until the data is received.
	unsigned long count = 10000L;
	while (BF == 0) {
		
		// If timeout...
		if (--count == 0) {
			// Send stop bit.
			PEN = 1;
			while (PEN == 1);
			
			// Set the error flag and exit.
			b_i2c_error_flag = 1;
			return 0;
		}
	}
 
  return SSPBUF;		// Return received byte
}