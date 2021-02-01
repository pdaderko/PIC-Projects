#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "tcp_server_demo.h"
#include "mcc_generated_files/TCPIPLibrary/tcpv4.h"
#include "mcc_generated_files/TCPIPLibrary/ipv4.h"
#include "mcc_generated_files/TCPIPLibrary/tcpip_config.h"

//Implement an echo server over TCP
void DEMO_TCP_EchoServer(void)
{
    // create the socket for the TCP Server
    static tcpTCB_t port7TCB;

    // create the TX and RX Server's buffers
    static uint8_t rxdataPort7[20];
    static uint8_t txdataPort7[20];

    uint16_t rxLen, txLen, i;
    socketState_t socket_state;

    socket_state = TCP_SocketPoll(&port7TCB);

    switch(socket_state)
    {
        case NOT_A_SOCKET:
            // Inserting and initializing the socket
            TCP_SocketInit(&port7TCB);
            break;
        case SOCKET_CLOSED:
            //configure the local port
            TCP_Bind(&port7TCB, 7);
            // add receive buffer
            TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof(rxdataPort7));
            // start the server
            TCP_Listen(&port7TCB);
            break;
        case SOCKET_CONNECTED:
            // check if the buffer was sent, if yes we can send another buffer
            if(TCP_SendDone(&port7TCB))
            {
                // check to see  if there are any received data
                rxLen = TCP_GetRxLength(&port7TCB);
                if(rxLen > 0)
                {
                    rxLen = TCP_GetReceivedData(&port7TCB);

                    //simulate some buffer processing
                    for(i = 0; i < rxLen; i++)
                    {
                        txdataPort7[i] = rxdataPort7[i];
                    }

                    // reuse the RX buffer
                    TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof(rxdataPort7));
                    txLen = rxLen;
                    //send data back to the source
                    TCP_Send(&port7TCB, txdataPort7, txLen);
                }
            }
            break;
        case SOCKET_CLOSING:
            TCP_SocketRemove(&port7TCB);
            break;
            
        default:
            // we should not end up here
            break;
    }
}
