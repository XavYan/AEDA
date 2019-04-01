#pragma once

#include "NumberException.hpp"

class NumberBase {
    private:
    std::size_t N_;
    std::size_t B_;

    protected:
    virtual void to_base (int n) = 0;
    virtual std::ostream& write (std::ostream& os) const = 0;
    virtual NumberBase* duplicate (void) const = 0;

    public:
    NumberBase (std::size_t N, std::size_t B);
    virtual ~NumberBase (void);

    virtual NumberBase* operator+ (const NumberBase* num) const = 0;
    virtual NumberBase* operator- (const NumberBase* num) const = 0;
    // virtual NumberBase* operator* (const NumberBase* num) const = 0;
    virtual NumberBase* operator/ (const NumberBase* num) const = 0;

    friend std::ostream& operator<< (std::ostream& os, const NumberBase& num);
    friend std::ostream& operator<< (std::ostream& os, const NumberBase* num);


};

NumberBase::NumberBase (std::size_t N, std::size_t B) {
    if (N <= 1 || B < 1) {
        throw wrong_number_exception();
    }
    N_ = N;
    B_ = B;
}

NumberBase::~NumberBase (void) {}

NumberBase* NumberBase::operator+ (const NumberBase* num) const {}
NumberBase* NumberBase::operator- (const NumberBase* num) const {}
// NumberBase* NumberBase::operator* (const NumberBase* num) const {}
NumberBase* NumberBase::operator/ (const NumberBase* num) const {}

void NumberBase::to_base (int n) {}
std::ostream& NumberBase::write (std::ostream& os) const {}
NumberBase* NumberBase::duplicate (void) const {}

std::ostream& operator<< (std::ostream& os, const NumberBase& num) {
    num.write(os);
    return os;
}

std::ostream& operator<< (std::ostream& os, const NumberBase* num) {
    num->write(os);
    return os;
}