
#include "IndexOutOfBound.h"
#include "Matrix.h"

int main() {
  // throw IndexOutOfBound(1, 2);
  Matrix<int> m1(2,2);
  m1.set(0, 0, 1);
  m1.set(1, 1, 1);
  Matrix<int> m2(2,2);
  m2.set(0, 1, 2);
  m2.set(1, 0, 4);
  Matrix<int> m3(2,2);
  m3 = m1 + m2;
  return 0;
}