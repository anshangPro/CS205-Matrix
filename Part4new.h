#ifndef Part4NEW_H
#define Part4NEW_H

#include <cassert>
#include <cmath>
#include <complex>
#include <cstring>

#include <iostream>
#include <memory>
#include <type_traits>

#define TEMPLATE_T template <class T>

const double DBL_MIN1 = (1E-10);

template <typename> struct __isComplex : public std::false_type {};

template <typename T>
struct __isComplex<std::complex<T>> : public std::true_type {};

template <typename T> constexpr bool isComplex(T const &) {
  return __isComplex<T>::value;
}

TEMPLATE_T
class SMatrix {
public:
  size_t size;
  std::unique_ptr<T[]> data;

  explicit SMatrix(size_t size) : size(size), data(new T[size * size]) {
    memset(data.get(), 0, sizeof(T) * size * size);
  };

  SMatrix(const SMatrix &other) {
    size = other.size;
    data = std::unique_ptr<T[]>(new T[size * size]);
    memcpy(data.get(), other.data.get(), size * size * sizeof(T));
  } // copy constructor

  SMatrix(SMatrix &&other) noexcept {
    size = other.size;
    data = std::move(other.data);
  } // move constructor

  SMatrix(T *data, size_t size) : size(size), data(new T[size * size]) {
    memcpy(this->data.get(), data, size * size * sizeof(T));
  }

  SMatrix &operator=(const SMatrix &other) = delete;

  SMatrix &operator=(SMatrix &&other) noexcept {
    size = other.size;
    data = std::move(other.data);
    return *this;
  } // move assignment

  inline const T *operator[](const size_t i) const {
    return data.get() + i * size;
  }

  inline T *operator[](const size_t i) { return data.get() + i * size; }

  void print() const noexcept {
    for (size_t i = 0; i < size; i++) {
      for (size_t j = 0; j < size; j++) {
        std::cout << data[i * size + j] << " ";
      }
      std::cout << std::endl;
    }
  }
};

TEMPLATE_T
class AugMatrix {
public:
  size_t row;
  size_t col;
  std::unique_ptr<T[]> data;

  explicit AugMatrix(size_t row, size_t col)
      : row(row), col(col), data(new T[row * col]) {
    memset(data.get(), 0, sizeof(T) * row * col);
  };

  AugMatrix(const AugMatrix &other) {
    row = other.row;
    col = other.col;
    data = std::unique_ptr<T[]>(new T[row * col]);
    memcpy(data.get(), other.data.get(), row * col * sizeof(T));
  } // copy constructor

  AugMatrix(AugMatrix &&other) noexcept {
    row = other.row;
    col = other.col;
    data = std::move(other.data);
  } // move constructor

  AugMatrix &operator=(const AugMatrix &other) = delete;

  AugMatrix &operator=(AugMatrix &&other) noexcept {
    row = other.row;
    col = other.col;
    data = std::move(other.data);
    return *this;
  } // move assignment

  inline T *operator[](const size_t i) { return data.get() + i * col; }

  explicit AugMatrix(const SMatrix<T> &left) {
    const size_t size = left.size;
    row = size;
    col = size * 2;
    data = std::unique_ptr<T[]>(new T[row * col]);
    // Copy Left
    for (size_t i = 0; i < size; i++) {
      // copy to data[i][0] from left[i][0]
      memcpy(this->operator[](i), left[i], sizeof(T) * size);
    }
    // Set Right to Identity
    for (size_t i = 0; i < size; ++i) {
      memset(this->operator[](i) + size, 0, sizeof(T) * size);
      this->operator[](i)[i + size] = 1;
    }
  }
};

TEMPLATE_T
SMatrix<T> matrixTranspose(const SMatrix<T> &src) {
  SMatrix<T> ret(src.size);
  for (size_t i = 0; i < src.size; i++) {
    for (size_t j = 0; j < src.size; j++) {
      ret[j][i] = src[i][j];
    }
  }
  return ret;
}

TEMPLATE_T
T vectorDotProduct(const T *src1, const T *src2, const size_t size) {
  T ret = 0;
  for (size_t i = 0; i < size; i++) {
    ret += src1[i] * src2[i];
  }
  return ret;
}

TEMPLATE_T
T matrixDeterminant(const SMatrix<T> &src) {
  if (src.size == 1) {
    return src[0][0];
  } else if (src.size == 2) {
    return src[0][0] * src[1][1] - src[0][1] * src[1][0];
  }
  // size >= 3
  const size_t size = src.size;
  T ret = 0;
  size_t k = 0;
  for (size_t i = 0; i < size; i++) {
    SMatrix<T> sub(size - 1);
    for (size_t j = 0; j < size - 1; j++) {
      k = 0;
      while (k < size - 1) {
        if (k < i) {
          sub[j][k] = src[j + 1][k];
        } else {
          sub[j][k] = src[j + 1][k + 1];
        }
        k++;
      }
    }
    ret += src[0][i] * std::pow(-1, i) * matrixDeterminant(sub);
  }
  return ret;
}

TEMPLATE_T
SMatrix<T> matrixGramSchimidt(const SMatrix<T> &src) {
  auto transposed = matrixTranspose(src);
  const size_t size = src.size;
  SMatrix<T> result(size);
  T tempValue = 0;
  T tempFactor = 0;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      tempValue = transposed[i][j];
      for (int k = 0; k < i; k++) {
        tempFactor = (vectorDotProduct(transposed[i], result[k], size)) /
                     vectorDotProduct(result[k], result[k], size);
        tempValue -= tempFactor * result[k][j];
      }
      result[i][j] = tempValue;
    }
  }
  return matrixTranspose(result);
}

TEMPLATE_T
SMatrix<T> matrixInverse(const SMatrix<T> &src) {
  if (std::abs(matrixDeterminant(src)) <= DBL_MIN1) {
    throw std::runtime_error("matrix is not invertible");
  }
  const size_t size = src.size;
  AugMatrix<T> AugmentedMatrix(src);

  T tempTimes = 0;
  for (int i = 0; i < size; i++) {
    if (std::abs(AugmentedMatrix[i][i]) <= DBL_MIN1) {
      int j;
      for (j = i + 1; j < size; j++) {
        if (std::abs(AugmentedMatrix[j][i]) > DBL_MIN1) {
          break;
        }
      }

      if (j != i + 1) {
        for (int k = 0; k < size * 2; k++) {
          T temppVlaue = AugmentedMatrix[i][k];
          AugmentedMatrix[i][k] = AugmentedMatrix[j][k];
          AugmentedMatrix[j][k] = temppVlaue;
        }
      }
    }

    for (int j = i + 1; j < size; j++) {
      if (std::abs(AugmentedMatrix[j][i]) > DBL_MIN1) {
        tempTimes = (AugmentedMatrix[j][i]) / AugmentedMatrix[i][i];
        for (int k = i; k < size * 2; k++) {
          AugmentedMatrix[j][k] /= tempTimes;
          AugmentedMatrix[j][k] -= AugmentedMatrix[i][k];
        }
      }
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size * 2 / 2.; j++) {
      if (std::abs(AugmentedMatrix[i][j]) > DBL_MIN1) {
        tempTimes = AugmentedMatrix[i][j] / AugmentedMatrix[j][j];
        for (int k = j; k < size * 2; k++) {
          AugmentedMatrix[i][k] -= tempTimes * AugmentedMatrix[j][k];
        }
      }
    }
  }

  for (int i = 0; i < size; i++) {
    tempTimes = AugmentedMatrix[i][i];
    for (int j = 0; j < size * 2; j++) {
      AugmentedMatrix[i][j] /= tempTimes;
    }
  }

  SMatrix<T> result(size);
  for (int i = 0; i < size; i++) {
    // TODO: call memset here
    for (int j = 0; j < size; j++) {
      result[i][j] = AugmentedMatrix[i][j + size];
    }
  }
  return result;
}

TEMPLATE_T
T magnitude(const T *vector, const size_t size) {
  T ret = 0;
  for (size_t i = 0; i < size; i++) {
    ret += vector[i] * vector[i];
  }
  return std::sqrt(ret);
}

TEMPLATE_T
SMatrix<T> matrixMultiply(const SMatrix<T> &src1, const SMatrix<T> &src2) {
  if (src1.size != src2.size) {
    throw std::runtime_error("matrix size is not equal");
  }
  const size_t size = src1.size;
  SMatrix<T> result(size);
  for (int i = 0; i < size; i++) {
    for (int k = 0; k < size; k++) {
      T temp = src1[i][k];
      for (int j = 0; j < size; j++) {
        result[i][j] += temp * src2[k][j];
      }
    }
  }
  return result;
}

TEMPLATE_T
std::pair<SMatrix<T>, SMatrix<T>> matrixQrDecomposition(const SMatrix<T> &src) {
  const size_t size = src.size;
  auto tempOrthogonalMatrix = matrixTranspose(matrixGramSchimidt(src));
  SMatrix<T> tempMatrixQ(size);
  for (int i = 0; i < size; i++) {
    T tempMag = magnitude(tempOrthogonalMatrix[i], size);
    for (int j = 0; j < size; j++) {
      tempMatrixQ[i][j] = tempOrthogonalMatrix[i][j] / tempMag;
    }
  }
  SMatrix<T> R = matrixMultiply(tempMatrixQ, src);
  return std::make_pair(matrixTranspose(tempMatrixQ), R);
}

TEMPLATE_T
SMatrix<T> matrixEigValue(const SMatrix<T> &src, int maxIteration) {
  SMatrix<T> result(src);
  for (int i = 0; i < maxIteration; i++) {
    auto qr = matrixQrDecomposition(result);
    const auto &q = qr.first;
    const auto &r = qr.second;
    result = matrixMultiply(r, q);
  }
  return result;
}

TEMPLATE_T
SMatrix<T> matrixSubtract(const SMatrix<T> &src1, const SMatrix<T> &src2) {
  assert(src1.size == src2.size);
  SMatrix<T> result(src1.size);
  for (int i = 0; i < src1.size; i++) {
    for (int j = 0; j < src1.size; j++) {
      result[i][j] = src1[i][j] - src2[i][j];
    }
  }
  return result;
}

TEMPLATE_T
SMatrix<T> matrixEigVector(const SMatrix<T> &src, const SMatrix<T> &eigValue,
                           int maxIteration) {
  const size_t size = src.size;
  SMatrix<T> eigValueCopied(eigValue);
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      if (i != j) {
        eigValueCopied[i][j] = 0;
      }
    }
  }
  return matrixInverse(matrixSubtract(src, eigValueCopied));
}

// using namespace std;
// #include <eigen3/Eigen/Dense>
// template <typename T>
// SMatrix<complex<T>> matrixEigVector(SMatrix<complex<T>> &src,
//                                     const SMatrix<complex<T>> &afawsga,
//                                     int maxIteration) {
//   std::cout << "hello" << std::endl;
//   using namespace Eigen;
//   int size = src.size;
//   Eigen::Matrix<complex<T>, 10, 10> eigVal;
//   for (int i = 0; i < size; i++) {
//     for (int j = 0; j < size; j++) {
//       eigVal(i, j) = src[i][j];
//     }
//   }
//   Eigen::EigenSolver<Eigen::MatrixXd> es(eigVal);
//   auto eigVec = es.eigenvectors();
//   SMatrix<complex<T>> result(size);
//   for (int i = 0; i < size; i++) {
//     for (int j = 0; j < size; j++) {
//       result[i][j] = eigVec(i, j);
//     }
//   }
//   return result;
// }

template <class T> std::string type_name() {
  typedef typename std::remove_reference<T>::type TR;
  std::unique_ptr<char, void (*)(void *)> own(nullptr, std::free);
  std::string r = own != nullptr ? own.get() : typeid(TR).name();
  if (std::is_const<TR>::value)
    r += " const";
  if (std::is_volatile<TR>::value)
    r += " volatile";
  if (std::is_lvalue_reference<T>::value)
    r += "&";
  else if (std::is_rvalue_reference<T>::value)
    r += "&&";
  return r;
}

// int main() {
//     using namespace std;

//     SMatrix<std::complex<double>> A(2);
//     //SMatrix<double> A(2);
//     A[0][0] = 6.0 + 1i;
//     A[0][1] = -1;
//     //A[0][2] = 2;
//     A[1][0] = 2;
//     A[1][1] = 3;
// //    A[1][2] = 4;
// //    A[2][0] = 7;
// //    A[2][1] = 8;
// //    A[2][2] = 8;
//     auto b = matrixInverse(A);
//     b.print();

// //    const auto cstA(A);
// //    cout << type_name<decltype(cstA)>() << endl;
// //    cout << type_name<decltype(cstA[0])>() << endl;
// //    cout << type_name<decltype(cstA[0][0])>() << endl;
// //    cout << "A:" << endl;
// //    cout << type_name<decltype(A)>() << endl;
// //    cout << type_name<decltype(A[0])>() << endl;
// //    cout << type_name<decltype(A[0][0])>() << endl;

//     A.print();
//     auto QR = matrixQrDecomposition(A);
//     cout << "Q:" << endl;
//     QR.first.print();
//     cout << "R:" << endl;
//     QR.second.print();
//     auto eigValue = matrixEigValue(A, 1000);
//     cout << "eig:" << endl;
//     eigValue.print();

//     auto eigVector = matrixEigVector(A, eigValue, 1000);
//     cout << "eigVector:" << endl;
//     eigVector.print();
//     return 0;
// }

// template<class T, class is_complex>
// struct GetIntermediaType;
//
// template<typename Test, template<typename...> class Ref>
// struct is_specialization : std::false_type {};
//
// template<template<typename...> class Ref, typename... Args>
// struct is_specialization<Ref<Args...>, Ref>: std::true_type {};
//
// template<class T>
// using is_complex = is_specialization<T, std::complex>;
//
// template<class T>
// using is_arithmetic = std::is_arithmetic<T>;
//
// template<class T>
// struct GetIntermediaType<T, is_arithmetic<T>> {
//     using type = double;
// };
//
// template<class T>
// struct GetIntermediaType<T, is_complex<T>> {
//     using type = std::complex<double>;
// };
//
// template<class T, typename I = (value ? double : std::complex<T>)>
// void test(T a){
//
// };
#endif // Part4NEW_H