#include <string>
#include "../include/NumberBasics.hpp"

int main (int argc, char* argv[]) {

    int N1 = 0, N2 = 0, base = 0;

    std::cout << "Indica la base: ";
    std::cin >> base;
    std::cout << "Numero 1: ";
    std::cin >> N1;
    std::cout << "Numero 2: ";
    std::cin >> N2;


    //Creamos los numeros
    NumberBase* num1;
    NumberBase* num2;
    switch (base) {
        case 2:
        num1 = new BinaryNumber(N1);
        num2 = new BinaryNumber(N2);
        break;
        case 8:
        num1 = new OctalNumber(N1);
        num2 = new OctalNumber(N2);
        break;
        case 10:
        num1 = new DecimalNumber(N1);
        num2 = new DecimalNumber(N2);
        break;
        case 16:
        num1 = new HexadecimalNumber(N1);
        num2 = new HexadecimalNumber(N2);
        break;
        default:
        std::cout << "La base no se puede usar.\n";
        return -1;
    }

    std::cout << num1 << " + " << num2 << " = " << ((*num1) + num2) << '\n';
    std::cout << num1 << " - " << num2 << " = " << ((*num1) - num2) << '\n';
    // std::cout << num1 << " * " << num2 << " = " << ((*num1) * num2) << '\n'; //La multiplicacion no funciona con este metodo
    std::cout << num1 << " / " << num2 << " = " << ((*num1) / num2) << '\n';

    delete num1;
    delete num2;

    return 0;
}
