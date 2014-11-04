#include <stdio.h>
#include "data.h"
#include <stdlib.h>

void err_sys (const char* message);

int main (int argc, char* argv[])
{
  if (argc < 2)
    err_sys ("missing command line argument");
  FILE* f = fopen (argv[1], "w");
  if (f == NULL)
    err_sys ("error in opening file");
  data* d = create_data ("Billy Bob", 28);
  int size = fwrite (d, sizeof(data), 1, f);
  if (size != 1)
    err_sys ("error in writing to file");
  fclose (f);
  return 0;
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}
