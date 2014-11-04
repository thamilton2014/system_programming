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

static void sig_alarm (int signo);

void err_sys (const char* message);

void sig_handler(int signo);

static jmp_buf alarm_jmp;

volatile sig_atomic_t quitflag; /* set nonzero by signal handler */

static void sig_int(int signo)  /* one signal handler for SIGINT and SIGQUIT */
{
  if (signo == SIGINT)
    printf("\ninterrupt\n");
  else if (signo == SIGQUIT)
    quitflag = 1; /* set flag for main loop */
}

int main (void)
{
  sigset_t  newmask, oldmask, zeromask;

  int time_left = 1;

  if (signal (SIGALRM, sig_alarm) == SIG_ERR)
    err_sys ("alarm signal error");

  alarm (1);

  if (sigsetjmp (alarm_jmp, 1) != 0)
  {
    time_left++;
    printf ("%d\n", time_left);

    if (signal(SIGINT, sig_int) == SIG_ERR)
      err_sys("signal(SIGINT) error");
    if (signal(SIGQUIT, sig_int) == SIG_ERR)
      err_sys("signal(SIGQUIT) error");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
  /*
     * Block SIGQUIT and save current signal mask.
     */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
      err_sys("SIG_BLOCK error");

    while (quitflag == 0)
      sigsuspend(&zeromask);

    /*
     * SIGQUIT has been caught and is now blocked; do whatever.
     */
    quitflag = 0;

    /*
     * Reset signal mask which unblocks SIGQUIT.
     */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
      err_sys("SIG_SETMASK error");

    alarm (1);
  }

  while (1);
  exit(0);
}

static void sig_alarm (int signo)
{
  siglongjmp (alarm_jmp, 1);
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}