'use strict';

const NotEqualLengthsOfMatrixException = require('./NotEqualLengthsOfMatrixException.js');

class Matrix {

  constructor(first, second) {
    if (typeof first === 'object') {
      this.n = first.length;
      this.m = first[0].length;
      this.mainMatrix = first;
    } else {
      this.n = first;
      this.m = second || 1;
      this.mainMatrix = [];
    }
  }

  // public Matrix(int[] vector) {
  //   this.n = vector.length;
  //   this.m = 1;
  //   this.mainMatrix = new int[this.n][1];
  //   this.mainMatrix[0] = vector;
  //   this.mainMatrix = transpone(this.mainMatrix);
  // }

  getElement(n, m) {
    return typeof m === 'number' ? this.mainMatrix[n][m] : this.mainMatrix[n];
  }

  setElement(value, n, m) {
    if (typeof m !== 'number') {
      this.mainMatrix[n] = value;
    } else {
      if (!this.mainMatrix[n]) {
        this.mainMatrix[n] = []
      }
      this.mainMatrix[n][m] = value;
    }
  }

  getVerticalLength() {
    return this.mainMatrix.length;
  }

  getHorizontalLength() {
    return this.mainMatrix[0].length;
  }

  fillRandomValues() {
    for (let i = 0; i < this.n; i++) {
      this.mainMatrix[i] = [];
      for (let j = 0; j < this.m; j++) {
        this.mainMatrix[i][j] = Math.floor(Math.random() * 100);
      }
    }
  }

  displayMatrix() {
    for (let i = 0; i < this.n; i++) {
      for (let j = 0; j < this.m; j++) {
        process.stdout.write(this.mainMatrix[i][j] + " ");
      }
      console.log('');
    }
  }

  static transpone(paramMatrix) {
    const tmpMatrix = [];
    for (let i = 0; i < paramMatrix[0].length; i++) {
      tmpMatrix[i] = [];
      for (let j = 0; j < paramMatrix.length; j++) {
        tmpMatrix[i][j] = paramMatrix[j][i];
      }
    }
    return tmpMatrix;
  }

  static transpone(paramMatrix) {
    const tmpMatrix = new Matrix(paramMatrix.m, paramMatrix.n);
    for (let i = 0; i < paramMatrix.m; i++) {
      for (let j = 0; j < paramMatrix.n; j++) {
        tmpMatrix.setElement(paramMatrix.getElement(j, i), i, j);
      }
    }
    return tmpMatrix;
  }

  static add(first, second) {
    if (
      first.getVerticalLength() != second.getVerticalLength()
      || first.getHorizontalLength() != second.getHorizontalLength()
    ) {
      throw new NotEqualLengthsOfMatrixException();
    }
    const tmpMatrix = new Matrix(first.getVerticalLength(), second.getHorizontalLength());
    for (let i = 0; i < first.getVerticalLength(); i++) {
      for (let j = 0; j < second.getHorizontalLength(); j++) {
        tmpMatrix.setElement(first.getElement(i, j) + second.getElement(i, j), i, j);
      }
    }
    return tmpMatrix;
  }

  static subtract(first, second) {
    if (
      first.getVerticalLength() != second.getVerticalLength()
      || first.getHorizontalLength() != second.getHorizontalLength()
    ) {
      throw new NotEqualLengthsOfMatrixException();
    }
    const tmpMatrix = new Matrix(first.getVerticalLength(), second.getHorizontalLength());
    for (let i = 0; i < first.getVerticalLength(); i++) {
      for (let j = 0; j < second.getHorizontalLength(); j++) {
        tmpMatrix.setElement(first.getElement(i, j) - second.getElement(i, j), i, j);
      }
    }
    return tmpMatrix;
  }

  static multiply(first, second) {
    if (first.getHorizontalLength() != second.getVerticalLength()) {
      throw new NotEqualLengthsOfMatrixException();
    }
    const n = first.getVerticalLength();
    const m = second.getHorizontalLength();
    const o = second.getVerticalLength();
    const tmpArr = [];
    for (let i = 0; i < n; i++) {
      tmpArr[i] = [];
      for (let j = 0; j < m; j++) {
        tmpArr[i][j] = 0;
        for (let k = 0; k < o; k++) {
          tmpArr[i][j] += first.getElement(i, k) * second.getElement(k, j);
        }
      }
    }
    return new Matrix(tmpArr);
  }

  static multiplyOnValue(matrix, value) {
    const n = matrix.getVerticalLength();
    const m = matrix.getHorizontalLength();
    const tmpArr = [];
    for (let i = 0; i < n; i++) {
      tmpArr[i] = [];
      for (let j = 0; j < m; j++) {
        tmpArr[i][j] = matrix.getElement(i, j) * value;
      }
    }
    return new Matrix(tmpArr);
  }

  // Function to sort each row of the matrix
  static sortByRow(matrix, n, m) {
    const tmpMatrix = new Matrix(n, m);
    for (let i = 0; i < n; i++) {
      // sorting row number 'i'
      const tmpArray = [ ...matrix.getElement(i) ].sort();
      tmpMatrix.setElement(tmpArray, i);
    }
    return tmpMatrix;
  }

  // Function to sort the matrix row-wise and column-wise
  static sort(matrix) {
    // sort rows of mat[][]
    const n = matrix.getVerticalLength();
    const m = matrix.getHorizontalLength();
    let tmpMatrix = this.sortByRow(matrix, n, m);

    // get transpose of mat[][]
    tmpMatrix = this.transpone(tmpMatrix);

    // again sort rows of mat[][]
    tmpMatrix = this.sortByRow(tmpMatrix, m, n);

    // again get transpose of mat[][]
    tmpMatrix = this.transpone(tmpMatrix);

    // generate Matrix class
    return tmpMatrix;
  }

  // Function to find cross product of two vector array
  static vectorCrossProductMatrix(first, second) {
    if (
      first.getVerticalLength() != second.getVerticalLength()
      || first.getHorizontalLength() != second.getHorizontalLength()
    ) {
      throw new NotEqualLengthsOfMatrixException();
    }
    const vectorA = this.transpone(first).getElement(0);
    const vectorB = this.transpone(second).getElement(0);
    tmpMatrix = new Matrix(vectorA.length, 1);
    const crossProductVector = [];

    crossProductVector[0][0] = vectorA[1] * vectorB[2] - vectorA[2] * vectorB[1];
    crossProductVector[0][1] = -(vectorA[0] * vectorB[2] - vectorA[2] * vectorB[0]);
    crossProductVector[0][2] = vectorA[0] * vectorB[1] - vectorA[1] * vectorB[0];
    crossProductVector = transpone(crossProductVector);

    // generate Matrix class
    tmpMatrix = new Matrix(crossProductVector);
    return tmpMatrix;
  }

  // Function that return dot product of two vector array
  static vectorDotProduct(first, second) {
    if (
      first.getVerticalLength() != second.getVerticalLength()
      || first.getHorizontalLength() != second.getHorizontalLength()
    ) {
      throw new NotEqualLengthsOfMatrixException();
    }
    const vectorA = this.transpone(first).getElement(0);
    const vectorB = this.transpone(second).getElement(0);

    let product = 0;

    // Loop for calculate dot product
    for (let i = 0; i < vectorA.length; i++) {
      product = product + vectorA[i] * vectorB[i];
    }
    return product;
  }

}

module.exports = Matrix;