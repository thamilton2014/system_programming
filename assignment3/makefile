list.o: list.c
	gcc -g -Wall -std=c99 -c list.c

test_list.o: test_list.c
	gcc -g -Wall -std=c99 -c test_list.c

test_list: list.o test_list.o
	gcc -o test_list list.o test_list.o