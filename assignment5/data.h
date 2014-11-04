#ifndef _DATA_H
#define _DATA_H

#define NAMESIZE 30

typedef struct
{
  char name[NAMESIZE];
  double price;
  int count;
} data;

data* create_data (char* n, double x, int c);

void display_data (data* d);

#endif
