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

int selectRandomPosition(int *target, int left, int right)
{
  return left + rand() % (right - left + 1);
}

void ternaryPartition(int* target, int left, int right, int* newleftright)
{
  // Select a number between left and right at random.
  int random = selectRandomPosition(target, left, right);

  // Exchange target[right] and target[random].
  int tmp = target[right];
  target[right] = target[random];
  target[random] = tmp;

  int pivot = target[right];
  int i = left-1;
  // i scans the array from the left.
  int j = right;
  // j scans the array from the right.

  int mi=left-1;
  int mj=right;
  
  for (;;)
    {
      // Move from the left until hitting a value no less than the pivot.
      for(i++; target[i] <= pivot && i <= j && i<right; i++)
        {
          if (target[i]==pivot)
            {
              tmp = target[i];
              target[i] = target[++mi];
              target[mi] = tmp;
            }
        }

      // Move from the right until hitting a value no greater than the pivot.
      for(j--; pivot <= target[j] && i <= j; j--)
        {
          if (target[i]==pivot)
            {
              tmp = target[i];
              target[i] = target[--mj];
              target[mj] = tmp;
            }
        }
// pivot=target[i]=target[j]の場合は除外されているので、もはや等号が成立することはない
      if (i >= j) break;

      // Exchange target[i] and target[j].
      tmp = target[i];
      target[i] = target[j];
      target[j] = tmp;
    }

  while (mi>=left)
    {
      tmp = target[mi];
      target[mi] = target[j];
      target[j] = tmp;
      mi--;
      j--;
    }
  
  while (mj<=right)
    {
      tmp = target[mj];
      target[mj] = target[i];
      target[i] = tmp;
      mj++;
      i++;
    }
  newleftright[0] = j;
  newleftright[1] = i;
}

void ternaryQuickSort1(int* target, int left, int right)
{
  int newleftright[2];
  if (left < right) 
    {
      ternaryPartition(target, left, right, newleftright);
      ternaryQuickSort1(target, left, newleftright[0]);
      ternaryQuickSort1(target, newleftright[1], right);
    }
}

void ternaryQuickSort2(int* target, int aLeft, int right)
{
  int newleftright[2];
  int left = aLeft;
  while (left < right)
    {
      ternaryPartition(target, left, right, newleftright);
      ternaryQuickSort2(target, left, newleftright[0]);
      left = newleftright[1];
    }
}

void ternaryQuickSort3(int* target, int aLeft, int aRight)
{
  // process shorter interval first to avoid stack overflow
  int newleftright[2];
  int left = aLeft;
  int right = aRight;
  while (left < right)
    {
      ternaryPartition(target, left, right, newleftright);
      if (newleftright[0] - left <= right - newleftright[1])
        {
          // left interval is shorter
          ternaryQuickSort3(target, left, newleftright[0]);
          left = newleftright[1];
        }
      else
        {
          // right interval is shorter
          ternaryQuickSort3(target, newleftright[1], right);
          right = newleftright[0];
        }
    }
}

void slip(int *target, int left, int right)
{
  int tmp = target[right];
  for (; right>left; right--)
    target[right] = target[right-1];
  target[left] = tmp;
}

void insertionSort(int *target, int left, int right)
{
  int i, j=left+1;
  while (j<=right)
    {
      i = j - 1;
      if (target[i] <= target[j])
        {
          j++;
          continue;
        }
      while (i>=left && target[j] < target[i])
        i--;
      
      slip(target, i+1, j);
      j++;
    }
}

void ternaryQuickSort4(int* target, int aLeft, int aRight, int minSize)
{
  int left = aLeft;
  int right = aRight;
  int newleftright[2];
  while (left + minSize < right)
    {
      ternaryPartition(target, left, right, newleftright);
      if (newleftright[0] - left <= right - newleftright[1])
        {
          // left interval is shorter
          ternaryQuickSort4(target, left, newleftright[0], minSize);
          left = newleftright[1];
        }
      else
        {
          // right interval is shorter
          ternaryQuickSort4(target, newleftright[1], right, minSize);
          right = newleftright[0];
        }
    }
  // switch to insertion sort when interval become short
  insertionSort(target, left, right);
}

void ternaryQuickSort5sub(int* target, int aLeft, int aRight, int minSize)
{
  int left = aLeft;
  int right = aRight;
  int newleftright[2];
  while (left + minSize < right)
    {
      ternaryPartition(target, left, right, newleftright);
      if (newleftright[0] - left <= right - newleftright[1])
        {
          // left interval is shorter
          ternaryQuickSort5sub(target, left, newleftright[0], minSize);
          left = newleftright[1];
        }
      else
        {
          // right interval is shorter
          ternaryQuickSort5sub(target, newleftright[1], right, minSize);
          right = newleftright[0];
        }
    }
}

void ternaryQuickSort5(int* target, int left, int right, int minSize)
{
  ternaryQuickSort5sub(target, left, right, minSize);
  // insertion sort is effective because there is no big data movement
  insertionSort(target, left, right);
}

int main(int argc, char** argv)
{
  int n, i, minSize=10;

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
  
  ternaryQuickSort5(target, 0, n-1, minSize);

  displayArray(target, n);
  
  return 0;
}
