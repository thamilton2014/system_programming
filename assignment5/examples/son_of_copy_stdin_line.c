#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024

void err_sys (const char* message);

int main ()
{
  char buf[MAXLINE];
  int done = 0;
  do
  {
    char* s = fgets (buf, MAXLINE, stdin);
    if (s == NULL)
      if (ferror (stdin))
	err_sys ("input error");
      else
	done = 1;
    else
    {
      int result = fputs (buf, stdout);
      if (result == EOF)
	err_sys ("output error");
    }
  }
  while (!done);
  return 0;
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}


