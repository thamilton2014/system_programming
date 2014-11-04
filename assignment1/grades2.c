#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

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
int calc_median (int* temp, int num_grades);
void display_median (int num_grades, int median);

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
  int median = calc_median (temp, num_grades);
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
    float var1;
    float var2;
    float squaredVar;
    float squaredAve = ave * ave;
    float sqrtVar;
    for (i = 0; i < num_grades; i++)
    {
      squaredVar += (grades[i] + grades[i]);
      var1 += squaredVar - squaredAve;
      // var += (grades[i] * grades[i]) - (2 * (grades[i] * ave)) + (ave * ave);
      // std += sqrt(((grades[i] * grades[i]) - (ave * ave)) / num_grades);
    }
    sqrtVar = sqrt(var1);
    var2 += var1 / num_grades;
    printf("Average: %f\n", ave);
    printf("Variance 1: %f\n", var1);
    printf("Variance 2: %f\n", var2);
    printf("Square Root: %f\n", sqrtVar);
    printf("std: %f\n", std);
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

int calc_median(int* temp, int num_grades)
{
  assert (temp != NULL);
  assert (num_grades >= 0);
  int median = 0;
  if (num_grades > 0)
  {
    // Need to check if num_grades is even or odd.
    int midNum = num_grades / 2;
    median = temp[midNum];
  }
  return median;
}

void display_median(int num_grades, int median)
{
  assert (num_grades >= 0);
  if (num_grades == 0)
    printf ("no data \n");
  else 
    printf ("median: %i\n", median);
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

  int f;
  for ( f = 0; f < num_grades; ++f)
  {
    printf("sorted: %i\n", grades[f]);
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