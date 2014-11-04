#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

void make_temp(char *template);

void err_exit (const char* message);

int main()
{
  char	good_template[] = "/tmp/dirXXXXXX";	/* right way */
  char	*bad_template = "/tmp/dirXXXXXX";	/* wrong way*/

  printf("trying to create first temp file...\n");
  make_temp(good_template);
  printf("trying to create second temp file...\n");
  make_temp(bad_template);
  exit(0);
}

void make_temp(char *template)
{
  struct stat sbuf;
  int fd = mkstemp(template);
  if (fd < 0)
    err_exit("can't create temp file");
  printf("temp name = %s\n", template);
  close(fd);
  int result = stat(template, &sbuf);
  if ( result < 0) 
  {
    if (errno == ENOENT)
      printf("file doesn't exist\n");
    else
      err_exit("stat failed");
  } 
  else 
  {
    printf("file exists\n");
    unlink(template);
  }
}

void err_exit (const char* message)
{
  printf ("%s\n", message);
  exit(0);
}
