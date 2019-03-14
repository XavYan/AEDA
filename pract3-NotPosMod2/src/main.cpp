#include "../include/NumberBasics.hpp"
#include "../include/NumberException.hpp"

int main (int argc, char* argv[]) {

    try {
        int base, num1, num2;
        std::cout << "Indica la base de los numeros: ";
        std::cin >> base;
        std::cout << "Numero 1: ";
        std::cin >> num1;
        std::cout << "Numero 2: ";
        std::cin >> num2;
        NumberBase* num_ptr1;
        NumberBase* num_ptr2;
        if (base == 2) {
            num_ptr1 = new BinaryNumber(num1);
            num_ptr2 = new BinaryNumber(num2);
        }
    }
    catch (NumberException& e) {
        std::cerr << "Error. " << e.what() << '\n';
    }
    catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    catch (...) {
        std::cerr << "Error desconocido.\n";
    }
    return 0;
}