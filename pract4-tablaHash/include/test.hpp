#pragma once

#include "DNI.hpp"
#include "Hash.hpp"
#include <vector>

class test {
    private:
    float factor_;
    unsigned int nPruebas_; //Numero de repeticiones

    std::vector<DNI> v_; //DNI a probar
    tablaHash<DNI> table_; //Tabla hash
    int N_; //Numero de DNI's a probar

    int min_;
    int max_;
    int acc_;

  public:
    test (float factor, unsigned int nPruebas, int nCeldas, int nClaves, FD fd, FE fe);
    ~test (void);

    void test_insert (void);
    void test_search (void);
};