//
// Created by xavyan on 22/04/19.
// Estatistic Mode
//

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include "../include/Sort.hpp"
#include "../include/DNI.hpp"

//Comprueba si dos vectores de DNI son iguales (para comparar dos tipos de ordenacion diferentes, y ver si coinciden)
bool is_equal (DNI* v1, DNI* v2, int tam) {
   for (int i = 0; i < tam; i++) {
      if (v1[i] != v2[i]) return false;
   }
   return true;
}

//Comprueba si los elementos estan ordenados
bool is_correct (DNI* v, int tam) {
   for (int i = 1; i < tam; i++) {
      if (v[i-1] > v[i]) return false;
   }
   return true;
}

int main (void) {
   srand(time(NULL)); //Establecemos la semilla

   int tam, nPruebas;

   std::cout << "Introduce el tamaño de la secuencia a ordenar > ";
   std::cin >> tam; //Numero total de elementos a ordenar

   std::cout << "Introduce el numero de pruebas a ejecutar > ";
   std::cin >> nPruebas; //Veces que se repite la ejecucion de cada metodo (conjunto de tam elementos

   //Creamos el conjunto de vectores con los que hacer las pruebas
   DNI** pruebas = new DNI* [nPruebas];

   //Creamos los vectores de DNI
   for (int i = 0; i < nPruebas; i++) {
      pruebas[i] = new DNI [tam];
   }

   //Mostramos los valores
   /*for (int i = 0; i < nPruebas; i++) {
      std::cout << "Elemento " << i+1 << ": ";
      for (int j = 0; j < tam; j++) {
         std::cout << "[" << pruebas[i][j] << "] ";
      }
      std::cout << '\n';
   }*/

   std::cout << "\t\tNumero de Comparaciones\n";
   std::cout << "\t\tMinimo\tMedio\tMaximo\n";

   //Metodo de la seleccion
   std::cout << "Seleccion\t";

   int min = 100000000;
   int max = 0;
   int acc = 0;
   for (int i = 0; i < nPruebas; i++) {
      int aux = 0;
      Sort<DNI> SV (pruebas[i], tam, SELECT, aux, 1);
      //Actualizamos los valores minimo y maximo
      acc += aux;
      if (min > aux) min = aux;
      if (max < aux) max = aux;
   }

   std::cout << min << '\t' << acc/nPruebas << '\t' << max << '\n';

   //Metodo de la sacudida
   std::cout << "Sacudida\t";

   int min2 = 100000000;
   int max2 = 0;
   int acc2 = 0;
   for (int i = 0; i < nPruebas; i++) {
      int aux = 0;
      Sort<DNI> SV (pruebas[i], tam, CHANGE, aux, 1);
      //Actualizamos los valores minimo y maximo
      acc2 += aux;
      if (min2 > aux) min2 = aux;
      if (max2 < aux) max2 = aux;
   }

   std::cout << min2 << '\t' << acc2/nPruebas << '\t' << max2 << '\n';

   //Metodo de heapsort
   std::cout << "HeapSort\t";

   int min3 = 100000000;
   int max3 = 0;
   int acc3 = 0;
   for (int i = 0; i < nPruebas; i++) {
      int aux = 0;
      Sort<DNI> SV (pruebas[i], tam, HEAPSORT, aux, 1);
      //Actualizamos los valores minimo y maximo
      acc3 += aux;
      if (min3 > aux) min3 = aux;
      if (max3 < aux) max3 = aux;
   }

   std::cout << min3 << '\t' << acc3/nPruebas << '\t' << max3 << '\n';

   //Metodo de mergesort
   std::cout << "MergeSort\t";

   int min4 = 100000000;
   int max4 = 0;
   int acc4 = 0;
   for (int i = 0; i < nPruebas; i++) {
      int aux = 0;
      Sort<DNI> SV (pruebas[i], tam, MERGESORT, aux, 1);
      //Actualizamos los valores minimo y maximo
      acc4 += aux;
      if (min4 > aux) min4 = aux;
      if (max4 < aux) max4 = aux;
   }

   std::cout << min4 << '\t' << acc4/nPruebas << '\t' << max4 << '\n';

   //Metodo ShellSort
   std::cout << "ShellSort\t";

   int min5 = 100000000;
   int max5 = 0;
   int acc5 = 0;
   for (int i = 0; i < nPruebas; i++) {
      int aux = 0;
      Sort<DNI> SV (pruebas[i], tam, SHELLSORT, aux, 1);
      //Actualizamos los valores minimo y maximo
      acc5 += aux;
      if (min5 > aux) min5 = aux;
      if (max5 < aux) max5 = aux;
   }

   std::cout << min5 << '\t' << acc5/nPruebas << '\t' << max5 << '\n';

   return 0;
}
