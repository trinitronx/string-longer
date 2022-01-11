// C++ program to segfault
#include<bits/stdc++.h>

using namespace std;

int main()
{
    cout << "Let's crash for no raisin! 🧠" << endl;

    cout << "Int size: " << sizeof(int) << endl;
    for (int n=1012; n < 2000; n++) {
      cout << "Declaring Matrix2D of size: " << n << "x" << n << " = " << n*n << endl;
      cout << "Bytes: " << n*n*sizeof(int) << endl;

      // segfault on my machine at 1448x1448 = 8386816 bytes
      int Matrix2D[n][n];
      // these two lines can be commented out and the program still reaches segfault
      // int* pM2D = (int*)malloc(n*n*sizeof(int));
      // free(pM2D);
    }
    return 0;
}
