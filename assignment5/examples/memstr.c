#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BSZ 48

void err_exit (const char* message);

int main()
{
  char buf[BSZ];

  memset(buf, 'a', BSZ-2);
  buf[BSZ-2] = '\0';
  buf[BSZ-1] = 'X';
  FILE *fp = fmemopen(buf, BSZ, "w+");
  if (fp == NULL)
    err_exit("fmemopen failed");
  printf("initial buffer contents: %s\n", buf);
  fprintf(fp, "hello, world");
  printf("before flush: %s\n", buf);
  fflush(fp);
  printf("after fflush: %s\n", buf);
  printf("len of string in buf = %ld\n", (long)strlen(buf));

  memset(buf, 'b', BSZ-2);
  buf[BSZ-2] = '\0';
  buf[BSZ-1] = 'X';
  fprintf(fp, "hello, world");
  fseek(fp, 0, SEEK_SET);
  printf("after  fseek: %s\n", buf);
  printf("len of string in buf = %ld\n", (long)strlen(buf));

  memset(buf, 'c', BSZ-2);
  buf[BSZ-2] = '\0';
  buf[BSZ-1] = 'X';
  fprintf(fp, "hello, world");
  fclose(fp);
  printf("after fclose: %s\n", buf);
  printf("len of string in buf = %ld\n", (long)strlen(buf));

  return(0);
}

void err_exit (const char* message)
{
  printf ("%s\n", message);
  exit(0);
}
