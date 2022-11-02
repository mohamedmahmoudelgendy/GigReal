#include "BigDecimalIntClass.h"
#include "BigDecimalIntClass.cpp"
#include <string>
using namespace std;

BigDecimalInt& BigDecimalInt::push_back(string zero){
    number += zero ;
    return *this ;
}

class BigReal {
    private:
        BigDecimalInt integer ;
        BigDecimalInt fraction ;
        BigDecimalInt sum ;
        string result ;
    public:
        
        BigReal(){
            integer.setNumber("0") ;
            fraction.setNumber("0");
            sum.setNumber("0");
            result = "0" ;
        }
        
        BigReal(string number){
            result = number ;
            string I , F ;
            bool point_found = false ;
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
            sum = integer;
            sum.push_back(fraction.getNumber());
        }

        void add_zeros(BigReal& a ,BigReal& b){
            int result = (a.fraction.size() - b.fraction.size()) ;
            for(int i = 0 ; i < abs(result) ; i++){
                if(result > 0){
                    b.sum.push_back("0");
                }
                else if(result < 0){
                    a.sum.push_back("0");
                }
                else{
                    break;
                }
            }
        }

        friend ostream& operator<<(ostream& out , BigReal other){
            out<<other.result ;
            return out ;
        }

        BigReal operator+(BigReal other){
            BigReal Return ;
            Return.integer = integer + other.integer ;
            Return.fraction = fraction + other.fraction ;
            add_zeros(*this ,other) ;
            Return.sum = (sum + other.sum) ;
            string sign ;
            if(sum.sign() == 1){sign = "" ;}
            else if (sum.sign() == 0){sign = '-';}
            string test = (Return.integer.getNumber() + '.' + Return.fraction.getNumber()) , Result = Return.sum.getNumber() ;
            for(int i = 0 ; i < Result.length() ; i++){
                if(Result[i] != test[i] && (abs((Result[i]- '0')-(test[i]- '0')) == 1)){
                    Result.insert(i+1,".");
                    break;
                }
                else if(Result[i] != test[i]){
                    Result.insert(i,".");
                    break;    
                }
            }
            if(Result[0] == '.'){
                Result = '0' + Result ;
            }
            Return.result = (sign + Result) ;
            return Return ;
        }

        // BigReal operator-(BigReal& other){
        // }
        
};

int main(){
    //BigDecimalInt a("232") , b("5796") ;
    BigReal a("232.924") , b("-232.39") ;
    cout << a+b ;
}