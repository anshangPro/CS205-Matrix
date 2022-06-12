//#include "Part4.h"

#include <cmath>
#include <cstring>
#include <map>

using namespace std;

template <class T>
void QRBreakDown(T *A, size_t n, T *Q_temp, T *R_temp) {
  long long size = sizeof(T);
  for (int k = 0; k < n; k++) {
    T norm = 0;
    for (int i = 0; i < n; i++) {
      norm += A[i * n + k] * A[i * n + k];
    }
    norm = sqrt(norm);
    R_temp[k * n + k] = norm;
    for (int i = 0; i < n; i++) {
      Q_temp[i * n + k] = A[i * n + k] / norm;
    }
    for (int j = k + 1; j < n; j++) {
      T sum = 0;
      for (int i = 0; i < n; i++) {
        sum += Q_temp[i * n + k] * A[i * n + j];
      }
      R_temp[k * n + j] = sum;
      for (int i = 0; i < n; i++) {
        A[i * n + j] -= Q_temp[i * n + k] * sum;
      }
    }
  }
}

template <class T>
long long determinant(T *matrix, int n) {
  long long det = 0;
  auto submatrix = new T[(n - 1) * (n - 1)];
  if (n == 2)
    return ((matrix[0] * matrix[3]) - (matrix[2] * matrix[1]));
  else {
    for (int x = 0; x < n; x++) {
      int subi = 0;
      for (int i = 1; i < n; i++) {
        int subj = 0;
        for (int j = 0; j < n; j++) {
          if (j == x) {
            continue;
          }
          submatrix[subi * (n - 1) + subj] = matrix[i * n + j];
          subj++;
        }
        subi++;
      }
      det = det + (pow(-1, x) * matrix[x] * determinant(submatrix, n - 1));
    }
  }
  return det;
}

template <class T>
long long trace(T *matrix, int n) {
  long long trace = 0;
  for (int i = 0; i < n; i++) {
    trace += matrix[i * n + i];
  }
  return trace;
}

template <class T>
bool inverse(int n, T *aa, T *re) {
  double det_aa = determinant(aa, n);
  if (det_aa == 0) {
    throw NoInverseMatrix();
    return false;
  }
  T *adjoint = new T[n * n];
  T *bb = new T[(n - 1) * (n - 1)];

  int pi, pj, q;
  for (int ai = 0; ai < n; ai++) {
    for (int aj = 0; aj < n; aj++) {
      for (int bi = 0; bi < n - 1; bi++) {
        for (int bj = 0; bj < n - 1; bj++) {
          if (ai > bi) {
            pi = 0;
          } else {
            pi = 1;
          }
          if (aj > bj) {
            pj = 0;
          }
          else {
            pj = 1;
          }
          bb[bi * (n - 1) + bj] = aa[(bi + pi) * n + bj + pj];
        }
      }
      if ((ai + aj) % 2 == 0)
        q = 1;
      else
        q = (-1);
      adjoint[ai * n + aj] = q * determinant(bb, n - 1);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      T tem = adjoint[i * n + j];
      adjoint[i * n + j] = adjoint[j * n + i];
      adjoint[j * n + i] = tem;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      re[i * n + j] = adjoint[i * n + j] / det_aa;
    }
  }
  delete[] adjoint;
  delete[] bb;
  return true;
}

/**
 * @brief 求实对称矩阵的特征值及特征向量的雅克比法
 * 利用雅格比(Jacobi)方法求实对称矩阵的全部特征值及特征向量
 * @param pMatrix				长度为n*n的数组，存放实对称矩阵
 * @param nDim					矩阵的阶数
 * @param pdblVects
 * 长度为n*n的数组，返回特征向量(按列存储)
 * @param dbEps					精度要求
 * @param nJt					整型变量，控制最大迭代次数
 * @param pdbEigenValues			特征值数组
 * @return
 */
bool JacbiCor(double *pMatrix, int nDim, double *pdblVects,
              double *pdbEigenValues, double dbEps, int nJt) {
  for (int i = 0; i < nDim; i++) {
    pdblVects[i * nDim + i] = 1.0f;
    for (int j = 0; j < nDim; j++) {
      if (i != j) pdblVects[i * nDim + j] = 0.0f;
    }
  }

  int nCount = 0;  //迭代次数
  while (1) {
    //在pMatrix的非对角线上找到最大元素
    double dbMax = pMatrix[1];
    int nRow = 0;
    int nCol = 1;
    for (int i = 0; i < nDim; i++)  //行
    {
      for (int j = 0; j < nDim; j++)  //列
      {
        double d = fabs(pMatrix[i * nDim + j]);

        if ((i != j) && (d > dbMax)) {
          dbMax = d;
          nRow = i;
          nCol = j;
        }
      }
    }

    if (dbMax < dbEps)  //精度符合要求
      break;

    if (nCount > nJt)  //迭代次数超过限制
      break;

    nCount++;

    double dbApp = pMatrix[nRow * nDim + nRow];
    double dbApq = pMatrix[nRow * nDim + nCol];
    double dbAqq = pMatrix[nCol * nDim + nCol];

    //计算旋转角度
    double dbAngle = 0.5 * atan2(-2 * dbApq, dbAqq - dbApp);
    double dbSinTheta = sin(dbAngle);
    double dbCosTheta = cos(dbAngle);
    double dbSin2Theta = sin(2 * dbAngle);
    double dbCos2Theta = cos(2 * dbAngle);

    pMatrix[nRow * nDim + nRow] = dbApp * dbCosTheta * dbCosTheta +
                                  dbAqq * dbSinTheta * dbSinTheta +
                                  2 * dbApq * dbCosTheta * dbSinTheta;
    pMatrix[nCol * nDim + nCol] = dbApp * dbSinTheta * dbSinTheta +
                                  dbAqq * dbCosTheta * dbCosTheta -
                                  2 * dbApq * dbCosTheta * dbSinTheta;
    pMatrix[nRow * nDim + nCol] =
        0.5 * (dbAqq - dbApp) * dbSin2Theta + dbApq * dbCos2Theta;
    pMatrix[nCol * nDim + nRow] = pMatrix[nRow * nDim + nCol];

    for (int i = 0; i < nDim; i++) {
      if ((i != nCol) && (i != nRow)) {
        int u = i * nDim + nRow;  // p
        int w = i * nDim + nCol;  // q
        dbMax = pMatrix[u];
        pMatrix[u] = pMatrix[w] * dbSinTheta + dbMax * dbCosTheta;
        pMatrix[w] = pMatrix[w] * dbCosTheta - dbMax * dbSinTheta;
      }
    }

    for (int j = 0; j < nDim; j++) {
      if ((j != nCol) && (j != nRow)) {
        int u = nRow * nDim + j;  // p
        int w = nCol * nDim + j;  // q
        dbMax = pMatrix[u];
        pMatrix[u] = pMatrix[w] * dbSinTheta + dbMax * dbCosTheta;
        pMatrix[w] = pMatrix[w] * dbCosTheta - dbMax * dbSinTheta;
      }
    }

    //计算特征向量
    for (int i = 0; i < nDim; i++) {
      int u = i * nDim + nRow;  // p
      int w = i * nDim + nCol;  // q
      dbMax = pdblVects[u];
      pdblVects[u] = pdblVects[w] * dbSinTheta + dbMax * dbCosTheta;
      pdblVects[w] = pdblVects[w] * dbCosTheta - dbMax * dbSinTheta;
    }
  }

  //对特征值进行排序以及重新排列特征向量,特征值即pMatrix主对角线上的元素
  std::map<double, int> mapEigen;
  for (int i = 0; i < nDim; i++) {
    pdbEigenValues[i] = pMatrix[i * nDim + i];

    mapEigen.insert(make_pair(pdbEigenValues[i], i));
  }

  double *pdbTmpVec = new double[nDim * nDim];
  std::map<double, int>::reverse_iterator iter = mapEigen.rbegin();
  for (int j = 0; iter != mapEigen.rend(), j < nDim; ++iter, ++j) {
    for (int i = 0; i < nDim; i++) {
      pdbTmpVec[i * nDim + j] = pdblVects[i * nDim + iter->second];
    }

    //特征值重新排列
    pdbEigenValues[j] = iter->first;
  }

  //设定正负号
  for (int i = 0; i < nDim; i++) {
    double dSumVec = 0;
    for (int j = 0; j < nDim; j++) dSumVec += pdbTmpVec[j * nDim + i];
    if (dSumVec < 0) {
      for (int j = 0; j < nDim; j++) pdbTmpVec[j * nDim + i] *= -1;
    }
  }

  memcpy(pdblVects, pdbTmpVec, sizeof(double) * nDim * nDim);
  delete[] pdbTmpVec;

  return 1;
}