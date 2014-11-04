#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void err_sys (const char* message);

void msg (const char* message);

void pr_siginfo(int status);

int main(void)
{
	pid_t  pid;
	int status;

	if ((pid = fork()) < 0) 
    	err_sys("waitpid error");
	else if (pid == 0) /* child */
		exit(7);
	
	if (waitpid(pid, &status, 0) < 0)	/* parent */
    	err_sys("waitpid error");
    pr_siginfo(status);

  	if (waitpid(pid, &status, 0) < 0)	/* parent */
    	err_sys("waitpid error");
	else if (pid == 0) /* child */
		abort();  /* generates SIGABRT */
	pr_siginfo(status);

  	if (waitpid(pid, &status, 0) < 0)	/* parent */
    	err_sys("waitpid error");
	pr_siginfo(status);

  	if (waitpid(pid, &status, 0) < 0)	/* parent */
    	err_sys("waitpid error");
	else if (pid == 0) /* child */
	pr_siginfo(status);

	if (waitpid(pid, &status, 0) < 0)	/* parent */
    	err_sys("waitpid error");
    pr_siginfo(status);
	exit(0);
}

void pr_siginfo(int status)
{
 if (WIFEXITED(status))
    printf("normal termination, exit status = %d\n",
	   WEXITSTATUS(status));
  else if (WIFSIGNALED(status))
printf("abnormal termination, signal number = %d%s\n",
   WTERMSIG(status),
#ifdef	WCOREDUMP
	   WCOREDUMP(status) ? " (core file generated)" : "");
#else
  "");
#endif
else if (WIFSTOPPED(status))
  printf("child stopped, signal number = %d\n",
	 WSTOPSIG(status));
}

void pr_exit(int status)
{
  if (WIFEXITED(status))
    printf("normal termination, exit status = %d\n",
	   WEXITSTATUS(status));
  else if (WIFSIGNALED(status))
    printf("abnormal termination, signal number = %d%s\n",
	   WTERMSIG(status),
#ifdef	WCOREDUMP
	   WCOREDUMP(status) ? " (core file generated)" : "");
#else
  "");
#endif
else if (WIFSTOPPED(status))
  printf("child stopped, signal number = %d\n",
	 WSTOPSIG(status));
} 

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (1);
}

void msg(const char* message)
{
	printf("%s\n", message);
}