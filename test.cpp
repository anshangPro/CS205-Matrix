
#include "IndexOutOfBound.h"
#include "Matrix.h"

int main() {
    using namespace std;
    Matrix<double> B(2, 2);
    B.set(0, 0, 1);
    B.set(0, 1, 2);
    B.set(1, 0, 3);
    B.set(1, 1, 4);
    auto C = B.inverse();
    cout<<"-----------------"<<endl;
    C.print();
    cout<<"-----------------"<<endl;

    // SMatrix<std::complex<double>> A(2);
    // //SMatrix<double> A(2);
    // A[0][0] = 6.0 + 1i;
    // A[0][1] = -1;
    // //A[0][2] = 2;
    // A[1][0] = 2;
    // A[1][1] = 3;
//    A[1][2] = 4;
//    A[2][0] = 7;
//    A[2][1] = 8;
//    A[2][2] = 8;
    // auto b = matrixInverse(A);
    // b.print();



    // A.print();
    // auto QR = matrixQrDecomposition(A);
    // cout << "Q:" << endl;
    // QR.first.print();
    // cout << "R:" << endl;
    // QR.second.print();
    // auto eigValue = matrixEigValue(A, 1000);
    // cout << "eig:" << endl;
    // eigValue.print();

    // auto eigVector = matrixEigVector(A, eigValue, 1000);
    // cout << "eigVector:" << endl;
    // eigVector.print();
    // return 0;
}

// int main() {
//   // throw IndexOutOfBound(1, 2);
//   Matrix<int> m1(2,2);
//   m1.set(0, 0, 1);
//   m1.set(1, 1, 1);
//   Matrix<int> m2(2,2);
//   m2.set(0, 1, 2);
//   m2.set(1, 0, 4);
//   Matrix<int> m3(2,2);
//   m3 = m1 + m2;
//   return 0;
// }