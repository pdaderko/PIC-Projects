#include <xc.h>         /* XC8 General Include File */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"
#include "eusart.h"
#include "interrupt_manager.h"

void SYSTEM_Initialize(void)
{
    PIN_Initialize();
    OSCILLATOR_Initialize();
    EUSART_Initialize();
    
    //enable interrupts
    INTERRUPT_PeripheralInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();
}

void PIN_Initialize(void)
{
    //all inputs (EUSART will handle Tx output)
    LATA = 0x00;
    LATC = 0x00;
    TRISA = 0x3F;
    TRISC = 0x3F;
    
    //all digital pins
    ANSELA = 0x00;
    ANSELC = 0x00;
    
    //all pullups enabled
    WPUA = 0x3F;
    WPUC = 0x3F;
    OPTION_REGbits.nWPUEN = 1;
}

void OSCILLATOR_Initialize(void)
{
    //config for 32 MHz
    OSCCONbits.SCS = 0b00; //INTOSC
    OSCCONbits.IRCF = 0b1110; //8MHz
    OSCCONbits.SPLLEN = 0b1; //4x PLL
}


