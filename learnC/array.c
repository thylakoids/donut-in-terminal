#include <stdio.h>

void len(char arr[]) { printf("sizeof arr: %d", (int)sizeof(*arr)); }

int main() {
  int arr1[10];
  double arr2[] = {1, 2, 3};
  char arr3[] = "hello";
  char *p = "abxxxxxxxxxxxc";

  arr1[3] = arr2[0];

  printf("sizeof(arr1) = %d\nsizeof(arr2) = %d\nsizeof(arr3) = %d\n",
         (int)sizeof(arr1[0]), (int)sizeof(arr2[0]), (int)sizeof(arr3[0]));

  printf("%c\nsizeof(p) = %d\n%p\n", *p, (int)sizeof(p), p);
  printf("sizeof arr3: %d\n", (int)sizeof(arr3));
  len(arr3);

  return 0;
}
