/* -- Includes ------------------------------------------------------------ */
#include <stddef.h>      //offsetof
#include <string.h>      //memcpy
#include <stdio.h>       //printf
#include "wiringPi.h"    //delay
#include "wiringPiSPI.h" //wiringPiSPIxDataRW
#include "mx_cc1101.h"

/* -- Defines ------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */

/* -- Module Global Variables ---------------------------------------------- */

// Base Frequency = 433.92 MHz
// CRC Autoflush = false
// CRC Enable = false
// Carrier Frequency = 433.92 MHz
// Channel Number = 0
// Channel Spacing = ~200 kHz (don't care, as only one channel is used)
// Data Format = Normal mode
// Data Rate = 4800 bps
// Deviation = ~24 kHz (don't care, as OOK is used)
// Device Address = 0
// Manchester Enable = false
// Modulation Format = ASK/OOK
// PA Ramping = false
// Packet Length = 1
// Packet Length Mode = fixed packet length mode.
// Preamble Count = 4 (don't care, as no preamble is used)
// RX Filter BW = ~100 kHz
// Sync Word Qualifier Mode = No preamble/sync
// TX Power = 10
// Whitening = false
static const MX_CC101_SpiRegister_t PAGER_CONFIG = {
    0x2E, //@00h IOCFG2              GDO2 Output Pin Configuration -> GDO2: High impedance (3-state)
    0x2E, //@01h IOCFG1*             GDO1 Output Pin Configuration -> GDO1: High impedance (3-state)
    0x2E, //@02h IOCFG0              GDO0 Output Pin Configuration -> GDO0: High impedance (3-state)
    0x06, //@03h FIFOTHR             RX FIFO and TX FIFO Thresholds -> ~50%
    0xD3, //@04h SYNC1*              Sync Word, High Byte -> don't care
    0x91, //@05h SYNC0*              Sync Word, Low Byte -> don't care
    0x01, //@06h PKTLEN*             Packet Length
    0x00, //@07h PKTCTRL1            Packet Automation Control -> do not append any status bytes
    0x01, //@08h PKTCTRL0            Packet Automation Control -> fixed packet lenght; crc disabled; rx/tx via fifo; whitening off
    0x00, //@09h ADDR*               Device Address -> don't care
    0x00, //@0Ah CHANNR*             Channel Number -> we will utilize channel 0 only!
    0x06, //@0Bh FSCTRL1             Frequency Synthesizer Control -> intermediate frequency f_if = ~152kHz (calculated by RFstudio)
    0x00, //@0Ch FSCTRL0*            Frequency Synthesizer Control
    0x10, //@0Dh FREQ2               Frequency Control Word, High Byte    -> f_carrier = 0x10B071 -> f_carrier = 433.92 MHz
    0xB0, //@0Eh FREQ1               Frequency Control Word, Middle Byte
    0x71, //@0Fh FREQ0               Frequency Control Word, Low Byte
    0xC7, //@10h MDMCFG4             Modem Configuration -> bandwith of 100kHz; datarate 4.8kbps
    0x83, //@11h MDMCFG3             Modem Configuration -> datarate 4k8kbps
    0x30, //@12h MDMCFG2             Modem Configuration -> ASK/OOK modulation; manchester disabled; no preamble; no sync-word
    0x22, //@13h MDMCFG1*            Modem Configuration
    0xF8, //@14h MDMCFG0*            Modem Configuration
    0x37, //@15h DEVIATN             Modem Deviation Setting -> don't care for OOK
    0x07, //@16h MCSM2*              Main Radio Control State Machine Configuration -> RX timeout until end of packet
    0x30, //@17h MCSM1*              Main Radio Control State Machine Configuration -> channel clear if RSSI is below threshold unless currently receiving; goto IDLE after RX/TX
    0x18, //@18h MCSM0               Main Radio Control State Machine Configuration -> automatic calibrate when going to RX/TX/IDLE
    0x16, //@19h FOCCFG              Frequency Offset Compensation Configuration -> frequency stuff (calculated by RFstudio)
    0x6C, //@1Ah BSCFG*              Bit Synchronization Configuration -> try 0x6D for +/- 3% data rate offset or even 0x6E or 6F (see page 84)
    0x07, //@1Bh AGCCTRL2            AGC Control -> these value was found in application note swra215e.pdf
    0x00, //@1Ch AGCCTRL1            AGC Control -> these value was found in application note swra215e.pdf
    0x92, //@1Dh AGCCTRL0            AGC Control -> these value was found in application note swra215e.pdf
    0x87, //@1Eh WOREVT1*            High Byte Event0 Timeout
    0x6B, //@1Fh WOREVT0*            Low Byte Event0 Timeout
    0xFB, //@20h WORCTRL             Wake On Radio Control
    0x56, //@21h FREND1*             Front End RX Configuration
    0x11, //@22h FREND0              Front End TX Configuration -> for OOK, selects the PATABLE index [1] to use when transmitting a '1'. index [0] is used for transmission of a '0'.
    0xE9, //@23h FSCAL3              Frequency Synthesizer Calibration
    0x2A, //@24h FSCAL2              Frequency Synthesizer Calibration
    0x00, //@25h FSCAL1              Frequency Synthesizer Calibration
    0x1F, //@26h FSCAL0              Frequency Synthesizer Calibration
    0x41, //@27h RCCTRL1*            RC Oscillator Configuration
    0x00, //@28h RCCTRL0*            RC Oscillator Configuration
};



/* -- Function Prototypes ------------------------------------------------- */

/* -- Implementation ------------------------------------------------------ */

int mx_cc1101_init(MX_CC101_GdoCfg_t gdo0, MX_CC101_GdoCfg_t gdo2, MX_CC1101_RxAttenuation_t rxAttenuation)
{
    int err;
    uint8_t spiXferBuf[MX_CC1101_FIFO_SIZE + 4];

    // Do a software reset of the chip
    spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_RESET;
    err = wiringPiSPIxDataRW(0, 0, spiXferBuf, 1);
    if (err <= 0)
    {
        fprintf(stderr, "Chip reset failed");
        return err;
    }
    delay(250); // Wait a ridiculous amount of time to be sure radio is ready.

    // ensure correct communication with the expected chip
    if (mx_cc1101_get_chip_version() != 0x14)
    {
        fprintf(stderr, "Version check failed");
        return err;
    }

    // write configuration ook modulation, frequency, datarate, bandwidth, ...
    spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_BURST | MX_CC1101_REG_IOCFG2;
    memcpy(&spiXferBuf[1], &PAGER_CONFIG, sizeof(PAGER_CONFIG));
    spiXferBuf[1 + offsetof(MX_CC101_SpiRegister_t, IOCFG0)] = (uint8_t)gdo0; // overwrite preset with parameter value
    spiXferBuf[1 + offsetof(MX_CC101_SpiRegister_t, IOCFG2)] = (uint8_t)gdo2; // overwrite preset with parameter value
    spiXferBuf[1 + offsetof(MX_CC101_SpiRegister_t, FIFOTHR)] |= (uint8_t)rxAttenuation; // set rx attenuation to reduce receiver sensitivity
    err = wiringPiSPIxDataRW(0, 0, spiXferBuf, 1 + sizeof(PAGER_CONFIG));
    if (err <= 0)
    {
        fprintf(stderr, "General configuration failed");
        return err;
    }

    // write PTABLE (see table 39 on page 60 of datasheet)
    spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_BURST | MX_CC1101_REG_PATABLE;
    spiXferBuf[1] = 0;    //power level of a 0 bit
    spiXferBuf[2] = 0xC0; //power level of a 1 bit (+10dB)
    spiXferBuf[3] = 0;
    spiXferBuf[4] = 0;
    spiXferBuf[5] = 0;
    spiXferBuf[6] = 0;
    spiXferBuf[7] = 0;
    spiXferBuf[8] = 0;
    err = wiringPiSPIxDataRW(0, 0, spiXferBuf, 1 + 8);
    if (err <= 0)
    {
        fprintf(stderr, "Power configuration failed");
        return err;
    }

    return 0;
}

//0x14 is expected!
uint8_t mx_cc1101_get_chip_version()
{
    uint8_t spiXferBuf[2];
    spiXferBuf[0] = MX_CC1101_CMD_READ | MX_CC1101_CMD_BURST | MX_CC1101_REG_VERSION;
    spiXferBuf[1] = 0; // value does not care!
    wiringPiSPIxDataRW(0, 0, spiXferBuf, 2);
    return spiXferBuf[1];
}

// get status byte (datasheet page 31)
// if fifo = MX_CC1101_STATUS_FIFO_RX, the least 4 bits contains the number of bytes *available* in the RX FIFO
// if fifo = MX_CC1101_STATUS_FIFO_TX, the least 4 bits contains the number of *free* bytes in the TX FIFO
uint8_t mx_cc1101_get_status(MX_CC1101_StatusFifo_t fifo)
{
    uint8_t cmd = MX_CC1101_CMD_NOP;
    if (fifo == MX_CC1101_STATUS_FIFO_RX)
    {
        cmd |= MX_CC1101_CMD_READ;
    }
    wiringPiSPIxDataRW(0, 0, &cmd, 1);
    return cmd;
}

int mx_cc1101_is_idle(void)
{
    return (mx_cc1101_get_status(MX_CC1101_STATUS_FIFO_RX) & 0xF0) == MX_CC1101_STATUS_IDLE;
}

// user has to wait for completion of transmission - by checking is_idle()!
int mx_cc1101_transmit(uint8_t *data, size_t len)
{
    if (len > MX_CC1101_FIFO_SIZE)
    {
        return -1;
    }

    uint8_t spiXferBuf[MX_CC1101_FIFO_SIZE + 4];
    const uint8_t status = mx_cc1101_get_status(MX_CC1101_STATUS_FIFO_TX) & 0xF0;
    // check for IDLE state
    if (status != MX_CC1101_STATUS_IDLE)
    {
        // Enter IDLE state
        spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_IDLE;
        wiringPiSPIxDataRW(0, 0, spiXferBuf, 1);
        delay(1); //wait for state transition
    }
    // flush tx fifo
    spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_FLUSH_TX;
    wiringPiSPIxDataRW(0, 0, spiXferBuf, 1);

    // set packet length and fix length format
    spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_BURST | MX_CC1101_REG_PKTLEN;
    spiXferBuf[1] = len; // PKTLEN
    spiXferBuf[2] = 0;   // PKTCTRL1
    spiXferBuf[3] = 0;   // PKTCTRL0
    wiringPiSPIxDataRW(0, 0, spiXferBuf, 4);

    // copy data into tx fifo
    spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_BURST | MX_CC1101_REG_FIFO;
    memcpy(&spiXferBuf[1], data, len);
    wiringPiSPIxDataRW(0, 0, spiXferBuf, 1 + len);

    // start transmission
    spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_TX;
    wiringPiSPIxDataRW(0, 0, spiXferBuf, 1);
    delay(1); //wait for state transition
    return 0;
}

int mx_cc1101_receive(uint8_t *buffer, size_t size)
{
    uint8_t spiXferBuf[MX_CC1101_FIFO_SIZE + 4];

    // check for RX state
    uint8_t status = mx_cc1101_get_status(MX_CC1101_STATUS_FIFO_RX);
    const uint8_t rxFifoCnt = status & 0x0F; //get fifo count
    status = status & 0xF0; //isolate status
    // noting in the rx buffer, and not in RX mode
    if ((rxFifoCnt == 0) && (status != MX_CC1101_STATUS_RX))
    {
        // not in idle mode
        if (status != MX_CC1101_STATUS_IDLE)
        {
            // Enter IDLE state
            spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_IDLE;
            wiringPiSPIxDataRW(0, 0, spiXferBuf, 1);
            delay(1); //wait for state transition
        }

        // flush rx fifo
        spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_FLUSH_TX;
        wiringPiSPIxDataRW(0, 0, spiXferBuf, 1);

        // set packet length to 1 byte fix
        spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_BURST | MX_CC1101_REG_PKTLEN;
        spiXferBuf[1] = 1; // PKTLEN
        spiXferBuf[2] = 0;   // PKTCTRL1
        spiXferBuf[3] = 0;   // PKTCTRL0
        wiringPiSPIxDataRW(0, 0, spiXferBuf, 4);

        // Enter RX state
        spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_RX;
        wiringPiSPIxDataRW(0, 0, spiXferBuf, 1);
        delay(1); //wait for state transition
        return 0;
    }

    // get the exact number of bytes in RX fifo (datasheet page 94)
    spiXferBuf[0] = MX_CC1101_CMD_READ | MX_CC1101_CMD_BURST | MX_CC1101_REG_RXBYTES;
    spiXferBuf[1] = 0; // value does not care!
    wiringPiSPIxDataRW(0, 0, spiXferBuf, 2);
    size_t rxBytes = spiXferBuf[1];
    // check for overflow
    if (rxBytes & 0x80)
    {
        return -1;
    }
    // limit byte count to buffer size (factor 3 because for each payload byte, there are 2 status bytes)
    if (rxBytes > size)
    {
        rxBytes = size;
    }
    // read data from fifo
    if (rxBytes > 0)
    {
        // read data out of fifo
        spiXferBuf[0] = MX_CC1101_CMD_READ | MX_CC1101_CMD_BURST | MX_CC1101_REG_FIFO;
        wiringPiSPIxDataRW(0, 0, spiXferBuf, 1 + rxBytes);
        memcpy(buffer, &spiXferBuf[1], rxBytes);
    }
    return rxBytes;
}


int mx_cc1101_receive_async(void)
{
    uint8_t spiXferBuf[2];

    // Enter IDLE state
    spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_IDLE;
    wiringPiSPIxDataRW(0, 0, spiXferBuf, 1);
    delay(1); //wait for state transition

    // set packet length to 1 byte fix
    spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_REG_PKTCTRL0;
    spiXferBuf[1] = 0x30; // async mode
    wiringPiSPIxDataRW(0, 0, spiXferBuf, 2);

    // Enter RX state
    spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_RX;
    wiringPiSPIxDataRW(0, 0, spiXferBuf, 1);
    delay(1); //wait for state transition
    return 0;
}


int mx_cc1101_get_rssi(uint32_t rxflush)
{
    // get number of bytes available in fifo
    uint8_t spiXferBuf[2];
    spiXferBuf[0] = MX_CC1101_CMD_READ | MX_CC1101_CMD_BURST | MX_CC1101_REG_RSSI;
    spiXferBuf[1] = 0; // value does not care!
    wiringPiSPIxDataRW(0, 0, spiXferBuf, 2);
    const int rssi = (int8_t)spiXferBuf[1]; //value is given as 2's complement value in 0.5db resolution
    //flush rx fifo to prevent overflow - which will stop reception
    if (rxflush)
    {
        const uint8_t rxCnt = spiXferBuf[0] & 0x0F; //number of bytes in rx fifo
        if (rxCnt)
        {
            // read data out of fifo - and drop them away
            uint8_t spiXferBuf[16];
            spiXferBuf[0] = MX_CC1101_CMD_READ | MX_CC1101_CMD_BURST | MX_CC1101_REG_FIFO;
            wiringPiSPIxDataRW(0, 0, spiXferBuf, 1 + rxCnt);
        }
        spiXferBuf[0] = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_FLUSH_TX;
        wiringPiSPIxDataRW(0, 0, spiXferBuf, 1);
    }
    return rssi/2 - 74; //the offset of 74 was fourn in application note swra114d.pdf
}


void mx_cc1101_close(void)
{
    uint8_t cmd = MX_CC1101_CMD_WRITE | MX_CC1101_CMD_IDLE;
    wiringPiSPIxDataRW(0, 0, &cmd, 1);
    delay(1); //wait for state transition
}
