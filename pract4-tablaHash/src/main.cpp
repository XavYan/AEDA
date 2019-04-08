#include <iostream>
#include "../include/Hash.hpp"
#include "../include/DNI.hpp"
#include "../include/test.hpp"

int main() {
    srand(time(NULL));
    FD fd; //Funcion dispersion
    FE fe; //Funcion exploracion
    int celdas;
    int claves;

    std::cout << "Número de celdas de la tabla: ";
    std::cin >> celdas;
    std::cout << "Número de claves por celda: ";
    std::cin >> claves;
    std::cout << "Funciones dispersión.\n";
    std::cout << "1.\tMódulo.\n";
    std::cout << "2.\tSuma.\n";
    std::cout << "3.\tPseudoaleatorio.\n";
    std::cout << "Indica el algoritmo a usar: ";
    int aux;
    std::cin >> aux;

    switch (aux) {
        case 1:
        fd = MOD;
        break;
        case 2:
        fd = ADD;
        break;
        case 3:
        fd = PSEUDO_RAND;
        break;
        default:
        std::cout << "Valor introducido incorrecto.\n";
        return -1;
    }

    std::cout << "Funciones exploración.\n";
    std::cout << "1.\tLineal.\n";
    std::cout << "2.\tCuadrática.\n";
    std::cout << "3.\tDispersión doble.\n";
    std::cout << "4.\tRe-Dispersión.\n";
    std::cout << "Indica el algoritmo a usar: ";
    std::cin >> aux;

    switch (aux) {
        case 1:
        fe = LINEAR;
        break;
        case 2:
        fe = QUADRATIC;
        break;
        case 3:
        fe = DOUBLE_DISP;
        break;
        case 4:
        fe = RE_DISP;
        break;
        default:
        std::cout << "Valor introducido incorrecto.\n";
        return -1;
    }

    //Creamos el factor y el numero de pruebas
    float factor;
    int nPruebas;

    std::cout << "Indica el factor: ";
    std::cin >> factor;
    std::cout << "Número de pruebas: ";
    std::cin >> nPruebas;

    //Creamos el banco de pruebas
    test t(factor,nPruebas,celdas,claves,fd,fe);

    //Imprimimos los datos
    system("clear");
    std::cout << "Celdas\tnClaves\tDispersión\tExploración\tCarga\tPruebas\n";
    std::cout << celdas << '\t' << claves << '\t';
    if (fd == ADD) std::cout << "ADD\t";
    if (fd == MOD) std::cout << "MOD\t";
    if (fd == PSEUDO_RAND) std::cout << "PSEUDO_RAND\t\t";

    if (fe == LINEAR) std::cout << "\tLINEAR\t\t";
    if (fe == QUADRATIC) std::cout << "QUADRATIC\t";
    if (fe == DOUBLE_DISP) std::cout << "DOUBLE_DISP\t";
    if (fe == RE_DISP) std::cout << "RE_DISP\t";

    std::cout << factor << '\t' << nPruebas << "\n\n";

    std::cout << "\t\tMínimo\tMedio\tMáximo\n";
    std::cout << "Búsquedas\t";
    t.test_search();
    std::cout << "\nInserción\t";   
    t.test_insert(); 

    return 0;
}