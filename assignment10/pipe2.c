#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

#define	DEF_PAGER "/bin/more"		/* default pager program */

#define	MAXLINE	4096 /* max line length */

void err_sys (const char* message);

int main(int argc, char *argv[])
{
  int n;
  int fd[2];
  pid_t	pid;
  char *pager, *argv0;
  char line[MAXLINE];
  FILE *fp;

  if (argc != 2)
    err_sys ("usage: a.out <pathname>");

  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    char buf[100];
    sprintf (buf, "can't open %s\n", argv[1]);
    err_sys(buf);
  }
  if (pipe(fd) < 0)
    err_sys("pipe error");

  if ((pid = fork()) < 0)
  {
    err_sys("fork error");
  } 
  else if (pid > 0) 
  {								/* parent */
    close(fd[0]);		/* close read end */

    /* parent copies argv[1] to pipe */
    while (fgets(line, MAXLINE, fp) != NULL)
    {
      n = strlen(line);
      if (write(fd[1], line, n) != n)
	err_sys("write error to pipe");
    }
    if (ferror(fp))
      err_sys("fgets error");

    close(fd[1]);	/* close write end of pipe for reader */

    if (waitpid(pid, NULL, 0) < 0)
      err_sys("waitpid error");
    exit(0);
  } 
  else
  {	/*   child */
    close(fd[1]);	/* close write end */
    if (fd[0] != STDIN_FILENO) 
    {
      if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
	err_sys("dup2 error to stdin");
      close(fd[0]);	/* don't need this after dup2 */
    }

    /* get arguments for execl() */
    if ((pager = getenv("PAGER")) == NULL)
      pager = DEF_PAGER;
    if ((argv0 = strrchr(pager, '/')) != NULL)
      argv0++;		/* step past rightmost slash */
    else
      argv0 = pager;	/* no slash in pager */

    if (execl(pager, argv0, (char *)0) < 0)
    {
      char buf[100];
      sprintf (buf, "execl error for %s\n", pager); 
      err_sys(buf);
    }
  }
  exit(0);
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (1);
}