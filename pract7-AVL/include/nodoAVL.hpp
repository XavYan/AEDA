//
// Created by xavyan on 13/05/19.
//

#pragma once

#include <cstddef>
#include <iostream>

template <class CLAVE>
class nodoAVL {
private:
    int bal_;
    CLAVE dato_;
    nodoAVL<CLAVE>* izq_;
    nodoAVL<CLAVE>* der_;

public:
    nodoAVL (int dato, int bal = 0, nodoAVL<CLAVE>* izq = NULL, nodoAVL<CLAVE>* der = NULL) :
    bal_(bal),
    dato_(dato),
    izq_(izq),
    der_(der)
    {}
    ~nodoAVL(void) {}

   nodoAVL<CLAVE>*& izq (void) { return izq_; }
   nodoAVL<CLAVE>*& der (void) { return der_; }
   int& bal (void) { return bal_; }

   void set_izq (const nodoAVL<CLAVE>* nodo) { izq_ = nodo; }
   void set_der (const nodoAVL<CLAVE>* nodo) { der_ = nodo; }


   const CLAVE& get (void) const { return dato_; }
   void set (const CLAVE dato) { dato_ = dato; }
};

