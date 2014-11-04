#ifndef _BANK_ACCOUNT_H
#define _BANK_ACCOUNT_H

/********** Owner **********/
typedef struct
{
	/* data */
	char* accName;
	char* accNum;
	float accBal;

} account;

/***** Owner
precondition: string is not NULL and has at least 1 character
*/
// char* accName();

/***** Account Number
precondition: string which is not NULL, has at least 1 character, all characters are digits
*/
// char* accNum();
/***** Balance
precondtion: must be non-negative
*/
// int accBal();

/********** Bank Account **********/

/***** Create Account
input: owner, initial balance, account number
output: pointer to a bank account
reutrn NULL is any input not valid
*/
account* create_account ( char* a_accName, char* a_accNum, float a_accBal );

/***** Display Account
input: pointer to a bank account
displays: all attributes of the account, format not specified
return assertion used to verify pointer to bank accounts is not NULL
*/
void display_account ( account* acc );

/***** Deposit
input: pointer to bank account (cannot be NULL) & amount of deposit (must be positive)
postcondition: amount has been added to balance
returns false if amount of deposit is not positive, true otherwise
return assertion used to verify pointer to the bank account is not NULL
*/
void deposit ( account* acc, float dep );

/***** Withdraw
input: pointer to bank account (cannot be NULL) & amount of withdrawal (must be positive 
& cannot be larger than the balance)
postcondition: amount has been subtracted from balance
returns false if amount of withdrawal is not valid, true otherwise
assertion used to verify pointer to the bank account is not NULL
*/
void withdrawal ( account* acc, float with);

/***** Delete Account
input: pointer to bank account
postcondition: all memeory allocated to the bank account has been deallocated
does nothing if input pointers are NULL
*/
void delete_account ( account* acc );

#endif