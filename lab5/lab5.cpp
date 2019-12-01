/**
 * Lab5. OPENMP library with
 * 
 * NOTES!
 * !!OPENMP HOW TO!! - https://bisqwit.iki.fi/story/howto/openmp/
 * !!OPENMP THREADS!! - http://jakascorner.com/blog/2016/05/omp-sections.html
 * Install gcc with openmp lib - https://github.com/microsoft/LightGBM/issues/3
 * Usage openmp lib - https://helloacm.com/simple-tutorial-with-openmp-how-to-use-parallel-block-in-cc-using-openmp/
 * How to build cpp file with gcc (not g++) with (-lstdc++) - https://stackoverflow.com/a/3206195
 * Matrix in heap - https://stackoverflow.com/questions/1403150/how-do-you-dynamically-allocate-a-matrix
 * Vector of vectors for matrix - https://stackoverflow.com/questions/12375591/vector-of-vectors-to-create-matrix
 * C++ classes and imports - https://stackoverflow.com/a/12734036
 * C++ vector init - https://www.techiedelight.com/initialize-two-dimensional-vector-cpp/
 * C++ classes tutorial - http://www.cplusplus.com/doc/tutorial/classes/
 * Executable build file - https://www.taniarascia.com/how-to-create-and-use-bash-scripts/
 * Work with time clock - https://en.cppreference.com/w/cpp/chrono/time_point
 * 
 * 
 * Simple explanation!
 * GCC implements this by creating a magic function and moving the associated code
 * into that function, so that all the variables declared within that block become
 * local variables of that function (and thus, locals to each thread).
 * ICC, on the other hand, uses a mechanism resembling fork(), and does not create 
 * a magic function. Both implementations are, of course, valid, and semantically identical.
 * 
 * 
 * Common usage!
 * 0. pragma omp simd - multiple calculations will be performed simultaneously by the processor
 * 1. pragma omp parallel - creates a team of threads
 * 2. pragma omp for - splits the for-loop so that each thread in the current team
 * 3. pragma omp parallel for - like 1 and 2 the same time
 * 4. pragma omp parallel for if(parallelism_enabled) - like 3, but with condition
 * 5. pragma omp parallel num_threads(3) - set amount of threads
 * 6. pragma omp sections (pragma omp parallel sections) - create sections for parallel
 * 6. pragma omp section - indicates section with NO parallel inside
 */

#include <iostream>
#include <vector>
#include <thread>
#include <omp.h>
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

  steady_clock::time_point begin = steady_clock::now();
  {
    F1Procedure(A, C, MA, ME, MD);
    cout << endl;
  
    F2Procedure(6574, 2342, MA, MD, ME);
    cout << endl;
  
    F3Procedure(P, R, MA, MD);
    cout << endl;
  }
  logTime(begin, "DIRECT execution finished with time: ");
  
  begin = steady_clock::now();
  #pragma omp parallel
  {
    #pragma omp sections
    {
      #pragma omp section
      {
        F1Procedure(A, C, MA, ME, MD);
        cout << endl;
      }

      #pragma omp section
      {
        F2Procedure(6574, 2342, MA, MD, ME);
        cout << endl;
      }

      #pragma omp section
      {
        F3Procedure(P, R, MA, MD);
        cout << endl;
      }
    }
  }
  logTime(begin, "OMP THREAD execution finished with time: ");

  return 0;
}

// ME = (A*SORT(C)) *(MA*ME+MD)
Matrix F1Procedure(Matrix A, Matrix C, Matrix MA, Matrix ME, Matrix MD) {
  cout << "F1 starts on thread with number: " << omp_get_thread_num() << endl;
  Matrix res = Matrix::multiplyOnValue(
    Matrix::add(
      Matrix::multiply(MA, ME),
      MD
    ),
    Matrix::vectorDotProduct(A, C)
  );
  cout << "F1 finished on thread with number: " << omp_get_thread_num() << endl;
  // res.displayMatrix();
  return res;
}

// MF = k*MG - h*MK*ML
Matrix F2Procedure(int k, int h, Matrix MG, Matrix MK, Matrix ML) {
  cout << "F2 starts on thread with number: " << omp_get_thread_num() << endl;
  Matrix res = Matrix::subtract(
    Matrix::multiplyOnValue(MG, k),
    Matrix::multiplyOnValue(
      Matrix::multiply(MK, ML),
      h
    )
  );
  cout << "F2 finished on thread with number: " << omp_get_thread_num() << endl;
  // res.displayMatrix();
  return res;
}

// MF = k*MG - h*MK*ML
Matrix F3Procedure(Matrix P, Matrix R, Matrix MS, Matrix MT) {
  cout << "F3 starts on thread with number: " << omp_get_thread_num() << endl;
  Matrix res = Matrix::multiply(
    Matrix::multiply(MS, MT),
    Matrix::add(P, R)
  );
  cout << "F3 finished on thread with number: " << omp_get_thread_num() << endl;
  // res.displayMatrix();
  return res;
}

void logTime(steady_clock::time_point begin, string msg) {
  steady_clock::time_point end = steady_clock::now();
  duration<double, std::milli> duration = (end - begin);
  cout << msg << duration.count() << "\n\n";
}
