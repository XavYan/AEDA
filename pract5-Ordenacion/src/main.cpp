//
// Created by xavyan on 8/04/19.
//

#include <iostream>
#include "../include/sort_methods.hpp"
#include "../include/DNI.hpp"

bool is_equal (DNI* v1, DNI* v2, int tam) {
   for (int i = 0; i < tam; i++) {
      if (v1[i] != v2[i]) return false;
   }
   return true;
}

bool is_correct (DNI* v, int tam) {
   for (int i = 1; i < tam; i++) {
      if (v[i-1] > v[i]) return false;
   }
   return true;
}

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
  /* std::cout << "\nEjecutando el algoritmo de seleccion...\n";
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
   std::cout << '\n';*/
   /*std::cout << "\nEjecutando ordenacion heapsort...\n";
   sort_by_heapsort(v_dni,n);
   std::cout << "Vector ordenado: ";
   for (int i = 0; i < n; i++) {
      std::cout << v_dni[i] << " ";
   }
   if (is_correct(v_dni,n)) std::cout << "CORRECTO\n"; else std::cout << "INCORRECTO\n";*/

  /* std::cout << "\nEjecutando ordenacion mergesort...\n";
   sort_by_mergesort(v_dni,n, 0, n-1);
   std::cout << "Vector ordenado: ";
   for (int i = 0; i < n; i++) {
      std::cout << v_dni[i] << " ";
   }
   if (is_correct(v_dni,n)) std::cout << "CORRECTO\n"; else std::cout << "INCORRECTO\n";*/

    std::cout << "\nEjecutando ordenacion shellSort...\n";
    std::cout << "Indica el valor de alpha (0 < alpha < 1): ";
    float alpha;
    std::cin >> alpha;
    sort_by_shellSort(v_dni,n, alpha*n);
    std::cout << "Vector ordenado: ";
    for (int i = 0; i < n; i++) {
       std::cout << v_dni[i] << " ";
    }
    if (is_correct(v_dni,n)) std::cout << "CORRECTO\n"; else std::cout << "INCORRECTO\n";
   return 0;
}