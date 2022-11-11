#include <iostream>
#include "BigDecimalIntClass.h"
#include "BigDecimalIntClass.cpp"
#include <string>
using namespace std;

string push_back(BigDecimalInt a ,const string zero){
    string Result = a.getNumber() + zero ;
    if(a.sign() == 0){Result = '-' + Result ;}
    return Result ;
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

        explicit BigReal(const string number){
            string I , F ;
            int point_found = 0 ;
            for(char i : number){
                if(i == '.'){
                    point_found += 1 ;
                }
                if(point_found == 0){
                    I.push_back(i);
                }
                else if(point_found == 1 && i != '.' ){
                    F.push_back(i);
                }
                else if(point_found > 1){
                    cout<< "invalid" << endl ;
                    exit(1);
                }
            }

            if(I.empty()){
                integer.setNumber("0") ;
                result = "0" ;
            }
            else{
                integer.setNumber(I) ;
                result = I ;
            }

            if(F.empty()){
                fraction.setNumber("0") ;
                result += ".0" ;
            }
            else{
                fraction.setNumber(F) ;
                result += "." + F ;
            }
            sum = integer ;
            sum.setNumber(push_back(sum , fraction.getNumber()));
        }

        static void add_zeros(BigReal& a ,BigReal& b){
            int result = (a.fraction.size() - b.fraction.size()) ;
            for(int i = 0 ; i < abs(result) ; i++){
                if(result > 0){
                    b.sum.setNumber(push_back(b.sum,"0"));
                }
                else if(result < 0){
                    a.sum.setNumber(push_back(a.sum,"0"));
                }
                else{
                    break;
                }
            }
        }

        friend ostream& operator<<(ostream& out , const BigReal other){
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
            if(Return.sum.sign() == 1){sign = "" ;}
            else if (Return.sum.sign() == 0){sign = '-';}
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

        BigReal operator-(BigReal other){
            BigReal Return ;
            Return.integer = integer - other.integer ;
            Return.fraction = fraction - other.fraction ;
            add_zeros(*this ,other) ;
            Return.sum = (sum - other.sum) ;
            string sign ;
            if(Return.sum.sign() == 1){sign = "" ;}
            else if (Return.sum.sign() == 0){sign = '-';}
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


        bool operator > ( BigReal& anotherReal) {

                if (this->integer > anotherReal.integer) {
                    return true;
                }
                else if (this->integer == anotherReal.integer) {
                    if (this->fraction > anotherReal.fraction) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
        }

        bool operator < ( BigReal &anotherReal) {

                if (this->integer < anotherReal.integer) {
                    return true;
                }
                else if (this->integer == anotherReal.integer) {
                    if (this->fraction < anotherReal.fraction) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
        }

        bool operator == ( BigReal &anotherReal){
            if (sum.sign() == anotherReal.sum.sign() && integer == anotherReal.integer &&fraction == anotherReal.fraction&& fraction.size() == anotherReal.fraction.size()  ){
                return true ;
            }
            else {
                return false;
            }
        }

        int Sign(){
            if (sum.sign() == 1){
                return 1 ;
            }
            else{
                return 0;
            }
        }

        int Size (){
            return sum.size() ;
        }

       BigReal& operator=(BigReal &anotherReal) {
            integer = anotherReal.integer;
            fraction = anotherReal.fraction;
            sum = anotherReal.sum ;
            result = anotherReal.result ;
            return *this;
        }

        friend istream& operator>>(istream& in, BigReal& other) {
            string number ;   
            cout << "Enter a number: ";
            in >> number;
            BigReal temp(number);
            other = temp ;
            return in;
        }

};

int main(){
    //BigDecimalInt a("232") , b("5796") ;
    BigReal a("-232.924999") , b("5796.399") , c ;
    cout << a <<endl;
    cout << b << endl ;
    cout << a+b<<endl;
    cout << a-b <<endl;
    cout << a.operator==(b) <<endl;
    cout << a.operator>(b) <<endl;
    cout << a.operator<(b) <<endl;
    cout << a.Size()<<endl;
    cout << a.Sign()<<endl;
    cout << "------------------------------------------------------------"<<endl;
    cin >> c;
    cout << c <<endl;
    cout << b << endl ;
    cout << c + b << endl ;
    cout << c - b <<endl;  //wrong output
    cout << c.operator==(b) <<endl;
    cout << c.operator>(b) <<endl;
    cout << c.operator<(b) <<endl;
    cout << c.Size()<<endl; //wrong output
    cout << c.Sign()<<endl;
    cout << "------------------------------------------------------------"<<endl;
    //5564.534 done
    //5563.466 done
    //-5564.534 done
    //-5563.466 done

}
