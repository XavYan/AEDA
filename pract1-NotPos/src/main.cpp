#include "../include/Number.hpp"

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

int main (void) {
    std::cout << "Probando...\n";

    int numeros[] = { 255, 17, 11, -29, -16, -47 };
    
    //Hallamos la cantidad de numeros
    //(asi evitamos que el programos las tenga que contar)
    int cantidad = sizeof(numeros) / sizeof(int);

    for (int i = 0; i < cantidad; i++) {
        test<64>(numeros[i]);
        std::cout << "--------------------------------------------\n";
    }

    test_operation<64>(numeros[0],numeros[1]);
    //std::cout << "--------------------------------------------\n";
    //test_operation<64>(numeros[2],numeros[3]);
    //std::cout << "--------------------------------------------\n";
    //test_operation<64>(numeros[4],numeros[5]);

    return 0;
}