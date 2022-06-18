#include <iostream>
#include <complex>
#include "Matrix.h"
#include "testbench.h"

using namespace std;

void testcase1() {
    cout << "This is the addition test:" << endl;
    complex<double> a[] = {1.0 + 1i, 2, 3, 4, 5, 6};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {2.0 + 1i, 4, 6, 8, 10, 12};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixSrc2 = initial(3, 2, b);
    auto matrixRes1 = initial(3, 2, c);
    assertEquales(1, matrixSrc1 + matrixSrc2, matrixRes1);
}

void testcase2() {
    cout << "This is the subtraction test:" << endl;
    complex<double> a[] = {3.0 + 1i, 6, 9, 12, 15, 18};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {2.0 + 1i, 4, 6, 8, 10, 12};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixSrc2 = initial(3, 2, b);
    auto matrixRes1 = initial(3, 2, c);
    assertEquales(2, matrixSrc1 - matrixSrc2, matrixRes1);
}

void testcase3() {
    cout << "This is the test for scalarMultiplication" << endl;
    complex<double> a[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {2, 4, 6, 8, 10, 12};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixRes1 = initial(3, 2, c);
    assertEquales(3, Matrix<complex<double>>::scalarMultiplication(2, matrixSrc1),
                  matrixRes1);
}

void testcase4() {
    cout << "This is the test for scalarDivision" << endl;
    complex<double> a[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {2, 4, 6, 8, 10, 12};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixRes1 = initial(3, 2, c);
    assertEquales(4, Matrix<complex<double>>::scalarDivision(2, matrixRes1), matrixSrc1);
}

void testcase5() {
    cout << "This is the test for transposition" << endl;
    complex<double> a[] = {1, 2, 3, 4, 5, 6};
    complex<double> b[] = {1, 4, 2, 5, 3, 6};
    complex<double> c[] = {2, 4, 6, 8, 10, 12};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixRes1 = initial(2, 3, b);
    assertEquales(5, Matrix<complex<double>>::transposition(matrixSrc1), matrixRes1);
}

void tesecase6() {
    cout << "This is the test for elementMultiplication" << endl;
    complex<double> a[] = {1, 2, 3, 4, 5, 6};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 9, 16, 25, 36};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixSrc2 = initial(3, 2, b);
    auto matrixRes1 = initial(3, 2, c);
    assertEquales(6, Matrix<complex<double>>::elementMultiplication(matrixSrc1, matrixSrc2),
                  matrixRes1);
}

void testcase7() {
    cout << "This is the test for matrixMultiplication" << endl;
    complex<double> a[] = {1, 2, 3, 4, 5, 6};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 9, 16, 25, 36};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 2, d);
    assertEquales(7, Matrix<complex<double>>::matrixMultiplication(matrixSrc1, matrixSrc2),
                  matrixRes1);
}

void testcase8() {
    cout << "This is the test for vectorMultiplication" << endl;
    complex<double> a[] = {1, 2, 3, 4, 5, 6};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 9, 16, 25, 36};
    complex<double> d[] = {22, 28, 49};
    complex<double> e[] = {225, 522};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixSrc2 = initial(1, 3, d);
    auto matrixRes1 = initial(1, 2, e);
    assertEquales(8, Matrix<complex<double>>::vectorMultiplication(matrixSrc1, matrixSrc2),
                  matrixRes1);
}

void testcase9() {
    cout << "This is the test for conjugation" << endl;
    complex<double> a[] = {1, 2, 3, 4, 5, 6};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixRes1 = initial(2, 3, c);
    assertEquales(9, conjugation(matrixSrc1), matrixRes1);
}

void testcase10() {
    cout << "This is the test for dotProduct" << endl;
    complex<double> a[] = {1, 2, 3, 4, 5, 6};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {1, 4, 9, 16, 25, 36};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixSrc2 = initial(3, 2, b);
    auto matrixRes1 = initial(3, 2, d);
    assertEquales(10, Matrix<complex<double>>::dotProduct(matrixSrc1, matrixSrc2),
                  matrixRes1);
}

void testcase11() {
    cout << "This is the test for crossProduct" << endl;
    complex<double> a[] = {1, 2, 3, 4, 5, 6};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 2, d);
    assertEquales(11, Matrix<complex<double>>::crossProduct(matrixSrc1, matrixSrc2),
                  matrixRes1);
}

void testcase12() {
    cout << "This is the test for getMax" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 1, c);
    auto res = complex<double> {2342,0};
    assertEquales(12, getMax(matrixSrc1), res);
}

void testcase13() {
    cout << "This is the test for getAvg" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 1, c);
    assertEquales(13, getAvg(matrixSrc1), 398.333333333);
}

void testcase14() {
    cout << "This is the test for getSum" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 1, c);
    auto res = complex<double> {2390,0};
    assertEquales(14, getSum(matrixSrc1), res);
}

void testcase15() {
    cout << "This is the test for getMin" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(3, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 1, c);
    auto res = complex<double> {1,0};
    assertEquales(15, getMin(matrixSrc1), res);
}

void testcase16() {
    cout << "This is the test for getMin axis-specific" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(3, 4, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 1, c);
    auto res = complex<double> {4,0};
    assertEquales(16, getMin(matrixSrc1, 0, 1, 1, 2), res);
}

void testcase17() {
    cout << "This is the test for getMax axis-specific" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(3, 4, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 1, c);
    auto res = complex<double> {8,0};
    assertEquales(17, getMax(matrixSrc1, 0, 1, 1, 2), res);
}

void testcase18() {
    cout << "This is the test for getSum axis-specific" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(3, 4, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 1, c);
    auto res = complex<double> {24,0};
    assertEquales(18, getSum(matrixSrc1, 0, 1, 1, 2), res);
}

void testcase19() {
    cout << "This is the test for getAvg axis-specific" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(3, 4, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 1, c);
    auto res = complex<double> {6,0};
    assertEquales(19, getAvg(matrixSrc1, 0, 1, 1, 2), res);
}

void testcase20() {
    cout << "This is the test for eigenValue" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {276.263, -271.263, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(2, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 1, c);
    assertEquales(20, matrixSrc1.eigenValue(), matrixRes1);
}

void testcase21() {
    cout << "This is the test for eigenValue add iterate time" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {200.92, -195.92, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(2, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 1, c);
    assertEquales(21, matrixSrc1.eigenValue(100), matrixRes1);
}

void testcase22() {
    cout << "This is the test for eigenVector" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {-0.0018264, 0.0155394, 0.000212323, 0.0018264, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(2, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 2, c);
    assertEquales(22, matrixSrc1.eigenVector(), matrixRes1);
}

void testcase23() {
    cout << "This is the test for eigenVector add iterate time" << endl;
    complex<double> a[] = {1, 2342, 32, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {-0.00173977, 0.0203808, 0.000278474, 0.00173977, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(2, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 2, c);
    assertEquales(23, matrixSrc1.eigenVector(100), matrixRes1);
}

void testcase24() {
    cout << "This is the test for getTrace" << endl;
    complex<double> a[] = {100, 2342, 32, 40, 542, 62, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {22, 28, 49, 64};
    auto matrixSrc1 = initial(2, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 1, c);
    auto res = complex<double> {140,0};
    assertEquales(24, matrixSrc1.getTrace(), res);
}

void testcase25() {
    cout << "This is the test for inverse" << endl;
    complex<double> a[] = {100, 100, 100, 99, 542, 62, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {-0.99, 1, 1, -1};
    auto matrixSrc1 = initial(2, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 2, d);
    assertEquales(25, matrixSrc1.inverse(), matrixRes1);
}

void testcase26() {
    cout << "This is the test for getDeterminant" << endl;
    complex<double> a[] = {100, 100, 100, 99, 542, 62, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {0, 1, 1, -1};
    auto matrixSrc1 = initial(2, 2, a);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 2, d);
    auto res = complex<double> {-100,0};
    assertEquales(26, res, matrixSrc1.getDeterminant());
}

void testcase27() {
    cout << "This is the test for reshape" << endl;
    complex<double> a[] = {100, 100, 100, 99, 542, 62, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {0, 1, 1, -1};
    auto matrixSrc1 = initial(2, 2, a);
    matrixSrc1.reshape(1, 4);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(1, 4, a);
    assertEquales(27, matrixSrc1, matrixRes1);
}

void testcase28() {
    cout << "This is the test for slicing" << endl;
    complex<double> a[] = {100, 100, 100, 99, 542, 62, 7, 8, 9, 10, 11, 12, 13};
    complex<double> b[] = {1, 2, 3, 4, 5, 6};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {542, 62, 8, 9};
    auto matrixSrc1 = initial(3, 3, a);
    auto t = matrixSrc1.slicing(1, 2, 1, 2);
    auto matrixSrc2 = initial(2, 3, b);
    auto matrixRes1 = initial(2, 2, d);
    assertEquales(28, t, matrixRes1);
}

void testcase29() {
    cout << "This is the test for convolution" << endl;
    complex<double> a[] = {100, 100, 100, 99, 542, 62, 7, 8, 9,
                           10, 11, 12, 13, 14, 15, 16, 17, 18};
    complex<double> b[] = {1, 2, 3, 4, 5, 6, 11, 112, 234, 1};
    complex<double> c[] = {1, 4, 2, 5, 3, 6};
    complex<double> d[] = {542, 62, 8, 9};
    complex<double> e[] = {2046, 3257, 1704, 1132, 15286, 39348, 36192, 34627,
                           61511, 134079, 15631, 2737, 1239, 3555, 3927, 4088};
    auto matrixSrc1 = initial(4, 4, a);
    auto matrixSrc2 = initial(3, 3, b);
    auto matrixRes1 = initial(4, 4, e);
    assertEquales(29, Matrix<complex<double>>::convolution(matrixSrc1, matrixSrc2),
                  matrixRes1);
}


int main() {
    testcase1();
    testcase2();
    testcase3();
    testcase4();
    testcase5();
    tesecase6();
    testcase7();
    testcase8();
    testcase9();
    testcase10();
    testcase11();
    testcase12();
    testcase13();
    testcase14();
    testcase15();
    testcase16();
    testcase17();
    testcase18();
    testcase19();
    testcase20();
    testcase21();
    testcase22();
    testcase23();
    testcase24();
    testcase25();
    testcase26();
    testcase27();
    testcase28();
    testcase29();
}
