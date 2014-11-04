#include <stdio.h>
#include <stdlib.h>

void err_sys (const char* message);

int main ()
{
  int ch;
  while ((ch = getc(stdin)) != EOF)
  {
    int result = putc (ch, stdout);
    if (result == EOF)
      err_sys ("output error");
  }
  if (ferror (stdin))
    err_sys ("input error");
  return 0;
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}
