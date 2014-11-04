#include "bank_account.h"
#include "bank_account.c"
#include <stdlib.h>
#include <stdio.h>

int main ()
{
	account* s = create_account("Tom", "abc123", 1234.00);
	display_account(s);
	deposit(s, 45);
	display_account(s);
	withdrawal(s, 54);
	display_account(s);
	delete_account(s);
}