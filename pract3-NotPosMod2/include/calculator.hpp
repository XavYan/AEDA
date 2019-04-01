#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <iostream>
#include <stack>
#include "../include/NumberBase.hpp"

using namespace std;

//  T=[BinaryNumber, OctalNumber, DecimalNumber, HexadecimalNumber]

template<class T>
NumberBase* calculador(istream& expresion) {
  int c, operando;
  char operador;
  NumberBase *op, *op1, *op2;
  stack<NumberBase*> pila;
  while(((c = expresion.peek()) != EOF) && (c != '=')) {
    switch(c) {
      case ' ': expresion.ignore(1); break;
      case '+':
                expresion >> operador;
                cout << "Operador: " << operador << endl; 
                op1 = pila.top();
                pila.pop();
                op2 = pila.top();
                pila.pop();
                pila.push((*op2)+(op1));
                delete op1;
                delete op2;
                break;
      case '-':
                expresion >> operador;
                cout << "Operador: " << operador << endl;
                op1 = pila.top();
                pila.pop();
                op2 = pila.top();
                pila.pop();
                pila.push((*op2)-(op1));
                delete op1;
                delete op2;
                break;
      default: expresion >> operando;
               cout << "Operando: (" << operando << ") "; 
               op = new T(operando);
               cout << *op << endl; 
               pila.push(op);
               break;
    }
  }
  return pila.top();
}

#endif

