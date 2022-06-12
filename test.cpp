
#include "IndexOutOfBound.h"
#include "Matrix.h"

int main() {
  // throw IndexOutOfBound(1, 2);
  Matrix<int> m1(2,2);
  Matrix<int> m2(2,2);
  Matrix<int> m3 = m1 + m2;
  return 0;
}