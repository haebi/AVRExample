avrdude -c usbasp -p t2313 -C /etc/avrdude.conf -U lfuse:w:0xff:m -U hfuse:w:0xd7:m -U efuse:w:0xff:m 
