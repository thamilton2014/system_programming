bank_account.o: bank_account.h bank_account.c
	gcc -g -Wall -c bank_account.c

test_bank_account.o: bank_account.h test_bank_account.c
	gcc -g -Wall -c test_bank_account.c

test_bank_account: bank_account.o test_bank_account.o
	gcc -g -o test_bank_account test_bank_account.o bank_account.o