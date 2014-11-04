#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void err_sys (const char* message);

int main ()
{
        char buf[] = "abcde";
        int fd = creat ("temp.dat", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd < 0)
                err_sys ("error in creating file");
        int result = write (fd, buf, 3);
        if (result != 3)
                err_sys("error in write");
        result = lseek (fd, 3, SEEK_SET);
        if (result < 0)
                err_sys("error in seek");
         result = write (fd, buf, 51);
        if (result != 5)
                err_sys("error in write");;
        close (fd);
        return 0;
}

void err_sys (const char* message)
{
        printf ("%s\n", message);
        exit(0);
}
