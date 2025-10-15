#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wiringPi.h"
#include "wiringPiSPI.h"
#include "mx_cc1101.h"


// GDO pins of the CC1101, connected to the Raspberry Pi GPIOs
// #define CC1100_GDO0 24 //PIN18 ^= GPIO24 (WiringPI #5) - not used here
#define CC1100_GDO2 25 //PIN22 ^= GPIO25 (WiringPI #6) - used with MX_CC1101_GDO_CFG_ASYNC_DATA_OUTPUT, to reflect rx data


// Sample the received signal and output a value-change-dump (VCD) that can be processed by Sigrok-PulseView later
// Program will run for 30 seconds and terminate automatically
// Usage: ./airsniffer > capture.vcd
int main(int argc, char *argv[])
{
    // Init wiringPi for GPIO and SPI
    wiringPiSetupPinType(WPI_PIN_BCM); // uses BCM numbering of the GPIOs
    pinMode(CC1100_GDO2, INPUT);
    wiringPiSPIxSetup(0, 0, 2000000); //2MHz
    delay(10);

    // Init CC1101
    // Use default settings from library (f = 433.92MHz, ASK/OOK modulation, 100 kHz bandwidth, baudrate doesn't care)
    // Do not use GDO0; Map RX signal/data to GDO2; Set some RX attenuation to filter out weak signals
    mx_cc1101_init(MX_CC1101_GDO_CFG_TRISTATE, MX_CC1101_GDO_CFG_ASYNC_DATA_OUTPUT, MX_CC1101_RX_ATTENUATION_18DB);

    // We will output the received signal as a value-change-dump, that can be processed by Sigrok-PulseView later
    // Write the header of the VCD file
    puts("$timescale 1us $end");
    puts("$var wire 1 ! RX $end");
    puts("$enddefinitions $end");

    // Start receiving data
    mx_cc1101_receive_async();
    unsigned int us = micros();
    const unsigned int us0 = us;
    unsigned int rx0 = (unsigned int)-1;
    while((us - us0) < 30000000) //run for 30 seconds
    {
        // get state of RX data from GDO2 pin (this is the fastest way to observe the signal)
        const unsigned int rx = digitalRead(CC1100_GDO2);
        if (rx != rx0) //on change
        {
            // Print the time since start and the new value
            printf("#%u\n%u!\n", us - us0, rx);
            rx0 = rx;
        }
        // update time
        us = micros();
    }

    // Stop reception
    mx_cc1101_close();
    return 0;
}
