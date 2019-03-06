#include "../include/Number.hpp"
#include <string>

template <size_t N, class T = char>
void test (int num) {
    std::cout << "[VALOR ACTUAL]\t" << num << '\n';
    std::cout << "[DECIMAL]\t";
    Number<N,10,T> decimal(num);
    std::cout << decimal << '\n';
    std::cout << "[BINARIO]\t";
    Number<N,2,T> binary(num);
    std::cout << binary << '\n';
    std::cout << "[OCTAL]\t\t";
    Number<N,8,T> octal(num);
    std::cout << octal << '\n';
    if (std::is_same<T, char>::value) {
        std::cout << "[HEXADECIMAL]\t";
        Number<N,16,T> hex(num);
        std::cout << hex << '\n';
    }
}

template <std::size_t N, class T = char>
void test_operation (const int num1, const int num2) {
    std::cout << "[NUMEROS] {" << num1 << "," << num2 << "}\n";
    Number<N,10,T> d1(num1), d2(num2);
    std::cout << "[OPERACIONES EN DECIMAL] {" << d1 << "," << d2 << "}\n";
    std::cout << "(" << d1 << ") + (" << d2 << ") = " << d1 + d2 << '\n';
    std::cout << "(" << d1 << ") - (" << d2 << ") = " << d1 - d2 << '\n';
    std::cout << "(" << d1 << ") * (" << d2 << ") = " << d1 * d2 << '\n';
    std::cout << "(" << d1 << ") / (" << d2 << ") = " << d1 / d2 << '\n';

    Number<N,2,T> b1(num1), b2(num2);
    std::cout << "[OPERACIONES EN BINARIO] {" << b1 << "," << b2 << "}\n";
    std::cout << "(" << b1 << ") + (" << b2 << ") = " << b1 + b2 << '\n';
    std::cout << "(" << b1 << ") - (" << b2 << ") = " << b1 - b2 << '\n';
    std::cout << "(" << b1 << ") * (" << b2 << ") = " << b1 * b2 << '\n';
    std::cout << "(" << b1 << ") / (" << b2 << ") = " << b1 / b2 << '\n';
    if (std::is_same<T,char>::value) {
        Number<N,16,T> h1(num1), h2(num2);
        std::cout << "[OPERACIONES EN HEXADECIMAL] {" << h1 << "," << h2 << "}\n";
        std::cout << "(" << h1 << ") + (" << h2 << ") = " << h1 + h2 << '\n';
        std::cout << "(" << h1 << ") - (" << h2 << ") = " << h1 - h2 << '\n';
        std::cout << "(" << h1 << ") * (" << h2 << ") = " << h1 * h2 << '\n';
        std::cout << "(" << h1 << ") / (" << h2 << ") = " << h1 / h2 << '\n';
    }
}

int main (int argc, char* argv[]) {
    // std::cout << "Probando...\n";

    int numeros[] = { 25, 5, -10, 5, 3, 6, -1, -3, -2, 0 };

    int cantidad = sizeof(numeros) / sizeof(int);
    
    //Si no hay argumentos por consola, utiliza los descritos en el vector numeros
    /*if (argc <= 1) {

        //Hallamos la cantidad de numeros
        //(asi evitamos que el programos las tenga que contar)

        for (int i = 1; i < cantidad; i++) {
            test<64>(numeros[i]);
            std::cout << "--------------------------------------------\n";
        }
    } else {
        for (int i = 1; i < argc; i++) {
            std::string str(argv[i]);
            test<64>(std::stoi(str));
            std::cout << "--------------------------------------------\n";
        }
    }*/

    test_operation<10>(numeros[0],numeros[1]);
    std::cout << "--------------------------------------------\n";
    test_operation<10>(numeros[2],numeros[3]);
    std::cout << "--------------------------------------------\n";
    test_operation<10>(numeros[cantidad-2],numeros[cantidad-1]);

    return 0;
}