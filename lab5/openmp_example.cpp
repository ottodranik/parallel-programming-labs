#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  const int size = 10;
  // int sinTable[size][size] {0};
  vector< vector<int> > sinTable;
  sinTable.resize(size);

  for(int i = 0 ; i < size ; ++i) {
    // Grow Columns by size
    sinTable[i].resize(size);
  }
  
  #pragma omp parallel
  {
    #pragma omp for
    for (int i = 0; i < size; ++i)
      // for (int j = 0; j < size; ++j)
      printf("%d", i);
  }
  
  // for (int i = sizeof(sinTable)/sizeof(sinTable[0]) - 1; i >= 0; i--) 
  //   cout << sinTable[i];
  // cout << "\n";
  // the table is now initialized
}