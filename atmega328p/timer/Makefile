timer.o: dummy
	avr-gcc -mmcu=atmega328p -Os timer.cpp -o timer.o

timer: timer.o
	avr-objcopy -j .text -j .data -O ihex timer.o timer.hex

dummy:
