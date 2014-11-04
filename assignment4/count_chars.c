#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>


#define BUFF_SIZE 50

void count_char_in_buffer ( char* buf, int* counter, int num );


void err_sys (const char* message);

int main ()
{
  int counters[128];
  int i;
  for ( i = 0; i < 128; i++ )
          counters[i] = 0;
  char buf[BUFF_SIZE];
  int fd1 = open ( "testfile.txt", O_RDONLY,
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
  if ( fd1 < 0 )
          err_sys( "error in opening the file" );
  int fd2 = creat ( "copy.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
  if ( fd2 < 0 )
          err_sys( "error in creating the file" );
  int done = 0;
  do
  {
    int amount = read ( fd1, buf, BUFF_SIZE );
    if ( amount < 0 )
            err_sys ("read error");
    if ( amount < BUFF_SIZE)
            done = 1;
    int result;
    if ( amount > 0 )
    result = write ( fd2, buf, amount );
  if ( result != amount )
    err_sys ( "Write error");
    count_char_in_buffer ( buf, counters, amount );
  }
  while ( !done );
  close (fd1);
  close (fd2);
  return 0;
}

void err_sys (const char* message)
{
        printf ( "%s\n", message );
        exit (0);
}

void count_char_in_buffer ( char* buf, int* counter, int num)
{
  assert(buf != NULL);
  assert(counter != NULL);
  assert(num >= 0 && num <= BUFF_SIZE);
  int i = 0;
  for ( i = 0; i < num; i++) {
          counter[buf[i]]++;
          printf(counter[buf[i]]++);
  }
}
