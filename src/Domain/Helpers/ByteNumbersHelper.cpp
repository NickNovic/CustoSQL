#include "ByteNumberHelper.hpp"
#include <stdexcept>
#include <iostream> 
#include <vector>

// Gets summ of two numbers in binary form
// They must have the same size

std::vector<bool> summ(std::vector<bool> a, std::vector<bool> b){
    int size = a.size();
    
    std::vector<bool> result(size);

    if(a.size() != b.size()){
        throw std::runtime_error("Sizes of numbers must be equal");
    }

    bool carry = false;
    std::vector<bool> invertedResult;
    for(int i = size - 1; i >= 0; i--){
        bool bit1 = a[i];
        bool bit2 = b[i];
        result[i] = bit1 ^ bit2 ^ carry;
        carry = (bit1 & bit2) | (carry & (bit1 ^ bit2));
    }

    if(carry){
        throw std::runtime_error("Summ overflow");
    }

    return result;
}