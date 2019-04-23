#pragma once

#include <iostream>
#include <iomanip>

enum sMethods { SELECT, CHANGE, HEAPSORT, MERGESORT, SHELLSORT };

template <class CLAVE>
class Sort {
private:
  CLAVE* obj_;
  int n_;
  int mode_; // Si es -1 no hay modo; 0 modo demostracion y 1 modo estadistico

public:
  Sort (CLAVE* v, int n, sMethods sM, int& acum, int mode = -1, float alpha = 1);
  ~Sort(void);

  CLAVE* to_ptr (void) {
     return obj_;
  }

  int sort_by_selection (CLAVE* v, int tam);
  int sort_by_change (CLAVE* v, int tam);
  int sort_by_heapsort (CLAVE* v, int tam);
  int sort_by_mergesort (CLAVE* v, int tam, int ini, int fin);
  int sort_by_shellSort (CLAVE* v, int tam, int delta);

  std::ostream& write (std::ostream& os) const;

private:
  int baja (int i, CLAVE* v, int tam);
  int merge (CLAVE* v, int tam, int ini, int cen, int fin);
  int deltaSort(int delta, CLAVE* v, int tam);
};

template <class CLAVE>
Sort<CLAVE>::Sort (CLAVE* v, int n, sMethods sM, int& acum, int mode, float alpha) : n_(n), mode_(mode) {
  obj_ = new CLAVE [n_];
  for (int i = 0; i < n; i++) {
    obj_[i] = v[i];
  }

  //Seleccionamos el metodo de ordenacion
  int aux;
  switch (sM) {
    case SELECT:
    aux = sort_by_selection(obj_, n_);
    break;
    case CHANGE:
    aux = sort_by_change(obj_, n_);
    break;
    case HEAPSORT:
    aux = sort_by_heapsort(obj_, n_);
    break;
    case SHELLSORT:
    aux = sort_by_shellSort(obj_, n_, alpha*n_);
    break;
    default: //Si no coincide con ninguno de los anteriores tenemos dos posibilidades: o es MERGESORT o no es ninguno, en cuyo caso se ha escogido el metodo mergesort por defecto
    aux = sort_by_mergesort(obj_, n_, 0, n_-1);
  }
  if (mode_ == 1) acum = aux;
}

template <class CLAVE>
Sort<CLAVE>::~Sort (void) {
  delete [] obj_;
  if (obj_ != NULL) {
    obj_ = NULL;
  }
}

template <class CLAVE>
std::ostream& Sort<CLAVE>::write (std::ostream& os) const {
  for (int i = 0; i < n_; i++) {
    os << "[" << std::setw(8) << obj_[i] << "] ";
  }
  return os;
}

template <class CLAVE>
int Sort<CLAVE>::sort_by_selection (CLAVE* v, int tam) {

   int acc = 0;

   if (mode_ == 0) {
      std::cout << "   --> Vector antes de aplicar el algoritmo: ";
      write(std::cout);
      std::cout << "\n\n";
   }

   int menor;
   for (int i = 0; i < tam; i++) {
      menor = i;
      for (int j = i+1; j < tam; j++) {

         if (mode_ == 0) std::cout << "COMPARANDO [" << v[menor] << "] Y [" << v[j] << "]\n";
         acc++; //Para el modo estadistico

         if (v[j] < v[menor]) {
            if (mode_ == 0) std::cout << '[' << v[j] << "] es mas pequeño que [" << v[menor] << "]. INTERCAMBIANDO...\n";
            menor = j;
            if (mode_ == 0) std::cout << "Nuevo menor: " << v[menor] << '\n';
         }
         if (mode_ == 0) {
            std::cout << "   --> Tras esta comparacion el vector es ";
            write(std::cout);
            std::cout << "\n\n";
         }
      }
      CLAVE x = v[i];
      v[i] = v[menor];
      v[menor] = x;
   }
//   std::cout << "Valor en sel: " << acc << '\n';
   return acc;
}

template <class CLAVE>
int Sort<CLAVE>::sort_by_change (CLAVE* v, int tam) {
   int ini = 1;
   int fin = tam-1;
   int cam = tam;

   int acc = 0; //Para modo estadistico

   if (mode_ == 0) {
      std::cout << "   --> Vector antes de aplicar el algoritmo: ";
      write(std::cout);
      std::cout << "\n\n";
   }

   while (ini < fin) {
      if (mode_ == 0) std::cout << "Fase descendente...\n";
      for (int j = fin; j >= ini; j--){
         acc++;
         if (mode_ == 0) std::cout << "COMPARANDO [" << v[j-1] << "] Y [" << v[j] << "]\n";
         if (v[j] < v[j-1]) {
            if (mode_ == 0) std::cout << '[' << v[j] << "] es mas pequeño que [" << v[j-1] << "]. INTERCAMBIANDO...\n";
            CLAVE aux = v[j];
            v[j] = v[j-1];
            v[j-1] = aux;
            cam = j;
         }
         if (mode_ == 0) {
            std::cout << "   --> Tras esta comparacion el vector es ";
            write(std::cout);
            std::cout << "\n\n";
         }
      }
      ini = cam +1;
      if (mode_ == 0) std::cout << "Fase ascendente...\n";
      for (int j = ini; j <= fin; j++) {
         acc++;
         if (mode_ == 0) std::cout << "COMPARANDO [" << v[j] << "] Y [" << v[j-1] << "]\n";
         if (v[j-1] > v[j]) {
            if (mode_ == 0) std::cout << '[' << v[j-1] << "] es mas pequeño que [" << v[j] << "]. INTERCAMBIANDO...\n";
            CLAVE aux = v[j];
            v[j] = v[j-1];
            v[j-1] = aux;
            cam = j;
         }
         if (mode_ == 0) {
            std::cout << "   --> Tras esta comparacion el vector es ";
            write(std::cout);
            std::cout << "\n\n";
         }
      }
      fin = cam -1;
   }
   return acc;
}

template <class CLAVE>
int Sort<CLAVE>::sort_by_heapsort (CLAVE* v, int tam) {

   int acc = 0; //Para modo estadistico

   for (int i = tam/2-1; i >= 0; i--) {
      acc += baja(i, v, tam);
   }

   for (int i = tam-1; i >= 0; i--) {
      CLAVE x = v[0];
      v[0] = v[i];
      v[i] = x;
      acc += baja(0,v,i);
   }
   return acc;
}

template <class CLAVE>
int Sort<CLAVE>::sort_by_mergesort (CLAVE* v, int tam, int ini, int fin) {

   int acc = 0; // Modo estadistico

   if (ini < fin) {
      int cen = (ini + fin) / 2;
      acc += sort_by_mergesort(v, tam, ini, cen);
      acc += sort_by_mergesort(v, tam, cen+1, fin);
      if (mode_ == 0) {
         std::cout << "Vector 1: ";
         for (int i = ini; i <= cen; i++) {
            std::cout << "[" << v[i] << "] ";
         }
         std::cout << "\nVector 2: ";
         for (int i = cen+1; i <= fin; i++) {
            std::cout << "[" << v[i] << "] ";
         }
         std::cout << '\n';
      }
      acc += merge(v, tam, ini, cen, fin);
   }
   return acc;
}

template <class CLAVE>
int Sort<CLAVE>::sort_by_shellSort (CLAVE* v, int tam, int delta) {

   int acc = 0; //Para modo estadistico

   int del = delta;
   while (del > 0) {
      if (mode_ == 0) std::cout << "Para un valor de delta = " << del << '\n';
      del = del / 2;
      acc += deltaSort(del, v, tam);
   }
   return acc;
}

//PRIVADOS///////////////////////////////////////////////////////////////////

template <class CLAVE>
int Sort<CLAVE>::baja (int i, CLAVE* v, int tam) {

   int acc = 0; //Para modo estadistico

   CLAVE x = v[i];
   while (2*i < tam) {
      acc++;
      int h;
      int h1 = 2*i;
      int h2 = h1 + 1;

      if (mode_ == 0) std::cout <<  "El hijo mayor es ";
      if (h1 == tam-1 || v[h1] > v[h2]) {
         h = h1;
      } else {
         h = h2;
      }
      if (mode_ == 0) std::cout << "[" << std::setw(8) << v[h] << "]\n";

      if (mode_ == 0) std::cout << "COMPARANDO [" << v[i] << "] Y [" << v[h] << "]\n";

      if (v[h] <= x) break;
      else {
         v[i] = v[h];
         v[h] = x;
         i = h;
      }
   }
   return acc;
}

template <class CLAVE>
int Sort<CLAVE>::merge (CLAVE* v, int tam, int ini, int cen, int fin) {

   int acc = 0; //Para modo estadistico

   int i = ini; int j = cen + 1; int k = ini;
   CLAVE* aux = new CLAVE [tam];
   if (mode_ == 0) std::cout << "Fusionando vectores...\n";
   while ((i <= cen) && (j <= fin)) {
      acc++;
      if (mode_ == 0) std::cout << "COMPARANDO [" << v[i] << "] Y [" << v[j] << "]\n";
      if (v[i] < v[j]) {
         if (mode_ == 0) std::cout << '[' << v[i] << "] es mas pequeño que [" << v[j] << "]. INTERCAMBIANDO...\n";
         aux[k] = v[i];
         i++;
      } else {
         if (mode_ == 0) std::cout << '[' << v[j] << "] es mas pequeño que [" << v[i] << "]. INTERCAMBIANDO...\n";
         aux[k] = v[j];
         j++;
      }
      k++;
   }

   if (i > cen) {
      while (j <= fin) {
         acc++;
         aux[k] = v[j];
         j++; k++;
      }
   } else {
      while (i <= cen) {
         acc++;
         aux[k] = v[i];
         i++; k++;
      }
   }
   for (int s = ini; s <= fin; s++) {
      v[s] = aux[s];
   }
   delete [] aux;
   return acc;
}

template <class CLAVE>
int Sort<CLAVE>::deltaSort(int delta, CLAVE* v, int tam) {

   int acc = 0; //Para modo estadistico

   int j = 0;
   for (int i = delta; i < tam; i++) {
      CLAVE x = v[i];
      j = i;
      while ((j >= delta) && (x < v[j-delta])) {
         acc++;
         if (mode_ == 0) std::cout << "COMPARANDO [" << v[j] << "] Y [" << v[j-delta] << "]\n";
         v[j] = v[j-delta];
         j = j - delta;
      }
      v[j] = x;
   }
   return acc;
}
