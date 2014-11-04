#include "data.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

data* create_data (char* n, double x, int c)
{
  assert (n != NULL);
  data* d = malloc (sizeof(data));
  if (d != NULL)
  {
    strncpy (d -> name, n, NAMESIZE - 1);
    d -> price = x;
    d -> count = c; 
  }
  return d;
}

void display_data (data* d)
{
  assert (d != NULL);
  printf ("%s\t%.2f\t%i = %.2f\n", d -> name, d -> price, d -> count, d -> price * d -> count);
}



