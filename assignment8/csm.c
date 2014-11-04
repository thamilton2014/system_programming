#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data {
  char *name[15];
  double price;
  int count;
};

void err_sys (const char* message);

int add_data(char* filename, double price, int count);

int report_data(char* filename);

void delete_data(char* filename, char* name);

int main (int argc, char* argv[])
{
  double price;
  int qty;
  sscanf (argv[4], "%lf", &price);
  sscanf (argv[5], "%i", &qty);

  add_data(argv[3], price, qty);

  if ( strcmp(argv[2],"add") == 0 )
  {
    int result = add_data(argv[1], price, qty);
      if( result == -1)
        err_sys("Unable to add data.");
  }

  else if (strcmp(argv[2],"report") == 0) 
    report_data(argv[1]);

  else if ( strcmp(argv[2], "delete") == 0 )
    delete_data(argv[1], argv[3]);
  
  return 0;
}

int add_data (char* filename, double price, int count)
{
  struct data d;
  FILE* f = fopen (filename, "wb");

  if (!f){
    err_sys ("error in opening file");
    return -1;
  }

  fwrite (&d, sizeof(struct data), 1, f);

  fclose (f);
  return 0;
}

int report_data(char* filename)
{  
  struct data d;
  FILE* f = fopen (filename, "rb");

  if (!f){
    err_sys ("error in opening file");
      return -1;
  }
  
  while(fread(&d, sizeof(struct data), 1, f) != NULL)
  {
    printf("%s\n", d.name);
    printf("%f\n", d.price);
    printf("%i\n", d.count);
  }
  fclose(f);
  return 0;
}

void delete_data( char* filename, char* name )
{
  FILE* f1;
  FILE* f2;
  int count = 0;
  struct data d;  

  f1 = fopen( filename, "rb" );
  if(!f1)
    err_sys( "Unable to open file." );

  f2 = fopen( "temp.dat", "wb");
  if(!f2)
    err_sys( "Unable to open file.");

  while ( !fread(&d, sizeof(struct data), 1, f1)) {
      if (strcmp ( name, d.name) == 0) {
        printf("The record was found and deleted.");
        count = 1;
      } else {
        fwrite( &d, sizeof(struct data), 1, f2);
      }
    }
    if ( !count ) {
      printf("The record was not found.");
    }

    fclose(f1);
    fclose(f2);
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}
  