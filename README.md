This project was aimed at us exploiting a buffer overflow expolit on the original_buffer_overflow programme. A buffer overflow occurs when there is excess data filling a buffer, the excess data overwrites adjacent memory. These attacks can be used to crash the programme or to change the order that functions are executed.
This exploit was possible because of 2 vulnerabilities. 
The arrays were staticaly sized, this is not inherently vulnerable but if it is used with other functions it could lead to a buffer overflow.
The critical vulnerability was that the strcpy function was used. This functions copies data from the source to the destination without checking the bounds of buffers.

This repository contains a total of 3 files 1 file w/ commands and 2 programme files in C:
Programme files:
original_buffer_overflow.c - the vulnerable C file
secure.c - the patched version of the original_buffer_overflow.c file.

Commands:
commands_for_buffer_overflow - contains the commands used to disable security, find the memory addresses of the programme functions and calculate the size of the buffer to fill, commands used to create the payload.bin file
The third file contains the commands that were used to exploit the buffer overflow
