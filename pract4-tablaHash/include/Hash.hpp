#pragma once

#include <iostream>
#include "Celda.hpp"
#include "FDispersion.hpp"
#include "FExploracion.hpp"

template<class CLAVE>
class tablaHash {
    private:
    Celda<CLAVE>* vCeldas_;
    int nCeldas_;
    FDispersionBase<CLAVE>* h_;
    FExploracionBase<CLAVE>* f_;

    public:
    tablaHash (int nCeldas, int n, FD fd, FE fe);
    ~tablaHash (void);

    bool search (const CLAVE& x);
    bool insert (const CLAVE& x);
};

template <class CLAVE>
tablaHash<CLAVE>::tablaHash (int nCeldas, int n, FD fd, FE fe) {
    
    nCeldas_ = nCeldas;
    vCeldas_ = new Celda<CLAVE>(nCeldas_);

    switch (fd) {
        case ADD:
        h_ = new FDispersionSum<CLAVE>(nCeldas_);
        break;
        case PSEUDO_RAND:
        h_ = new FDispersionPseudo<CLAVE>(nCeldas_);
        break;
        case MOD:
        h_ = new FDispersionMod<CLAVE>(nCeldas_);
        break;
    }

    switch (fe) {
        case LINEAR:
        f_ = new FExploracionLineal<CLAVE>(nCeldas_);
        break;
        case QUADRATIC:
        f_ = new FExploracionCuadrado<CLAVE>(nCeldas_);
        break;
        case DOUBLE_DISP:
        f_ = new FExploracionDispDoble<CLAVE>(nCeldas_);
        break;
        case RE_DISP:
        f_ = new FExploracionReDisp<CLAVE>(nCeldas_);
    }
}

template <class CLAVE>
tablaHash<CLAVE>::~tablaHash (void) {
    delete [] vCeldas_;
    delete h_;
    delete f_;

    vCeldas_ = NULL;
    h_ = NULL;
    f_ = NULL;
}

template <class CLAVE>
bool tablaHash<CLAVE>::search (const CLAVE& x) {
    for (int i = 0; i < nCeldas_; i++) {
        if (vCeldas_[i].search(x)) {
            return true;
        }
        if (!vCeldas_.is_full()) {
            return false;
        }
    }
    return false;
}

template <class CLAVE>
bool tablaHash<CLAVE>::insert (const CLAVE& x) {
    int dir = *h_(x);

    bool inserted = vCeldas_[dir].insert(x);
    if (inserted) return true;

    for (int i = 0; i < nCeldas_; i++) {
        dir = *f_(x,i);
        inserted = vCeldas_[dir].insert(x);
        if (inserted) return true;
    }
}