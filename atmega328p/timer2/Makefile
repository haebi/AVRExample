timer2.o: dummy
	avr-gcc -mmcu=atmega328p -Os timer2.cpp -o timer2.o

timer2: timer2.o
	avr-objcopy -j .text -j .data -O ihex timer2.o timer2.hex

dummy:
