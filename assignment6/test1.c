#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void err_sys(const char* message);

void msg(const char* message);

void openFile();

void childProcess();

void check();

#define BUFF_SIZE 52

int main()
{
	char str[BUFF_SIZE] = "abcdefghijklmnopqrstuvwxyz";
	char str2[BUFF_SIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

		pid_t pid = fork();
		if(pid == 0)
		{
			int i;
			for(i = 0; i < sizeof(str); i++)
			{
				if((i % 2) == 0)
				{
					FILE* f = fopen ("filename.txt", "a");
	  				if (f == NULL)
	    				err_sys ("error in opening file");
					 	// int size = fwrite (str[i], sizeof(str), 1, f);
					fputc(str[i], f);
				}
			}
		}
		else
		{
			int i;
			for(i = 0; i < sizeof(str2); i++)
			{
				if((i % 2) == 1)
				{
					FILE* f = fopen ("filename.txt", "a");
	  				if (f == NULL)
	    				err_sys ("error in opening file");
					 	// int size = fwrite (str[i], sizeof(str), 1, f);
				 	fputc(str2[i], f);
				}
			}
		}
  	fclose (f);
	exit( 0 );
}

void err_sys(const char* message)
{
  printf ("%s\n", message);
  exit (0);
}

void msg(const char* message)
{
	printf ( "%s\n", message);
}

void openFile()
{
	msg("File opened.");

}

void check()
{

}