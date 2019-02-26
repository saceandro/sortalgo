#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayArray(int *array, int n)
{
  int i;
  for (i=0; i<n; i++)
    printf("%d ", array[i]);
  printf("\n");
}

void displayArrayDebug(int *array, int n)
{
  int i;
  for (i=0; i<n; i++)
    fprintf(stderr, "%d ", array[i]);
  fprintf(stderr, "\n");
}

int selectRandomPosition(int *target, int left, int right)
{
  return left + rand() % (right - left + 1);
}

void ternaryPartition(int* target, int left, int right, int* newleftright, int targetLen)
{
  fprintf(stderr, "partition between %d and %d\n", left, right);
  
  // Select a number between left and right at random.
  int random = selectRandomPosition(target, left, right);

  fprintf(stderr, "random: %d\n", random);
  
  // Exchange target[right] and target[random].
  int tmp = target[right];
  target[right] = target[random];
  target[random] = tmp;
  displayArrayDebug(target, targetLen);
  

  int pivot = target[right];
  int i = left-1;
  // i scans the array from the left.
  int j = right;
  // j scans the array from the right.

  int mi=left-1;
  int mj=right;
  
  for (;;)
    {
      fprintf(stderr, "i's turn\n");
      
      // Move from the left until hitting a value no less than the pivot.
      for(i++; target[i] <= pivot && i <= j && i<right; i++)
        {
          if (target[i]==pivot)
            {
              tmp = target[i];
              target[i] = target[++mi];
              target[mi] = tmp;
              fprintf(stderr, "mi: %d and i: %d is swaped\n", mi, i);
              displayArrayDebug(target, targetLen);
              
            }
        }

      fprintf(stderr, "j's turn\n");
      
      // Move from the right until hitting a value no greater than the pivot.
      for(j--; pivot <= target[j] && i <= j; j--)
        {
          if (target[i]==pivot)
            {
              tmp = target[i];
              target[i] = target[--mj];
              target[mj] = tmp;
              fprintf(stderr, "j: %d and mj: %d is swaped\n", j, mj);
              displayArrayDebug(target, targetLen);
            }
        }
// pivot=target[i]=target[j]の場合は除外されているので、もはや等号が成立することはない
      if (i >= j) break;

      // Exchange target[i] and target[j].
      tmp = target[i];
      target[i] = target[j];
      target[j] = tmp;
      fprintf(stderr, "i: %d and j: %d is swaped\n", i, j);
      displayArrayDebug(target, targetLen);
    }
  fprintf(stderr, "left: %d\tright: %d\n", j, i);
  while (mi>=left)
    {
      fprintf(stderr, "mi: %d\n", mi);
      
      tmp = target[mi];
      target[mi] = target[j];
      target[j] = tmp;
      displayArrayDebug(target, targetLen);
      mi--;
      j--;
    }
  
  while (mj<=right)
    {
      fprintf(stderr, "mj: %d\n", mj);
      
      tmp = target[mj];
      target[mj] = target[i];
      target[i] = tmp;
      displayArrayDebug(target, targetLen);
      mj++;
      i++;
    }
  
  newleftright[0] = j;
  newleftright[1] = i;

  
}

void randomQuickSort1(int* target, int left, int right, int targetLen ) 
{
  int newleftright[2];
  if (left < right) 
    {
      ternaryPartition(target, left, right, newleftright, targetLen);
      // i: Position of the pivot.
      randomQuickSort1(target, left, newleftright[0], targetLen);
      randomQuickSort1(target, newleftright[1], right, targetLen);
    }
}

int isSorted(int* target, int targetLen)
{
  int i=0;
  while (i<targetLen-1)
    {
      if (target[i] > target[i+1])
        return 0;
      i++;
    }
  return 1;
}

int sameElements(int* target, int* posTarget, int targetLen, int max)
{
  int *targetCount = (int*) calloc(max+1, sizeof(int));
  int *posTargetCount = (int*) calloc(max+1, sizeof(int));
  int i;
  for (i=0; i<targetLen; i++)
    {
      targetCount[target[i]]++;
      posTargetCount[posTarget[i]]++;
    }
  for (i=0; i<=max; i++)
    {
      if (targetCount[i] != posTargetCount[i])
        {
          free(targetCount);
          free(posTargetCount);
          return 0;
        }
    }
  free(targetCount);
  free(posTargetCount);
  return 1;
}

int main(int argc, char** argv)
{
  int m = 100, n=20, max=100, i, j;
  
  int *target = (int*) calloc(n, sizeof(int));
  int *posTarget = (int*) calloc(n, sizeof(int));
  
  srand((unsigned) time(NULL));

  for (j=0; j<m; j++)
    {
      for (i=0; i<n; i++)
        target[i] = posTarget[i] = rand() % max;

      displayArray(target, n);
  
      randomQuickSort1(target, 0, n-1, n);

      displayArray(target, n);
      if (sameElements(target, posTarget, n, max) && isSorted(target, n))
        printf("ok\n");
      else
        printf("Bug!!!!!!!");
    }
      free(target);
      free(posTarget);
  return 0;
}
