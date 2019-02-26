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

void ternaryPartition(int* target, int* posTarget, int left, int right, int* newleftright)
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

              tmp = posTarget[i];
              posTarget[i] = posTarget[++mi];
              posTarget[mi] = tmp;
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

              tmp = posTarget[i];
              posTarget[i] = posTarget[--mj];
              posTarget[mj] = tmp;
            }
        }
// pivot=target[i]=target[j]の場合は除外されているので、もはや等号が成立することはない
      if (i >= j) break;

      // Exchange target[i] and target[j].
      tmp = target[i];
      target[i] = target[j];
      target[j] = tmp;

      tmp = posTarget[i];
      posTarget[i] = posTarget[j];
      posTarget[j] = tmp;
}

  while (mi>=left)
    {
      tmp = target[mi];
      target[mi] = target[j];
      target[j] = tmp;

      tmp = posTarget[mi];
      posTarget[mi] = posTarget[j];
      posTarget[j] = tmp;
      
      mi--;
      j--;
    }
  
  while (mj<=right)
    {
      tmp = target[mj];
      target[mj] = target[i];
      target[i] = tmp;

      tmp = posTarget[mj];
      posTarget[mj] = posTarget[i];
      posTarget[i] = tmp;

      mj++;
      i++;
    }
  newleftright[0] = j;
  newleftright[1] = i;
}

void slip(int *target, int* posTarget, int left, int right)
{
  int tmp1 = target[right];
  int tmp2 = posTarget[right];
  for (; right>left; right--)
    {
      target[right] = target[right-1];
      posTarget[right] = posTarget[right-1];
    }
  target[left] = tmp1;
  posTarget[left] = tmp2;
}

void insertionSort(int* target, int* posTarget, int left, int right)
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
      
      slip(target, posTarget, i+1, j);
      j++;
    }
}

void ternaryQuickSort5sub(int* target, int* posTarget, int aLeft, int aRight, int minSize)
{
  int left = aLeft;
  int right = aRight;
  int newleftright[2];
  while (left + minSize < right)
    {
      ternaryPartition(target, posTarget, left, right, newleftright);
      if (newleftright[0] - left <= right - newleftright[1])
        {
          // left interval is shorter
          ternaryQuickSort5sub(target, posTarget, left, newleftright[0], minSize);
          left = newleftright[1];
        }
      else
        {
          // right interval is shorter
          ternaryQuickSort5sub(target, posTarget, newleftright[1], right, minSize);
          right = newleftright[0];
        }
    }
}

void ternaryQuickSort5(int* target, int* posTarget, int left, int right, int minSize)
{
  ternaryQuickSort5sub(target, posTarget, left, right, minSize);
  // insertion sort is effective because there is no big data movement
  insertionSort(target, posTarget, left, right);
}

void binarySearch(int* target, int targetLen, int query, int minSize){
  //Sort elements in target and memorize the original positions in posTarget.
  int* posTarget = new int[targetLen];
  for(int i=0; i<targetLen; i++) posTarget[i]=i;
  ternaryQuickSort5(target, posTarget, 0, targetLen-1, minSize);

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

int base(char b)
{
  switch(b)
    {
    case 'A':
      return 0;
    case 'C':
      return 1;
    case 'G':
      return 2;
    case 'T':
      return 3;
    }
  printf("target includes non-base!\n");
  exit(EXIT_FAILURE);
}

int mer(char* str, int offset, int m)
{
  int num=0;
  for (int i=0; i<m; i++)
    num = num*4 + base(str[i+offset]);
  return num;
}

void merSearch(char* charTarget, int charTargetLen, char* query, int queryLen, int minSize)
{
  int* target = (int*) calloc(charTargetLen-queryLen+1, sizeof(int));
  for (int i=0; i<=charTargetLen-queryLen; i++)
    target[i] = mer(charTarget, i, queryLen);
  int querynum = mer(query, 0, queryLen);
  
  binarySearch(target, charTargetLen-queryLen+1, querynum, minSize);
  free(target);
}

int main(){
  int charTargetLen, queryLen, minSize=10;
  printf("target's length?: ");
  scanf("%d", &charTargetLen);
  
  char *charTarget = (char*) calloc(charTargetLen, sizeof(int));
  if (charTarget==NULL)
    {
      perror("calloc");
      exit(EXIT_FAILURE);
    }
  
  printf("target?: ");  
  scanf("%s", charTarget);
  
  srand((unsigned) time(NULL));

  printf("query's length?: ");
  scanf("%d", &queryLen);

  char *query = (char*) calloc(queryLen, sizeof(char));
  if (query==NULL)
    {
      perror("calloc");
      exit(EXIT_FAILURE);
    }
  
  printf("query?: ");
  scanf("%s", query);
  
  merSearch(charTarget, charTargetLen, query, queryLen, minSize);
  return 0;
}
