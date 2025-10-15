# CC1101

Unstructured notes for CC1101.

## RadioLib

There is a *RadioLib* (found at https://github.com/jgromes/RadioLib) for a lot of radio tranceivers, incl. CC1101 out there. 
It was made for *Arduino*. For use with Raspberry PI, you need to adapt the *PiHal*.
In the "Issues" on github you can find a thread where someone copied a `PiHAL_WG.h`, to use it in combination with *WiringPi*
(which is probably more maintained than default "lower-layer" *lg* (https://abyz.me.uk/lg)).


```
git clone https://github.com/jgromes/RadioLib.git
cd RadioLib
mkdir build && cd build
cmake ..
make
sudo make install
```

Header will be installed to `/usr/local/include/RadioLib`.
A static library can be found at `/usr/local/lib/aarch64-linux-gnu/libRadioLib.a`.


## Python CC1101

See https://github.com/fphammerle/python-cc1101

```
sudo apt install pip
sudo apt install --no-install-recommends python3-spidev
pip3 install --user --upgrade cc1101
```

### Example Application

```python
import cc1101

with cc1101.CC1101() as transceiver:
    transceiver.set_base_frequency_hertz(433.92e6)
    print(transceiver)
    transceiver.transmit(b"\x01\xff\x00 message")
```

### Example CLI Usage

```bash
cc1101-transmit --help
```

```
usage: cc1101-transmit [-h] [-f BASE_FREQUENCY_HERTZ] [-r SYMBOL_RATE_BAUD]
                       [-s {no-preamble-and-sync-word,transmit-16-match-15-bits,transmit-16-match-16-bits,transmit-32-match-30-bits}]
                       [-l {fixed,variable}] [--disable-checksum] [-p SETTING [SETTING ...]] [-d]

Transmits the payload provided via standard input (stdin) ASK/OOK-modulated in big-endian bit order.

optional arguments:
  -h, --help            show this help message and exit
  -f BASE_FREQUENCY_HERTZ, --base-frequency-hertz BASE_FREQUENCY_HERTZ
  -r SYMBOL_RATE_BAUD, --symbol-rate-baud SYMBOL_RATE_BAUD
  -s {no-preamble-and-sync-word,transmit-16-match-15-bits,transmit-16-match-16-bits,transmit-32-match-30-bits}, --sync-mode {no-preamble-and-sync-word,transmit-16-match-15-bits,transmit-16-match-16-bits,transmit-32-match-30-bits}
  -l {fixed,variable}, --packet-length-mode {fixed,variable}
  --disable-checksum
  -p SETTING [SETTING ...], --output-power SETTING [SETTING ...]
                        Configures output power levels by setting PATABLE and FREND0.PA_POWER. Up to 8 bytes may be provided. For OOK modulation,
                        exactly 2 bytes must be provided: 0 to turn off the transmission for logical 0, and a level > 0 to turn on the transmission for
                        logical 1 (e.g., --output-power 0 198). See "Table 39: Optimum PATABLE Settings for Various Output Power Levels [...]" and
                        section "24 Output Power Programming".
  -d, --debug
```

```bash
printf '\x03\xC0\xD2' | cc1101-transmit -f 433920000 -r 4960 -s no-preamble-and-sync-word -l fixed --disable-checksum
```


## Other resources

- https://github.com/rmja/festivalpos/tree/master/pagers/retekess/td158
- https://github.com/meoker/pagger
- https://github.com/baycom/rps (SX1278 is a LoRA transceiver but it can also do OOK)
- https://github.com/xb8/t119bruteforcer
- https://github.com/DeiteriyLab/pager-beeper-tool
- https://github.com/francispoisson/retekess-pager-hackrf
- https://github.com/denr01/FZ-ChiefCooker
- https://github.com/denr01/FZ-ChiefCooker/blob/master/app/pager/decoder/Td157Decoder.hpp
- https://git.selfmade.ninja/zer0sec/Flipper/-/tree/main/Sub-GHz/Restaurant_Pagers/Retekess_Pagers/TD157
- https://k3xec.com/td158
