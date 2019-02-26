#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

void displayArray(int *array, int n)
{
  int i;
  for (i=0; i<n; i++)
    printf("%d ", array[i]);
  printf("\n");
}

int selectRandomPosition(int *target, int left, int right)
{
  return left + rand() % (right - left + 1);
}

int partition(int* target, int* posTarget, int left, int right) 
{

  // Select a number between left and right at random.
  int random = selectRandomPosition(target, left, right);

  // Exchange target[right] and target[random].
  int tmp = target[right];
  target[right] = target[random];
  target[random] = tmp;

  tmp = posTarget[right];
  posTarget[right] = posTarget[random];
  posTarget[random] = tmp;

  int pivot = target[right];
  int i = left-1;
  // i scans the array from the left.
  int j = right;
  // j scans the array from the right.

  for (;;)
    {
      // Move from the left until hitting a value no less than the pivot.
      for(i++; target[i] < pivot; i++)
        {
        }

      // Move from the right until hitting a value no greater than the pivot.
      for(j--; pivot < target[j] && i < j; j--)
        {
        }

      if (i >= j) break;

      // Exchange target[i] and target[j].
      tmp = target[i];
      target[i] = target[j];
      target[j] = tmp;

      tmp = posTarget[i];
      posTarget[i] = posTarget[j];
      posTarget[j] = tmp;
    }
  
  // Exchange target[i] and target[right].
  tmp = target[i];
  target[i] = target[right];
  target[right] = tmp;

  tmp = posTarget[i];
  posTarget[i] = posTarget[right];
  posTarget[right] = tmp;
  
  return i;
}

void randomQuickSort1(int* target, int* posTarget, int left, int right ) 
{
  if (left < right) 
    {
      int i = partition(target, posTarget, left, right);
      // i: Position of the pivot.
      randomQuickSort1(target, posTarget, left, i - 1);
      randomQuickSort1(target, posTarget, i + 1, right);
    }
}

void binarySearch(int* target, int targetLen, int query ){
  //Sort elements in target and memorize the original positions in posTarget.
  int* posTarget = new int[targetLen];
  for(int i=0; i<targetLen; i++) posTarget[i]=i;
  randomQuickSort1(target, posTarget, 0, targetLen-1);

  int left, right, middle;
  // Search for the left boundary.
  for(left=0, right=targetLen; left < right; ){
    middle = (left + right) / 2;
    if( target[middle] < query) left = middle + 1;
    else right = middle;
  }

  int leftBoundary = left;
  // Search for the right boundary.
  for(left=0, right=targetLen; left < right; ){
    middle = (left + right) / 2;
    if( target[middle] <= query ) left = middle + 1;
    else right = middle;
  }
  // Print positions in the range between the two boundaries.

  if(leftBoundary >= right)
    cout << "No positions are found";
  else{
    for(int i = leftBoundary; i < right; i++) cout << posTarget[i] << " "; }
  cout << endl;
}

int main(){
  int n, q, i;
  printf("target's length?: ");
  scanf("%d", &n);
  
  int *target = (int*) calloc(n, sizeof(int));
  if (target==NULL)
    {
      perror("calloc");
      exit(EXIT_FAILURE);
    }
  
  printf("target?: ");
  
  for (i=0; i<n; i++)
    scanf("%d", &target[i]);
  
  srand((unsigned) time(NULL));

  printf("query?: ");
  scanf("%d", &q);
  binarySearch(target, n, q);
  return 0;
}
