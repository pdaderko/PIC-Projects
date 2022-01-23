#ifndef EUSART_H
#define EUSART_H


#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif


#define EUSART_DataReady  (EUSART_is_rx_ready())


typedef union {
    struct {
        unsigned perr : 1;
        unsigned ferr : 1;
        unsigned oerr : 1;
        unsigned reserved : 5;
    };
    uint8_t status;
}eusart_status_t;


extern volatile uint8_t eusartTxBufferRemaining;
extern volatile uint8_t eusartRxCount;


extern void (*EUSART_TxDefaultInterruptHandler)(void);
extern void (*EUSART_RxDefaultInterruptHandler)(void);


//EUSART Initialization routine
void EUSART_Initialize(void);

//Checks if the EUSART transmitter is ready to transmit data
bool EUSART_is_tx_ready(void);

//Checks if the EUSART receiver ready for reading
bool EUSART_is_rx_ready(void);

//Checks if EUSART data is transmitted
bool EUSART_is_tx_done(void);

//Gets the error status of the last read byte.
eusart_status_t EUSART_get_last_status(void);

//Read a byte of data from the EUSART.
uint8_t EUSART_Read(void);

//Writes a byte of data to the EUSART.
void EUSART_Write(uint8_t txData);

//Maintains the driver's transmitter state machine and implements its ISR.
void EUSART_Transmit_ISR(void);

//Maintains the driver's receiver state machine and implements its ISR
void EUSART_Receive_ISR(void);

//Maintains the driver's receiver state machine
void EUSART_RxDataHandler(void);

//Set EUSART Framing Error Handler
void EUSART_SetFramingErrorHandler(void (* interruptHandler)(void));

//Set EUSART Overrun Error Handler
void EUSART_SetOverrunErrorHandler(void (* interruptHandler)(void));

//Set EUSART Error Handler
void EUSART_SetErrorHandler(void (* interruptHandler)(void));

//Sets the transmit handler function to be called by the interrupt service
void EUSART_SetTxInterruptHandler(void (* interruptHandler)(void));

//Sets the receive handler function to be called by the interrupt service
void EUSART_SetRxInterruptHandler(void (* interruptHandler)(void));

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // EUSART_H
