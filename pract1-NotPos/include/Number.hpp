#pragma once

#include <iostream>
#include <vector>

//Los unsigned char usan un rango entre 0 y 255. Los char usan valores con signo
template<size_t N, size_t B, class T>
class Number {
private:
  vector<int> number_;
  bool sign_;
public:

  Number (int value = 0);
  ~Number (void);

  ostream& write (ostream& os) const;

  //Realizar las operaciones basicas: suma, resta, multiplicacion y division.

private:
  //Calcula los 0's y 1's del numero con respecto de la base mediante el resto de las divisiones del valor actual entre la base,
  //y lo devuelve en un vector.
  void to_base(int n);
};
