#pragma once
#include <iostream>
#include <exception>

class NumberException : public std::exception {

};

class overflow_exeption : public NumberException {
    public:
    const char* what () const throw () {
        return "El valor que se pretende almacenar requiere más dígitos de los disponibles";
    }
};

class invalid_argument_exception : public NumberException {
    public:
    const char* what () const throw () {
        return "Argumento inválido";
    }
};