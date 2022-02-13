/* 
 * GPS receivers in Acura (Honda/Alpine) navigation units have a GPS 1024 week
 * rollover issue causing January 2022 to roll back to May 2002.  In doing so,
 * this prevents the user from setting the clock due to a check in the main
 * navigation software, presumably ignoring 2002 since that's the (obviously
 * incorrect) default year when the GPS unit is powered up.
 * 
 * This PIC16 code receives binary data from the Furuno GN80 and outputs the
 * corrected (+1024 week) date.
 * 
 * The binary protocol looks to be a clone of Trimble TSIP, with Furuno's own
 * packet structures.
 * This code only modifies the 0x75 packet.  All other data passes through unmodified.
 * 
 * Connections:
 * PIC Rx on RC5 (pin 5) - Connect to GPS receiver Tx
 * PIC Tx on RC4 (pin 6) - Connect to Navigation Rx (where GPS Tx was connected)
 * 
 * Furuno GPS pinout:
 * (unable to find GN80 pinout, but found similar GT-8031 and confirmed pins where possible)
 * 1: TEST Connected to GND on motherboard
 * 2: MODE Connected to GND on motherboard through 0 ohm resistor
 * 3: Tx
 * 4: Rx
 * 5: 1PPS (appears unconnected on motherboard)
 * 6: RST_N
 * 7: VBATT (approximately +3.3V)
 * 8: GND
 * 9: VCC (+3.3V)
 * 10: VANT (+5V)
 * Mechanical pins: N/C on both sides
 * 
 * Communicates at 9600 bps with 8 data bits, odd parity, 1 stop bit
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "system.h"
#include "eusart.h"
#include "add1024weeks.h"


//convert BCD to decimal
uint8_t bcd_to_dec(uint8_t data)
{
  return (((data>>4)*10)+(data&0x0F));
}

//convert decimal to BCD
uint8_t dec_to_bcd(uint8_t data)
{
  return (uint8_t)(((data/10)<<4)|(data%10));
}

//send serial byte
void send_byte(uint8_t data)
{
  //should always have room in the buffer, but if not, just drop the byte
  if(EUSART_is_tx_ready())
  {
    EUSART_Write(data);
  }
}

void main(void)
{
  uint8_t rx_data, tmp_tx, check_xor=0, byte10=0, pktcnt=0;
  uint8_t pktid=0x03; //packet ID of 0x03 should be invalid (end of packet), so use for unknown ID
  uint8_t year, month, day;

  SYSTEM_Initialize();

  while(1)
  {
    CLRWDT(); //poke watchdog
    
    //echo bytes, except modify date in 0x75 message
    if(EUSART_is_rx_ready()) //there's one or more bytes waiting
    {
      rx_data = EUSART_Read(); //get received byte
      if (rx_data==0x10) //0x10 is special case
      {
        if (byte10==0) //first 0x10
        {
          byte10=1;
          pktcnt++; //do the ++ on first 0x10, so code below can grab this before echoing if necessary
        }
        else //consecutive 0x10, so 0x10 data
          byte10=0;
      }
      else
      {
        pktcnt++;
        if (byte10) //if previous byte was non-repeated 0x10, next byte should either be packet ID or end of packet (0x03)
        {
          pktid=rx_data;
          pktcnt=0; //clear packet data byte counter
        }
        byte10=0; //not a 0x10 byte
      }
      
      if (pktid==0x75) //packet 0x75, look through the data
      {
        if ((pktcnt==20)||(pktcnt==26)) //year (20=current, 26=last fix)
        {
          if (!byte10) //if 0x10 data, only want to do this once (check XOR doesn't include both 0x10s)
          {
            check_xor^=rx_data; //will remove this byte from check byte
            year=bcd_to_dec(rx_data); //year since 2000
          }
        }
        else if ((pktcnt==21)||(pktcnt==27)) //month (21=current, 27=last fix)
        {
          if (!byte10) //if 0x10 data, only want to do this once (check XOR doesn't include both 0x10s)
          {
            check_xor^=rx_data; //will remove this byte from check byte
            month=bcd_to_dec(rx_data); //months, 1-indexed
          }
        }
        else if ((pktcnt==22)||(pktcnt==28)) //day (22=current, 28=last fix)
        {
          if (!byte10) //if 0x10 data, only want to do this once (check XOR doesn't include both 0x10s, and don't want to send twice)
          {
            check_xor^=rx_data; //will remove this byte from check byte
            day=bcd_to_dec(rx_data); //day of the month (1-31)
            
            //fix the date
            add_1024_weeks(&year, &month, &day); // Uh

            //send replacement bytes (duplicating 0x10 if necessary)
            tmp_tx=dec_to_bcd(year); //year
            send_byte(tmp_tx);
            if (tmp_tx==0x10)
              send_byte(tmp_tx);
            check_xor^=tmp_tx; //XOR replacement byte
            
            tmp_tx=dec_to_bcd(month); //month
            send_byte(tmp_tx);
            if (tmp_tx==0x10)
              send_byte(tmp_tx);
            check_xor^=tmp_tx; //XOR replacement byte
            
            tmp_tx=dec_to_bcd(day); //day
            send_byte(tmp_tx);
            if (tmp_tx==0x10)
              send_byte(tmp_tx);
            check_xor^=tmp_tx; //XOR replacement byte
          }
        }
        else if (pktcnt==45) //fix check byte
        {
          if (!byte10) //if 0x10 data, only want to do this once
          {
            check_xor^=rx_data; //XOR replacement check with original
            tmp_tx=check_xor;
            send_byte(tmp_tx); //send fixed check byte
            if (tmp_tx==0x10) //duplicate 0x10 if necessary
              send_byte(tmp_tx);
            check_xor=0; //clear check XOR
          }
        }
        else //not one of the bytes I care about, simply echo the data
        {
          send_byte(rx_data);
        }
      }
      else //not a packet I care about, simply echo the data
      {
        send_byte(rx_data);
      }
    }
  }
}

