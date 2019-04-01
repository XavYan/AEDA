#include "../include/DNI.hpp"

DNI::DNI (void) {
    dato_ = rand() % MAX_DNI;
}

DNI::DNI (const unsigned long i) {
    dato_ = i;
}

DNI::~DNI (void) {}

bool DNI::operator== (const DNI& dni) {
    if (dato_ == dni.dato_) return true;
    return false;
}

bool DNI::operator< (const DNI& dni) {
    if (dato_ < dni.dato_) return true;
    return false;
}

bool DNI::operator> (const DNI& dni) {
    if (dato_ > dni.dato_) return true;
    return false;
}

DNI::operator unsigned long (void) const {
    unsigned long d = dato_;
    return d;
}

std::ostream& operator<< (std::ostream& os, const DNI& dni) {
    os << std::setw(8) << dni.dato_;
    return os;
}