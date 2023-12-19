database : driver.o argument.o allocator.o
	gcc -Wall driver.o argument.o allocator.o -o database

driver.o : driver.c argument.o
	gcc -Wall -c driver.c -o driver.o

argument.o : argument.c argument.h allocator.o
	gcc -Wall -c argument.c -o argument.o

allocator.o : allocator.c allocator.h common.h
	gcc -Wall -c allocator.c -o allocator.o

clean : 
	rm *.o database
	clear
