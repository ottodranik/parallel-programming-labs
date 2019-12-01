#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Matrix {
  public:
    Matrix(int n, int m);
    Matrix(int n);
    Matrix(vector< vector<int> > paramMatrix);
    Matrix(vector<int> paramArray);
    int getElement(int n, int m);
    vector<int> getElement(int n);
    void setElement(int value, int n, int m);
    void setElement(vector<int> value, int n);
    int getVerticalLength();
    int getHorizontalLength();
    void fillRandomValues();
    void displayMatrix();
    static vector< vector<int> > transpone(vector< vector<int> > paramMatrix);
    static Matrix transpone(Matrix paramMatrix);
    static Matrix add(Matrix first, Matrix second);
    static Matrix subtract(Matrix first, Matrix second);
    static Matrix multiply(Matrix first, Matrix second);
    static Matrix multiplyOnValue(Matrix matrix, int value);
    static Matrix sort(Matrix matrix);
    static Matrix vectorCrossProductMatrix(Matrix first, Matrix second);
    static int vectorDotProduct(Matrix first, Matrix second);
  private:
    int n, m;
    vector< vector<int> > mainMatrix;
    static Matrix sortByRow(Matrix matrix, int n, int m);
};
