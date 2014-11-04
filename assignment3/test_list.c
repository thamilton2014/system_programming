#include "list.h"
#include <stdio.h>

void display_list (const list* l);

int main ()
{
  list* l = create_list();
  append (l, "aaa");
  prepend (l, "bbb");
  insert (l, "ccc", 1);
  insert (l, "ddd", 3);
  remove_from_list (l, 3);
  display_list (l);
  return 0;
}

void display_list (const list* l)
{
  for (int i = 0; i < size(l); i++)
  {
    char* s = (char*)get(l,i);
    printf ("%s\n", s);
  }
}
