#include "data.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

data* create_data (char* n, int a)
{
  assert (n != NULL);
  data* d = malloc (sizeof(data));
  if (d != NULL)
  {
    strncpy (d -> name, n, NAMESIZE - 1);
    d -> age = a;
  }
  return d;
}

void display_data (data* d)
{
  assert (d != NULL);
  printf ("name: %s\tage: %d\n", d -> name, d -> age);
}

