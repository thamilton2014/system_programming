#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
/************************************************
Thomas Hamilton
Professor Gayler
CS 3540 - Linux and C programming
*/

/************************************************
preconditions: num_grades is not NULL 
postconditions: num_grades points to the number of grades in the array
return: non-NULL pointer to an array of grades
*/

int* get_grades (int* num_grades);

/**********************************************************
precondition: grades is not NULL & num_grades >= 0
return: average of elements in array - 0 if array is empty
*/
float calc_ave (int* grades, int num_grades);
void display_ave (int num_grades, float ave);

/**********************************************************
Sort Grades
precondition: 
return: Sorted grades array.

*/
int* sort_grades(int* grades, int num_grades);

/**********************************************************
Calculate Median
precondition:   
return: Median of elelments in array.
*/
double calc_median (int* temp, int num_grades);
void display_median (int num_grades, double median);

/**********************************************************
Calculate Standard Deviation
precondition: 
return: Standard deviation of elelments in array.
*/
float calc_std (int* grades, float ave, int num_grades);
void display_std (int num_grades, float std);

/*************************************************
precondition: num_grades >= 0
*/

int main ()
{
  int num_grades = 0;
  int* grades = get_grades (&num_grades);
  // Calculate and Display average
  float ave = calc_ave (grades, num_grades);
  display_ave (num_grades, ave); 
  // Sort the grades
  int* temp = sort_grades(grades, num_grades);
  // Calculate and Display median 
  double median = calc_median (temp, num_grades);
  display_median (num_grades, median);
  // Calculate and Display standard deviation.
  float std = calc_std (grades, ave, num_grades);
  display_std (num_grades, std);

  return 0;
}

float calc_std(int* grades, float ave, int num_grades)
{
  assert (grades != NULL);
  assert (ave >= 0);
  assert (num_grades > 0);
  float std = 0;
  if (ave > 0){
    int i;
    for (i = 0; i < num_grades; i++)
    {
      std += pow(grades[i] - ave, 2);
    }
    std = std / num_grades;
    printf("%f\n",std);
    std = sqrt(std);
  }
  return std;
}

void display_std(int num_grades, float std)
{
  assert (num_grades >= 0);
  if (num_grades == 0)
    printf("no data \n");
  else
    printf("standard deviation: %f\n", std);
}

double calc_median(int* temp, int num_grades)
{
  assert (temp != NULL);
  assert (num_grades >= 0);
  double median = 0;
  double index_1 = 0;
  double index_2 = 0;
  index_1 = temp[(num_grades - 1) / 2];
  index_2 = temp[(num_grades + 1) / 2];
  median = (index_1 + index_2) / 2;
  return median;
}

void display_median(int num_grades, double median)
{
  assert (num_grades >= 0);
  if (num_grades == 0)
    printf ("no data \n");
  else 
    printf ("median: %f\n", median);
}

int* sort_grades(int* grades, int num_grades)
{
  assert (grades != NULL);
  int i;
  for (i = 0; i < num_grades; ++i)
  {
    int j, min, temp;
    min = i;
    for (j = i + 1; j < num_grades; ++j)
    {
      if (grades[j] < grades[min])
        min = j;
    }
    temp = grades[i];
    grades[i] = grades[min];
    grades[min] = temp;
  }
  return grades;
}

void display_ave (int num_grades, float ave)
{
  assert (num_grades >= 0);
  if (num_grades == 0)
    printf ("no data\n");
  else
    printf ("average: %f\n", ave);
}

float calc_ave (int* grades, int num_grades)
{
  assert (grades != NULL);
  assert (num_grades >= 0);
  float ave = 0;
  if (num_grades > 0)
  {
    int sum = 0;
    int i = 0;
    for (i = 0; i < num_grades; i++)
      sum += grades[i];
    ave = (float)sum / num_grades;
  }
  return ave;
}

int* get_grades (int* num_grades)
{
  assert (num_grades != NULL);
 *num_grades = 0;
  int size = 10;
  int* grades = malloc (size * sizeof (int));
  int grade;
  printf ("enter a grade: \n");
  scanf ("%d", &grade);
  while (grade >= 0)
  {
    if (*num_grades == size)
    {
      int* temp = malloc (2 * size * sizeof (int));
      int i;
      for (i = 0; i < size; i++)
  temp[i] = grades[i];
      free (grades);
      grades = temp;
      size *= 2;
    }
    grades[*num_grades] = grade;
    (*num_grades)++;
    printf ("enter a grade: \n");
    scanf ("%d", &grade);
  }
  assert (grades != NULL);
  assert (*num_grades >= 0);
  return grades;
}