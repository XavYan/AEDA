#include "Number.hpp"

class BinaryNumber : public Number<8,2,char> {
    public:
    BinaryNumber(int n) : Number<8,2,char>(n) {}
};

class OctalNumber : public Number<8,8,char> {
    public:
    OctalNumber(int n) : Number<8,8,char>(n) {}
};

class DecimalNumber : public Number<8,10,char> {
    public:
    DecimalNumber(int n) : Number<8,10,char>(n) {}
};

class HexadecimalNumber : public Number<8,16,char> {
    public:
    HexadecimalNumber(int n) : Number<8,16,char>(n) {}
};