// C++ program to segfault on linux
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

template<class T>
void printVector(std::vector<std::vector<T>> const &matrix) {
    for (std::vector<T> row: matrix)
    {
        for (T val: row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    cout << "Let's crash for no raisin! 🧠" << endl;

    cout << "Int size: " << sizeof(int) << endl;
    for (int n=1; n < 100; n++) {
//    for (int n=1012; n < 2000; n++) {
      cout << "Declaring Matrix2D of size: " << n << "x" << n << " = " << n*n << endl;
      cout << "Bytes: " << n*n*sizeof(int) << endl;

      // segfault on my machine at 1448x1448 = 8386816 bytes
      //int Matrix2D[n][n];
      //Matrix2D[n-1][n-1] = 1; // try to trigger segfault
      //vector<vector<int>> v;
      //v.reserve(n*n*sizeof(int));
      vector<vector<int>> Matrix2D(n, std::vector<int>(n, 0));
      printVector(Matrix2D);
      // these two lines can be commented out and the program still reaches segfault
      // int* pM2D = (int*)malloc(n*n*sizeof(int));
      // free(pM2D);
    }
    return 0;
}
