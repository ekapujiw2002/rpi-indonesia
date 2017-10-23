#!/bin/sh
 
	for i in *.c; do
	    echo "compiling $i"
	    gcc -ggdb -o `basename $i .c` $i ;
	done
 
