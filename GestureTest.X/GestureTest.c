/* 
 * File       : GestureTest.c
 * Author     : Nurul Syuhada @Cytron Technologies Sdn. Bhd.
 * Description: This sample code is for Gesture sensor(APDS-9960). This sample code is to
 *              detect the motion of the hand gesture/ swiping will be display on LCD. 
 *              This sample code is by using PIC16F877A.
 *              Compatible with MPLABX IDE with XC8 C compiler
 * Created on July 21, 2015, 1:51 PM 
 */


#include  <xc.h>       //Define PIC Registers 
#include  <stdio.h>
#include  <stdbool.h>
#include "lcd.h"
#include "i2c.h"
#include "APDS9960.h"


#pragma config FOSC = HS      // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF     // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF    // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF    // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF      // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming disabled)
#pragma config CPD = OFF      // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF      // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF       // Flash Program Memory Code Protection bit (Code protection off)                  
                              
unsigned int id;
int t;
bool handleGestureFlag = 0;

void handleGesture();
void DelayMs(unsigned int Ms);

void interrupt isr()
{
  if (INTF)
  {
    INTE = 0;
    handleGestureFlag = 1;
    INTF = 0;
    INTE = 1;
  }
}

int main(void)
{
  //clear port
  PORTA = 0;
  PORTB = 0;
  PORTC = 0;
  PORTD = 0;
  PORTE = 0;

  TRISA = 0;
  TRISB = 0b00000001; //RB0 as input(interrupt)
  TRISC = 0b00011000; //RC3 and RC4 as input (I2C communication)
  TRISD = 0;
  TRISE = 0;

  // Initialize interrupt service routine
  
  INTF = 0; // Reset the external interrupt flag
  INTE = 1; // Enable external interrupts from
  PEIE = 1;// Enable peripheral interrupt
  GIE = 1; // Global interrupt enable
  OPTION_REG = 0; // Enable Internal Pull-ups and Interrupt on falling edge

  DelayMs(20);
  lcd_initialize();

  lcd_goto(0x42);
  lcd_putstr("gesture test");
  __delay_ms(1000);

  if (initialize())
  {
    lcd_clear();
    lcd_home();
    lcd_putstr("Initialize");
    __delay_ms(1000);

  }
  else
  {
    lcd_clear();
    lcd_home();
    lcd_putstr("Error");
    __delay_ms(1000);

  }
  
  if (enableGestureSensor(true))
  {
    lcd_clear();
    lcd_home();
    lcd_putstr("enable sensor");
    __delay_ms(1000);
  }
  else
  {
    lcd_clear();
    lcd_home();
    lcd_putstr("st wrong");
    __delay_ms(1000);
  }

  while (1)
  {
    if(handleGestureFlag)
    {
      
      handleGestureFlag = 0;
      handleGesture();  
      
    }
     
  }

}

void handleGesture()
{
  if (isGestureAvailable())
  {
    switch (readGesture())
    {
      case DIR_UP:
        lcd_clear();
        lcd_home();
        lcd_putstr("up");
        __delay_ms(1000);
        break;
      case DIR_DOWN:
        lcd_clear();
        lcd_home();
        lcd_putstr("down");
        __delay_ms(1000);
        break;
      case DIR_LEFT:
        lcd_clear();
        lcd_home();
        lcd_putstr("left");
        __delay_ms(1000);
        break;
      case DIR_RIGHT:
        lcd_clear();
        lcd_home();
        lcd_putstr("right");
        __delay_ms(1000);
        break;
      case DIR_NEAR:
        lcd_clear();
        lcd_home();
        lcd_putstr("near");
        __delay_ms(1000);
        break;
      case DIR_FAR:
        lcd_clear();
        lcd_home();
        lcd_putstr("far");
        __delay_ms(1000);
        break;
      default:
        lcd_clear();
        lcd_home();
        lcd_putstr("NONE");
        __delay_ms(1000);
    }
    lcd_clear();
  }
}

void DelayMs(unsigned int Ms)
{
  int delay_cnst;
  while (Ms > 0)
  {
    Ms--;
    for (delay_cnst = 0; delay_cnst < 220; delay_cnst++);
  }
}
