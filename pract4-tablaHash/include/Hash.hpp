#pragma once

#include <iostream>
#include <vector>
#include "Celda.hpp"
#include "FDispersion.hpp"
#include "FExploracion.hpp"
#include "Contador.hpp"

template<class CLAVE>
class tablaHash {
    private:
    std::vector<Celda<CLAVE> > vCeldas_;
    int nCeldas_;
    FDispersionBase<CLAVE>* H_;
    FExploracionBase<CLAVE>* F_;

    public:
    Contador cont_;

    public:
    tablaHash (int nCeldas, int nClaves, FD fd, FE fe);
    ~tablaHash (void);

    bool search (const CLAVE& x);
    bool insert (const CLAVE& x);

    Contador& get_cont (void);
};

template <class CLAVE>
tablaHash<CLAVE>::tablaHash (int nCeldas, int nClaves, FD fd, FE fe) {
    
    nCeldas_ = nCeldas;
    for (int i = 0; i < nCeldas_; i++) {
        vCeldas_.emplace(vCeldas_.begin() + i, nClaves);
    }

    switch (fd) {
        case ADD:
        H_ = new FDispersionSum<CLAVE>(nCeldas_);
        break;
        case PSEUDO_RAND:
        H_ = new FDispersionPseudo<CLAVE>(nCeldas_);
        break;
        case MOD:
        H_ = new FDispersionMod<CLAVE>(nCeldas_);
        break;
    }

    switch (fe) {
        case LINEAR:
        F_ = new FExploracionLineal<CLAVE>(nCeldas_,H_);
        break;
        case QUADRATIC:
        F_ = new FExploracionCuadrado<CLAVE>(nCeldas_,H_);
        break;
        case DOUBLE_DISP:
        F_ = new FExploracionDispDoble<CLAVE>(nCeldas_,H_);
        break;
        case RE_DISP:
        F_ = new FExploracionReDisp<CLAVE>(nCeldas_,H_);
    }
}

template <class CLAVE>
tablaHash<CLAVE>::~tablaHash (void) {
    vCeldas_.clear();
    delete H_;
    delete F_;

    H_ = NULL;
    F_ = NULL;
}

template <class CLAVE>
bool tablaHash<CLAVE>::search (const CLAVE& x) {

    ++cont_;
    if (vCeldas_[H_->operator()(x)].search(x)) {
        return true;
    } else {
        if (!vCeldas_[H_->operator()(x)].is_full()) {
            return false;
        }
        for (int i = 0; i < nCeldas_; i++) {
            ++cont_;
            if (vCeldas_[F_->operator()(x,i)].search(x)) {
                return true;
            }
            if (!vCeldas_[F_->operator()(x,i)].is_full()) {
                return false;
            }
        }
    }
    return false;
}

template <class CLAVE>
bool tablaHash<CLAVE>::insert (const CLAVE& x) {

    ++cont_;
    bool inserted = vCeldas_[H_->operator()(x)].insert(x);
    // std::cout << "Hemos insertado la celda en la posicion:" << H_->operator()(x) << '\n';
    if (inserted) return true;

    // std::cout << "No se pudo insertar el elemento. Usando funcion exploracion\n";

    for (int i = 0; i < nCeldas_; i++) {
        ++cont_;
        inserted = vCeldas_[F_->operator()(x, i)].insert(x);
        if (inserted) return true;
    }
    return false;
}

template <class CLAVE>
Contador& tablaHash<CLAVE>::get_cont (void) {
    return cont_;
}