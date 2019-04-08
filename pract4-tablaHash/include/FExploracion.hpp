#pragma once

#include <cmath>
#include "FDispersion.hpp"

enum FE { LINEAR, QUADRATIC, DOUBLE_DISP, RE_DISP };

template <class CLAVE>
class FExploracionBase {
    public:
    FExploracionBase (void);
    virtual ~FExploracionBase (void);

    virtual int operator() (const CLAVE& x, const int& i) = 0;
};

template <class CLAVE>
FExploracionBase<CLAVE>::FExploracionBase (void) {}

template <class CLAVE>
FExploracionBase<CLAVE>::~FExploracionBase (void) {}

template <class CLAVE>
class FExploracionLineal : public FExploracionBase<CLAVE> {
    private:
    int nCeldas_;
    const FDispersionBase<CLAVE>* fd_;

    public:
    FExploracionLineal (int nCeldas, FDispersionBase<CLAVE>* fd) : nCeldas_(nCeldas), fd_(fd) {}
    ~FExploracionLineal (void) {}

    int operator() (const CLAVE& x, const int& i) {
        return (fd_->operator()(x)+i) % nCeldas_;
    }
};

template <class CLAVE>
class FExploracionCuadrado : public FExploracionBase<CLAVE> {
    private:
    int nCeldas_;
    const FDispersionBase<CLAVE>* fd_;


    public:
    FExploracionCuadrado (int nCeldas, FDispersionBase<CLAVE>* fd) : nCeldas_(nCeldas), fd_(fd) {}
    ~FExploracionCuadrado (void) {}

    int operator() (const CLAVE& x, const int& i) {
        return (fd_->operator()(x)+static_cast<int>(pow(i,2))) % nCeldas_;
    }
};

template <class CLAVE>
class FExploracionDispDoble : public FExploracionBase<CLAVE> {
    private:
    int nCeldas_;
    const FDispersionBase<CLAVE>* fd_;

    public:
    FExploracionDispDoble (int nCeldas, FDispersionBase<CLAVE>* fd) : nCeldas_(nCeldas), fd_(fd) {}
    ~FExploracionDispDoble (void) {}

    int operator() (const CLAVE& x, const int& i) {
        const FDispersionPseudo<CLAVE> fd2(nCeldas_);
        return (fd_->operator()(x) + i * fd2(x)) % nCeldas_;
    }
};

template <class CLAVE>
class FExploracionReDisp : public FExploracionBase<CLAVE> {
    private:
    int nCeldas_;
    const FDispersionBase<CLAVE>* fd_;

    public:
    FExploracionReDisp (int nCeldas, FDispersionBase<CLAVE>* fd) : nCeldas_(nCeldas), fd_(fd) {}
    ~FExploracionReDisp (void) {}

    int operator() (const CLAVE& x, const int& i) { //FALLA, REVISAR
        srand(x);
        int result = 0;
        for (int j = 0; j < i; j++) {
            result = rand() % nCeldas_;
        }
        return result;
    }
};