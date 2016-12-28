#!/bin/bash

avrdude -c usbasp -p t2313 -e -U flash:w:ledblink.hex
