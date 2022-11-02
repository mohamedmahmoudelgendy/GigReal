#include "BigDecimalIntClass.h"
#include "BigDecimalIntClass.cpp"
#include <string>
using namespace std;

string push_back(BigDecimalInt a ,string zero);

class BigReal {
    private:
        BigDecimalInt integer ;
        BigDecimalInt fraction ;
        BigDecimalInt sum ;
        string result ;
    public:
        BigReal();
        BigReal(string number);
        void add_zeros(BigReal& a ,BigReal& b);
        friend ostream& operator<<(ostream& out , BigReal other);
        BigReal operator+(BigReal other);
        BigReal operator-(BigReal& other);
};