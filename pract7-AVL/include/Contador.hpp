#pragma once

#include <iostream>

class Contador {
    private:
    int n_;

    public:
    Contador (int n = 0);
    ~Contador (void);

    void start (void);  //Asigna al contador un valor de 0
    void set (int n = 0);   //Pone el contador a un valor concreto
    int end (void);     //Devuelve el valor actual del contador

    int operator++ (void);
};