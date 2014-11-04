#include <stdio.h>
#include "data.h"
#include <stdlib.h>
#include <string.h>

void err_sys (const char* message);

int main (int argc, char* argv[])
{
  if (argc < 4)
    err_sys ("missing command line argument");
  if ( strcmp(argv[1], "add"))
  {
      add_data();
  }
  else if ( strcmp(argv[1], "report"))
  {
      report_data();
  }
  else
      delete_data();  

  data* d = create_data (argv[3], price, qty);
  int size = fwrite (d, sizeof(data), 1, f);
  if (size != 1)
    err_sys ("error in writing to file");
  fclose (f);

  double price;
  sscanf(argv[4], "%lf", &price);
  int qty;
  sscanf(argv[5], "%i", &qty);

  if (argv[2] == "add"){
    add_data(argv[3], price, qty);
  }
  else if (argv[2] == "report"){
    report_data();
    status("Items are being reported");
    int size = fread (&d, sizeof(data), 1, f);
  if (size != 1)
    err_sys ("error in reading from file");
  else
    display_data (&d);
  fclose (f);
  }
  else
    delete_data();
    status("Items are being deleted");
  return 0;
}

void status (const char* message){
  printf ("%s\n", message);
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}


