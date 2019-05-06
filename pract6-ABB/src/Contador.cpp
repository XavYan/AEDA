#include "../include/Contador.hpp"

Contador::Contador (int n) : n_(n) {}
Contador::~Contador (void) {}

void Contador::start (void) { n_ = 0; }
void Contador::set (int n) { n_ = n; }
int Contador::end (void) { return n_; }

int Contador::operator++ (void) {
    n_++;
    return n_;
}