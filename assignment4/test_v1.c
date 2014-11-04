#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 50

void err_sys ( const char* message );

void check(char buf[]);

int main ()
{
        char buf[BUFF_SIZE];

        char temp[BUFF_SIZE];

        int fd1 = open ( "README", O_RDONLY,
                        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );

        if ( fd1 < 0 )
                err_sys( "error in opening the file" );
        int fd2 = creat ( "reversed.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );

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

        }
        while ( !done );
        close (fd1);
        close (fd2);

        

        // check(buf);
        // check(temp);

        return 0;
}

void check(char buf[]){
   printf("##### Values #####\n");
   int i;
   for ( i = 0; i < sizeof(buf); i++ ){
      printf("%c", buf[i]);
   }
}

void err_sys (const char* message)
{
        printf ( "%s\n", message );
        exit (0);
}

 // for ( i = last - 1; i >= 0; i--){

 //         printf("%s\n", temp[i]);
 //         printf("%s\n", buf[i]);
 //      }
