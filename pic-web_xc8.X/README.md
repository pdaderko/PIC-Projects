## PIC-WEB XC8
### Ethernet example for Olimex PIC-WEB (PIC18F67J60 MCU) using XC8 compiler and Microchip TCP/IP Lite Stack

This is an example to get Ethernet running on Olimex's PIC-WEB (and any other PIC18F97J60 family MCU) using Microchip's TCP/IP Lite stack and the (newer/supported) XC8 compiler.

The sample projects available under "SOFTWARE" on the PIC-WEB product page are based on the old MLA TCP/IP stack and only support the (old/unsupported) C18 compiler.  Microchip has a newer TCP/IP Lite Stack which supports XC8 (AN1921: https://www.microchip.com/wwwAppNotes/AppNotes.aspx?appnote=en573940 ), but that AN doesn't directly support the PIC18F97J60 family (with the integrated MAC and PHY).

The PIC18F97J60 family is supported by MPLAB Code Configurator (MCC), and uses the same TCP/IP Lite Stack from AN1921, meaning we can use MCC to create the TCP/IP project for the PIC-WEB board, then use the sample application code from AN1921 for sample TCP and UDP functions.  I was able to create a functional project using the current (at this time) versions of MPLAB X v5.45, XC8 v2.31, MCC v4.0.2 .


While you should be able to download and run this project "out of the box", below is a rundown of the process to recreate exactly what I did:
Create New Standalone Project  
Device PIC18F67J60  
Open MPLAB Code Configurator (creating the new mc3 file)  
Here, you can start to follow along on page 3 of the AN1921 PDF, though it's a bit different for our chip, so I've detailed it below.  As you're going through this, be sure to read the INFO, HINT, and WARNING Notifications.

Configure system module as desired (for maximum 41.667 MHz, change to HSPLL, set external clock to 25 MHz, enable Software PLL)  
Under "Device Resources" click the '+' on TCP/IP Lite  
This seems to add a few things to the "Project Resources".  First, drop down "Ethernet" and click "MAC", then select "ETHxxJ6x".  This gets rid of some of the extra things that were added because it was assuming an external MAC/PHY.  You can also set your MAC address here.  
As noted in the WARNING, click TMR1 and check "Enable Timer Interrupt".  Then change the Prescaler to 1:8, and (as noted in the new warning), change the Timer Period to 50ms and the Callback Function Rate to 20, in order to get a Callback Rate of (roughly) 1 second.  
Under "Project Resources" click TCP/IP Lite, select which protocols you want enabled (uncheck DHCP if you want a static IP, then set your static IP).  In my case, I have UDP, IPV4, TCP, ICMP, and ARP checked, so we can ping the device, and run all the TCP and UDP demos from AN1921.  
Lastly, under Pin Manager I selected both ports A0 and A1 to be outputs, which enables the two Ethernet LEDs (alternatively, you could do this with TRISA in your code).

That's all there is to configuring it through MCC.  You can configure other code if you'd like, otherwise next to "Project Resources" click the "Generate" button, and save/close MCC.  When you go back to your project, you'll see a bunch of MCC Generated files with all the TCP/IP stuff in it.

If you don't want to ever use MCC again and/or plan to modify the generated files, you can delete your mc3 file and move everything out of mcc_generated_files.  That way accidentally running MCC again won't clobber the files.  But otherwise, you can leave them as-is.


Here's where you can follow along with the specific examples from AN1921.  TCP client demo: pg. 9, TCP server demo: pg. 15, and UDP demo: pg. 19.

For this example, I'm going to add the TCP server demo.  Add the tcp_server_demo .c and .h files from the AN1921 code to your project.  In your main.c, enable your interrupts by uncommenting the INTERRUPT_GlobalInterruptEnable(); and INTERRUPT_PeripheralInterruptEnable(); lines.  Also, in the while (1) loop, add Network_Manage(); and DEMO_TCP_EchoServer(); .  Lastly, you need to include the tcp_server_demo.h file (#include "tcp_server_demo.h" at the top).

Building shows quite a few warnings from the generated code, but seem mostly mundane.  If you run the project, assuming you're plugged into the network and properly configured (IP, netmask, etc.) you should notice that you can ping the device.

Now, if you run the TCPIP_Demo.jar GUI file from AN1921 on your PC, you should be able to go to the TCP Client Demo tab, put in the IP address of the PIC-WEB, port 7 and click connect.  The status section should show that you're connected.  The demo code simply echoes back any characters sent, so if you send "abc", you should see:  
<-: abc  
->: abc  

If you want to make it do something else, simply change the code between TCP_GetReceivedData() and TCP_Send() in tcp_server_demo.c .


One thing to note - the generated code and sample code from AN1921 only includes simple TCP and UDP code (which for a small MCU powered device, may be all you need).  For example, from Microchip's site: https://www.microchip.com/SWLibraryWeb/product.aspx?product=TCPIPSTACK , it specifically shows that the old "MLA" supports HTTP while the new "Lite" does not.  So while out of the box you got a website that could blink an LED with the MLA sample, on Lite, you get much less.  Though with a little bit of effort you could write your own HTTP server - start with the TCP server demo listening on port 80, and write the code to handle HTTP requests as necessary.

As compiled using the free version of the compiler, this uses 1305 of 3808 bytes of RAM (34%), and 36685 of 131064 bytes of flash (28%).  The precompiled .hex file is also included.  This has the IP address (default, as currently configured in the project) as 192.168.0.1, and the TCP echo server running on port 7.
