/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

//Microcontroller MIPs (FCY)
//uses 6.144 MHz pixel clock for CLKIN (with x4 PLL)
#define _XTAL_FREQ      24576000
#define SYS_FREQ        24576000L
#define FCY             SYS_FREQ/4

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

void SYSTEM_Initialize(void);
uint16_t TMR0_ReadTimer(void);
void TMR0_WriteTimer(uint16_t timerVal);
