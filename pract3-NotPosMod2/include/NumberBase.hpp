#pragma once

#include <iostream>
#include <cstdlib>
#include "NumberException.hpp"

class NumberBase {
private:
    std::size_t B_;
    std::size_t N_;
protected:
    virtual void to_base (int n);
    virtual std::ostream& write (std::ostream& os) const;
    virtual NumberBase& duplicate (void) const;
public:
     NumberBase (std::size_t N, std::size_t B);
    ~NumberBase (void);

    virtual NumberBase& operator+ (const NumberBase& num) const;
    virtual NumberBase& operator- (const NumberBase& num) const;
    friend std::ostream& operator<< (std::ostream& os, const NumberBase& number);
};

NumberBase::NumberBase (std::size_t N, std::size_t B) {
    if (B <= 1 || (N <= 0)) {
        throw wrong_number_exception();
    }
    N_ = N;
    B_ = B;
}

NumberBase::~NumberBase (void) {}


void NumberBase::to_base (int n) {}
std::ostream& NumberBase::write (std::ostream& os) const {}
NumberBase& NumberBase::duplicate (void) const {}

NumberBase& NumberBase::operator+ (const NumberBase& num) const {}
NumberBase& NumberBase::operator- (const NumberBase& num) const {}
std::ostream& operator<< (std::ostream& os, const NumberBase& number) {
    number.write(os);
    return os;
}