#include "../include/Number.hpp"

template<size_t N, size_t B, class T>
Number::Number (int value) {
  to_base(value);
}

template<size_t N, size_t B, class T>
Number::~Number (void) {}

template<size_t N, size_t B, class T>
ostream& Number::write (ostream& os) const {
  for (int i = 0; i < number_.size(); i++) {
    os << number_[i];
  }
  os << '\n';
  return os;
}

//METODOS PRIVADOS///////////////////////////////////////////
template<size_t N, size_t B, class T>
void Number::to_base (int n) {
  number_.resize(N,0);
  int div = n, it = N;
  while (aux >= B) {
    number_[it--] = div%B; //Hay que tener en cuenta el hecho de que it no llegue a -1 y asegurarse que N es suficiente para almacenar el valor.
    div /= B;
  }
}
