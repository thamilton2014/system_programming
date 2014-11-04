#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024

void err_sys (const char* message);

int main ()
{
  char buf[MAXLINE];
  while (fgets (buf, MAXLINE, stdin) != NULL)
    if (fputs (buf, stdout) == EOF)
      err_sys ("output error");
  if (ferror (stdin))
    err_sys ("input error");
  return 0;
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}


