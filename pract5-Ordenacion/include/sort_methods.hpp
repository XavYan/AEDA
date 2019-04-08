//
// Created by xavyan on 8/04/19.
//

#pragma once

template <class CLAVE>
void sort_by_selection (CLAVE* v, int tam) {
   int menor;
   for (int i = 0; i < tam; i++) {
      menor = i;
      for (int j = i+1; j < tam; j++) {
         if (v[j] < v[menor]) {
            menor = j;
         }
      }
      CLAVE x = v[i];
      v[i] = v[menor];
      v[menor] = x;
   }
}

template <class CLAVE>
void sort_by_change (CLAVE* v, int tam) {
   int ini = 1;
   int fin = tam-1;
   int cam = tam;
   while (ini < fin) {
      for (int j = fin; j >= ini; j--){
         if (v[j] < v[j-1]) {
            CLAVE aux = v[j];
            v[j] = v[j-1];
            v[j-1] = aux;
            cam = j;
         }
      }
      ini = cam +1;
      for (int j = ini; j <= fin; j++) {
         if (v[j-1] > v[j]) {
            CLAVE aux = v[j];
            v[j] = v[j-1];
            v[j-1] = aux;
            cam = j;
         }
      }
      fin = cam -1;
   }
}