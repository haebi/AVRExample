#!/bin/bash

avrdude -c usbasp -p m328p -e -U flash:w:input.hex
