#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 50

void err_sys ( const char* message );

int main ()
{
        char buf[BUFF_SIZE];

        char temp[BUFF_SIZE];

        int result;

        int fd1 = open ( "README", O_RDONLY,
                        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
        if ( fd1 < 0 )
            err_sys( "error in opening the file" );
        
        int fd2 = creat ( "reversed.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
        if ( fd2 < 0 )
                err_sys( "error in creating the file" );

        int amount = read ( fd1, buf, BUFF_SIZE );
        if ( amount < 0 )
        	err_sys ( "read error");

    	int last = lseek ( fd1 , 0, SEEK_END);
    	if (result < 0)
    		err_sys ("error in seek");

// result = write ( fd2, temp, amount );
//                 if ( result != amount )
//                         err_sys ( "Write error");
    	int i;
    	for ( i = last - 1; i >= 0; i--){
            // result = write ( fd2, temp, amount );
            // printf("%c\n", buf[i]);
            temp[i] += buf[i];
            printf("%c\n", temp[i]);
        }



        close (fd1);
        close (fd2);
        return 0;
    }

void err_sys (const char* message)
{
        printf ( "%s\n", message );
        exit (0);
}