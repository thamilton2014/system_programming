#include "stdio.h"
#include <stdlib.h>

#define	MAXLINE	4096			/* max line length */

void err_exit (const char* message);

int main(void)
{
  char	name[L_tmpnam], line[MAXLINE];
  FILE	*fp;

  printf("%s\n", tmpnam(NULL));		/* first temp name */

  tmpnam(name);					/* second temp name */
  printf("%s\n", name);

  if ((fp = tmpfile()) == NULL)		/* create temp file */
    err_exit("tmpfile error");
  fputs("one line of output\n", fp);	/* write to temp file */
  rewind(fp);				/* then read it back */
  if (fgets(line, sizeof(line), fp) == NULL)
    err_exit("fgets error");
  fputs(line, stdout);				/* print the line we wrote */

  exit(0);
}

void err_exit (const char* message)
{
  printf ("%s\n", message);
  exit(0);
}
