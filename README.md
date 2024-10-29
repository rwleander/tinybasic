# tinyBasic - tiny basic interpreter for Arduino and ms command line

This is an implementation of a Tiny Basic interpreter written in C++ for any ESP32 board. 
The code was written first using Microsoft C++ with unit tests for each module, 
then ported to Arduino for the ESP32 board. 

Use the following commands to control the interpreter:
* NEW - erase all program code from memory,
*LIST - list the program code,
* RUN - run the program,
* LOAD - load a program (Windows only),
* SAVE - save the   program (Windows only),
*QUIT - close the program (Windows only),

Statements start with a line number followed by the basic code.
To replace a line, type that line number followed by the new code.
To delete a line, enter the line number and press 'enter'.

Statements:
* LET
* IF
* GOTO
* GOSUB / RETURN
* INPUT
* PRINT
* REM
* STOP

Functions:
ABS(n) - absolute value of n
INT(n) - integer portion of n
RND() - generate a random number
PI() pi (3.14159)
SQR(n) - square root of n

Sample program:

10 REM  SUM NUMBERS 1 TO 10
20 LET N = 0
30 LET I = 1
40 REM  START LOOP
50 LET N = N + I  
60 LET I = I + 1
70 IF I <= 10 THEN 50


Folders:
esp32 - Arduino code for ESP32 boards
windows - c++ code for windows

ESP32 folders:
tiny - Arduino sketch files


Build instructions:

For ESP32 Arduino: 
1. Connect your ESP32 board to a Windows computer,
2. Open a command window, 
3. Navigate to \tinybasic\esp32,  
4. Type the command 'build tiny',
5. After build, the code will be flashed to the ESP32 board,
6. Open your favorite  serial terminall program and hit the enter key to get a basic prompt.

For Windows:
1. Open the Visual Studio Developer Command Prompt,
2. Navigate to \tinybasic\windows,
3. Type the command 'buildtiny',
4. Type the command 'tiny' to start the interpreter.

Requirements: 
1.    Arduino command line tool,
2. The ESP32 board manager for Arduino command line,
3. Microsoft Visual Studio community edition.
