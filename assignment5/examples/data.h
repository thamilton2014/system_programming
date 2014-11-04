#ifndef _DATA_H
#define _DATA_H

#define NAMESIZE 30

typedef struct
{
  char name[NAMESIZE];
  int age;
} data;

data* create_data (char* n, int a);

void display_data (data* d);

#endif
