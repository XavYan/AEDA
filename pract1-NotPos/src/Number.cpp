#include "../include/Number.hpp"

template<std::size_t N, std::size_t B>
void Number<N,B,char>::to_base (int n) {
    number_.resize(N,'0');
    int div = n, it = 0;
    do {
      assert(it+1 < N);
      number_[it++] = (div%B >= 10 ? div%B+55 : div%B + '0');
      div /= B;
    } while (div >= B);
    if (div != 0) number_[it] = div + '0';
}