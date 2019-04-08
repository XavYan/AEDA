#pragma once

#include <iostream>
#include<vector>

/*
    El -1 indica que esta vacio
    El -2 indica que se ha borrado un dato
*/

template<class CLAVE>
class Celda {
    private:

    int nClaves_; //Cantidad de bloques totales
    int nBloques_; //Registra la cantidad de bloques ocupados
    std::vector<CLAVE> v_;
    
    public:

    Celda (int nClaves);
    ~Celda (void);
    
    bool search (CLAVE key);
    bool insert (CLAVE key);
    bool is_full (void);
};

template<class CLAVE>
Celda<CLAVE>::Celda (int nClaves) {
    nClaves_ = nClaves;
    nBloques_ = 0;
    v_.resize(nClaves_);
}

template<class CLAVE>
Celda<CLAVE>::~Celda (void) {
    v_.clear();
}

template<class CLAVE>
bool Celda<CLAVE>::search (CLAVE key) {
    for (int i = 0; i < nClaves_; i++) {
        if (key == v_[i]) {
            return true;
        }
    }
    return false;
}

template<class CLAVE>
bool Celda<CLAVE>::insert (CLAVE key) {
    if (is_full()) return false;
    v_[nBloques_] = key;
    nBloques_++;
    return true;
}

template<class CLAVE>
bool Celda<CLAVE>::is_full (void) {

    return (nBloques_ >= nClaves_ ? true : false);
}