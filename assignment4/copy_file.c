#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 50

void err_sys (const char* message);

int main ()
{
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
              // S_IRWXU  00700 user (file owner) has read, write and execute permission

              // S_IRUSR  00400 user has read permission

              // S_IWUSR  00200 user has write permission

              // S_IXUSR  00100 user has execute permission

              // S_IRWXG  00070 group has read, write and execute permission

              // S_IRGRP  00040 group has read permission

              // S_IWGRP  00020 group has write permission

              // S_IXGRP  00010 group has execute permission

              // S_IRWXO  00007 others have read, write and execute permission

              // S_IROTH  00004 others have read permission

              // S_IWOTH  00002 others have write permission

              // S_IXOTH  00001 others have execute permission
