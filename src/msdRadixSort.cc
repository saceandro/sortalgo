#include <stdio.h>
#include <stdlib.h>

void displayArray(int *array, int n)
{
  int i;
  for (i=0; i<n; i++)
    printf("%d ", array[i]);
  printf("\n");
}

int digit(int num, int j, int m)
{
  int quotient = num;
  int remainder = 0;

  for(int i=0; i<j; i++)
    {
      remainder = quotient%m;
      quotient = quotient/m;
    }

  return remainder;
}

int maxDigit(int* target, int targetLen, int m)
{
  // Compute the max and set maxDigit to its number of digits.
  int max = target[0];

  //配列の最大値を求める
  for(int i=1; i<targetLen; i++)
    {
      if(max < target[i]) max = target[i];
    }

  //配列の最大値は何桁か?
  int maxD = 0;

  for(; max > 0; maxD++)
    {
      max = max/m;
    }
  return maxD;
}

void msdRadixSortSub(int* target, int left, int right, int m, int currdig, int maxDig)
{
  // Array for counting numbers in the significant digit.
  int* count = (int*)calloc(m, sizeof(int));
  if (count==NULL)
    {
      perror("calloc");
      exit(EXIT_FAILURE);
    }

  int* count2 = (int*)calloc(m, sizeof(int));
  if (count2==NULL)
    {
      perror("calloc");
      exit(EXIT_FAILURE);
    }

  int* tmp = (int*)calloc(right-left+1, sizeof(int));
  if (tmp==NULL)
    {
      perror("calloc");
      exit(EXIT_FAILURE);
    }
  
  for(int i = left; i <= right; i++)
    count[digit(target[i], currdig, m)]++;

  count2[0] = count[0];
  for(int i=1; i<m; i++)
    count2[i] = count[i] = count[i-1] + count[i];
  
  // Scan the input array from the tail, and
  // insert each element in the proper position in tmp.
  for(int i = right; left <= i; i--)
    // Putting -- before count decrements count first.
    tmp[ --count[digit(target[i], currdig, m)] ] = target[i];
  free(count);
  
  for (int i=0; i<=right-left; i++)
    target[i+left] = tmp[i];
  free(tmp);

  if (currdig>1)
    {
      if (count2[0] > 1)
        msdRadixSortSub(target, left, count2[0]-1, m, currdig-1, maxDig);

      for (int i=0; i<m-1; i++)
        if (count2[i+1] > count2[i]+1)
          msdRadixSortSub(target, left+count2[i], left+count2[i+1]-1, m, currdig-1, maxDig);
    }
  free(count2);
}

void msdRadixSort(int* target, int targetLen, int m)
{
  // All elements are assumed to be nonnegative integers.
  int maxDig = maxDigit(target, targetLen, m);
  msdRadixSortSub(target, 0, targetLen-1, m, maxDig, maxDig);
}

int main(int argc, char** argv)
{
  int m, n, i;
  printf("radix?: ");
  scanf("%d", &m);

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
  
  msdRadixSort(target, n, m);

  displayArray(target, n);
  free(target);
  return 0;
}
