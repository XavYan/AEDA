#pragma once

#include <iostream>
#include <iomanip>

#define MAX_DNI 100000000;

class DNI {
    private:
    unsigned long dato_;

    public:
    DNI (void);
    DNI (const unsigned long i);
    ~DNI (void);

    //Operadores
    bool operator== (const DNI& dni);
    bool operator> (const DNI& dni);
    bool operator< (const DNI& dni);

    operator unsigned long (void) const;

    friend std::ostream& operator<< (std::ostream& os, const DNI& dni);

};