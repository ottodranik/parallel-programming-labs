#include <cmath>
#include <iostream>
#include <vector>
#include <thread>
using namespace std;

int main() {
  const int size = 50000;
  // int sinTable[size][size] {0};
  vector< vector<int> > sinTable;
  sinTable.resize(size);

  for(int i = 0 ; i < size ; ++i) {
    // Grow Columns by size
    sinTable[i].resize(size);
  }

  // unsigned int nthreads = std::thread::hardware_concurrency();
  // cout << nthreads + "\n";

  #pragma omp parallel for
  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
      sinTable[i][j] = i + j;

  // nthreads = std::thread::hardware_concurrency();
  
  // cout << nthreads + "\n";
  // for (int i = sizeof(sinTable)/sizeof(sinTable[0]) - 1; i >= 0; i--) 
  //   cout << sinTable[i];
  // cout << "\n";
  // the table is now initialized
}