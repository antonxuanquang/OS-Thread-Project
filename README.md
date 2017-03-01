#Thread Lab

Part 1: Token Identifier
------------------------
Introduction:  Write a program that specifies where a token is consonant, vowel, or another type. The order of tokens should not be changed in the console. The program can't use mutexas or semaphores. It should use sched_yield() instead.

#Compile
To compile the program:
```
make
```

#Usage:
Run program:
```
./osp2a TCU Mens basketball overall standings is 15 wins and 10 losses
```

Result print out to the console:
```
CONSONANT: TCU
CONSONANT: Mens
CONSONANT: basketball
VOWEL: overall
CONSONANT: standings
VOWEL: is
OTHER: 15
CONSONANT: wins
VOWEL: and
OTHER: 10
CONSONANT: losses
```


Part 2: Connect Four Solution Validator
---------------------------------------
Introduction: This program will try to validate a snapshot of a Connect Four board (6x7) and determine where it has a winning solution. The program should use a total of 15 threads: 6 threads for 6 rows, 7 threads for 7 columns, and 2 threads for 2 diagonals. 

The program assumes that input file is correct and valid. There is no error checking in the program.

#Compile
To compile the program:
```
make
```

Run program:
```
./osp2b t1.txt
```

You can run the program with multiple input files
```
./osp2b t1.txt t2.txt t3.txt
```