#include <vector>
#include <iostream>


int main() {
  int ang = 10;
  int *u = &ang; // u == alamat ang
                 //
  int **test = new int*[10]; // alamat2 -> alamat1
  for (int i = 0; i < 10; i++) {
    test[i] = new int[10];
  }
  std::cout << test[9][9];
}
