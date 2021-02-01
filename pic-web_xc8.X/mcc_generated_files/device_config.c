/**
  @Generated PIC10 / PIC12 / PIC16 / PIC18 MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the device_config.c file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F67J60
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above or later
        MPLAB             :  MPLAB X 5.45
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

// Configuration bits: selected in the GUI

// CONFIG1L
#pragma config WDT = OFF    // Watchdog Timer Enable bit->WDT disabled (control is placed on SWDTEN bit)
#pragma config STVR = ON    // Stack Overflow/Underflow Reset Enable bit->Reset on stack overflow/underflow enabled
#pragma config XINST = OFF    // Extended Instruction Set Enable bit->Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
#pragma config DEBUG = OFF    // Background Debugger Enable bit->Background debugger disabled; RB6 and RB7 configured as general purpose I/O pins

// CONFIG1H
#pragma config CP0 = OFF    // Code Protection bit->Program memory is not code-protected

// CONFIG2L
#pragma config FOSC = HSPLL    // Oscillator Selection bits->HS oscillator, PLL enabled and under software control
#pragma config FOSC2 = ON    // Default/Reset System Clock Select bit->Clock selected by FOSC1:FOSC0 as system clock is enabled when OSCCON<1:0> = 00
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor enabled
#pragma config IESO = ON    // Two-Speed Start-up (Internal/External Oscillator Switchover) Control bit->Two-Speed Start-up enabled

// CONFIG2H
#pragma config WDTPS = 32768    // Watchdog Timer Postscaler Select bits->1:32768

// CONFIG3H
#pragma config ETHLED = ON    // Ethernet LED Enable bit->RA0/RA1 are multiplexed with LEDA/LEDB when Ethernet module is enabled and function as I/O when Ethernet is disabled
