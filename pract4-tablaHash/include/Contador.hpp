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

Contador::Contador (int n) : n_(n) {}
Contador::~Contador (void) {}

void Contador::start (void) { n_ = 0; }
void Contador::set (int n) { n_ = n; }
int Contador::end (void) { return n_; }

int Contador::operator++ (void) {
    n_++;
    return n_;
}