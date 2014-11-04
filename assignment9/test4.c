#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>

void err_sys (const char* message);

static void sig_quit(int);

static void sig_int(int);

static void sig_alarm(int);

static jmp_buf alarm_jmp;

int main(void)
{
  // sigset_t newmask, oldmask, pendmask;
  int timer   =   1; 

  if(signal(SIGALRM, sig_alarm) == SIG_ERR)
    err_sys("alarm signal error");
  if (sigsetjmp(alarm_jmp, 1) != 0)
  {
    timer++;
    printf ("%d\n", timer);
    alarm(1);
    
    if (signal(SIGQUIT, sig_quit) == SIG_ERR)
      err_sys("can't catch SIGQUIT");
    if (signal(SIGINT, sig_int) == SIG_ERR)
      err_sys("can''t catch SIGINT");
  }
  /*
   * Block SIGQUIT and save current signal mask.
   */
  // sigemptyset(&newmask);
  // sigaddset(&newmask, SIGINT);
  // if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
  //   err_sys("SIG_BLOCK error");

  // sleep(5);	/* SIGQUIT here will remain pending */

  // if (sigpending(&pendmask) < 0)
  //   err_sys("sigpending error");
  // if (sigismember(&pendmask, SIGINT))
  //   printf("\nSIGINT pending\n");

  /*
   * Restore signal mask which unblocks SIGQUIT.
   */
  // if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
  //   err_sys("SIG_SETMASK error");
  // printf("SIGINT unblocked\n");

  // sleep(5);	/* SIGQUIT here will terminate with core file */
  while(1);
  exit(0);
}

static void sig_alarm (int signo)
{
  siglongjmp (alarm_jmp, 1);
}

static void sig_int(int signo)
{
  printf("caught SIGINT\n");
  // if (signal(SIGINT, SIG_DFL) == SIG_ERR)
  //   err_sys("can't reset SIGINT");
  if (signal(SIGTSTP, SIG_DFL) == SIG_ERR)
    err_sys("can't reset SIGTSTP");
}

static void sig_quit(int signo)
{
  printf("caught SIGQUIT\n");
  if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
    err_sys("can't reset SIGQUIT");
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}