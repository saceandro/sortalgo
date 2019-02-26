#include <stdio.h>
#include <stdlib.h>

void displayArray(int *array, int n)
{
  int i;
  for (i=0; i<n; i++)
    printf("%d ", array[i]);
  printf("\n");
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

int main()
{
  int n, i;

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
  
  insertionSort(target, 0, n-1);

  displayArray(target, n);
  
  return 0;

}
