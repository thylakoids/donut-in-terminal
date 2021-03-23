#include <stdio.h>

int main() {
  int slices = 17;
  int people = 2;

  // type casting
  double halfThePizza = (double)slices / people;

  printf("Pizza for each people:%f", halfThePizza);

  return 0;
}
