// Adapted from https://github.com/jgromes/RadioLib

#ifndef _MX_CC1101_H_
#define _MX_CC1101_H_

/* -- Includes ------------------------------------------------------------ */
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */
#define MX_CC1101_FREQUENCY_STEP_SIZE                     396.7285156
#define MX_CC1101_MAX_PACKET_LENGTH                       255
#define MX_CC1101_FIFO_SIZE                               64
#define MX_CC1101_CRYSTAL_FREQ                            26.0f
#define MX_CC1101_DIV_EXPONENT                            16

// CC1101 SPI commands
#define MX_CC1101_CMD_READ                                0b10000000
#define MX_CC1101_CMD_WRITE                               0b00000000
#define MX_CC1101_CMD_BURST                               0b01000000
#define MX_CC1101_CMD_ACCESS_STATUS_REG                   0b01000000
#define MX_CC1101_CMD_FIFO_RX                             0b10000000
#define MX_CC1101_CMD_FIFO_TX                             0b00000000
#define MX_CC1101_CMD_RESET                               0x30
#define MX_CC1101_CMD_FSTXON                              0x31
#define MX_CC1101_CMD_XOFF                                0x32
#define MX_CC1101_CMD_CAL                                 0x33
#define MX_CC1101_CMD_RX                                  0x34
#define MX_CC1101_CMD_TX                                  0x35
#define MX_CC1101_CMD_IDLE                                0x36
#define MX_CC1101_CMD_WOR                                 0x38
#define MX_CC1101_CMD_POWER_DOWN                          0x39
#define MX_CC1101_CMD_FLUSH_RX                            0x3A
#define MX_CC1101_CMD_FLUSH_TX                            0x3B
#define MX_CC1101_CMD_WOR_RESET                           0x3C
#define MX_CC1101_CMD_NOP                                 0x3D

// CC1101 register map
#define MX_CC1101_REG_IOCFG2                              0x00
#define MX_CC1101_REG_IOCFG1                              0x01
#define MX_CC1101_REG_IOCFG0                              0x02
#define MX_CC1101_REG_FIFOTHR                             0x03
#define MX_CC1101_REG_SYNC1                               0x04
#define MX_CC1101_REG_SYNC0                               0x05
#define MX_CC1101_REG_PKTLEN                              0x06
#define MX_CC1101_REG_PKTCTRL1                            0x07
#define MX_CC1101_REG_PKTCTRL0                            0x08
#define MX_CC1101_REG_ADDR                                0x09
#define MX_CC1101_REG_CHANNR                              0x0A
#define MX_CC1101_REG_FSCTRL1                             0x0B
#define MX_CC1101_REG_FSCTRL0                             0x0C
#define MX_CC1101_REG_FREQ2                               0x0D
#define MX_CC1101_REG_FREQ1                               0x0E
#define MX_CC1101_REG_FREQ0                               0x0F
#define MX_CC1101_REG_MDMCFG4                             0x10
#define MX_CC1101_REG_MDMCFG3                             0x11
#define MX_CC1101_REG_MDMCFG2                             0x12
#define MX_CC1101_REG_MDMCFG1                             0x13
#define MX_CC1101_REG_MDMCFG0                             0x14
#define MX_CC1101_REG_DEVIATN                             0x15
#define MX_CC1101_REG_MCSM2                               0x16
#define MX_CC1101_REG_MCSM1                               0x17
#define MX_CC1101_REG_MCSM0                               0x18
#define MX_CC1101_REG_FOCCFG                              0x19
#define MX_CC1101_REG_BSCFG                               0x1A
#define MX_CC1101_REG_AGCCTRL2                            0x1B
#define MX_CC1101_REG_AGCCTRL1                            0x1C
#define MX_CC1101_REG_AGCCTRL0                            0x1D
#define MX_CC1101_REG_WOREVT1                             0x1E
#define MX_CC1101_REG_WOREVT0                             0x1F
#define MX_CC1101_REG_WORCTRL                             0x20
#define MX_CC1101_REG_FREND1                              0x21
#define MX_CC1101_REG_FREND0                              0x22
#define MX_CC1101_REG_FSCAL3                              0x23
#define MX_CC1101_REG_FSCAL2                              0x24
#define MX_CC1101_REG_FSCAL1                              0x25
#define MX_CC1101_REG_FSCAL0                              0x26
#define MX_CC1101_REG_RCCTRL1                             0x27
#define MX_CC1101_REG_RCCTRL0                             0x28
#define MX_CC1101_REG_FSTEST                              0x29
#define MX_CC1101_REG_PTEST                               0x2A
#define MX_CC1101_REG_AGCTEST                             0x2B
#define MX_CC1101_REG_TEST2                               0x2C
#define MX_CC1101_REG_TEST1                               0x2D
#define MX_CC1101_REG_TEST0                               0x2E
#define MX_CC1101_REG_PARTNUM                             0x30
#define MX_CC1101_REG_VERSION                             0x31
#define MX_CC1101_REG_FREQEST                             0x32
#define MX_CC1101_REG_LQI                                 0x33
#define MX_CC1101_REG_RSSI                                0x34
#define MX_CC1101_REG_MARCSTATE                           0x35
#define MX_CC1101_REG_WORTIME1                            0x36
#define MX_CC1101_REG_WORTIME0                            0x37
#define MX_CC1101_REG_PKTSTATUS                           0x38
#define MX_CC1101_REG_VCO_VC_DAC                          0x39
#define MX_CC1101_REG_TXBYTES                             0x3A
#define MX_CC1101_REG_RXBYTES                             0x3B
#define MX_CC1101_REG_RCCTRL1_STATUS                      0x3C
#define MX_CC1101_REG_RCCTRL0_STATUS                      0x3D
#define MX_CC1101_REG_PATABLE                             0x3E
#define MX_CC1101_REG_FIFO                                0x3F

// status byte (returned during SPI transactions)                             MSB   LSB   DESCRIPTION
#define MX_CC1101_STATUS_CHIP_READY                       0b00000000  //  7     7   chip ready
#define MX_CC1101_STATUS_CHIP_NOT_READY                   0b10000000  //  7     7   chip not ready (power/crystal not stable)
#define MX_CC1101_STATUS_IDLE                             0b00000000  //  6     4   idle
#define MX_CC1101_STATUS_RX                               0b00010000  //  6     4   Rx
#define MX_CC1101_STATUS_TX                               0b00100000  //  6     4   Tx
#define MX_CC1101_STATUS_FSTXON                           0b00110000  //  6     4   Fast Tx ready
#define MX_CC1101_STATUS_CALIBRATE                        0b01000000  //  6     4   synthesizer calibration running
#define MX_CC1101_STATUS_SETTLING                         0b01010000  //  6     4   PLL settling
#define MX_CC1101_STATUS_RXFIFO_OVERFLOW                  0b01100000  //  6     4   Rx FIFO overflow
#define MX_CC1101_STATUS_TXFIFO_UNDERFLOW                 0b01110000  //  6     4   Tx FIFO underflow

// MX_CC1101_REG_IOCFG2
#define MX_CC1101_GDO2_NORM                               0b00000000  //  6     6   GDO2 output: active high (default)
#define MX_CC1101_GDO2_INV                                0b01000000  //  6     6                active low

// MX_CC1101_REG_IOCFG1
#define MX_CC1101_GDO_DS_LOW                              0b00000000  //  7     7   GDOx output drive strength: low (default)
#define MX_CC1101_GDO_DS_HIGH                             0b10000000  //  7     7                               high
#define MX_CC1101_GDO1_NORM                               0b00000000  //  6     6   GDO1 output: active high (default)
#define MX_CC1101_GDO1_INV                                0b01000000  //  6     6                active low

// MX_CC1101_REG_IOCFG0
#define MX_CC1101_GDO0_TEMP_SENSOR_OFF                    0b00000000  //  7     7   analog temperature sensor output: disabled (default)
#define MX_CC1101_GDO0_TEMP_SENSOR_ON                     0b10000000  //  7     7                                     enabled
#define MX_CC1101_GDO0_NORM                               0b00000000  //  6     6   GDO0 output: active high (default)
#define MX_CC1101_GDO0_INV                                0b01000000  //  6     6                active low

// MX_CC1101_REG_IOCFG2 + REG_IOCFG1 + REG_IOCFG0
#define MX_CC1101_GDOX_RX_FIFO_FULL                       0x00        //  5     0   Rx FIFO full or above threshold
#define MX_CC1101_GDOX_RX_FIFO_FULL_OR_PKT_END            0x01        //  5     0   Rx FIFO full or above threshold or reached packet end
#define MX_CC1101_GDOX_TX_FIFO_ABOVE_THR                  0x02        //  5     0   Tx FIFO above threshold
#define MX_CC1101_GDOX_TX_FIFO_FULL                       0x03        //  5     0   Tx FIFO full
#define MX_CC1101_GDOX_RX_FIFO_OVERFLOW                   0x04        //  5     0   Rx FIFO overflowed
#define MX_CC1101_GDOX_TX_FIFO_UNDERFLOW                  0x05        //  5     0   Tx FIFO underflowed
#define MX_CC1101_GDOX_SYNC_WORD_SENT_OR_PKT_RECEIVED     0x06        //  5     0   sync word was sent or packet was received
#define MX_CC1101_GDOX_PKT_RECEIVED_CRC_OK                0x07        //  5     0   packet received and CRC check passed
#define MX_CC1101_GDOX_PREAMBLE_QUALITY_REACHED           0x08        //  5     0   received preamble quality is above threshold
#define MX_CC1101_GDOX_CHANNEL_CLEAR                      0x09        //  5     0   RSSI level below threshold (channel is clear)
#define MX_CC1101_GDOX_PLL_LOCKED                         0x0A        //  5     0   PLL is locked
#define MX_CC1101_GDOX_SERIAL_CLOCK                       0x0B        //  5     0   serial data clock
#define MX_CC1101_GDOX_SERIAL_DATA_SYNC                   0x0C        //  5     0   serial data output in: synchronous mode
#define MX_CC1101_GDOX_SERIAL_DATA_ASYNC                  0x0D        //  5     0                          asynchronous mode
#define MX_CC1101_GDOX_CARRIER_SENSE                      0x0E        //  5     0   RSSI above threshold
#define MX_CC1101_GDOX_CRC_OK                             0x0F        //  5     0   CRC check passed
#define MX_CC1101_GDOX_RX_HARD_DATA1                      0x16        //  5     0   direct access to demodulated data
#define MX_CC1101_GDOX_RX_HARD_DATA0                      0x17        //  5     0   direct access to demodulated data
#define MX_CC1101_GDOX_PA_PD                              0x1B        //  5     0   power amplifier circuit is powered down
#define MX_CC1101_GDOX_LNA_PD                             0x1C        //  5     0   low-noise amplifier circuit is powered down
#define MX_CC1101_GDOX_RX_SYMBOL_TICK                     0x1D        //  5     0   direct access to symbol tick of received data
#define MX_CC1101_GDOX_WOR_EVNT0                          0x24        //  5     0   wake-on-radio event 0
#define MX_CC1101_GDOX_WOR_EVNT1                          0x25        //  5     0   wake-on-radio event 1
#define MX_CC1101_GDOX_CLK_256                            0x26        //  5     0   256 Hz clock
#define MX_CC1101_GDOX_CLK_32K                            0x27        //  5     0   32 kHz clock
#define MX_CC1101_GDOX_CHIP_RDYN                          0x29        //  5     0    (default for GDO2)
#define MX_CC1101_GDOX_XOSC_STABLE                        0x2B        //  5     0
#define MX_CC1101_GDOX_HIGH_Z                             0x2E        //  5     0   high impedance state (default for GDO1)
#define MX_CC1101_GDOX_HW_TO_0                            0x2F        //  5     0
#define MX_CC1101_GDOX_CLOCK_XOSC_1                       0x30        //  5     0   crystal oscillator clock: f = f(XOSC)/1
#define MX_CC1101_GDOX_CLOCK_XOSC_1_5                     0x31        //  5     0                             f = f(XOSC)/1.5
#define MX_CC1101_GDOX_CLOCK_XOSC_2                       0x32        //  5     0                             f = f(XOSC)/2
#define MX_CC1101_GDOX_CLOCK_XOSC_3                       0x33        //  5     0                             f = f(XOSC)/3
#define MX_CC1101_GDOX_CLOCK_XOSC_4                       0x34        //  5     0                             f = f(XOSC)/4
#define MX_CC1101_GDOX_CLOCK_XOSC_6                       0x35        //  5     0                             f = f(XOSC)/6
#define MX_CC1101_GDOX_CLOCK_XOSC_8                       0x36        //  5     0                             f = f(XOSC)/8
#define MX_CC1101_GDOX_CLOCK_XOSC_12                      0x37        //  5     0                             f = f(XOSC)/12
#define MX_CC1101_GDOX_CLOCK_XOSC_16                      0x38        //  5     0                             f = f(XOSC)/16
#define MX_CC1101_GDOX_CLOCK_XOSC_24                      0x39        //  5     0                             f = f(XOSC)/24
#define MX_CC1101_GDOX_CLOCK_XOSC_32                      0x3A        //  5     0                             f = f(XOSC)/32
#define MX_CC1101_GDOX_CLOCK_XOSC_48                      0x3B        //  5     0                             f = f(XOSC)/48
#define MX_CC1101_GDOX_CLOCK_XOSC_64                      0x3C        //  5     0                             f = f(XOSC)/64
#define MX_CC1101_GDOX_CLOCK_XOSC_96                      0x3D        //  5     0                             f = f(XOSC)/96
#define MX_CC1101_GDOX_CLOCK_XOSC_128                     0x3E        //  5     0                             f = f(XOSC)/128
#define MX_CC1101_GDOX_CLOCK_XOSC_192                     0x3F        //  5     0                             f = f(XOSC)/192 (default for GDO0)

// MX_CC1101_REG_FIFOTHR
#define MX_CC1101_ADC_RETENTION_OFF                       0b00000000  //  6     6   do not retain ADC settings in sleep mode (default)
#define MX_CC1101_ADC_RETENTION_ON                        0b01000000  //  6     6   retain ADC settings in sleep mode
#define MX_CC1101_RX_ATTEN_0_DB                           0b00000000  //  5     4   Rx attenuation: 0 dB (default)
#define MX_CC1101_RX_ATTEN_6_DB                           0b00010000  //  5     4                   6 dB
#define MX_CC1101_RX_ATTEN_12_DB                          0b00100000  //  5     4                   12 dB
#define MX_CC1101_RX_ATTEN_18_DB                          0b00110000  //  5     4                   18 dB
#define MX_CC1101_FIFO_THR_TX_61_RX_4                     0b00000000  //  3     0   TX fifo threshold: 61, RX fifo threshold: 4
#define MX_CC1101_FIFO_THR_TX_33_RX_32                    0b00000111  //  3     0   TX fifo threshold: 33, RX fifo threshold: 32
#define MX_CC1101_FIFO_THR_TX_1_RX_64                     0b00001111  //  3     0   TX fifo threshold: 1, RX fifo threshold: 64
#define MX_CC1101_FIFO_THRESH_TX                          33
#define MX_CC1101_FIFO_THRESH_RX                          32

// MX_CC1101_REG_SYNC1
#define MX_CC1101_SYNC_WORD_MSB                           0xD3        //  7     0   sync word MSB

// MX_CC1101_REG_SYNC0
#define MX_CC1101_SYNC_WORD_LSB                           0x91        //  7     0   sync word LSB

// MX_CC1101_REG_PKTCTRL1
#define MX_CC1101_PQT                                     0x00        //  7     5   preamble quality threshold
#define MX_CC1101_CRC_AUTOFLUSH_OFF                       0b00000000  //  3     3   automatic Rx FIFO flush on CRC check fail: disabled (default)
#define MX_CC1101_CRC_AUTOFLUSH_ON                        0b00001000  //  3     3                                              enabled
#define MX_CC1101_APPEND_STATUS_OFF                       0b00000000  //  2     2   append 2 status bytes to packet: disabled
#define MX_CC1101_APPEND_STATUS_ON                        0b00000100  //  2     2                                    enabled (default)
#define MX_CC1101_ADR_CHK_NONE                            0b00000000  //  1     0   address check: none (default)
#define MX_CC1101_ADR_CHK_NO_BROADCAST                    0b00000001  //  1     0                  without broadcast
#define MX_CC1101_ADR_CHK_SINGLE_BROADCAST                0b00000010  //  1     0                  broadcast address 0x00
#define MX_CC1101_ADR_CHK_DOUBLE_BROADCAST                0b00000011  //  1     0                  broadcast addresses 0x00 and 0xFF

// MX_CC1101_REG_PKTCTRL0
#define MX_CC1101_WHITE_DATA_OFF                          0b00000000  //  6     6   data whitening: disabled
#define MX_CC1101_WHITE_DATA_ON                           0b01000000  //  6     6                   enabled (default)
#define MX_CC1101_PKT_FORMAT_NORMAL                       0b00000000  //  5     4   packet format: normal (FIFOs)
#define MX_CC1101_PKT_FORMAT_SYNCHRONOUS                  0b00010000  //  5     4                  synchronous serial
#define MX_CC1101_PKT_FORMAT_RANDOM                       0b00100000  //  5     4                  random transmissions
#define MX_CC1101_PKT_FORMAT_ASYNCHRONOUS                 0b00110000  //  5     4                  asynchronous serial
#define MX_CC1101_CRC_OFF                                 0b00000000  //  2     2   CRC disabled
#define MX_CC1101_CRC_ON                                  0b00000100  //  2     2   CRC enabled (default)
#define MX_CC1101_LENGTH_CONFIG_FIXED                     0b00000000  //  1     0   packet length: fixed
#define MX_CC1101_LENGTH_CONFIG_VARIABLE                  0b00000001  //  1     0                  variable (default)
#define MX_CC1101_LENGTH_CONFIG_INFINITE                  0b00000010  //  1     0                  infinite

// MX_CC1101_REG_ADDR
#define MX_CC1101_DEVICE_ADDR                             0x00        //  7     0   device address

// MX_CC1101_REG_CHANNR
#define MX_CC1101_CHAN                                    0x00        //  7     0   channel number

// MX_CC1101_REG_FSCTRL1
#define MX_CC1101_FREQ_IF                                 0x0F        //  4     0   IF frequency setting; f_IF = (f(XOSC) / 2^10) * CC1101_FREQ_IF

// CC1101_REG_FSCTRL0
#define MX_CC1101_FREQOFF                                 0x00        //  7     0   base frequency offset (2s-compliment)

// MX_CC1101_REG_FREQ2 + REG_FREQ1 + REG_FREQ0
#define MX_CC1101_FREQ_MSB                                0x1E        //  5     0   base frequency setting: f_carrier = (f(XOSC) / 2^16) * FREQ
#define MX_CC1101_FREQ_MID                                0xC4        //  7     0       where f(XOSC) = 26 MHz
#define MX_CC1101_FREQ_LSB                                0xEC        //  7     0             FREQ = 3-byte value of FREQ registers

// MX_CC1101_REG_MDMCFG4
#define MX_CC1101_CHANBW_E                                0b10000000  //  7     6   channel bandwidth: BW_channel = f(XOSC) / (8 * (4 + CHANBW_M)*2^CHANBW_E) [Hz]
#define MX_CC1101_CHANBW_M                                0b00000000  //  5     4       default value for 26 MHz crystal: 203 125 Hz
#define MX_CC1101_DRATE_E                                 0x0C        //  3     0   symbol rate: R_data = (((256 + DRATE_M) * 2^DRATE_E) / 2^28) * f(XOSC) [Baud]

// MX_CC1101_REG_MDMCFG3
#define MX_CC1101_DRATE_M                                 0x22        //  7     0   default value for 26 MHz crystal: 115 051 Baud

// MX_CC1101_REG_MDMCFG2
#define MX_CC1101_DEM_DCFILT_OFF                          0b10000000  //  7     7   digital DC filter: disabled
#define MX_CC1101_DEM_DCFILT_ON                           0b00000000  //  7     7                      enabled - only for data rates above 250 kBaud (default)
#define MX_CC1101_MOD_FORMAT_2_FSK                        0b00000000  //  6     4   modulation format: 2-FSK (default)
#define MX_CC1101_MOD_FORMAT_GFSK                         0b00010000  //  6     4                      GFSK
#define MX_CC1101_MOD_FORMAT_ASK_OOK                      0b00110000  //  6     4                      ASK/OOK
#define MX_CC1101_MOD_FORMAT_4_FSK                        0b01000000  //  6     4                      4-FSK
#define MX_CC1101_MOD_FORMAT_MFSK                         0b01110000  //  6     4                      MFSK - only for data rates above 26 kBaud
#define MX_CC1101_MANCHESTER_EN_OFF                       0b00000000  //  3     3   Manchester encoding: disabled (default)
#define MX_CC1101_MANCHESTER_EN_ON                        0b00001000  //  3     3                        enabled
#define MX_CC1101_SYNC_MODE_NONE                          0b00000000  //  2     0   synchronization: no preamble/sync
#define MX_CC1101_SYNC_MODE_15_16                         0b00000001  //  2     0                    15/16 sync word bits
#define MX_CC1101_SYNC_MODE_16_16                         0b00000010  //  2     0                    16/16 sync word bits (default)
#define MX_CC1101_SYNC_MODE_30_32                         0b00000011  //  2     0                    30/32 sync word bits
#define MX_CC1101_SYNC_MODE_NONE_THR                      0b00000100  //  2     0                    no preamble sync, carrier sense above threshold
#define MX_CC1101_SYNC_MODE_15_16_THR                     0b00000101  //  2     0                    15/16 sync word bits, carrier sense above threshold
#define MX_CC1101_SYNC_MODE_16_16_THR                     0b00000110  //  2     0                    16/16 sync word bits, carrier sense above threshold
#define MX_CC1101_SYNC_MODE_30_32_THR                     0b00000111  //  2     0                    30/32 sync word bits, carrier sense above threshold

// MX_CC1101_REG_MDMCFG1
#define MX_CC1101_FEC_OFF                                 0b00000000  //  7     7   forward error correction: disabled (default)
#define MX_CC1101_FEC_ON                                  0b10000000  //  7     7                             enabled - only for fixed packet length
#define MX_CC1101_NUM_PREAMBLE_2                          0b00000000  //  6     4   number of preamble bytes: 2
#define MX_CC1101_NUM_PREAMBLE_3                          0b00010000  //  6     4                             3
#define MX_CC1101_NUM_PREAMBLE_4                          0b00100000  //  6     4                             4 (default)
#define MX_CC1101_NUM_PREAMBLE_6                          0b00110000  //  6     4                             6
#define MX_CC1101_NUM_PREAMBLE_8                          0b01000000  //  6     4                             8
#define MX_CC1101_NUM_PREAMBLE_12                         0b01010000  //  6     4                             12
#define MX_CC1101_NUM_PREAMBLE_16                         0b01100000  //  6     4                             16
#define MX_CC1101_NUM_PREAMBLE_24                         0b01110000  //  6     4                             24
#define MX_CC1101_CHANSPC_E                               0x02        //  1     0   channel spacing: df_channel = (f(XOSC) / 2^18) * (256 + CHANSPC_M) * 2^CHANSPC_E [Hz]

// MX_CC1101_REG_MDMCFG0
#define MX_CC1101_CHANSPC_M                               0xF8        //  7     0   default value for 26 MHz crystal: 199 951 kHz

// MX_CC1101_REG_DEVIATN
#define MX_CC1101_DEVIATION_E                             0b01000000  //  6     4   frequency deviation: f_dev = (f(XOSC) / 2^17) * (8 + DEVIATION_M) * 2^DEVIATION_E [Hz]
#define MX_CC1101_DEVIATION_M                             0b00000111  //  2     0       default value for 26 MHz crystal: +- 47 607 Hz
#define MX_CC1101_MSK_PHASE_CHANGE_PERIOD                 0x07        //  2     0   phase change symbol period fraction: 1 / (MSK_PHASE_CHANGE_PERIOD + 1)

// MX_CC1101_REG_MCSM2
#define MX_CC1101_RX_TIMEOUT_RSSI_OFF                     0b00000000  //  4     4   Rx timeout based on RSSI value: disabled (default)
#define MX_CC1101_RX_TIMEOUT_RSSI_ON                      0b00010000  //  4     4                                   enabled
#define MX_CC1101_RX_TIMEOUT_QUAL_OFF                     0b00000000  //  3     3   check for sync word on Rx timeout
#define MX_CC1101_RX_TIMEOUT_QUAL_ON                      0b00001000  //  3     3   check for PQI set on Rx timeout
#define MX_CC1101_RX_TIMEOUT_OFF                          0b00000111  //  2     0   Rx timeout: disabled (default)
#define MX_CC1101_RX_TIMEOUT_MAX                          0b00000000  //  2     0               max value (actual value depends on WOR_RES, EVENT0 and f(XOSC))

// MX_CC1101_REG_MCSM1
#define MX_CC1101_CCA_MODE_ALWAYS                         0b00000000  //  5     4   clear channel indication: always
#define MX_CC1101_CCA_MODE_RSSI_THR                       0b00010000  //  5     4                             RSSI below threshold
#define MX_CC1101_CCA_MODE_RX_PKT                         0b00100000  //  5     4                             unless receiving packet
#define MX_CC1101_CCA_MODE_RSSI_THR_RX_PKT                0b00110000  //  5     4                             RSSI below threshold unless receiving packet (default)
#define MX_CC1101_RXOFF_IDLE                              0b00000000  //  3     2   next mode after packet reception: idle (default)
#define MX_CC1101_RXOFF_FSTXON                            0b00000100  //  3     2                                     FSTxOn
#define MX_CC1101_RXOFF_TX                                0b00001000  //  3     2                                     Tx
#define MX_CC1101_RXOFF_RX                                0b00001100  //  3     2                                     Rx
#define MX_CC1101_TXOFF_IDLE                              0b00000000  //  1     0   next mode after packet transmission: idle (default)
#define MX_CC1101_TXOFF_FSTXON                            0b00000001  //  1     0                                        FSTxOn
#define MX_CC1101_TXOFF_TX                                0b00000010  //  1     0                                        Tx
#define MX_CC1101_TXOFF_RX                                0b00000011  //  1     0                                        Rx

// MX_CC1101_REG_MCSM0
#define MX_CC1101_FS_AUTOCAL_NEVER                        0b00000000  //  5     4   automatic calibration: never (default)
#define MX_CC1101_FS_AUTOCAL_IDLE_TO_RXTX                 0b00010000  //  5     4                          every transition from idle to Rx/Tx
#define MX_CC1101_FS_AUTOCAL_RXTX_TO_IDLE                 0b00100000  //  5     4                          every transition from Rx/Tx to idle
#define MX_CC1101_FS_AUTOCAL_RXTX_TO_IDLE_4TH             0b00110000  //  5     4                          every 4th transition from Rx/Tx to idle
#define MX_CC1101_PO_TIMEOUT_COUNT_1                      0b00000000  //  3     2   number of counter expirations before CHP_RDYN goes low: 1 (default)
#define MX_CC1101_PO_TIMEOUT_COUNT_16                     0b00000100  //  3     2                                                           16
#define MX_CC1101_PO_TIMEOUT_COUNT_64                     0b00001000  //  3     2                                                           64
#define MX_CC1101_PO_TIMEOUT_COUNT_256                    0b00001100  //  3     2                                                           256
#define MX_CC1101_PIN_CTRL_OFF                            0b00000000  //  1     1   pin radio control: disabled (default)
#define MX_CC1101_PIN_CTRL_ON                             0b00000010  //  1     1                      enabled
#define MX_CC1101_XOSC_FORCE_OFF                          0b00000000  //  0     0   do not force XOSC to remain on in sleep (default)
#define MX_CC1101_XOSC_FORCE_ON                           0b00000001  //  0     0   force XOSC to remain on in sleep

// MX_CC1101_REG_FOCCFG
#define MX_CC1101_FOC_BS_CS_GATE_OFF                      0b00000000  //  5     5   do not freeze frequency compensation until CS goes high
#define MX_CC1101_FOC_BS_CS_GATE_ON                       0b00100000  //  5     5   freeze frequency compensation until CS goes high (default)
#define MX_CC1101_FOC_PRE_K                               0b00000000  //  4     3   frequency compensation loop gain before sync word: K
#define MX_CC1101_FOC_PRE_2K                              0b00001000  //  4     3                                                      2K
#define MX_CC1101_FOC_PRE_3K                              0b00010000  //  4     3                                                      3K (default)
#define MX_CC1101_FOC_PRE_4K                              0b00011000  //  4     3                                                      4K
#define MX_CC1101_FOC_POST_K                              0b00000000  //  2     2   frequency compensation loop gain after sync word: same as FOC_PRE
#define MX_CC1101_FOC_POST_K_2                            0b00000100  //  2     2                                                     K/2 (default)
#define MX_CC1101_FOC_LIMIT_NO_COMPENSATION               0b00000000  //  1     0   frequency compensation saturation point: no compensation - required for ASK/OOK
#define MX_CC1101_FOC_LIMIT_BW_CHAN_8                     0b00000001  //  1     0                                            +- BW_chan/8
#define MX_CC1101_FOC_LIMIT_BW_CHAN_4                     0b00000010  //  1     0                                            +- BW_chan/4 (default)
#define MX_CC1101_FOC_LIMIT_BW_CHAN_2                     0b00000011  //  1     0                                            +- BW_chan/2

// MX_CC1101_REG_BSCFG
#define MX_CC1101_BS_PRE_KI                               0b00000000  //  7     6   clock recovery integral gain before sync word: Ki
#define MX_CC1101_BS_PRE_2KI                              0b01000000  //  7     6                                                  2Ki (default)
#define MX_CC1101_BS_PRE_3KI                              0b10000000  //  7     6                                                  3Ki
#define MX_CC1101_BS_PRE_4KI                              0b11000000  //  7     6                                                  4Ki
#define MX_CC1101_BS_PRE_KP                               0b00000000  //  5     4   clock recovery proportional gain before sync word: Kp
#define MX_CC1101_BS_PRE_2KP                              0b00010000  //  5     4                                                      2Kp
#define MX_CC1101_BS_PRE_3KP                              0b00100000  //  5     4                                                      3Kp (default)
#define MX_CC1101_BS_PRE_4KP                              0b00110000  //  5     4                                                      4Kp
#define MX_CC1101_BS_POST_KI                              0b00000000  //  3     3   clock recovery integral gain after sync word: same as BS_PRE
#define MX_CC1101_BS_POST_KI_2                            0b00001000  //  3     3                                                 Ki/2 (default)
#define MX_CC1101_BS_POST_KP                              0b00000000  //  2     2   clock recovery proportional gain after sync word: same as BS_PRE
#define MX_CC1101_BS_POST_KP_1                            0b00000100  //  2     2                                                     Kp (default)
#define MX_CC1101_BS_LIMIT_NO_COMPENSATION                0b00000000  //  1     0   data rate compensation saturation point: no compensation
#define MX_CC1101_BS_LIMIT_3_125                          0b00000001  //  1     0                                            +- 3.125 %
#define MX_CC1101_BS_LIMIT_6_25                           0b00000010  //  1     0                                            +- 6.25 %
#define MX_CC1101_BS_LIMIT_12_5                           0b00000011  //  1     0                                            +- 12.5 %

// MX_CC1101_REG_AGCCTRL2
#define MX_CC1101_MAX_DVGA_GAIN_0                         0b00000000  //  7     6   reduce maximum available DVGA gain: no reduction (default)
#define MX_CC1101_MAX_DVGA_GAIN_1                         0b01000000  //  7     6                                       disable top gain setting
#define MX_CC1101_MAX_DVGA_GAIN_2                         0b10000000  //  7     6                                       disable top two gain setting
#define MX_CC1101_MAX_DVGA_GAIN_3                         0b11000000  //  7     6                                       disable top three gain setting
#define MX_CC1101_LNA_GAIN_REDUCE_0_DB                    0b00000000  //  5     3   reduce maximum LNA gain by: 0 dB (default)
#define MX_CC1101_LNA_GAIN_REDUCE_2_6_DB                  0b00001000  //  5     3                               2.6 dB
#define MX_CC1101_LNA_GAIN_REDUCE_6_1_DB                  0b00010000  //  5     3                               6.1 dB
#define MX_CC1101_LNA_GAIN_REDUCE_7_4_DB                  0b00011000  //  5     3                               7.4 dB
#define MX_CC1101_LNA_GAIN_REDUCE_9_2_DB                  0b00100000  //  5     3                               9.2 dB
#define MX_CC1101_LNA_GAIN_REDUCE_11_5_DB                 0b00101000  //  5     3                               11.5 dB
#define MX_CC1101_LNA_GAIN_REDUCE_14_6_DB                 0b00110000  //  5     3                               14.6 dB
#define MX_CC1101_LNA_GAIN_REDUCE_17_1_DB                 0b00111000  //  5     3                               17.1 dB
#define MX_CC1101_MAGN_TARGET_24_DB                       0b00000000  //  2     0   average amplitude target for filter: 24 dB
#define MX_CC1101_MAGN_TARGET_27_DB                       0b00000001  //  2     0                                        27 dB
#define MX_CC1101_MAGN_TARGET_30_DB                       0b00000010  //  2     0                                        30 dB
#define MX_CC1101_MAGN_TARGET_33_DB                       0b00000011  //  2     0                                        33 dB (default)
#define MX_CC1101_MAGN_TARGET_36_DB                       0b00000100  //  2     0                                        36 dB
#define MX_CC1101_MAGN_TARGET_38_DB                       0b00000101  //  2     0                                        38 dB
#define MX_CC1101_MAGN_TARGET_40_DB                       0b00000110  //  2     0                                        40 dB
#define MX_CC1101_MAGN_TARGET_42_DB                       0b00000111  //  2     0                                        42 dB

// MX_CC1101_REG_AGCCTRL1
#define MX_CC1101_AGC_LNA_PRIORITY_LNA2                   0b00000000  //  6     6   LNA priority setting: LNA2 first
#define MX_CC1101_AGC_LNA_PRIORITY_LNA                    0b01000000  //  6     6                         LNA first (default)
#define MX_CC1101_CARRIER_SENSE_REL_THR_OFF               0b00000000  //  5     4   RSSI relative change to assert carrier sense: disabled (default)
#define MX_CC1101_CARRIER_SENSE_REL_THR_6_DB              0b00010000  //  5     4                                                 6 dB
#define MX_CC1101_CARRIER_SENSE_REL_THR_10_DB             0b00100000  //  5     4                                                 10 dB
#define MX_CC1101_CARRIER_SENSE_REL_THR_14_DB             0b00110000  //  5     4                                                 14 dB
#define MX_CC1101_CARRIER_SENSE_ABS_THR                   0x00        //  3     0   RSSI threshold to assert carrier sense in 2s compliment, Thr = MAGN_TARGET + CARRIER_SENSE_ABS_TH [dB]

// MX_CC1101_REG_AGCCTRL0
#define MX_CC1101_HYST_LEVEL_NONE                         0b00000000  //  7     6   AGC hysteresis level: none
#define MX_CC1101_HYST_LEVEL_LOW                          0b01000000  //  7     6                         low
#define MX_CC1101_HYST_LEVEL_MEDIUM                       0b10000000  //  7     6                         medium (default)
#define MX_CC1101_HYST_LEVEL_HIGH                         0b11000000  //  7     6                         high
#define MX_CC1101_WAIT_TIME_8_SAMPLES                     0b00000000  //  5     4   AGC wait time: 8 samples
#define MX_CC1101_WAIT_TIME_16_SAMPLES                    0b00010000  //  5     4                  16 samples (default)
#define MX_CC1101_WAIT_TIME_24_SAMPLES                    0b00100000  //  5     4                  24 samples
#define MX_CC1101_WAIT_TIME_32_SAMPLES                    0b00110000  //  5     4                  32 samples
#define MX_CC1101_AGC_FREEZE_NEVER                        0b00000000  //  3     2   freeze AGC gain: never (default)
#define MX_CC1101_AGC_FREEZE_SYNC_WORD                    0b00000100  //  3     2                    when sync word is found
#define MX_CC1101_AGC_FREEZE_MANUAL_A                     0b00001000  //  3     2                    manually freeze analog control
#define MX_CC1101_AGC_FREEZE_MANUAL_AD                    0b00001100  //  3     2                    manually freeze analog and digital control
#define MX_CC1101_FILTER_LENGTH_8                         0b00000000  //  1     0   averaging length for channel filter: 8 samples
#define MX_CC1101_FILTER_LENGTH_16                        0b00000001  //  1     0                                        16 samples (default)
#define MX_CC1101_FILTER_LENGTH_32                        0b00000010  //  1     0                                        32 samples
#define MX_CC1101_FILTER_LENGTH_64                        0b00000011  //  1     0                                        64 samples
#define MX_CC1101_ASK_OOK_BOUNDARY_4_DB                   0b00000000  //  1     0   ASK/OOK decision boundary: 4 dB
#define MX_CC1101_ASK_OOK_BOUNDARY_8_DB                   0b00000001  //  1     0                              8 dB (default)
#define MX_CC1101_ASK_OOK_BOUNDARY_12_DB                  0b00000010  //  1     0                              12 dB
#define MX_CC1101_ASK_OOK_BOUNDARY_16_DB                  0b00000011  //  1     0                              16 dB

// MX_CC1101_REG_WOREVT1 + REG_WOREVT0
#define MX_CC1101_EVENT0_TIMEOUT_MSB                      0x87        //  7     0   EVENT0 timeout: t_event0 = (750 / f(XOSC)) * EVENT0_TIMEOUT * 2^(5 * WOR_RES) [s]
#define MX_CC1101_EVENT0_TIMEOUT_LSB                      0x6B        //  7     0       default value for 26 MHz crystal: 1.0 s

// MX_CC1101_REG_WORCTRL
#define MX_CC1101_RC_POWER_UP                             0b00000000  //  7     7   power up RC oscillator
#define MX_CC1101_RC_POWER_DOWN                           0b10000000  //  7     7   power down RC oscillator
#define MX_CC1101_EVENT1_TIMEOUT_4                        0b00000000  //  6     4   EVENT1 timeout: 4 RC periods
#define MX_CC1101_EVENT1_TIMEOUT_6                        0b00010000  //  6     4                   6 RC periods
#define MX_CC1101_EVENT1_TIMEOUT_8                        0b00100000  //  6     4                   8 RC periods
#define MX_CC1101_EVENT1_TIMEOUT_12                       0b00110000  //  6     4                   12 RC periods
#define MX_CC1101_EVENT1_TIMEOUT_16                       0b01000000  //  6     4                   16 RC periods
#define MX_CC1101_EVENT1_TIMEOUT_24                       0b01010000  //  6     4                   24 RC periods
#define MX_CC1101_EVENT1_TIMEOUT_32                       0b01100000  //  6     4                   32 RC periods
#define MX_CC1101_EVENT1_TIMEOUT_48                       0b01110000  //  6     4                   48 RC periods (default)
#define MX_CC1101_RC_CAL_OFF                              0b00000000  //  3     3   disable RC oscillator calibration
#define MX_CC1101_RC_CAL_ON                               0b00001000  //  3     3   enable RC oscillator calibration (default)
#define MX_CC1101_WOR_RES_1                               0b00000000  //  1     0   EVENT0 resolution: 1 period (default)
#define MX_CC1101_WOR_RES_2_5                             0b00000001  //  1     0                      2^5 periods
#define MX_CC1101_WOR_RES_2_10                            0b00000010  //  1     0                      2^10 periods
#define MX_CC1101_WOR_RES_2_15                            0b00000011  //  1     0                      2^15 periods

// MX_CC1101_REG_FREND1
#define MX_CC1101_LNA_CURRENT                             0x01        //  7     6   front-end LNA PTAT current output adjustment
#define MX_CC1101_LNA2MIX_CURRENT                         0x01        //  5     4   front-end PTAT output adjustment
#define MX_CC1101_LODIV_BUF_CURRENT_RX                    0x01        //  3     2   Rx LO buffer current adjustment
#define MX_CC1101_MIX_CURRENT                             0x02        //  1     0   mixer current adjustment

// MX_CC1101_REG_FREND0
#define MX_CC1101_LODIV_BUF_CURRENT_TX                    0x01        //  5     4   Tx LO buffer current adjustment
#define MX_CC1101_PA_POWER                                0x00        //  2     0   set power amplifier power according to PATABLE

// MX_CC1101_REG_FSCAL3
#define MX_CC1101_CHP_CURR_CAL_OFF                        0b00000000  //  5     4   disable charge pump calibration
#define MX_CC1101_CHP_CURR_CAL_ON                         0b00100000  //  5     4   enable charge pump calibration (default)
#define MX_CC1101_FSCAL3                                  0x09        //  3     0   charge pump output current: I_out = I_0 * 2^(FSCAL3/4) [A]

// MX_CC1101_REG_FSCAL2
#define MX_CC1101_VCO_CORE_LOW                            0b00000000  //  5     5   VCO: low (default)
#define MX_CC1101_VCO_CORE_HIGH                           0b00100000  //  5     5        high
#define MX_CC1101_FSCAL2                                  0x0A        //  4     0   VCO current result/override

// MX_CC1101_REG_FSCAL1
#define MX_CC1101_FSCAL1                                  0x20        //  5     0   capacitor array setting for coarse VCO tuning

// MX_CC1101_REG_FSCAL0
#define MX_CC1101_FSCAL0                                  0x0D        //  6     0   frequency synthesizer calibration setting

// MX_CC1101_REG_RCCTRL1
#define MX_CC1101_RCCTRL1                                 0x41        //  6     0   RC oscillator configuration

// MX_CC1101_REG_RCCTRL0
#define MX_CC1101_RCCTRL0                                 0x00        //  6     0   RC oscillator configuration

// MX_CC1101_REG_PTEST
#define MX_CC1101_TEMP_SENS_IDLE_OFF                      0x7F        //  7     0   temperature sensor will not be available in idle mode (default)
#define MX_CC1101_TEMP_SENS_IDLE_ON                       0xBF        //  7     0   temperature sensor will be available in idle mode

// MX_CC1101_REG_TEST0
#define MX_CC1101_VCO_SEL_CAL_OFF                         0b00000000  //  1     1   disable VCO selection calibration stage
#define MX_CC1101_VCO_SEL_CAL_ON                          0b00000010  //  1     1   enable VCO selection calibration stage

// MX_CC1101_REG_PARTNUM
#define MX_CC1101_PARTNUM                                 0x00

// MX_CC1101_REG_VERSION
#define MX_CC1101_VERSION_CURRENT                         0x14
#define MX_CC1101_VERSION_LEGACY                          0x04
#define MX_CC1101_VERSION_CLONE                           0x17

// MX_CC1101_REG_MARCSTATE
#define MX_CC1101_MARC_STATE_SLEEP                        0x00        //  4     0   main radio control state: sleep
#define MX_CC1101_MARC_STATE_IDLE                         0x01        //  4     0                             idle
#define MX_CC1101_MARC_STATE_XOFF                         0x02        //  4     0                             XOFF
#define MX_CC1101_MARC_STATE_VCOON_MC                     0x03        //  4     0                             VCOON_MC
#define MX_CC1101_MARC_STATE_REGON_MC                     0x04        //  4     0                             REGON_MC
#define MX_CC1101_MARC_STATE_MANCAL                       0x05        //  4     0                             MANCAL
#define MX_CC1101_MARC_STATE_VCOON                        0x06        //  4     0                             VCOON
#define MX_CC1101_MARC_STATE_REGON                        0x07        //  4     0                             REGON
#define MX_CC1101_MARC_STATE_STARTCAL                     0x08        //  4     0                             STARTCAL
#define MX_CC1101_MARC_STATE_BWBOOST                      0x09        //  4     0                             BWBOOST
#define MX_CC1101_MARC_STATE_FS_LOCK                      0x0A        //  4     0                             FS_LOCK
#define MX_CC1101_MARC_STATE_IFADCON                      0x0B        //  4     0                             IFADCON
#define MX_CC1101_MARC_STATE_ENDCAL                       0x0C        //  4     0                             ENDCAL
#define MX_CC1101_MARC_STATE_RX                           0x0D        //  4     0                             RX
#define MX_CC1101_MARC_STATE_RX_END                       0x0E        //  4     0                             RX_END
#define MX_CC1101_MARC_STATE_RX_RST                       0x0F        //  4     0                             RX_RST
#define MX_CC1101_MARC_STATE_TXRX_SWITCH                  0x10        //  4     0                             TXRX_SWITCH
#define MX_CC1101_MARC_STATE_RXFIFO_OVERFLOW              0x11        //  4     0                             RXFIFO_OVERFLOW
#define MX_CC1101_MARC_STATE_FSTXON                       0x12        //  4     0                             FSTXON
#define MX_CC1101_MARC_STATE_TX                           0x13        //  4     0                             TX
#define MX_CC1101_MARC_STATE_TX_END                       0x14        //  4     0                             TX_END
#define MX_CC1101_MARC_STATE_RXTX_SWITCH                  0x15        //  4     0                             RXTX_SWITCH
#define MX_CC1101_MARC_STATE_TXFIFO_UNDERFLOW             0x16        //  4     0                             TXFIFO_UNDERFLOW

// MX_CC1101_REG_WORTIME1 + REG_WORTIME0
#define MX_CC1101_WORTIME_MSB                             0x00        //  7     0   WOR timer value
#define MX_CC1101_WORTIME_LSB                             0x00        //  7     0

// MX_CC1101_REG_PKTSTATUS
#define MX_CC1101_CRC_OK                                  0b10000000  //  7     7   CRC check passed
#define MX_CC1101_CRC_ERROR                               0b00000000  //  7     7   CRC check failed
#define MX_CC1101_CS                                      0b01000000  //  6     6   carrier sense
#define MX_CC1101_PQT_REACHED                             0b00100000  //  5     5   preamble quality reached
#define MX_CC1101_CCA                                     0b00010000  //  4     4   channel clear
#define MX_CC1101_SFD                                     0b00001000  //  3     3   start of frame delimiter - sync word received
#define MX_CC1101_GDO2_ACTIVE                             0b00000100  //  2     2   GDO2 is active/asserted
#define MX_CC1101_GDO0_ACTIVE                             0b00000001  //  0     0   GDO0 is active/asserted


/* -- Types --------------------------------------------------------------- */

typedef struct {
    uint8_t IOCFG2;     //@00h : GDO2 Output Pin Configuration
    uint8_t IOCFG1;     //@01h : GDO1 Output Pin Configuration
    uint8_t IOCFG0;     //@02h : GDO0 Output Pin Configuration
    uint8_t FIFOTHR;    //@03h : RX FIFO and TX FIFO Thresholds
    uint8_t SYNC1;      //@04h : Sync Word, High Byte
    uint8_t SYNC0;      //@05h : Sync Word, Low Byte
    uint8_t PKTLEN;     //@06h : Packet Length
    uint8_t PKTCTRL1;   //@07h : Packet Automation Control
    uint8_t PKTCTRL0;   //@08h : Packet Automation Control
    uint8_t ADDR;       //@09h : Device Address
    uint8_t CHANNR;     //@0Ah : Channel Number
    uint8_t FSCTRL1;    //@0Bh : Frequency Synthesizer Control
    uint8_t FSCTRL0;    //@0Ch : Frequency Synthesizer Control
    uint8_t FREQ2;      //@0Dh : Frequency Control Word, High Byte
    uint8_t FREQ1;      //@0Eh : Frequency Control Word, Middle Byte
    uint8_t FREQ0;      //@0Fh : Frequency Control Word, Low Byte
    uint8_t MDMCFG4;    //@10h : Modem Configuration
    uint8_t MDMCFG3;    //@11h : Modem Configuration
    uint8_t MDMCFG2;    //@12h : Modem Configuration
    uint8_t MDMCFG1;    //@13h : Modem Configuration
    uint8_t MDMCFG0;    //@14h : Modem Configuration
    uint8_t DEVIATN;    //@15h : Modem Deviation Setting
    uint8_t MCSM2;      //@16h : Main Radio Control State Machine Configuration
    uint8_t MCSM1;      //@17h : Main Radio Control State Machine Configuration
    uint8_t MCSM0;      //@18h : Main Radio Control State Machine Configuration
    uint8_t FOCCFG;     //@19h : Frequency Offset Compensation Configuration
    uint8_t BSCFG;      //@1Ah : Bit Synchronization Configuration
    uint8_t AGCCTRL2;   //@1Bh : AGC Control
    uint8_t AGCCTRL1;   //@1Ch : AGC Control
    uint8_t AGCCTRL0;   //@1Dh : AGC Control
    uint8_t WOREVT1;    //@1Eh : High Byte Event0 Timeout
    uint8_t WOREVT0;    //@1Fh : Low Byte Event0 Timeout
    uint8_t WORCTRL;    //@20h : Wake On Radio Control
    uint8_t FREND1;     //@21h : Front End RX Configuration
    uint8_t FREND0;     //@22h : Front End TX Configuration
    uint8_t FSCAL3;     //@23h : Frequency Synthesizer Calibration
    uint8_t FSCAL2;     //@24h : Frequency Synthesizer Calibration
    uint8_t FSCAL1;     //@25h : Frequency Synthesizer Calibration
    uint8_t FSCAL0;     //@26h : Frequency Synthesizer Calibration
    uint8_t RCCTRL1;    //@27h : RC Oscillator Configuration
    uint8_t RCCTRL0;    //@28h : RC Oscillator Configuration
} MX_CC101_SpiRegister_t;


//GDOx config, see page 62 of datasheet
typedef enum
{
    MX_CC1101_GDO_CFG_RX_FIFO_FILLSTATE_0 = 0,
    MX_CC1101_GDO_CFG_RX_FIFO_FILLSTATE_1 = 1,
    MX_CC1101_GDO_CFG_TX_FIFO_FILLSTATE_0 = 2,
    MX_CC1101_GDO_CFG_TX_FIFO_FILLSTATE_1 = 3,
    MX_CC1101_GDO_CFG_RX_FIFO_OVERFLOW = 4,
    MX_CC1101_GDO_CFG_TX_FIFO_UNDERFLOW = 5,
    MX_CC1101_GDO_CFG_SYNC_WORD_XFER = 6,
    MX_CC1101_GDO_CFG_RX_PACKET_OK = 7,
    MX_CC1101_GDO_CFG_CLEAR_CHANNEL = 9,
    MX_CC1101_GDO_CFG_ASYNC_DATA_OUTPUT = 0x0D, //GDO1/2 only!
    MX_CC1101_GDO_CFG_CARRIER_SENSE = 0x0E,
    MX_CC1101_GDO_CFG_CHIP_READY = 0x29,
    MX_CC1101_GDO_CFG_TRISTATE = 0x2E,
    MX_CC1101_GDO_CFG_DIGITAL_0 = 0x2F,
    MX_CC1101_GDO_CFG_DIGITAL_1 = 0x6F, //inverted DIGITAL 0
} MX_CC101_GdoCfg_t;


// RX Dämpfung/Abschwächung
// Höhere Dämpfung lässt nur starke Signale durch
// Can be used to filter out weak signals
typedef enum
{
    MX_CC1101_RX_ATTENUATION_0DB = 0x00,
    MX_CC1101_RX_ATTENUATION_6DB = 0x10,
    MX_CC1101_RX_ATTENUATION_12DB = 0x20,
    MX_CC1101_RX_ATTENUATION_18DB = 0x30,
} MX_CC1101_RxAttenuation_t;


typedef enum
{
    MX_CC1101_STATUS_FIFO_TX = 0,
    MX_CC1101_STATUS_FIFO_RX = 1,
} MX_CC1101_StatusFifo_t;

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

// Use the following parameter values, if you do not use these pins!
// gdo0 = GDO_CFG_TRISTATE
// gdo2 = GDO_CFG_TRISTATE
// Use rxAttenuation = MX_CC1101_RX_ATTENUATION_0DB for most "sensitive" reception
int mx_cc1101_init(MX_CC101_GdoCfg_t gdo0, MX_CC101_GdoCfg_t gdo2, MX_CC1101_RxAttenuation_t rxAttenuation);

// 0x14 is expected
uint8_t mx_cc1101_get_chip_version(void);

// returns a 8 bit status word. 
// the upper 4 bits defines the current state - cf. MX_CC1101_STATUS_xxx
// the lower 4 bits reflects the number of bytes available in the RX fifo, resp. free in the TX fifo (saturated to 15)
uint8_t mx_cc1101_get_status(MX_CC1101_StatusFifo_t fifo);

// 1 if chip is in idle state
// 0 otherwise
int mx_cc1101_is_idle(void);

// currently, length is limited to the fifo size (64 bytes)
int mx_cc1101_transmit(uint8_t * data, size_t len);

// buffer and size may be 0 if you only want to start rx mode - for example if you want to measure rssi!
int mx_cc1101_receive(uint8_t * buffer, size_t size);
int mx_cc1101_receive_async(void); //output data on GDO2 pin (requires MX_CC1101_GDO_CFG_ASYNC_DATA_OUTPUT config)

// get rssi in dB
// must be called in rx mode only
// to prevent rx overflow state, you must read the received data manually, or set rxflush = true, to drop them away silently
int mx_cc1101_get_rssi(uint32_t rxflush);

// go to idle state
void mx_cc1101_close(void);

/* -- Implementation ------------------------------------------------------ */



#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
