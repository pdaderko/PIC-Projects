## Acura Navigation Clock Fix

GPS receivers in Acura (Honda/Alpine) navigation units have a GPS 1024 week
rollover issue causing January 2022 to roll back to May 2002.  In doing so,
this prevents the user from setting the clock due to a check in the main
navigation software, presumably ignoring 2002 since that's the (obviously
incorrect) default year when the GPS unit is powered up.

This PIC16F1825 code receives binary data from the Furuno GN80 and outputs the
corrected (+1024 week) date.  This uses a signed 32-bit time_t with <time.h>
functions, so this will suffer from the 2038 date problem.

The GPS receiver is soldered to the navigation unit motherboard, and needs to be removed
in order to use this, as the PIC needs to intercept and modify the serial data.  I
connectorized the GPS receiver for convenience of reverse engineering and prototyping,
though creating a small PCB to sit between the GPS receiver and motherboard would be a
better permanent solution.

Connections:  
PIC Rx on RC5 (pin 5) - Connect to GPS receiver Tx  
PIC Tx on RC4 (pin 6) - Connect to Navigation Rx (where GPS Tx was connected)  

Furuno GPS pinout:  
(unable to find GN80 pinout, but found similar GT-8031 and confirmed pins where possible)  
1: TEST Connected to GND on motherboard  
2: MODE Connected to GND on motherboard through 0 ohm resistor  
3: Tx  
4: Rx  
5: 1PPS (appears unconnected on motherboard)  
6: RST_N  
7: VBATT (approximately +3.3V)  
8: GND  
9: VCC (+3.3V)  
10: VANT (+5V)  
Mechanical pins: N/C on both sides  

![unit_open](pics/unit_open.jpg)

![connected](pics/connected.jpg)

![testing_in_trunk](pics/testing_in_trunk.jpg)

Once connected and running, enjoy being in 2022 instead of 2002... and a correct
dash clock!
![fixed_data](pics/fixed_data.jpg)

Some notes:  
The binary protocol from the Furuno GPS unit looks to be a clone of Trimble TSIP,
with Furuno's own packet structures.  
This code only modifies the 0x75 packet.  All other data passes through unmodified.

The GPS receiver communicates at 9600 bps with 8 data bits, odd parity, 1 stop bit

As compiled using the free version of the compiler with -o2 optimization, this uses
605 of 1024 bytes of RAM (59%), and 8057 of 8192 words of flash (98%).
Including the <time.h> functions ate up almost all of the flash, but greatly simplified
my code.  Alternatively, u-blox has an application note (UBX-19016936) with example code,
which could likely be implemented with a much smaller flash footprint.
The precompiled .hex file is also included.