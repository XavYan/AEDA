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

template <class CLAVE>
void baja (int i, CLAVE* v, int tam) {
   CLAVE x = v[i];
   while (2*i < tam) {
      int h;
      int h1 = 2*i;
      int h2 = h1 + 1;

      if (h1 == tam-1 || v[h1] > v[h2]) {
         h = h1;
      } else {
         h = h2;
      }

      if (v[h] <= x) break;
      else {
         v[i] = v[h];
         v[h] = x;
         i = h;
      }
   }
}

template <class CLAVE>
void sort_by_heapsort (CLAVE* v, int tam) {
   for (int i = tam/2-1; i >= 0; i--) {
      baja(i, v, tam);
   }

   for (int i = tam-1; i >= 0; i--) {
      CLAVE x = v[0];
      v[0] = v[i];
      v[i] = x;
      baja(0,v,i);
   }
}

template <class CLAVE>
void merge (CLAVE* v, int tam, int ini, int cen, int fin) {
   int i = ini; int j = cen + 1; int k = ini;
   CLAVE* aux = new CLAVE [tam];
   while ((i <= cen) && (j <= fin)) {
      if (v[i] < v[j]) {
         aux[k] = v[i];
         i++;
      } else {
         aux[k] = v[j];
         j++;
      }
      k++;
   }

   if (i > cen) {
      while (j <= fin) {
         aux[k] = v[j];
         j++; k++;
      }
   } else {
      while (i <= cen) {
         aux[k] = v[i];
         i++; k++;
      }
   }
   for (int s = ini; s <= fin; s++) {
      v[s] = aux[s];
   }
}

template <class CLAVE>
void sort_by_mergesort (CLAVE* v, int tam, int ini, int fin) {
   if (ini < fin) {
      int cen = (ini + fin) / 2;
      sort_by_mergesort(v, tam, ini, cen);
      sort_by_mergesort(v, tam, cen+1, fin);
      merge(v, tam, ini, cen, fin);
   }
}

template <class CLAVE>
void deltaSort(int delta, CLAVE* v, int tam) {
   int j = 0;
   for (int i = delta; i < tam; i++) {
      CLAVE x = v[i];
      j = i;
      while ((j >= delta) && (x < v[j-delta])) {
         v[j] = v[j-delta];
         j = j - delta;
      }
      v[j] = x;
   }
}

template <class CLAVE>
void sort_by_shellSort (CLAVE* v, int tam, int delta) {
   std::cout << "delta: " << delta << '\n';
   int del = delta;
   while (del > 0) {
      del = del / 2;
      deltaSort(del, v, tam);
   }
}