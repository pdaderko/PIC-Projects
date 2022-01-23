/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define _XTAL_FREQ      32000000L
#define SYS_FREQ        32000000L
#define FCY             SYS_FREQ/4

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

void SYSTEM_Initialize(void);
void PIN_Initialize (void);
void OSCILLATOR_Initialize(void);
