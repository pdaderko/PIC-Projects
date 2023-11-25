/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>             // XC8 General Include File
#include <stdint.h>         // For uint8_t definition

#include "system.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

uint8_t clk_sync=0; //flag to tell interrupt whether it has synchronized HSYNC phase
uint8_t vsync_act=0; //flag to tell main loop that VSYNC is active

void __interrupt() isr(void)
{
  //IOC interrupt handler for VSYNC pin
  if ((PIE0bits.IOCIE == 1) && (PIR0bits.IOCIF == 1))
  {
    //set initial HSYNC phase at power up
    //after this, everything runs fully synchronized to pixel CLK through TMR2 and PWM3
    //could reset every VSYNC, but possibility of tiny jitter based on slight variation of interrupt timing
    if (clk_sync == 0)
    {
      T2TMR = 0x00; //sets TMR2 for HSYNC phase
      clk_sync = 1; //set flag to prevent this from running again
    }

    TMR0_WriteTimer(0x0000); //reset TMR0 for main loop to measure VSYNC delay
    vsync_act = 1; //tell main loop that VSYNC is active

    //clear interrupt on change for pin IOCAF2 (only IOC pin used, so simply clear all)
    IOCAF = 0;
  }
}
