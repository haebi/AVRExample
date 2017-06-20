uart: uart.o
	avr-objcopy -j .text -j .data -O ihex uart.o uart.hex

uartio: uartio.o
	avr-objcopy -j .text -j .data -O ihex uartio.o uartio.hex

uart.o: dummy
	avr-gcc -mmcu=atmega328p -Os uart.cpp -o uart.o

uartio.o: dummy
	avr-gcc -mmcu=atmega328p -Os uartio.cpp -o uartio.o

clean:
	rm -rf *.o *.hex

dummy:
