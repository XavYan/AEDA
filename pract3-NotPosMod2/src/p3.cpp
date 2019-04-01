#include <iostream>
#include <string>
#include <sstream>
#include "../include/calculator.hpp"
#include "../include/NumberBasics.hpp"
using namespace std;

int main() {

  string expr_str( "4 3 + 7 -");
  istringstream expresion(expr_str);

  cout << expr_str << " =\n" << *calculador<DecimalNumber>(expresion) << endl;

  expresion.seekg(0, expresion.beg);
  cout << expr_str << " =\n" << *calculador<BinaryNumber>(expresion) << endl;

  expresion.seekg(0, expresion.beg);
  cout << expr_str << " =\n" << *calculador<OctalNumber>(expresion) << endl;

  cout << "Postfix expresion = " << *calculador<HexadecimalNumber>(cin) << endl;

  return 0;
}
