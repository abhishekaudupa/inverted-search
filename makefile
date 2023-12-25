database : driver.o argument.o allocator.o create_index.o word_list_table.o word_list.o word_file_list.o display_index.o search_index.o save_index.o
	gcc -Wall driver.o argument.o allocator.o create_index.o word_list_table.o word_list.o word_file_list.o display_index.o search_index.o save_index.o -o database

driver.o : driver.c argument.o allocator.o word_list_table.o create_index.o display_index.o
	gcc -Wall -c driver.c -o driver.o

argument.o : argument.c argument.h allocator.o
	gcc -Wall -c argument.c -o argument.o

allocator.o : allocator.c allocator.h common.h
	gcc -Wall -c allocator.c -o allocator.o

create_index.o : create_index.c create_index.h word_list_table.o
	gcc -Wall -c create_index.c -o create_index.o

word_list_table.o : word_list_table.c word_list_table.h word_list.o allocator.o
	gcc -Wall -c word_list_table.c -o word_list_table.o

word_list.o : word_list.c word_list.h word_file_list.o allocator.o
	gcc -Wall -c word_list.c -o word_list.o

word_file_list.o : word_file_list.c word_file_list.h allocator.o
	gcc -Wall -c word_file_list.c -o word_file_list.o

display_index.o : display_index.c display_index.h word_file_list.o
	gcc -Wall -c display_index.c -o display_index.o

search_index.o : search_index.c search_index.h word_list_table.o display_index.o
	gcc -Wall -c search_index.c -o search_index.o

save_index.o : save_index.c save_index.h word_list_table.o
	gcc -Wall -c save_index.c -o save_index.o

clean : 
	rm *.o database backup.txt
	clear
