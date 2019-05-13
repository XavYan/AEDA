//
// Created by xavyan on 30/04/19.
//

#pragma once

#include "nodoBB.hpp"
//#include "Contador.hpp"
#include <queue> // std::queue
#include <utility> // std::pair

template <class CLAVE>
class ABB {
private:
    nodoBB<CLAVE>* head_; //Se trata de un puntero al nodo raiz

public:
    static Contador cont_;

public:
    ABB (void);
    ~ABB(void);

    const nodoBB<CLAVE>* head (void);

    // Lo que nos piden en la practica
    nodoBB<CLAVE>* search (CLAVE x);
    void insert (CLAVE x);
    void eliminate (CLAVE x);

    void write (std::ostream& os); //Implementa un recorrido por niveles

private:
    void podar (nodoBB<CLAVE>*& nodo);
    nodoBB<CLAVE>* searchBranch (nodoBB<CLAVE>* nodo, CLAVE x);
    void insertBranch (nodoBB<CLAVE>* &nodo, CLAVE x);
    void eliminateBranch (nodoBB<CLAVE>* &nodo, CLAVE x);
    void substitute (nodoBB<CLAVE>* &deleted, nodoBB<CLAVE>* &sust);
};

//Definimos el metodo estatico
template <class CLAVE>
Contador ABB<CLAVE>::cont_ = 0;


template <class CLAVE>
ABB<CLAVE>::ABB (void) : head_(NULL) {}

template <class CLAVE>
ABB<CLAVE>::~ABB (void) { podar(head_); }

template <class CLAVE>
const nodoBB<CLAVE>* ABB<CLAVE>::head (void) {
   return head_;
}

template <class CLAVE>
nodoBB<CLAVE>* ABB<CLAVE>::search(CLAVE x) {
   return searchBranch(head_, x);
}

template <class CLAVE>
void ABB<CLAVE>::insert(CLAVE x) {
   insertBranch(head_, x);
}

template <class CLAVE>
void ABB<CLAVE>::eliminate(CLAVE x) {
   eliminateBranch(head_, x);
}

template <class CLAVE>
void ABB<CLAVE>::write (std::ostream& os) {
   std::queue<std::pair<nodoBB<CLAVE>*,int> > Q; //Guardamos en la pila un par formado por un nodo y el nivel de ese nodo
   nodoBB<CLAVE>* nodo;

   int nivel, nivel_actual = 0;

   std::pair<nodoBB<CLAVE>*,int> paux (head_, 0);
   os << "Nivel " << nivel_actual << ": ";
   Q.push(paux);

   while (!Q.empty()) {
      std::pair<nodoBB<CLAVE>*,int> aux = Q.front();
      Q.pop();
      nivel = std::get<1>(aux);
      nodo = std::get<0>(aux);

      if (nivel > nivel_actual) {
         nivel_actual = nivel;
         os << "\nNivel " << nivel_actual << ": ";
      }
      if (nodo != NULL) {
         os << "[" << nodo->get() << "] ";
         std::pair<nodoBB<CLAVE>*,int> paux1 (nodo->izq(), nivel+1);
         Q.push(paux1);
         std::pair<nodoBB<CLAVE>*,int> paux2 (nodo->der(), nivel+1);
         Q.push(paux2);
      } else {
         //Subarbol vacio
         os << "[.] ";
      }
   }
}

//METODOS PRIVADOS/////////////////////////////////////////////////////////////////////

template <class CLAVE>
void ABB<CLAVE>::podar(nodoBB<CLAVE> *&nodo) {
   if (nodo == NULL) return;
   podar(nodo->izq());
   podar(nodo->der());
   delete nodo;
   nodo = NULL;
}

template <class CLAVE>
nodoBB<CLAVE>* ABB<CLAVE>::searchBranch(nodoBB<CLAVE> *nodo, CLAVE x) {
   if (nodo == NULL) return NULL;

   ++cont_;
   if (x == nodo->get()) return nodo;
   if (x < nodo->get()) {
      return searchBranch(nodo->izq(), x);
   }
   return searchBranch(nodo->der(), x);
}

template <class CLAVE>
void ABB<CLAVE>::insertBranch(nodoBB<CLAVE>* &nodo, CLAVE x) {
   ++cont_;
   if (nodo == NULL) {
      nodo = new nodoBB<CLAVE>(x);
   }
   else if (x < nodo->get())
      insertBranch(nodo->izq(), x);
   else
      insertBranch(nodo->der(), x);
}

template <class CLAVE>
void ABB<CLAVE>::eliminateBranch(nodoBB<CLAVE> *&nodo, CLAVE x) {
   if (nodo == NULL) return;

   if (x < nodo->get())
      eliminateBranch(nodo->izq(), x);
   else if (x > nodo->get())
      eliminateBranch(nodo->der(), x);
   else {
      nodoBB<CLAVE>* eliminated = nodo;
      if (nodo->der() == NULL)
         nodo = nodo->izq();
      else if (nodo->izq() == NULL)
         nodo = nodo->der();
      else {
         substitute(eliminated, nodo->izq());
      }
      delete eliminated;
   }
}

template <class CLAVE>
void ABB<CLAVE>::substitute(nodoBB<CLAVE> *&deleted, nodoBB<CLAVE> *&sust) {
   if (sust->der() != NULL)
      substitute(deleted, sust->der());
   else {
      deleted->set(sust->get());
      deleted = sust;
      sust = sust->izq();
   }
}