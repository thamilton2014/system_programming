#include "bank_account.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


int is_valid_owner_name ( char* s )
{
	return s != NULL && strlen (s) > 0;
}

int is_valid_account_number ( char* s )
{
  return s != NULL && strlen (s) > 0;
}

int is_valid_balance ( float s )
{
	return s >= 0;
}

int is_valid_deposit( float s )
{
	return s > 0;
}

void err_msg ( char* message );

int is_valid_withdrawal( int s )
{
	return s > 0 && s < is_valid_balance(s);
}

account* create_account( char* a_accName, char* a_accNum, float a_accBal)
{
	account* s = NULL;
	if (is_valid_owner_name (a_accName) && is_valid_account_number (a_accNum) && is_valid_balance (a_accBal))
	{
		s = malloc (sizeof(account));
	    s -> accName = malloc ((strlen (a_accName) + 1) * sizeof(char));
	    strcpy (s -> accName, a_accName);
	    s -> accNum = malloc ((strlen (a_accNum) + 1) * sizeof(char));
	    strcpy (s -> accNum, a_accNum);
	    s -> accBal = a_accBal;
	}
	return s;
}

void display_account(account* acc)
{
	if(acc != NULL)
	{
		printf("name: %s\n", acc -> accName);
		printf("account: %s\n", acc -> accNum);
		printf("balance: %f\n", acc -> accBal);
	}
}

void deposit(account* acc, float dep)
{
	if(acc != NULL)
	{
		if(dep > 0)
		{
			acc -> accBal += dep;
		}
	}
}

void withdrawal(account* acc, float with)
{
	if(acc != NULL)
	{
		if(with < acc -> accBal)
		{
			acc -> accBal -= with;
		}
	}
}

void delete_account(account* acc)
{
	if ( acc != NULL )
	{
		if ( acc -> accName != NULL )
			free ( acc -> accName );
		if ( acc -> accNum != NULL )
			free ( acc -> accNum );
		if (acc != NULL)
		{
			free ( acc );
			printf("name: %s\n", acc -> accName);
			printf("account: %s\n", acc -> accNum);
			printf("balance: %f\n", acc -> accBal);
		}
	}
}
