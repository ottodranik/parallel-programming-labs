#include <iostream>

int main(){
  // Code inside this region runs in parallel.
  #pragma omp parallel
  {
    printf("Hello!\n");
  }
}

void function_1()
{
    #pragma omp parallel for ordered
    for (int i = 0; i != 100; i++)
    {
        std::cout << "Function 1 (i = " << i << ")" << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void function_2()
{
    #pragma omp parallel for ordered
    for (int j = 0; j != 100; j++)
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "                   Function 2 "
                  << "(j = " << j << ")" << std::endl;
    }
}

long getTime(long nanoValue) {
  return nanoValue/1000000;
}