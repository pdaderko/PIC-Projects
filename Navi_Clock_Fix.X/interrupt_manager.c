#include "interrupt_manager.h"
#include "eusart.h"

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(INTCONbits.PEIE == 1)
    {
        if(PIE1bits.TXIE == 1 && PIR1bits.TXIF == 1)
        {
            EUSART_TxDefaultInterruptHandler();
        } 
        else if(PIE1bits.RCIE == 1 && PIR1bits.RCIF == 1)
        {
            EUSART_RxDefaultInterruptHandler();
        } 
        else
        {
            //Unhandled Interrupt
        }
    }      
    else
    {
        //Unhandled Interrupt
    }
}
