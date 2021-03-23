#include <stdio.h>

int main() {
  // implicit type conversion - promotion

  float x = 50.0f;

  printf("%f", x); // printf takes a double
  // x is PROMOTED

  return 0;
}
