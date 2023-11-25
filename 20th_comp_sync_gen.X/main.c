//Composite sync generator for Namco Ms. Pac Man / Galaga 20 Year Reunion PCB
//by Pat Daderko (DogP)

//Video output pins on these boards seem to take abuse, commonly having blown video drivers and output resistors
//Composite sync is generated in CPLD at U11 and outputs directly to JAMMA pin (no resistor or extra buffer)
//A blown sync output pin makes the game unusable, and U11 has no dump and the part is obsolete
//This project uses an 8-pin PIC16F15313 to recreate the composite sync from a 6.144 MHz pixel clock and 60 Hz VSYNC pin available on the board

//Connections:
//RA5: 6.144 MHz pixel clock input
//RA2: ~60 Hz vertical sync input
//RA4: Generated composite sync output


/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>            // XC8 General Include File
#include <stdint.h>        // For uint8_t definition

#include "system.h"        // System funct/params, like osc/peripheral config


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern uint8_t vsync_act;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
  //do system initialization
  SYSTEM_Initialize();

  //main loop only handles VSYNC timing
  while(1)
  {
    if (vsync_act == 1) //VSYNC interrupt occurred
    {
      while (TMR0_ReadTimer() < 0x1800); //wait for 1 ms after VSYNC
      //hold CSYNC low for VSYNC
      RA4PPS = 0x00; //RA4->GPIO (output latch already set to 0)
      while (TMR0_ReadTimer() < 0x2385); //hold until 1.480 ms after VSYNC (480 us pulse)
      //go back to HSYNC pulses
      RA4PPS = 0x0B; //RA4->PWM3:PWM3OUT;

      vsync_act = 0; //done with VSYNC handling
    }
    CLRWDT(); //clear watchdog
  }
}

