#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int globvar = 6;		/* external variable in initialized data */
char buf[] = "a write to stdout\n";

void err_sys (const char* message);

int main(void)
{
  int var;		/* automatic variable on the stack */
  pid_t	pid;
  
  var = 88;
  int result = write(STDOUT_FILENO, buf, sizeof(buf)-1);
  if (result != sizeof(buf)-1)
    err_sys("write error");
  printf("before fork\n");	/* we don't flush stdout */

  pid = fork();
  if (pid < 0)
  {
    err_sys("fork error");
  }
  else if (pid == 0)
  {		/* child */
    globvar++;				/* modify variables */
    var++;
    printf ("child pid %d\n", getpid());
  }
  else
  {
    sleep(2);
    printf ("parent pid %d\n", getpid());	/* parent */
  }

  printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,
	 var);
  exit(0);
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}
