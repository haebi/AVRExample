avrdude -c usbasp -p m328p -C /etc/avrdude.conf -U lfuse:w:0xff:m -U hfuse:w:0xde:m -U efuse:w:0xfd:m
