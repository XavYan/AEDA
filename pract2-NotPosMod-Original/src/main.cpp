#include "../include/Number.hpp"
#include <string>
#include "../include/NumberException.hpp"

template <size_t N, class T = char>
void test (int num) {
    std::cout << "[VALOR ACTUAL]\t" << num << '\n';

    try {
        std::cout << "[DECIMAL]\t";
        Number<N,10,T> decimal(num);
        std::cout << decimal << '\n';
    }
    catch (NumberException& e) {
        std::cout << "Error al crear el dígito en decimal: " << e.what() << '\n';
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

    try {
        std::cout << "[BINARIO]\t";
        Number<N,2,T> binary(num);
        std::cout << binary << '\n';
    }
    catch (NumberException& e) {
        std::cout << "Error al crear el dígito en binario: " << e.what() << '\n';
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

    if (std::is_same<T, char>::value) {
        try {
            std::cout << "[HEXADECIMAL]\t";
            Number<N,16,T> hex(num);
            std::cout << hex << '\n';
        }
        catch (NumberException& e) {
            std::cout << "Error al crear el dígito en hexadecimal: " << e.what() << '\n';
        }
        catch (std::exception& e) {
            std::cout << e.what() << '\n';
        }
    }
}

template <std::size_t N, class T = char>
void test_operation (const int num1, const int num2) {
    std::cout << "[NUMEROS] {" << num1 << "," << num2 << "}\n";
    std::cout << "para N = " << N << '\n';
    Number<N,10,T> d1(num1), d2(num2);
    std::cout << "[OPERACIONES EN DECIMAL] {" << d1 << "," << d2 << "}\n";
    //Suma
    try {
        std::cout << "(" << d1 << ") + (" << d2 << ") = " << d1 + d2 << '\n';
    } catch (NumberException& e) {
        std::cout << "Problema al realizar (" << d1 << ") + (" << d2 << "): " << e.what() << '\n';
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
    //Resta
    try {
        std::cout << "(" << d1 << ") - (" << d2 << ") = " << d1 - d2 << '\n';
    } catch (NumberException& e) {
        std::cout << "Problema al realizar (" << d1 << ") - (" << d2 << "): " << e.what() << '\n';
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
    //Multiplicacion
    try {
        std::cout << "(" << d1 << ") * (" << d2 << ") = " << d1 * d2 << '\n';
    } catch (NumberException& e) {
        std::cout << "Problema al realizar (" << d1 << ") * (" << d2 << "): " << e.what() << '\n';
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
    //Division
    try {
        std::cout << "(" << d1 << ") / (" << d2 << ") = " << d1 / d2 << '\n';
    } catch (NumberException& e) {
        std::cout << "Problema al realizar (" << d1 << ") / (" << d2 << "): " << e.what() << '\n';
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

    Number<N,2,T> b1(num1), b2(num2);
    std::cout << "[OPERACIONES EN BINARIO] {" << b1 << "," << b2 << "}\n";
    //Suma
    try {
        std::cout << "(" << b1 << ") + (" << b2 << ") = " << b1 + b2 << '\n';
    } catch (NumberException& e) {
        std::cout << "Problema al realizar (" << b1 << ") + (" << b2 << "): " << e.what() << '\n';
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
    //Resta
    try {
        std::cout << "(" << b1 << ") - (" << b2 << ") = " << b1 - b2 << '\n';
    } catch (NumberException& e) {
        std::cout << "Problema al realizar (" << b1 << ") - (" << b2 << "): " << e.what() << '\n';
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
    //Multiplicacion
    try {
        std::cout << "(" << b1 << ") * (" << b2 << ") = " << b1 * b2 << '\n';
    } catch (NumberException& e) {
        std::cout << "Problema al realizar (" << b1 << ") * (" << b2 << "): " << e.what() << '\n';
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
    //Division
    try {
        std::cout << "(" << b1 << ") / (" << b2 << ") = " << b1 / b2 << '\n';
    } catch (NumberException& e) {
        std::cout << "Problema al realizar (" << b1 << ") / (" << b2 << "): " << e.what() << '\n';
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }


    if (std::is_same<T,char>::value) {
        Number<N,16,T> h1(num1), h2(num2);
        std::cout << "[OPERACIONES EN HEXADECIMAL] {" << h1 << "," << h2 << "}\n";
        //Suma
        try {
            std::cout << "(" << h1 << ") + (" << h2 << ") = " << h1 + h2 << '\n';
        } catch (NumberException& e) {
            std::cout << "Problema al realizar (" << h1 << ") + (" << h2 << "): " << e.what() << '\n';
        } catch (std::exception& e) {
            std::cout << e.what() << '\n';
        }
        //Resta
        try {
            std::cout << "(" << h1 << ") - (" << h2 << ") = " << h1 - h2 << '\n';
        } catch (NumberException& e) {
            std::cout << "Problema al realizar (" << h1 << ") - (" << h2 << "): " << e.what() << '\n';
        } catch (std::exception& e) {
            std::cout << e.what() << '\n';
        }
        //Multiplicacion
        try {
            std::cout << "(" << h1 << ") * (" << h2 << ") = " << h1 * h2 << '\n';
        } catch (NumberException& e) {
            std::cout << "Problema al realizar (" << h1 << ") * (" << h2 << "): " << e.what() << '\n';
        } catch (std::exception& e) {
            std::cout << e.what() << '\n';
        }
        //Division
        try {
            std::cout << "(" << h1 << ") / (" << h2 << ") = " << h1 / h2 << '\n';
        } catch (NumberException& e) {
            std::cout << "Problema al realizar (" << h1 << ") / (" << h2 << "): " << e.what() << '\n';
        } catch (std::exception& e) {
            std::cout << e.what() << '\n';
        }
    }
}

int main (int argc, char* argv[]) {

    int numeros[] = { 2, 0, -8, 7, -6, 5 };

    int cantidad = sizeof(numeros) / sizeof(int);
    test_operation<4>(numeros[0],numeros[1]);
    std::cout << "--------------------------------------------\n";
    // test<10>(numeros[2]);
    // test<10>(numeros[3]);
    test_operation<4>(numeros[2],numeros[3]);
    std::cout << "--------------------------------------------\n";
    test_operation<4>(numeros[cantidad-2],numeros[cantidad-1]);
    return 0;
}