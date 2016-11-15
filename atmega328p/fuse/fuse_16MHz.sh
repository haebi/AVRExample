avrdude -c usbasp -p m328p -C /etc/avrdude.conf -U lfuse:w:0xFF:m -U hfuse:w:0xDE:m -U efuse:w:0x05:m
