input.o: dummy
	avr-gcc -mmcu=atmega328p -Os input.cpp -o input.o

input: input.o
	avr-objcopy -j .text -j .data -O ihex input.o input.hex

dummy:
