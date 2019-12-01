#include "Matrix.hpp"
using namespace std;

int defaultValue = 1;

/**
 * Example - https://java.mazurok.com/?p=2509
 */

Matrix::Matrix(int n, int m) {
  this->n = n;
  this->m = m;
  this->mainMatrix.resize(this->n, vector<int>(this->m, defaultValue));
}

Matrix::Matrix(int n) {
  this->n = n;
  this->m = 1;
  this->mainMatrix.resize(this->n, vector<int>(1, defaultValue));
}

Matrix::Matrix(vector< vector<int> > paramMatrix) {
  this->n = paramMatrix.size();
  this->m = paramMatrix[0].size();
  this->mainMatrix = paramMatrix;
}

Matrix::Matrix(vector<int> paramArray) {
  this->n = paramArray.size();
  this->m = 1;
  this->mainMatrix.resize(1, vector<int>(this->n, defaultValue));
  for (int i = 0; i < this->n; i++) {
    this->mainMatrix[0][i] = paramArray[i];
  }
  this->mainMatrix = Matrix::transpone(this->mainMatrix);
}

int Matrix::getElement(int n, int m) {
  return this->mainMatrix[n][m];
}

vector<int> Matrix::getElement(int n) {
  vector<int> tmpArr(this->mainMatrix[0].size(), defaultValue);
  for (int i = 0; i < tmpArr.size(); i++) {
    tmpArr[i] = this->mainMatrix[n][i];
  }
  return tmpArr;
}

void Matrix::setElement(int value, int n, int m) {
  this->mainMatrix[n][m] = value;
}

void Matrix::setElement(vector<int> value, int n) {
  for (int i = 0; i < this->mainMatrix[0].size(); i++) {
    this->mainMatrix[n][i] = value[i];
  }
}

int Matrix::getVerticalLength() {
  return this->mainMatrix.size();
}

int Matrix::getHorizontalLength() {
  return this->mainMatrix[0].size();
}

void Matrix::fillRandomValues() {
  for (int i = 0; i < this->n; i++) {
    for (int j = 0; j < this->m; j++) {
      this->mainMatrix[i][j] = rand() % 100;
    }
  }
}

void Matrix::displayMatrix() {
  for (int i = 0; i < this->n; ++i) {
    for (int j = 0; j < this->m; ++j) {
      cout << this->mainMatrix[i][j] << " ";
    }
    cout << endl;
  }
}

vector< vector<int> > Matrix::transpone(vector< vector<int> > paramMatrix) {
  vector< vector<int> > tmpMatrix(paramMatrix[0].size(), vector<int>(paramMatrix.size(), defaultValue));
  for (int i = 0; i < paramMatrix[0].size(); i++) {
    for (int j = 0; j < paramMatrix.size(); j++) {
      tmpMatrix[i][j] = paramMatrix[j][i];
    }
  }
  return tmpMatrix;
}

Matrix Matrix::transpone(Matrix paramMatrix) {
  Matrix tmpMatrix(paramMatrix.m, paramMatrix.n);
  for (int i = 0; i < paramMatrix.m; i++) {
    for (int j = 0; j < paramMatrix.n; j++) {
      tmpMatrix.setElement(paramMatrix.getElement(j, i), i, j);
    }
  }
  return tmpMatrix;
}

Matrix Matrix::add(Matrix first, Matrix second) {
  if (
    first.getVerticalLength() != second.getVerticalLength()
    || first.getHorizontalLength() != second.getHorizontalLength()
  ) {
    throw new exception;
  }
  Matrix tmpMatrix(first.getVerticalLength(), second.getHorizontalLength());
  for (int i = 0; i < tmpMatrix.getVerticalLength(); i++) {
    for (int j = 0; j < tmpMatrix.getHorizontalLength(); j++) {
      tmpMatrix.setElement(first.getElement(i, j) + second.getElement(i, j), i, j);
    }
  }
  return tmpMatrix;
}

Matrix Matrix::subtract(Matrix first, Matrix second) {
  if (
    first.getVerticalLength() != second.getVerticalLength()
    || first.getHorizontalLength() != second.getHorizontalLength()
  ) {
    throw new exception;
  }
  Matrix tmpMatrix(first.getVerticalLength(), second.getHorizontalLength());
  for (int i = 0; i < tmpMatrix.getVerticalLength(); i++) {
    for (int j = 0; j < tmpMatrix.getHorizontalLength(); j++) {
      tmpMatrix.setElement(first.getElement(i, j) - second.getElement(i, j), i, j);
    }
  }
  return tmpMatrix;
}

Matrix Matrix::multiply(Matrix first, Matrix second) {
  if (first.getHorizontalLength() != second.getVerticalLength()) {
    throw new exception;
  }
  int n = first.getVerticalLength();
  int m = second.getHorizontalLength();
  int o = second.getVerticalLength();
  vector< vector<int> > tmpArr(n, vector<int>(m, defaultValue));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < o; k++) {
        tmpArr[i][j] += first.getElement(i, k) * second.getElement(k, j);
      }
    }
  }
  Matrix tmpMatrix(tmpArr);
  return tmpMatrix;
}

Matrix Matrix::multiplyOnValue(Matrix matrix, int value) {
  int n = matrix.getVerticalLength();
  int m = matrix.getHorizontalLength();
  vector< vector<int> > tmpArr(n, vector<int>(m, defaultValue));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      tmpArr[i][j] = matrix.getElement(i, j) * value;
    }
  }
  Matrix tmpMatrix(tmpArr);
  return tmpMatrix;
}

// Function to sort each row of the matrix
Matrix Matrix::sortByRow(Matrix matrix, int n, int m) {
  // vector<int> tmpArray(m, defaultValue);
  Matrix tmpMatrix(n, m);
  for (int i = 0; i < n; i++) {
    // sorting row number 'i'
    vector<int> tmpArray = matrix.getElement(i);
    std::sort(tmpArray.begin(), tmpArray.end());
    tmpMatrix.setElement(tmpArray, i);
  }
  return tmpMatrix;
}

// Function to sort the matrix row-wise and column-wise
Matrix Matrix::sort(Matrix matrix) {
  // sort rows of mat[][]
  int n = matrix.getVerticalLength();
  int m = matrix.getHorizontalLength();
  Matrix tmpMatrix = sortByRow(matrix, n, m);

  // get transpose of mat[][]
  tmpMatrix = transpone(tmpMatrix);

  // again sort rows of mat[][]
  tmpMatrix = sortByRow(tmpMatrix, m, n);

  // again get transpose of mat[][]
  tmpMatrix = transpone(tmpMatrix);

  // generate Matrix class
  return tmpMatrix;
}

// Function to find cross product of two vector array
Matrix Matrix::vectorCrossProductMatrix(Matrix first, Matrix second) {
  if (
    first.getVerticalLength() != second.getVerticalLength()
    || first.getHorizontalLength() != second.getHorizontalLength()
  ) {
    throw new exception;
  }
  vector<int> vectorA = transpone(first).getElement(0);
  vector<int> vectorB = transpone(second).getElement(0);
  vector< vector<int> > crossProductVector(1, vector<int>(vectorA.size(), defaultValue));

  crossProductVector[0][0] = vectorA[1] * vectorB[2] - vectorA[2] * vectorB[1];
  crossProductVector[0][1] = -(vectorA[0] * vectorB[2] - vectorA[2] * vectorB[0]);
  crossProductVector[0][2] = vectorA[0] * vectorB[1] - vectorA[1] * vectorB[0];
  crossProductVector = transpone(crossProductVector);

  // generate Matrix class
  Matrix tmpMatrix(crossProductVector);
  return tmpMatrix;
}

// Function that return dot product of two vector array
int Matrix::vectorDotProduct(Matrix first, Matrix second) {
  if (
    first.getVerticalLength() != second.getVerticalLength()
    || first.getHorizontalLength() != second.getHorizontalLength()
  ) {
    throw new exception;
  }
  vector<int> vectorA = transpone(first).getElement(0);
  vector<int> vectorB = transpone(second).getElement(0);

  int product = 0;

  // Loop for calculate dot product
  for (int i = 0; i < vectorA.size(); i++) {
    product = product + vectorA[i] * vectorB[i];
  }
  return product;
}