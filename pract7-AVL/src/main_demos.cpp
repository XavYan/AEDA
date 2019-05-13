//
// Created by xavyan on 3/05/19.
//

#include "../include/AVL.hpp"
#include "../include/DNI.hpp"

int main (void) {
   int opcion = 0;

   //Creamos el arbol vacio
   AVL<int> arbol;

   do {

      std::cout << "---- MENU ----\n";
      std::cout << "[0] Salir\n";
      std::cout << "[1] Insertar Clave\n";
      std::cout << "[2] Eliminar Clave\n";
      std::cout << "\n";

      std::cout << "ARBOL BINARIO DE BUSQUEDA BALANCEADO\n";
      arbol.write(std::cout);
      std::cout << "\n\n";

      std::cout << "Elige opcion > ";
      std::cin >> opcion;

      switch (opcion) {
         case 0: {
            std::cout << "Has salido del programa. Gracias por usar nuestro software!\n";
            break;
         }
         case 1: {
            std::cout << "Insertar: ";
            int dato;
            std::cin >> dato;
            arbol.insertar(dato); //Insertamos el dato
            break;
         }
         case 2: {
            std::cout << "Eliminar: ";
            int dato;
            std::cin >> dato;
            arbol.eliminar(dato); //Eliminamos el dato
            break;
         }
         default:
            std::cout << "Elige una opcion entre las indicadas\n";
      }

   } while (opcion != 0);
}