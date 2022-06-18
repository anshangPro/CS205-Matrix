#include <iostream>

#include "Matrix.h"
#include "testbench.h"

using namespace std;
void testcase1(){
    cout << "This is the test of eigenValue" <<endl;
    int data[] = {1,2,3};
    auto a = initial(1,2,data);
    testNotSquareMatrix(1,1,a);
}
void testcase2(){
    cout << "This is the test of eigenValue add iterate time" <<endl;
    int data[] = {1,2,3};
    auto a = initial(1,2,data);
    testNotSquareMatrix(2,2,a);
}
void testcase3(){
    cout << "This is the test of eigenVector" <<endl;
    int data[] = {1,2,3};
    auto a = initial(1,2,data);
    testNotSquareMatrix(3,3,a);
}
void testcase4(){
    cout << "This is the test of eigenVector add iterate time" <<endl;
    int data[] = {1,2,3};
    auto a = initial(1,2,data);
    testNotSquareMatrix(4,4,a);
}
void testcase5(){
    cout << "This is the test of inverse" <<endl;
    int data[] = {1,2,3};
    auto a = initial(1,2,data);
    testNotSquareMatrix(5,5,a);
}
void testcase6(){
    cout << "This is the test of getTrace" <<endl;
    int data[] = {1,2,3};
    auto a = initial(1,2,data);
    testNotSquareMatrix(6,6,a);
}
void testcase7(){
    cout << "This is the test of getDeterminant" <<endl;
    int data[] = {1,2,3};
    auto a = initial(1,2,data);
    testNotSquareMatrix(7,7,a);
}
int main(){
    testcase1();
    testcase2();
    testcase3();
    testcase4();
    testcase5();
    testcase6();
    testcase7();
}