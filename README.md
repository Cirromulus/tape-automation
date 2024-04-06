# USB automation for a H&K tape deck

This repo is WIP. It will contain the USB bridge powered by an `rp2040` that translates USB serial commands (and reads) into the HK OneWire flavor, analyzed in [this repository](https://github.com/Cirromulus/HK-OneWire-Analyzer/).
The other part will be a python script running on the host computer that uses the Read/Write commands to automate digitizing audio data from tape or recording cool mixtapes to ... tape.

See also https://hackaday.io/project/195474-reversing-the-harmankardon-sound-system-protocol.


```
 ----------------                      ----------                           ---------------
| HOST PC        |                    |  RP2040  |    EXT Power 19v AC --> | HK Tape Deck  |
|                |                    |          | <-- HK Onewire Data --> |         -----+
|    Python lib  | <-- USB Serial --> |  Bridge  | <-- HK Onewire Busy --> |        | TAPE 
 ----------------                      ----------                           -------- ------
```
