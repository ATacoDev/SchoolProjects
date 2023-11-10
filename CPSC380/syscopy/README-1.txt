README

Jaden Johnson
ID: 2405823
Email: Jadjohnson@chapman.edu
CPSC-380 Section 2
Programming Assignment 1

Submission of syscopy.c & README.txt

Compilation command: gcc syscopy.c -o syscopy -Wno-deprecated 
Run command: ./syscopy inputFile.txt outputFile.txt  

Current Errors/Bugs/Notes:

 -Wno-deprecated is there because otherwise, at least on my system, I get warnings because it wants me
 to use a separate version of macOS

References:
- Tyler Edwards

- https://stackoverflow.com/questions/13459602/how-can-i-get-rid-of-deprecated-warnings-in-deprecated-functions-in-gcc
    Learning how to get rid of deprecated warnings when compiling

- https://jameshfisher.com/2018/02/19/how-to-syscall-in-c/
    Clarify difference between using read() vs syscall(SYS_read)

- https://dextutor.com/write-read-system-call/
    Learning how to use C syntax

- https://www.geeksforgeeks.org/compiling-a-c-program-behind-the-scenes/
    Learning how to compile in C

-  https://linuxhint.com/c-language-o_donly-o_wrongly-and-o_rdwr-flags/
    Different open() flags

SAMPLE OUTPUTS:

Success:
./syscopy inputFile.txt outputFile.txt  
Successful Copy!

Error on input file:
./syscopy inputile.txt outputFile.txt 
Error opening inputFile. Error code: 2

Error on number of arguments given on command line:
./syscopy inputFile.txt outputFile.txt other
Invalid number of arguments. Error code: 0

Error on output file already existing:
./syscopy inputFile.txt outputFile.txt     
Output file already exists! Please specify new name
