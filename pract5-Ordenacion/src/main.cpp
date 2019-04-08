//
// Created by xavyan on 8/04/19.
//

#include <iostream>
#include "../include/sort_methods.hpp"
#include "../include/DNI.hpp"

int main (void) {
   srand(time(NULL));
   int n;
   std::cout << "Introduce numero de elementos: ";
   std::cin >> n;
   DNI* v_dni = new DNI [n];
   DNI* v_dni2 = new DNI [n];
   std::cout << "Vector 1: ";
   for (int i = 0; i < n; i++) {
      std::cout << v_dni[i] << " ";
      v_dni2[i] = v_dni[i];
   }
   std::cout << "\nEjecutando el algoritmo de seleccion...\n";
   sort_by_selection(v_dni,n);
   std::cout << "Vector ordenado: ";
   for (int i = 0; i < n; i++) {
      std::cout << v_dni[i] << " ";
   }
   std::cout << '\n';
   std::cout << "Vector 2: ";
   for (int i = 0; i < n; i++) {
      std::cout << v_dni2[i] << " ";
   }
   std::cout << "\nEjecutando metodo de la sacudida...\n";
   sort_by_change(v_dni2,n);
   std::cout << "Vector ordenado: ";
   for (int i = 0; i < n; i++) {
      std::cout << v_dni2[i] << " ";
   }
   std::cout << '\n';
   std::cout << "Los resultados " << (v_dni == v_dni2 ? "" : "no ") << "coinciden\n";
}