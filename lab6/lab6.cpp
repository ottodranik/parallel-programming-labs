/**
 * Lab6. MPI library C++
 * 
 * NOTES!
 * !!MPI BASICS!! - https://people.sc.fsu.edu/~jburkardt/cpp_src/mpi/mpi.html
 * MPI hello world - https://mpitutorial.com/tutorials/mpi-hello-world/
 * How use funcs on diff MPI "threads" - https://stackoverflow.com/q/13108937
 * Install on mac - https://stackoverflow.com/questions/42703861/how-to-use-mpi-on-mac-os-x/42780322
 * run with flag "--use-hwthread-cpus" to use logical cores too
 * 
 * 
 * Features explanation!
 * ====================
 * !!MAIN NOTE!! MPI creates multiple processes within their own separate address spaces, not threads. 
 * ====================
 * 1. User writes a single program which runs on all the computers. 
 * However, because each computer is assigned a unique identifying number, 
 * it is possible for different actions to occure on different machines by the same program.
 * 2. The data stored on each computer is entirely separate from that stored on other computers.
 * 3. MPI - the Message Passing Interface model of parallel programming.
 * "Notion of a communicator". A communicator defines a group of processes 
 * that have the ability to communicate with one another.
 * In this group of processes, each is assigned a unique rank, and they 
 * explicitly communicate with one another by their ranks.
 * 
 * 
 * Common usage!
 * All MPI/C programs must include a header file mpi.h.
 * - All MPI programs must call MPI INT as the first MPI call, to initialize themselves.
 * - Most MPI programs call MPI COMM SIZE to get the number of processes that are running
 * - Most MPI programs call MPI COMM RANK to determine their rank, which is a number between 0 and size-1.
 * - Conditional process and general message passing can take place. For example, using the calls MPI SEND and MPI RECV.
 * - All MPI programs must call MPI FINALIZE as the last call to an MPI library routine.
 */

#include <iostream>
#include <vector>
#include <thread>
#include "mpi.h"
#include "../shared/Matrix.hpp"
using namespace std;
using namespace std::chrono;

Matrix F1Procedure(Matrix A, Matrix C, Matrix MA, Matrix ME, Matrix MD, int rank);
Matrix F2Procedure(int k, int h, Matrix MG, Matrix MK, Matrix ML, int rank);
Matrix F3Procedure(Matrix P, Matrix R, Matrix MS, Matrix MT, int rank);
void logTime(steady_clock::time_point begin);

int main(int argc, char** argv) {
  srand((int)time(0));

  // Init MPI with rank and size
  int provided;
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // get rank (THREAD_ID)
  MPI_Comm_size(MPI_COMM_WORLD, &size); // get amount of cores
  size--;

  // Init Matrices and Vectors
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

  // Init time

  steady_clock::time_point begin = high_resolution_clock::now();
  {
    if (rank == 0) {
      // F1Procedure(A, C, MA, ME, MD, 0);
      // F2Procedure(6574, 2342, MA, MD, ME, 0);
      // F3Procedure(P, R, MA, MD, 0);
      // logTime(begin);
    } else if (rank == 1) {
      F1Procedure(A, C, MA, ME, MD, rank);
      logTime(begin);
    }
    else if (rank == 2) {
      F2Procedure(6574, 2342, MA, MD, ME, rank);
      logTime(begin);
    }
    else if (rank == 3) {
      F3Procedure(P, R, MA, MD, rank);
      logTime(begin);
    }
  }

  MPI_Finalize(); // finalize MPI 
}

// ME = (A*SORT(C)) *(MA*ME+MD)
Matrix F1Procedure(Matrix A, Matrix C, Matrix MA, Matrix ME, Matrix MD, int rank) {
  cout << "F1 starts on thread with number: " << rank << endl;
  Matrix res = Matrix::multiplyOnValue(
    Matrix::add(
      Matrix::multiply(MA, ME),
      MD
    ),
    Matrix::vectorDotProduct(A, C)
  );
  cout << "F1 finished on thread with number: " << rank << endl;
  // res.displayMatrix();
  return res;
}

// MF = k*MG - h*MK*ML
Matrix F2Procedure(int k, int h, Matrix MG, Matrix MK, Matrix ML, int rank) {
  cout << "F2 starts on thread with number: " << rank << endl;
  Matrix res = Matrix::subtract(
    Matrix::multiplyOnValue(MG, k),
    Matrix::multiplyOnValue(
      Matrix::multiply(MK, ML),
      h
    )
  );
  cout << "F2 finished on thread with number: " << rank << endl;
  // res.displayMatrix();
  return res;
}

// MF = k*MG - h*MK*ML
Matrix F3Procedure(Matrix P, Matrix R, Matrix MS, Matrix MT, int rank) {
  cout << "F3 starts on thread with number: " << rank << endl;
  Matrix res = Matrix::multiply(
    Matrix::multiply(MS, MT),
    Matrix::add(P, R)
  );
  cout << "F3 finished on thread with number: " << rank << endl;
  // res.displayMatrix();
  return res;
}

void logTime(steady_clock::time_point begin) {
  steady_clock::time_point end = high_resolution_clock::now();
  duration<double, std::milli> duration = (end - begin);
  cout << "MPI execution finished with time: " << duration.count() << "\n\n";
}
