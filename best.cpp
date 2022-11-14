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

        BigDecimalInt add_zeros(BigReal a ,BigReal b , char sign){
            BigDecimalInt s ; int result = (a.fraction.size() - b.fraction.size()) ;
            for(int i = 0 ; i < abs(result) ; i++){
                if(result > 0){
                    b.sum.setNumber(push_back(b.sum,"0"));
                    if(sign == '+'){
                        s =(a.sum + b.sum);
                    }
                    else if(sign == '-'){
                        s =(a.sum - b.sum);
                    }
                }
                else if(result < 0){
                    a.sum.setNumber(push_back(a.sum,"0"));
                    if(sign == '+'){
                        s =(a.sum + b.sum);
                    }
                    else if(sign == '-'){
                        s =(a.sum - b.sum);
                    }
                }
                else{
                    break;
                }
            }
            return s ;
        }

        BigReal operations_on_plus_and_minus(BigReal r){
            string sign = "" , test , Result ;
            Result = r.sum.getNumber() ;
            test = (r.integer.getNumber() + '.' + r.fraction.getNumber()) ;
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
            if (r.sum.sign() == 0){sign = '-';}
            r.result = (sign + Result) ;
            return r ;
        }

        void constructors(string number){
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
        
        BigReal(){
            integer.setNumber("0") ;
            fraction.setNumber("0");
            sum.setNumber("0");
            result = "0" ;
        }

        explicit BigReal(const string number){
            constructors(number);
        }

        BigReal(BigDecimalInt biginteger){
            string number = biginteger.getNumber() ;
            if(biginteger.sign() == 0){ number = '-' + number ;}
            constructors(number);
        }

        // //Lvalues
        // BigReal (const BigReal& other){
        //     integer= other.integer;
        //     fraction= other.fraction;
        //     sum= other.sum;
        //     result= other.result;

        // }

        // //Rvalues
        // BigReal (BigReal&& other){
        // this->integer= other.integer;
        // this->fraction= other.fraction;
        // this->sum= other.sum;
        // this->result= other.result;
        // cout<<"move constractor/n";

        // other.integer.setNumber("0") ;
        // other.fraction.setNumber("0");
        // other.sum.setNumber("0");
        // other.result = "0";

        // }

        BigReal& operator=(BigReal &anotherReal) {
            integer = anotherReal.integer;
            fraction = anotherReal.fraction;
            sum = anotherReal.sum ;
            result = anotherReal.result ;
            return *this;
        }


        BigReal operator+(BigReal other){
            BigReal Return ;
            Return.integer = integer + other.integer ;
            Return.fraction = fraction + other.fraction ;
            if((fraction.size()- other.fraction.size()) != 0){
                Return.sum = add_zeros(*this ,other,'+') ;
            }
            else{
                Return.sum = sum + other.sum ;
            }
            return operations_on_plus_and_minus(Return);
        }

        BigReal operator-(BigReal other){
            BigReal Return ; 
            Return.integer = integer - other.integer ;
            Return.fraction = fraction - other.fraction ;
           if((fraction.size()- other.fraction.size()) != 0){
                Return.sum = add_zeros(*this ,other,'-') ;
            }
            else{
                Return.sum = sum - other.sum ;
            }
            return operations_on_plus_and_minus(Return);
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

        bool operator == ( BigReal &anotherReal){
            if (sum.sign() == anotherReal.sum.sign() && integer == anotherReal.integer &&fraction == anotherReal.fraction&& fraction.size() == anotherReal.fraction.size()  ){
                return true ;
            }
            else {
                return false;
            }
        }

        int Size (){
            return sum.size() ;
        }

        int Sign(){
            if (sum.sign() == 1){
                return 1 ;
            }
            else{
                return 0;
            }
        }

        friend ostream& operator<<(ostream& out , const BigReal other){
            out<<other.result ;
            return out ;
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
    BigReal a("12.3") , b("6.759") , c ;
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
    cout << c - b <<endl;  
    cout << c.operator==(b) <<endl;
    cout << c.operator>(b) <<endl;
    cout << c.operator<(b) <<endl;
    cout << c.Size()<<endl;
    cout << c.Sign()<<endl;
    cout << "------------------------------------------------------------"<<endl;

    //5564.534 done
    //5563.466 done
    //-5564.534 done
    //-5563.466 done

}
