#include <iostream>
#include "../include/Hash.hpp"
#include "../include/DNI.hpp"

int main() {
    srand(time(NULL));
    tablaHash<DNI> table(10,1,MOD,LINEAR);
    std::cout << "Tabla creada\n";
    DNI* dni = new DNI [10];
    for (int i = 0; i < 10; i++) {
        bool correct = table.insert(dni[i]);
        if (correct) {
            std::cout << "DNI " << dni[i] << " insertado correctamente\n";
        } else {
            std::cout << "Fallo al insertar DNI " << dni[i] << '\n';
        }
    }

    for (int i = 0; i < 10; i++) {
        std::cout << "Buscando..." << dni[i] << '\n';
        bool found = table.search(dni[i]);
        if (found) {
            std::cout << "Encontrado\n";
        } else {
            std::cout << "No encontrado\n";
        }
    }
    return 0;
}