#include <stdio.h>

int main() {
  int radius;
  printf("Please enter a radius:");
  scanf("%i", &radius);
  double area = 3.14159 * (radius * radius);
  printf("%f\n", area);
  return 0;
}
