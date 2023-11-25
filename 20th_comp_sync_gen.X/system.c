/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>            // XC8 General Include File
#include <stdint.h>        // For uint8_t definition

#include "system.h"

/******************************************************************************/
/* System Functions                                                           */
/******************************************************************************/

void PMD_Initialize(void)
{
  //CLKRMD CLKR enabled; SYSCMD SYSCLK enabled; FVRMD FVR enabled; IOCMD IOC enabled; NVMMD NVM enabled;
  PMD0 = 0x00;

  //TMR0MD TMR0 enabled; TMR1MD TMR1 enabled; TMR2MD TMR2 enabled; NCOMD DDS(NCO) enabled;
  PMD1 = 0x00;

  //ZCDMD ZCD enabled; CMP1MD CMP1 enabled; ADCMD ADC enabled; DAC1MD DAC1 enabled;
  PMD2 = 0x00;

  //CCP2MD CCP2 enabled; CCP1MD CCP1 enabled; PWM4MD PWM4 enabled; PWM3MD PWM3 enabled; PWM6MD PWM6 enabled; PWM5MD PWM5 enabled;
  PMD3 = 0x00;

  //CWG1MD CWG1 enabled; MSSP1MD MSSP1 enabled; UART1MD EUSART enabled;
  PMD4 = 0x00;

  //CLC3MD CLC3 enabled; CLC4MD CLC4 enabled; CLC1MD CLC1 enabled; CLC2MD CLC2 enabled;
  PMD5 = 0x00;
}


void PIN_Initialize(void)
{
  //LATx registers
  LATA = 0x00;

  //TRISx registers
  TRISA = 0x27;

  //ANSELx registers
  ANSELA = 0x00;

  //WPUx registers
  WPUA = 0x3F;

  //ODx registers
  ODCONA = 0x00;

  //SLRCONx registers
  SLRCONA = 0x37;

  //INLVLx registers
  INLVLA = 0x3F;

  //IOCx registers
  //interrupt on change for group IOCAF - flag
  IOCAFbits.IOCAF2 = 0;
  //interrupt on change for group IOCAN - negative
  IOCANbits.IOCAN2 = 0;
  //interrupt on change for group IOCAP - positive
  IOCAPbits.IOCAP2 = 1;

  //Enable IOCI interrupt
  PIE0bits.IOCIE = 1;

  RA4PPS = 0x0B;   //RA4->PWM3:PWM3OUT;
}


void OSCILLATOR_Initialize(void)
{
  //NOSC EXTOSC   with 4x PLL; NDIV 1;
  OSCCON1 = 0x20;

  //CSWHOLD may proceed;
  OSCCON3 = 0x00;

  //MFOEN disabled; LFOEN disabled; ADOEN disabled; EXTOEN disabled; HFOEN disabled;
  OSCEN = 0x00;

  //HFFRQ 4_MHz;
  OSCFRQ = 0x02;

  //MFOR not ready;
  OSCSTAT = 0x00;

  //HFTUN 0;
  OSCTUNE = 0x00;

  //wait for PLL to stabilize
  while(PLLR == 0);
}


void PWM3_Initialize(void)
{
  //PWM3POL active_lo; PWM3EN enabled;
  PWM3CON = 0x90;

  //DC 12;
  PWM3DCH = 0x0C;

  //DC 0;
  PWM3DCL = 0x00;
}


void TMR2_Initialize(void)
{
  //T2CS FOSC/4;
  T2CLKCON = 0x01;

  //T2PSYNC Not Synchronized; T2MODE Software control; T2CKPOL Rising Edge; T2CKSYNC Not Synchronized;
  T2HLT = 0x00;

  //T2RSEL T2INPPS pin;
  T2RST = 0x00;

  //T2PR 191;
  T2PR = 0xBF;

  //TMR2 0;
  T2TMR = 0x00;

  //Clear IF flag
  PIR4bits.TMR2IF = 0;

  //T2CKPS 1:2; T2OUTPS 1:1; TMR2ON on;
  T2CON = 0x90;
}


void TMR0_Initialize(void)
{
  //T0CS FOSC/4; T0CKPS 1:1; T0ASYNC synchronized;
  T0CON1 = 0x40;

  //TMR0H 0;
  TMR0H = 0x00;

  //TMR0L 0;
  TMR0L = 0x00;

  //Clear IF flag
  PIR0bits.TMR0IF = 0;

  //T0OUTPS 1:1; T0EN enabled; T016BIT 16-bit;
  T0CON0 = 0x90;
}

//read the 16-bit Timer0 register
uint16_t TMR0_ReadTimer(void)
{
  uint8_t readValLow;
  uint8_t readValHigh;

  readValLow  = TMR0L;
  readValHigh = TMR0H; //must read TMR0H after TMR0L
  return ((uint16_t)readValHigh << 8) | readValLow;
}

//write to the 16-bit Timer0 register
void TMR0_WriteTimer(uint16_t timerVal)
{
  TMR0H = timerVal >> 8; //must write TMR0H before TMR0L
  TMR0L = (uint8_t) timerVal;
}


void SYSTEM_Initialize(void)
{
  //initialize system
  PMD_Initialize();
  PIN_Initialize();
  OSCILLATOR_Initialize();
  PWM3_Initialize();
  TMR2_Initialize();
  TMR0_Initialize();

  //enable interrupts
  INTCONbits.PEIE = 1;
  INTCONbits.GIE = 1;
}
