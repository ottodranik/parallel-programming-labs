/**
 * Lab4. NATIVE C++ std::thread (no Win32)
 * 
 * NOTES!
 * Native C++ threads tutorial - https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/
 * Not priority in C++11 - https://stackoverflow.com/a/18884946
 * About thread join - https://stackoverflow.com/a/52307406
 * 
 * 
 * Common usage!
 * std::thread(call_from_thread, param1, param2)
 */

#include <iostream>
#include <vector>
#include <thread>
#include "../shared/Matrix.hpp"
using namespace std;
using namespace std::chrono;

Matrix F1Procedure(Matrix A, Matrix C, Matrix MA, Matrix ME, Matrix MD);
Matrix F2Procedure(int k, int h, Matrix MG, Matrix MK, Matrix ML);
Matrix F3Procedure(Matrix P, Matrix R, Matrix MS, Matrix MT);
void logTime(steady_clock::time_point begin, string msg);

int main() {
  srand((int)time(0));

  Matrix A(1000);
  Matrix C(1000);
  Matrix P(1000);
  Matrix R(1000);
  Matrix MA(1000, 1000);
  Matrix ME(1000, 1000);
  Matrix MD(1000, 1000);
  Matrix MF(1000, 1000);
  Matrix O(1000, 1000);
  A.fillRandomValues();
  C.fillRandomValues();
  P.fillRandomValues();
  R.fillRandomValues();
  MA.fillRandomValues();
  ME.fillRandomValues();
  MD.fillRandomValues();

  // DIRECT calculations
  steady_clock::time_point begin = steady_clock::now();
  F1Procedure(A, C, MA, ME, MD);
  cout << endl;

  F2Procedure(6574, 2342, MA, MD, ME);
  cout << endl;

  F3Procedure(P, R, MA, MD);
  cout << endl;
  logTime(begin, "DIRECT execution finished with time: ");
  
  // Native THREADs calculations
  begin = steady_clock::now();

  std::thread t1(F1Procedure, A, C, MA, ME, MD);
  std::thread t2(F2Procedure, 6574, 2342, MA, MD, ME);
  std::thread t3(F3Procedure, P, R, MA, MD);

  t1.join();
  t2.join();
  t3.join();

  logTime(begin, "Native THREAD execution finished with time: ");

  return 0;
}

// ME = (A*SORT(C)) *(MA*ME+MD)
Matrix F1Procedure(Matrix A, Matrix C, Matrix MA, Matrix ME, Matrix MD) {
  cout << "F1 starts on thread with number: " << std::this_thread::get_id() << endl;
  Matrix res = Matrix::multiplyOnValue(
    Matrix::add(
      Matrix::multiply(MA, ME),
      MD
    ),
    Matrix::vectorDotProduct(A, C)
  );
  cout << "F1 finished on thread with number: " << std::this_thread::get_id() << endl;
  // res.displayMatrix();
  return res;
}

// MF = k*MG - h*MK*ML
Matrix F2Procedure(int k, int h, Matrix MG, Matrix MK, Matrix ML) {
  cout << "F2 starts on thread with number: " << std::this_thread::get_id() << endl;
  Matrix res = Matrix::subtract(
    Matrix::multiplyOnValue(MG, k),
    Matrix::multiplyOnValue(
      Matrix::multiply(MK, ML),
      h
    )
  );
  cout << "F2 finished on thread with number: " << std::this_thread::get_id() << endl;
  // res.displayMatrix();
  return res;
}

// MF = k*MG - h*MK*ML
Matrix F3Procedure(Matrix P, Matrix R, Matrix MS, Matrix MT) {
  cout << "F3 starts on thread with number: " << std::this_thread::get_id() << endl;
  Matrix res = Matrix::multiply(
    Matrix::multiply(MS, MT),
    Matrix::add(P, R)
  );
  cout << "F3 finished on thread with number: " << std::this_thread::get_id() << endl;
  // res.displayMatrix();
  return res;
}

void logTime(steady_clock::time_point begin, string msg) {
  steady_clock::time_point end = steady_clock::now();
  duration<double, std::milli> duration = (end - begin);
  cout << msg << duration.count() << "\n\n";
}
