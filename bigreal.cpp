#include "BigDecimalIntClass.h"
#include "BigDecimalIntClass.cpp"
#include <string>
using namespace std;

BigDecimalInt& BigDecimalInt::push_back(string zero){
    number += zero ;
    return *this ;
}

BigDecimalInt& BigDecimalInt::pop_front(){
    number.erase(0,1);
    return *this ;
}

BigDecimalInt& BigDecimalInt::change_sign_to(char sign){
    signNumber = sign ;
    return *this ;
}

class BigReal {
    private:
        BigDecimalInt integer ;
        BigDecimalInt fraction ;
        char number_sign ;
        int fractian_length ;
    public:
        
        BigReal(){
            integer.setNumber("0") ;
            fraction.setNumber("0");
            number_sign = '+' ;
            fractian_length = 1 ;
        }
        
        BigReal(string number){
            string I , F ;
            bool point_found = false ;
            if(number[0] == '+'){
                number.erase(0,1);
                number_sign = '+';
            }
            else if (number[0] == '-'){
                number.erase(0,1);
                number_sign = '-';
            }
            else{
                number_sign = '+';
            }
            for(int i = 0 ; i < number.length() ; i++ ){
                if(number[i] == '.'){
                    point_found = true ;
                }
                if(point_found == false){
                    I.push_back(number[i]);
                }
                else if(point_found == true && number[i] != '.' ){
                    F.push_back(number[i]);
                }
            }
            integer.setNumber(I) ;
            fraction.setNumber(F) ;
            integer.change_sign_to(number_sign);
            fraction.change_sign_to(number_sign);
            fractian_length = F.length() ;
        }

        friend ostream& operator<<(ostream& out , BigReal other){
            BigDecimalInt zero("0") ;
            if(other.number_sign == '+'){
                out << other.integer << '.' << other.fraction ;
            }
            else{
                if(other.integer == zero && other.fraction == zero ){
                    out << other.integer << '.' << other.fraction ;
                }
                else{
                    out << other.integer << '.' << other.fraction.getNumber() ;
                }
            }
            return out ;
        }

        BigReal operator+(BigReal other){
            BigReal third ;
            while(fraction.size() > other.fraction.size()){
                other.fraction.push_back("0") ;
            }
            while(fraction.size() < other.fraction.size()){
                fraction.push_back("0") ;
            }
            if(number_sign == other.number_sign){
                third.number_sign = number_sign ;
                third.fractian_length = fraction.size() ;
                third.integer = integer + other.integer ;
                third.fraction = fraction + other.fraction ;
                if (third.fractian_length < third.fraction.size()){
                    if(number_sign == '+'){
                        BigDecimalInt one("1") ;
                        third.integer = third.integer + one ;
                        third.fraction.pop_front();
                    }
                    else{
                        BigDecimalInt one("-1") ;
                        third.integer = third.integer + one ;
                        third.fraction.pop_front();
                    }
                }
            }
            else{
                if(integer.sign() == 0){
                    integer.change_sign_to('+');
                    fraction.change_sign_to('+');
                    third.integer = (other.integer - integer);
                    third.fraction = (other.fraction - fraction);
                }
                else{
                    other.integer.change_sign_to ('+');
                    other.fraction.change_sign_to ('+');
                    third.integer = (integer - other.integer);
                    third.fraction = (fraction - other.fraction);
                }
            } 
            return third ;
        }

//         BigReal operator-(BigReal& other){
//             BigReal third ;
//             third.integer = integer - other.integer ;
//             third.fraction = fraction - other.fraction ;
//             return third ;
//         }        

    
};

int main(){
    //BigDecimalInt c , v ;
    BigReal a("232.924") , b("5796.39") ;
    cout << a+b ;

}
