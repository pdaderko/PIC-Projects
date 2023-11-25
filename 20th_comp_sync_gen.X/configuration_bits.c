// PIC16F15313 Configuration Bit Settings

// CONFIG1
#pragma config FEXTOSC = ECM    // External Oscillator mode selection bits->EC for 500kHz to 8MHz; PFM set to medium power
#pragma config RSTOSC = EXT4X    // Power-up default value for COSC bits->EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; i/o or oscillator function on OSC2
#pragma config CSWEN = OFF    // Clock Switch Enable bit->The NOSC and NDIV bits cannot be changed by user software
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable bit->FSCM timer disabled

// CONFIG2
#pragma config MCLRE = ON    // Master Clear Enable bit->MCLR pin is Master Clear function
#pragma config PWRTE = OFF    // Power-up Timer Enable bit->PWRT disabled
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit->ULPBOR disabled
#pragma config BOREN = ON    // Brown-out reset enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = LO    // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices
#pragma config ZCD = OFF    // Zero-cross detect disable->Zero-cross detect circuit is disabled at POR.
#pragma config PPS1WAY = ON    // Peripheral Pin Select one-way control->The PPSLOCK bit can be cleared and set only once in software
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG3
#pragma config WDTCPS = WDTCPS_11    // WDT Period Select bits->Divider ratio 1:65536
#pragma config WDTE = ON    // WDT operating mode->WDT enabled regardless of sleep; SWDTEN ignored
#pragma config WDTCWS = WDTCWS_6    // WDT Window Select bits->window always open (100%); no software control; keyed access required
#pragma config WDTCCS = LFINTOSC    // WDT input clock selector->WDT reference clock is the 31.0kHz LFINTOSC output

// CONFIG4
#pragma config BBSIZE = BB512    // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF    // Boot Block Enable bit->Boot Block disabled
#pragma config SAFEN = OFF    // SAF Enable bit->SAF disabled
#pragma config WRTAPP = OFF    // Application Block Write Protection bit->Application Block not write protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block not write protected
#pragma config WRTC = OFF    // Configuration Register Write Protection bit->Configuration Register not write protected
#pragma config WRTSAF = OFF    // Storage Area Flash Write Protection bit->SAF not write protected
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.

// CONFIG5
#pragma config CP = OFF    // UserNVM Program memory code protection bit->UserNVM code protection disabled

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
