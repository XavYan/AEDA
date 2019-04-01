#include "../include/test.hpp"

test::test (float factor, unsigned int nPruebas, int nCeldas, int nClaves, FD fd, FE fe) :
table_(nCeldas, nClaves, fd, fe) {
    factor_ = factor;
    nPruebas_ = nPruebas;

    N_ = factor * nCeldas * nClaves;
    v_.resize(2 * N_);

    min_ = max_ = acc_ = 0;

    //Insertamos los N primeros valores del vector
    for (int i = 0; i < N_; i++) {
        table_.insert(v_[i]);
    }
}

test::~test (void) {
    v_.clear();
}

void test::test_search (void) {
    max_ = 0, acc_ = 0; min_ = 255;

    for (unsigned i = 0; i < nPruebas_; i++) {
        table_.get_cont().start();
        table_.search(v_[i]);
        acc_ += table_.get_cont().end();
        if (table_.get_cont().end() < min_) min_ = table_.get_cont().end();
        if (table_.get_cont().end() > max_) max_ = table_.get_cont().end();
    }

    std::cout << min_ << "\t" << acc_/nPruebas_ << "\t" << max_ << '\n';

}

void test::test_insert (void) {
    max_ = 0, acc_ = 0; min_ = 255;

    for (unsigned i = 0; i < nPruebas_; i++) {
        table_.get_cont().start();
        table_.insert(v_[N_+i]);
        acc_ += table_.get_cont().end();
        if (table_.get_cont().end() < min_) min_ = table_.get_cont().end();
        if (table_.get_cont().end() > max_)
            max_ = table_.get_cont().end();
    }

    std::cout << min_ << "\t" << acc_/nPruebas_ << "\t" << max_ << '\n';

}