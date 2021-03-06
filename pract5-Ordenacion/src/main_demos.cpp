//
// Created by xavyan on 8/04/19.
// Demostration Mode
//

#include <iostream>
#include <cassert>
#include "../include/Sort.hpp"
#include "../include/DNI.hpp"

//Comprueba si los elementos estan ordenados
bool is_correct (DNI* v, int tam) {
   for (int i = 1; i < tam; i++) {
      if (v[i-1] > v[i]) return false;
   }
   return true;
}

int main (void) {
   srand(time(NULL)); //Establecemos la semilla

   int tam = 25;
   while (tam >= 25) {
      std::cout << "Indica el número de elementos a ordenar (máx. 25) > ";
      std::cin >> tam;
      if (tam >= 25) std::cout << "Debes introducir un dato mayor a 25.\n";
   }

   std::cout << "Los algoritmos disponibles son:\n";
   std::cout << "1. Ordenación por selección.\n";
   std::cout << "2. Método de la sacudida.\n";
   std::cout << "3. Método HeapSort.\n";
   std::cout << "4. Método MergeSort.\n";
   std::cout << "5. Método ShellSort.\n";
   sMethods sM;
   unsigned short algoritmo;
   float alpha = 1;
   std::cout << "Indica el algoritmo a usar > ";
   std::cin >> algoritmo;
   switch (algoritmo) {
      case 1:
         sM = SELECT;
         break;
      case 2:
         sM = CHANGE;
         break;
      case 3:
         sM = HEAPSORT;
         break;
      case 4:
         sM = MERGESORT;
         break;
      case 5:
         sM = SHELLSORT;
         while (alpha < 0 || alpha > 1) {
            std::cout << "Indica el valor del factor > ";
            std::cin >> alpha;
            if (alpha < 0 || alpha > 1) std::cout << "El factor debe estar entre 0 y 1.\n";
         }
         break;
      default:
         std::cout << "Dato introducido incorrecto. Ejecutando algoritmo por defecto: MERGESORT.\n";
   }

   //Generamos el vector de DNI's
   DNI* v = new DNI [tam];

   std::cout << "\nVector sin ordenar: ";
   for (int i = 0; i < tam; i++) {
      std::cout << "[" << v[i] << "] ";
   }
   std::cout << "\n\n";

   //Empezamos la ejecucion una vez el usuario ha pulsado una tecla
   std::cout << "Listo para realizar la demostracion. Pulsa una tecla para empezar la ejecución...";
   std::cin.ignore();
   getchar();

   int dummy; //Simplemente para engañar al constructor
   Sort<DNI> SV (v, tam, sM, dummy, 0, alpha); //El mode = 0 significa que se trata del modo demostracion

   std::cout << "\nResultado de la ordenacion: ";
   SV.write(std::cout);
   std::cout << '\n';

   std::cout << "El resultado " << (is_correct(SV.to_ptr(),tam) ? "" : "no ") << "es correcto.\n";

   return 0;
}