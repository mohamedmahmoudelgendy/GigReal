#include "BigDecimalIntClass.h"
#include "BigDecimalIntClass.cpp"
#include <string>
using namespace std;

BigDecimalInt& BigDecimalInt:: operator= (string n){
        if(number[0] == '+')
        {
            n.erase(0,1);
            signNumber = '+';
        }
        else if (n[0] == '-')
        {
            n.erase(0,1);
            signNumber = '-';
        }
        else
        {
            signNumber = '+';
        }
        number = n ;
        return *this ; 
    }

BigDecimalInt& BigDecimalInt::push_back(string zero){
    number += zero ;
    return *this ;
}

BigDecimalInt& BigDecimalInt::pop_front(){
    number.erase(0,1);
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
            integer = "0" ;
            fraction = "0";
            number_sign = '+' ;
            fractian_length = 1 ;
        }
        
        BigReal(string number){
            string I , F ;
            bool point_found = false ;
            if(number[0] == '+')
            {
                number.erase(0,1);
                number_sign = '+';
            }
            else if (number[0] == '-')
            {
                number.erase(0,1);
                number_sign = '-';
            }
            else
            {
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
            integer = I ;
            fraction = F ;
            fractian_length = F.length() ;
        }

        // friend ostream& operator<<(ostream& out , BigReal other){
        //     if(other.number_sign == '+'){
        //         out << other.integer << '.' << other.fraction ;
        //     }
        //     else{
        //         if(other.integer == "0"  && ){
        //             out << num.number ;
        //         }
        //         else{
        //             out << num.signNumber << num.number ;
        //         }
        //     }
            
        //     return out ;
        // }

        // BigReal operator+(BigReal& other){
        //     BigReal third ;
        //     if(fraction.size() > other.fraction.size()){
        //         while(fraction.size() != other.fraction.size()){
        //             other.fraction.push_back("0") ;
        //         }
        //     }
        //     else if (fraction.size() < other.fraction.size()){
        //         while(fraction.size() != other.fraction.size()){
        //             fraction.push_back("0") ;
        //         }
        //     }
        //     third.fractian_length = fraction.size() ;
        //     if(integer > other.integer){
        //         third.number_sign = number_sign ;
        //     }
        //     else if(integer < other.integer){
        //         third.number_sign = other.number_sign ;
        //     }
        //     else if (){

        //     }
        //     third.integer = integer + other.integer ;
        //     third.fraction = fraction + other.fraction ;
        //     if (third.fractian_length < third.fraction.size()){
        //       BigDecimalInt one ;
        //       one = "1" ;
        //       third.integer = third.integer + one ;
        //       third.fraction.pop_front();
        //     }
        //     return third ;
        // }

        // BigReal operator-(BigReal& other){
        //     BigReal third ;
        //     third.integer = integer - other.integer ;
        //     third.fraction = fraction - other.fraction ;
        //     return third ;
        // }        

    
};

int main(){
    //BigDecimalInt c , v ;
    // BigReal a("232.924") , b("5796.3") ;
    // cout << a+b ;

}
