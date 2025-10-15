#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wiringPi.h"
#include "wiringPiSPI.h"
#include "dep/argtable3.h"
#include "mx_cc1101.h"


#define APP_NAME "pagercall"
#define APP_VERSION "1.0.0"


// Symbols for encoding bits (each bit is represented by 4 output bits)
// A '0' bit is represented by 1000 (short on, long off)
// A '1' bit is represented by 1110 (long on, short off)
#define SYMBOL_0    0x08 //0b1000
#define SYMBOL_1    0x0E //0b1110

// Encode input bits into output symbols
// Each input bit is represented by 4 output bits. Thus, 2 input bits fit into one output byte.
// The output is written to the 'out' buffer
// The input is taken from the 'in' variable, which contains 'num' bits (from MSB to LSB)
// The function returns the number of output bytes written to the 'out' buffer
//
// For example, if in=0x890024 (which (274<<15 | 1<<5 | 4), the num = 25-bit pattern to call pager 1, of keyboard 274, with action 4),
// the output will be: { 0x8e, 0x88, 0x8e, 0x88, 0xe8, 0x88, 0x88, 0x88, 0x88, 0x8e, 0x88, 0xe8, 0x80 }
static uint32_t encode_bits(uint8_t * out, const uint32_t in, const uint32_t num)
{
    uint32_t cnt = 0;
    uint32_t mask = 1u << num;
    while (mask = (mask >> 1))
    {
        uint32_t val;
        val = ((in & mask) ? SYMBOL_1 : SYMBOL_0) << 4;
        if (mask = (mask >> 1))
        {
            val |= ((in & mask) ? SYMBOL_1 : SYMBOL_0);
        }
        *out++ = val;
        ++cnt;
    }
    return cnt;
}


// Call Retekess TD157 Pager
//
// Usage: ./pagercall -k <keyboard id> -p <pager id> [--help] [--version]
// Keyboard ID: 1 .. 999
// Pager ID: 1 .. 999
int main(int argc, char *argv[])
{
    struct arg_lit *argHelp;
    struct arg_lit *argVersion;
    struct arg_int *argKeyboard;
    struct arg_int *argPager;
    struct arg_end *argEnd;
    void * const argtable[] =
    {
        argHelp = arg_lit0(NULL, "help", "Print help and exit"),
        argVersion = arg_lit0(NULL, "version", "Print version and exit"),
        argKeyboard = arg_int0("k", "keyboard", "<ID>", "ID of keyboard (1 .. 999)"),
        argPager = arg_int0("p", "pager", "<ID>", "ID of pager (1 .. 999)"),
        argEnd = arg_end(3),
    };

    // Parse command line arguments.
    arg_parse(argc, argv, argtable);

    // Help
    if (argHelp->count)
    {
        print_help(argtable);
        return 0;
    }

    // Version
    if (argVersion->count)
    {
        puts(APP_VERSION);
        return 0;
    }

    // Keyboard ID
    const uint32_t keyboard = (uint32_t)(argKeyboard->count ? argKeyboard->ival[0] : 0);
    if (keyboard < 1 || keyboard >  999)
    {
        fprintf(stderr, "Error: A Keyboard ID in range 1 .. 999 is required\n");
        return 1;
    }

    // Pager ID
    const uint32_t pager = (uint32_t)(argPager->count ? argPager->ival[0] : 0);
    if (pager < 1 || pager >  999)
    {
        fprintf(stderr, "Error: A Pager ID in range 1 .. 999 is required\n");
        return 1;
    }

    // Init wiringPi for GPIO and SPI use
    //wiringPiSetupPinType(WPI_PIN_BCM); // uses BCM numbering of the GPIOs
    wiringPiSPIxSetup(0, 0, 2000000); //2MHz
    delay(10);

    // Use default settings from library (f = 433.92MHz, ASK/OOK modulation, 100 kHz bandwidth, baudrate 4800 bps)
    // Do not use GDO0/2; Map RX signal/data to GDO2; RX attenuation doesn't matter, as we are only transmitting
    mx_cc1101_init(MX_CC1101_GDO_CFG_TRISTATE, MX_CC1101_GDO_CFG_TRISTATE, MX_CC1101_RX_ATTENUATION_0DB);

    // Setup telegram to call the respective pager
    uint8_t data[13];
    const uint32_t action = 4;
    const uint32_t code = (keyboard << 15) | (pager << 5) | action;
    const uint32_t len = encode_bits(data, code, 25);

    // Send the telegram several times, with short pauses in between (5ms)
    for (uint32_t versuch = 1; versuch < 32; ++versuch)
    {
        // Do transmission (with a inter-frame delay prepended)
        delay(5);
        mx_cc1101_transmit(data, len);
        // Wait until transmission is complete
        while (!mx_cc1101_is_idle())
        {
            putchar('.');
            delay(1); //at 4k8bps, transmission of one byte takes ~1.67ms ... so the length is a good value for delay
        }
    }

    // Shutdown
    mx_cc1101_close();
    return 0;
}
