#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

#include <xc.h>

//This macro will enable global interrupts.
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)

//This macro will disable global interrupts.
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

//This macro will enable peripheral interrupts.
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)

//This macro will disable peripheral interrupts.
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)


#endif  // INTERRUPT_MANAGER_H
