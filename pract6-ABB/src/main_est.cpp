//
// Created by xavyan on 6/05/19.
//

#include <iostream>
#include "../include/DNI.hpp"
#include "../include/ABB.hpp"
#include "../include/Contador.hpp"

int main (void) {

   srand(time(NULL));

   int n, nPruebas;

   std::cout << "Indica el tamaño el arbol > ";
   std::cin >> n;
   std::cout << "Indica el numero de pruebas > ";
   std::cin >> nPruebas;

   DNI* valores = new DNI [2*n];

   ABB<DNI> arbol;

   for (int i = 0; i < n; i++) {
      arbol.insert(valores[i]);
   }

   //Imprimimos la primera fila de la tabla
   std::cout << "\t\t\tNumero de comparaciones\n";
   std::cout << "\t\tN\tPruebas\tMinimo\tMedio\tMaximo\n";

   //Empezamos con el analisis de la busqueda
   int min, acc, max;
   min = 100000000;
   acc = max = 0;
   for (int i = 0; i < n; i++) {
      ABB<DNI>::cont_.start();
      arbol.search(valores[i]);
      int resultado = ABB<DNI>::cont_.end();
      if (min > resultado) min = resultado;
      if (max < resultado) max = resultado;
      acc += resultado;
   }

   std::cout << "Busqueda\t" << n << '\t' << nPruebas << '\t' << min << '\t' << (acc/nPruebas) << '\t' << max << '\n';

   //Empezamos con el analisis de insercion
   min = 100000000;
   acc = max = 0;
   for (int i = n; i < 2*n; i++) {
      ABB<DNI>::cont_.start();
      arbol.insert(valores[i]);
      int resultado = ABB<DNI>::cont_.end();
      if (min > resultado) min = resultado;
      if (max < resultado) max = resultado;
      acc += resultado;
   }

   std::cout << "Insercion\t" << n << '\t' << nPruebas << '\t' << min << '\t' << (acc/nPruebas) << '\t' << max << '\n';

   return 0;
}