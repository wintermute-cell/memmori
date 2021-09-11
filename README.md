# memmori
This reminder uses the average life expectancy of 75 years to calculate and  
visualize both, time passed and and time remaining, until death.  
It is written in C, using the ncurses library for graphics.


![alt text](https://github.com/wintermute-cell/memmori/blob/main/memmoriscreen.png?raw=true)


## Installation
1. Clone this repo:
      ```git clone https://github.com/wintermute-cell/memmori.git```
2. Compile:
      ```gcc -lncurses -o memmori memmori.c```
3. Run with your birthdate as an argument:
      ```./memmori [00-00-0000]```
