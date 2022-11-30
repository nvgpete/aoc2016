#### These are solutions written in c for the Advent of Code - 2016. 
See https://adventofcode.com/2016

Each problem generally has two parts. Examples of filenames for day 3 are:
- d03a.c - solution for first part
- d03b.c - solution for second part
- d03a.txt - problem data set; the same for both parts.

Very often the files of the sort d06b.c may not exist if the two parts of
the problem were similar enough to do both in d06a.c.

There may be a file like d07notes.txt if I felt more explanation was needed,
or just felt like making general comments. Sometimes it is just additional
compilation notes.

Sometimes the problem data set files (eg. d05a.txt) do not exist because the
problem data was simple enough to be provided on the web page. Other times
it is there, but I have not attempted to read it. In either case the notes
file will give the input and my reasoning.

Sometimes there may also be a php version of the program for reasons
described in the notes.

Compilation is generally something like
gcc/clang -O3 -Wall -o d01a d01a.c
with exceptions listed in the notes. 

These are not examples of good coding style nor necessarily of good code
as they are one-offs where getting them to work quickly and correctly was the
main objective. (Though I have cleaned them up a bit to remove debugging
printfs() and such.) (Also, unlike most people, I find code with a minimum of
extraneous spaces easier to read. YMMV) Most of them are short enough and
straightforward enough to not require any comments.

## Synopsis of each days problem

```
Day  1 - Find location from directions like Left 2 blocks etc.
Day  2 - Open door lock with unusual keypad.
Day  3 - Find valid triangles with given sides.
Day  4 - Find North Pole storage room from encrypted names.
Day  5 - Generate security code from MD5 hashes starting with '00000'.
Day  6 - Extracting signal from noise by repetition.
Day  7 - Find IPv7 capabilities from patterns in strings.
Day  8 - Generate password on 50x6 pixel screen from odd operations.
Day  9 - Decompressing files.
Day 10 - Bots sorting microchips and putting them in bins.
Day 11 - Moving dangerous and fragile components to assembly area.
Day 12 - Interpret weird assembly code to find password.
Day 13 - Find distance between points in a room with pseudo random blocks.
Day 14 - Generate some one time pad values from MD5 hashes.
Day 15 - Dropping a ball through rotating slotted disks.
Day 16 - Filling small and large disks with data and finding the checksum.
Day 17 - Move through doors which are (un)locked based on MD5 hashes.
Day 18 - Finding traps and safe tiles in a room.
Day 19 - White elephant parties with odd rules.
Day 20 - Finding allowed IP's in a list of blocked ports.
Day 21 - Scrambling passwords
Day 22 - Moving some data in a grid storage to where you can get it.
Day 23 - More weird assembly code to open safe
Day 24 - Traveling salesman problem in a maze.
Day 25 - One last assembly code problem to clock antenna.
```