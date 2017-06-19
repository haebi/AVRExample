uart.o: dummy
	avr-gcc -mmcu=attiny2313a -Os uart.cpp -o uart.o

uart: uart.o
	avr-objcopy -j .text -j .data -O ihex uart.o uart.hex

dummy:
