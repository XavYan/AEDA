//
// Created by xavyan on 13/05/19.
//

#pragma once

#include "nodoAVL.hpp"
#include "Contador.hpp"
#include <queue> // std::queue
#include <utility> // std::pair

template <class CLAVE>
class AVL {
private:
    nodoAVL<CLAVE>* raiz_;

public:
    static Contador cont_;

public:
    AVL (void) : raiz_(NULL) {}
    ~AVL (void) { podar(raiz_); }

    const nodoAVL<CLAVE>* raiz (void) { return raiz_; }

    //Lo que nos piden en la practica
    nodoAVL<CLAVE>* buscar (CLAVE x);
    void insertar (CLAVE x);
    void eliminar (CLAVE x);

    void write (std::ostream& os); //Recorrido por niveles

private:

    //Propios del arbol binario de busqueda (ABB)
    void podar (nodoAVL<CLAVE>*& nodo);
    nodoAVL<CLAVE>* buscarRama (nodoAVL<CLAVE>* nodo, CLAVE x);
    void eliminarRama (nodoAVL<CLAVE>* &nodo, CLAVE x, bool& decrece);

    //Metodos necesarios para el AVL
    void sustituye (nodoAVL<CLAVE>* &eliminado, nodoAVL<CLAVE>* &sustituto, bool& decrece);
    void eliminar_re_balancea_izq (nodoAVL<CLAVE>* &nodo, bool& decrece);
    void eliminar_re_balancea_der (nodoAVL<CLAVE>* &nodo, bool& decrece);
    void insertar_bal (nodoAVL<CLAVE>* &nodo, nodoAVL<CLAVE>* nuevo, bool& crece);
    void insertar_re_balancea_izq(nodoAVL<CLAVE>* &nodo, bool& crece);
    void insertar_re_balancea_der(nodoAVL<CLAVE>* &nodo, bool& crece);
    void rotacion_II (nodoAVL<CLAVE>* &nodo);
    void rotacion_DD (nodoAVL<CLAVE>* &nodo);
    void rotacion_ID (nodoAVL<CLAVE>* &nodo);
    void rotacion_DI (nodoAVL<CLAVE>* &nodo);

};

//Definimos el contador estatico
template <class CLAVE>
Contador AVL<CLAVE>::cont_ = 0;

//METODOS PUBLICOS///////////////////////////////////////////////////

template <class CLAVE>
nodoAVL<CLAVE>* AVL<CLAVE>::buscar(CLAVE x) {
   return buscarRama (raiz_, x);
}

template <class CLAVE>
void AVL<CLAVE>::insertar(CLAVE x) {
   nodoAVL<CLAVE>* nuevo = new nodoAVL<CLAVE> (x);
   bool crece = false;
   insertar_bal (raiz_, nuevo, crece);
}

template <class CLAVE>
void AVL<CLAVE>::eliminar(CLAVE x) {
   bool decrece = false;
   eliminarRama(raiz_, x, decrece);
}

template <class CLAVE>
void AVL<CLAVE>::write(std::ostream &os) {
   std::queue<std::pair<nodoAVL<CLAVE>*,int> > Q; //Guardamos en la pila un par formado por un nodo y el nivel de ese nodo
   nodoAVL<CLAVE>* nodo;

   int nivel, nivel_actual = 0;

   std::pair<nodoAVL<CLAVE>*,int> paux (raiz_, 0);
   os << "Nivel " << nivel_actual << ": ";
   Q.push(paux);

   while (!Q.empty()) {
      std::pair<nodoAVL<CLAVE>*,int> aux = Q.front();
      Q.pop();
      nivel = std::get<1>(aux);
      nodo = std::get<0>(aux);

      if (nivel > nivel_actual) {
         nivel_actual = nivel;
         os << "\nNivel " << nivel_actual << ": ";
      }
      if (nodo != NULL) {
         os << "[" << nodo->get() << "] ";
         std::pair<nodoAVL<CLAVE>*,int> paux1 (nodo->izq(), nivel+1);
         Q.push(paux1);
         std::pair<nodoAVL<CLAVE>*,int> paux2 (nodo->der(), nivel+1);
         Q.push(paux2);
      } else {
         //Subarbol vacio
         os << "[.] ";
      }
   }
}

//METODOS PRIVADOS///////////////////////////////////////////////////

template <class CLAVE>
void AVL<CLAVE>::podar(nodoAVL<CLAVE> *&nodo) {
   if (nodo == NULL) return;

   podar(nodo->izq());
   podar(nodo->der());
   delete nodo;
   nodo = NULL;
}

template <class CLAVE>
nodoAVL<CLAVE>* AVL<CLAVE>::buscarRama (nodoAVL<CLAVE>* nodo, CLAVE x) {
   if (nodo == NULL) return NULL;

   ++cont_;
   if (x == nodo->get()) return nodo;
   if (x < nodo->get()) {
      return buscarRama(nodo->izq(), x);
   }
   return buscarRama(nodo->der(), x);
}

template <class CLAVE>
void AVL<CLAVE>::eliminarRama(nodoAVL<CLAVE> *&nodo, CLAVE x, bool& decrece) {
   if (nodo == NULL) return;

   if (x < nodo->get()) {
      eliminarRama(nodo->izq(), x, decrece);
      if (decrece) eliminar_re_balancea_izq(nodo,decrece);
   } else if (x > nodo->get()) {
      eliminarRama(nodo->der(),x,decrece);
      if (decrece) {
         eliminar_re_balancea_der(nodo, decrece);
      }
   } else { // x == nodo->get()
      nodoAVL<CLAVE>* eliminado = nodo;
      if (nodo->izq() == NULL) {
         nodo = nodo->der();
         decrece = true;
      } else if (nodo->der() == NULL) {
         nodo = nodo->izq();
         decrece = true;
      } else {
         sustituye(eliminado, nodo->izq(), decrece);
         if (decrece) eliminar_re_balancea_izq(nodo, decrece);
      }
   }
}

template <class CLAVE>
void AVL<CLAVE>::eliminar_re_balancea_izq(nodoAVL<CLAVE> *&nodo, bool &decrece) {
   switch (nodo->bal()) {
      case -1: {
         nodoAVL<CLAVE> *nodo1 = nodo->der();
         if (nodo1->bal() > 0) {
            rotacion_DI(nodo);
         } else {
            if (nodo1->bal() == 0) {
               decrece = false;
            }
            rotacion_DD(nodo);
         }
         break;
      }
      case 0: {
         nodo->bal() = -1;
         decrece = false;
         break;
      }
      case 1: {
         nodo->bal() = 0;
      }
   }
}

template <class CLAVE>
void AVL<CLAVE>::eliminar_re_balancea_der(nodoAVL<CLAVE> *&nodo, bool &decrece) {
   switch (nodo->bal()) {
      case 1: {
         nodoAVL<CLAVE> *nodo1 = nodo->izq();
         if (nodo1->bal() < 0) {
            rotacion_ID(nodo);
         } else {
            if (nodo1->bal() == 0) {
               decrece = false;
            }
            rotacion_II(nodo);
         }
         break;
      }
      case 0: {
         nodo->bal() = 1;
         decrece = false;
         break;
      }
      case -1: {
         nodo->bal() = 0;
      }
   }
}

template <class CLAVE>
void AVL<CLAVE>::sustituye(nodoAVL<CLAVE> *&eliminado, nodoAVL<CLAVE> *&sust, bool &decrece) {
   if (sust->der() != NULL) {
      sustituye(eliminado,sust->der(),decrece);
      if (decrece) eliminar_re_balancea_der(sust, decrece);
   } else {
      eliminado->set(sust->get());
      eliminado = sust;
      sust = sust->izq();
      decrece = true;
   }
}

template <class CLAVE>
void AVL<CLAVE>::insertar_bal(nodoAVL<CLAVE> *&nodo, nodoAVL<CLAVE> *nuevo, bool &crece) {
   if (nodo == NULL) {
      nodo = nuevo;
      crece = true;
   }
   else if (nuevo->get() < nodo->get()) {
      ++cont_;
      insertar_bal(nodo->izq(), nuevo, crece);
      if (crece) insertar_re_balancea_izq(nodo,crece);
   }
   else {
      ++cont_;
      insertar_bal(nodo->der(), nuevo, crece);
      if (crece) insertar_re_balancea_der(nodo,crece);
   }
}

template <class CLAVE>
void AVL<CLAVE>::insertar_re_balancea_izq(nodoAVL<CLAVE> *&nodo, bool& crece) {
   switch (nodo->bal()) {
      case -1:
         nodo->bal() = 0;
         crece = false;
         break;
      case 0:
         nodo->bal() = 1;
         break;
      case 1:
         nodoAVL<CLAVE>* nodo1 = nodo->izq();
         if (nodo1->bal() == 1) {
            rotacion_II(nodo);
         } else {
            rotacion_ID(nodo);
         }
         crece = false;
   }
}


template <class CLAVE>
void AVL<CLAVE>::insertar_re_balancea_der(nodoAVL<CLAVE> *&nodo, bool& crece) {
   switch (nodo->bal()) {
      case 1:
         nodo->bal() = 0;
         crece = false;
         break;
      case 0:
         nodo->bal() = -1;
         break;
      case -1:
         nodoAVL<CLAVE>* nodo1 = nodo->der();
         if (nodo1->bal() == -1) {
            rotacion_DD(nodo);
         } else {
            rotacion_DI(nodo);
         }
         crece = false;
   }
}

template <class CLAVE>
void AVL<CLAVE>::rotacion_II(nodoAVL<CLAVE> *&nodo) {
   nodoAVL<CLAVE>* nodo1 = nodo->izq();
   nodo->izq() = nodo1->der();
   nodo1->der() = nodo;
   if (nodo1->bal() == 1) {
      nodo->bal() = 0;
      nodo1->bal() = 0;
   }
   else { // nodo1->bal() == 0
      nodo->bal() = 1;
      nodo1->bal() = -1;
   }
   nodo = nodo1;
}

template <class CLAVE>
void AVL<CLAVE>::rotacion_DD(nodoAVL<CLAVE> *&nodo) {
   nodoAVL<CLAVE>* nodo1 = nodo->der();
   nodo->der() = nodo1->izq();
   nodo1->izq() = nodo;

   if (nodo1->bal() == -1) {
      nodo->bal() = 0;
      nodo1->bal() = 0;
   }
   else { // nodo1->bal() = 0
      nodo->bal() = -1;
      nodo1->bal() = 1;
   }
   nodo = nodo1;
}

template <class CLAVE>
void AVL<CLAVE>::rotacion_ID(nodoAVL<CLAVE> *&nodo) {
   nodoAVL<CLAVE>* nodo1 = nodo->izq();
   nodoAVL<CLAVE>* nodo2 = nodo1->der();

   nodo->izq() = nodo2->der();
   nodo2->der() = nodo;
   nodo1->der() = nodo2->izq();
   nodo2->izq() = nodo1;

   if (nodo2->bal() == -1) {
      nodo1->bal() = 1;
   }
   else nodo1->bal() = 0;

   if (nodo2->bal() == 1) {
      nodo->bal() = -1;
   }
   else nodo->bal() = 0;

   nodo2->bal() = 0;
   nodo = nodo2;
}

template <class CLAVE>
void AVL<CLAVE>::rotacion_DI(nodoAVL<CLAVE> *&nodo) {
   nodoAVL<CLAVE>* nodo1 = nodo->der();
   nodoAVL<CLAVE>* nodo2 = nodo1->izq();

   nodo->der() = nodo2->izq();
   nodo2->izq() = nodo;
   nodo1->izq() = nodo2->der();
   nodo2->der() = nodo1;

   if (nodo2->bal() == 1) {
      nodo1->bal() = -1;
   }
   else nodo1->bal() = 0;

   if (nodo2->bal() == -1) {
      nodo->bal() = 1;
   }
   else nodo->bal() = 0;

   nodo2->bal() = 0;
   nodo = nodo2;
}