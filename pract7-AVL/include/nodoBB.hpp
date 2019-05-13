//
// Created by xavyan on 30/04/19.
//

#pragma once

#include <cstddef>
#include <iostream>

template <class CLAVE>
class nodoBB {
private:
   CLAVE dato_;
   nodoBB<CLAVE>* izq_;
   nodoBB<CLAVE>* der_;

public:
    nodoBB (void);
    nodoBB (CLAVE dato, nodoBB<CLAVE>* izq = NULL, nodoBB<CLAVE>* der = NULL);
    ~nodoBB (void);

    nodoBB<CLAVE>*& izq (void);
    nodoBB<CLAVE>*& der (void);
    void set_izq (const nodoBB<CLAVE>* node);
    void set_der (const nodoBB<CLAVE>* node);

    const CLAVE& get (void) const; //Obtienes la clave
    void set (const CLAVE dato);
};

template <class CLAVE>
nodoBB<CLAVE>::nodoBB (void) : dato_(), izq_(NULL), der_(NULL) {}

template <class CLAVE>
nodoBB<CLAVE>::nodoBB (CLAVE dato, nodoBB<CLAVE>* izq, nodoBB<CLAVE>* der) :
dato_(dato),
izq_(izq),
der_(der)
{}

template <class CLAVE>
nodoBB<CLAVE>::~nodoBB (void) {
   izq_ = NULL;
   der_ = NULL;
}

template <class CLAVE>
nodoBB<CLAVE>*& nodoBB<CLAVE>::izq(void) {
   return izq_;
}

template <class CLAVE>
nodoBB<CLAVE>*& nodoBB<CLAVE>::der(void) {
   return der_;
}

template <class CLAVE>
void nodoBB<CLAVE>::set_izq(const nodoBB<CLAVE> *node) {
   if (izq_ != NULL) {
      std::cerr << "No se puede insertar por la izquierda.\n";
      return;
   }
   izq_ = node;
}

template <class CLAVE>
void nodoBB<CLAVE>::set_der(const nodoBB<CLAVE> *node) {
   if (der_ != NULL) {
      std::cerr << "No se puede insertar por la derecha.\n";
      return;
   }
   der_ = node;
}

template <class CLAVE>
const CLAVE& nodoBB<CLAVE>::get (void) const {
   return dato_;
}

template <class CLAVE>
void nodoBB<CLAVE>::set (const CLAVE dato) {
   dato_ = dato;
}