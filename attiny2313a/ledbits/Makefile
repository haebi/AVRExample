ledbits.o: dummy
	avr-gcc -mmcu=attiny2313a -Os ledbits.cpp -o ledbits.o

ledbits: ledbits.o
	avr-objcopy -j .text -j .data -O ihex ledbits.o ledbits.hex

dummy:
