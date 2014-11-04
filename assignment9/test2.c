#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

/*
Features:
  Scneario: Given the program will start at 1
            And there is a 1 second delay between consecutive integers
            Then the timer will will be displayed

  Scenario: Given the user enters 'Control-C'
            Then the program's display will stop
            And if the user enters 'Control-C' for a second time
            Then the program's display will start

  Scenario: Given the user enters 'Control-\'
            Then the program will terminate
*/

/*
  signal(): 
    enter here 

  alarm():
    enter here

  sigsetjmp():
    enter here

*/

static volatile sig_atomic_t quitFlag = 0;
static volatile int sigintCnt = 		0;

void err_sys (const char* message);

static void sig_handler(int signo)
{
	printf("Caught signal %d (%s)\n", signo, strsignal(signo));
	if ( signo == SIGQUIT )
		quitFlag = 1;
	sigintCnt++;
}

int main(void)
{
	int timer 	= 	1;
	sigset_t 	=	newMask, oldMask, zeroMask;

   	printSigMask(stdout, "Initial signal mask is:\n");
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGINT);
    sigaddset(&blockMask, SIGQUIT);

	if 
	while(quitFlag == 0)

}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}