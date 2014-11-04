#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_usr(int); /* one handler for both signals */
void err_sys (const char* message);

int main(void)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
	err_sys("can’t catch SIGUSR1");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
	err_sys("can’t catch SIGUSR2");
	for ( ; ; )
	pause();
}

static void sig_usr(int signo) /* argument is signal number */
{
	if (signo == SIGUSR1)
	printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
	printf("received SIGUSR2\n");
	else
	printf("received signal %d\n", signo);
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}
