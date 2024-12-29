#include "PrimitiveTypes.hpp"
#include <cstddef>
#include <stdexcept>
#include <cmath>

// Helper static functions
SqlInt SqlInt::binarySumm(bool sign, SqlInt a, SqlInt b){
    using namespace std;
    bitset<size> result;
    result[signBit] = sign;

    int carry = 0;
    
    for(int i = size - 1; i > 0; i--){

        bool bit1 = a.bits[i];
        bool bit2 = b.bits[i];
        result[i] = (bit1 ^ bit2 ^ carry);
        carry = (bit1 & bit2) | (carry & (bit1 ^ bit2));
    }

    if(carry != 0){
        throw runtime_error("Summ overflow");
    }

    return SqlInt(result);
}

// Gets flipped number
// Ex: 0000101101 -> 0000010010
SqlInt SqlInt::flipNumber(SqlInt number, int position){
    int counter = signBit + 1;
    while (number.bits[counter] != 1 && counter < size){
        counter++;
    }
    for(int i = position; i < size; i++){
        number.bits.flip(i);
    }

    return number;
}

// Constructors & destructors

// Here I convert int to bitset, in future I will make an helper class for
// converting from base-2 to base-10 and vice versa
SqlInt::SqlInt(int value){    
    using namespace std;
    // Set the sign bit
    bits[signBit] = value > 0;
    
    for (int i = 0; i < size - 1; i++) {
        int bit = value % 2;
        value /= 2;
        bits[size - 1 - i] = bit;
    }

    if(value != 0){
        throw runtime_error("Invalid number");
    }
}
SqlInt::SqlInt(std::bitset<size> bits){
    this->bits = bits;
}

SqlInt::~SqlInt(){}

// Implementing methods
std::vector<std::byte> SqlInt::toBytes(){
    using namespace std;
    return std::vector<std::byte>();
}

std::string SqlInt::toString(){
    std::string result = "";

    for(int i = 0; i < size; i++){
        result += bits[i] ? '1' : '0';
    }

    return result;
}

// Converters
int SqlInt::toInt(SqlInt value){
    return value.toInt();
}
int SqlInt::toInt(){
    int result = 0;
    // size - 2 because of sign bit and because we count from 0
    int powder = size - 2;
    for(int i = signBit + 1; i < size; i++){
        result += bits[i] * (int)pow(2, powder);
        powder--;
    }
    // +1 because 0 stands for - and 1 stands for +
    // but here we need odd and even numbers
    result = result * (int)pow(-1, (double)bits[signBit] + 1);
    return result;
}

// Math methods
SqlInt SqlInt::Abs(SqlInt value){
    value.bits[signBit] = 1;
    return value;
}

// Appropriation
SqlInt SqlInt::operator=(int value){
    return SqlInt(value);
}
// Logical operators
bool SqlInt::operator<(SqlInt value){
    int counter = signBit;
    while (value.bits[counter] == this->bits[counter]&& counter < size){
        counter++;
    }
    
    return this->bits[counter] < value.bits[counter];
}

bool SqlInt::operator<=(SqlInt value){
    return !(*this > value);
}

bool SqlInt::operator>(SqlInt value){
    int counter = signBit;
    while (value.bits[counter] == this->bits[counter] && counter < size){
        counter++;
    }
 
    return this->bits[counter] > value.bits[counter];
}

bool SqlInt::operator>=(SqlInt value){
    return !(*this < value);
}

bool SqlInt::operator==(SqlInt value){
    for(int i = 0; i < size; i++){
        if(bits[i] == value.bits[i]){
            return true;
        }
    }
    return false;
}

bool SqlInt::operator!=(SqlInt value){
    for(int i = 0; i < size; i++){
        if(bits[i] != value.bits[i]){
            return true;
        }
    }
    return false;
}

// Arithmetic operators
SqlInt SqlInt::operator+(SqlInt value){
    SqlInt* valuePtr = &value;
    SqlInt result(0);
    // Is two numbers of the same sign get pure summ with sign
    if(value.bits[signBit] == bits[signBit]){
        result = binarySumm(bits[signBit], *this, value);
        return result;
    }

    // Getting num what is more in absolute value
    SqlInt min; 
    SqlInt max;
    bool sign;
    if(Abs(value) < Abs(*this)){
        sign = this->bits[signBit];
        
        min = Abs(value);
        max = Abs(*this);
    }else{
        sign = value.bits[signBit];
        min = Abs(*this);
        max = Abs(value);
    }
    int counter = signBit + 1;
    while (max.bits[counter] != 1) {
        counter++;
    }
    min = flipNumber(Abs(min), counter);

    min = binarySumm(max.bits[signBit], min, SqlInt(1));
    
    result = binarySumm(sign, min, max);
    // Get rid of carry bit
    counter = signBit + 1;
    while (result.bits[counter] != 1) {
        counter++;
    }
    result.bits.flip(counter);
    
    return result;
}

SqlInt& SqlInt::operator++(int){
    *this = *this + SqlInt(1);
    return *this;
}

SqlInt SqlInt::operator+=(SqlInt value){
    *this = *this + value;
    return *this;
}

SqlInt SqlInt::operator-(SqlInt value){
    SqlInt result;

    value.bits[signBit] = !value.bits[signBit];
    result = *this + value;
    return result;
}

SqlInt& SqlInt::operator--(int){
    *this = *this - SqlInt(1);
    return *this;
}
SqlInt SqlInt::operator-=(SqlInt value){
    *this = *this - value;
    return *this;
}

SqlInt::operator int(){
    return this->toInt();
}

SqlInt SqlInt::operator*(SqlInt value){
    SqlInt result = 0;
    for(int i = 0; i < Abs(value).toInt(); i++){
        result += Abs(*this);
    }
    result.bits[signBit] = this->bits[signBit] == value.bits[signBit];
    return result;
}

SqlInt SqlInt::operator*=(SqlInt value){
    *this = *this * value;
    return *this;
}

/*
* Rounds to the bottom of the fraction
*/
SqlInt SqlInt::operator/(SqlInt value){
    SqlInt result = Abs(*this);
    SqlInt divisor = Abs(value);

    int counter = 0;
    do{
        result -= divisor;
        counter++;
    }while(result.toInt() >= 0);

    // Because we round to the bottom of the fraction
    counter--;

    return counter;
}

SqlInt SqlInt::operator/=(SqlInt value){
    *this = *this / value;
    return *this;
}

SqlInt SqlInt::operator%(SqlInt value){
    SqlInt result = *this;
    result = *this - ((*this / value) * value);
    return result;
}

SqlInt SqlInt::operator%=(SqlInt value){
    *this = *this % value;
    return *this;
}