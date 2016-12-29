ledblink.o: dummy
	avr-gcc -mmcu=attiny2313a -Os ledblink.cpp -o ledblink.o

ledblink: ledblink.o
	avr-objcopy -j .text -j .data -O ihex ledblink.o ledblink.hex

dummy:
