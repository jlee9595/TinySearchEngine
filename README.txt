README

Simply build my submission by calling make in the lab4 directory (using the Makefile that I have provided inside the directory)

The assumptions that my crawler program make are that the directory that it writes files to exists already, is empty prior to calling it, and the target directory ends in a "/" when it is passed as a parameter (the directory name itself shouldn't contain any punctuation).

My program can be run with the following syntax: crawler [seed-url] [target directory] [depth]
example: crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./target/ 2
