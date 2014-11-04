#include <stdio.h>
#include "data.h"
#include <stdlib.h>
#include <string.h>

void err_sys (const char* message);

void delete_data_v2(char* filename, char* name);

void add_data(char* filename, data* d);

void report_data(char* filename);

void delete_data(char* filename, char* name);

int check(data* d, char* name);

int main (int argc, char* argv[])
{
  if ( strcmp(argv[2],"add") == 0 && argc == 5 )
  { 
    printf("%i\n", argc);
    double price;
    int qty;
    sscanf (argv[4], "%lf", &price);
    sscanf (argv[5], "%i", &qty);
    data* d = create_data(argv[3], price, qty);
    add_data(argv[1], d);
  }
   
  else if (strcmp(argv[2],"report") == 3)
    report_data(argv[1]);
  
  else if ( strcmp(argv[2], "delete") == 0 && argc == 4)
  delete_data(argv[1], argv[3]);

else 
  err_sys("There is something wrong with your argument count or action.");
  
  return 0;
}

void add_data (char* filename, data* d)
{

// To insert a record into the file, use one of the "dummy records" 
// (deletion occurred at that location) to store the new record.  
// If no dummy record exists, append a new record to the end of the file.

  FILE* f = fopen (filename, "a");
  if (f == NULL)
    err_sys ("error in opening file");
  int size = fwrite (d, sizeof(data), 1, f);
  if (size != 1)
    err_sys ("error in writing to file");
  fclose (f);
}

void report_data(char* filename)
{  
  FILE* f = fopen (filename, "r");
  if (f == NULL)
    err_sys ("error in opening file");
  data d;
  while(!feof(f))
  
  /**********************************************
   * This is why the last record is being displayed
   * twice.
   */
  {
    fread (&d, sizeof(d), 1, f);
    display_data(&d);
  }
  fclose (f);
}

// To delete a record from the file, change the item 
// name of the record to some "dummy name" 
// to indicate that the record has been deleted.
void delete_data( char* filename, char* name )
{
  // Open file to modify
  FILE* f1 = fopen( filename, "r+" );
  fscanf( f1, "%s", &name );

  printf( "%s\n", "Removing item..." );

  // Add a new value
  char* rmv = "Removed";
  scanf( "%s", &rmv );

  name += rmv;

  fseek( f1, 0, SEEK_SET );
  fprintf( f1, "%s", name); 
   
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}

int check(data* d, char* name)
{
  if (strcmp(d -> name, name) == 0 )
    return 1;
  return 0;
}

