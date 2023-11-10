README

Jaden Johnson
ID: 2405823
Email: Jadjohnson@chapman.edu
CPSC-350 Section 1
The Mario Project

Submission of Hero.cpp, Hero.h, input.txt, output.txt, main.cpp, Mario(executable), README, World.cpp, World.h
*As well as World.o* (I think this is from a g++ -c of a file, but not going to delete just in case)

Compilation command: g++ -o Mario *.cpp
Run command: ./Mario input.txt output.txt

Current Errors/Bugs/Notes:
 Ok so there's only a couple -

 1) There is a rare case in smaller grids (4x4 and smaller), where Mario will go through a warp portal, and then spawn right on
 top of the boss and then replace his spot. This only happens occasionally, and this causes mario to endlessly wander around the level
 and interact until there is nothing left. This is RARE, but causes the program to run infinitely with Mario being lost forever xD
      EDIT: From my testing, everything with a 5x5 grid or bigger has never run into this issue.

 2) Possible issues with the grid is 2x2 or smaller, in which obviously, there is not enough space for both the Hero, Warp, and Boss.
 Not sure if you will be looking for that, but at least the Hero should spawn in always!

That's it from my knowledge :)


References:
- Received help with srand from Prof. Stevens, to ensure that rand() generation was purely random every single time.

- Received help with taking input from a file, it was bugging out and I needed a different solution
    Link: https://stackoverflow.com/questions/3946558/c-read-from-text-file-and-separate-into-variable
