#pragma once

#include <iostream>

enum FD { ADD, PSEUDO_RAND, MOD };

template <class CLAVE>
class FDispersionBase {
    public:
    FDispersionBase (void);
    virtual ~FDispersionBase (void);

    virtual int operator() (const CLAVE& x) const = 0;
};

template <class CLAVE>
FDispersionBase<CLAVE>::FDispersionBase (void) {}

template <class CLAVE>
FDispersionBase<CLAVE>::~FDispersionBase (void) {}

// template <class CLAVE>
// int FDispersionBase<CLAVE>::operator() (const CLAVE& x) const { return 0; }

template <class CLAVE>
class FDispersionMod : public FDispersionBase<CLAVE> {
    private:
    int nCeldas_; //Numero de celdas de la tabla

    public:
    FDispersionMod (int nCeldas) : nCeldas_(nCeldas) {};
    ~FDispersionMod (void) {};

    int operator() (const CLAVE& x) const {
        return x % nCeldas_;
    }
};

template <class CLAVE>
class FDispersionSum : public FDispersionBase<CLAVE> {
    private:
    int nCeldas_; //Numero de celdas de la tabla

    public:
    FDispersionSum (int nCeldas) : nCeldas_(nCeldas) {};
    ~FDispersionSum (void) {};

    int operator() (const CLAVE& x) const {
        int d;
        int p = x;
        while (p > 0) {
            int y = p % 10;
            d = d + y;
            p = p / 10;
        }
        return (d % nCeldas_);
    }
};

template <class CLAVE>
class FDispersionPseudo : public FDispersionBase<CLAVE> {
    private:
    int nCeldas_;

    public:
    FDispersionPseudo (int nCeldas) : nCeldas_(nCeldas) {}
    ~FDispersionPseudo (void) {}

    int operator() (const CLAVE& x) const {
        srand(x);
        return rand() % nCeldas_;
    }
};