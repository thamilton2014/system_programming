#include <stdio.h>
#include <stdlib.h>

void err_sys (const char* message);

int main ()
{
  int ch;
  int done = 0;
  do
  {
    ch = getc (stdin);
    if (ch == EOF)
      if (ferror (stdin))
	err_sys ("input error");
      else
	done = 1;
    else
    {
      int result = putc (ch, stdout);
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
