#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// 1.2 Вернуть значение бита в числе N по его номеру K.
// Формат входных данных. Число N, номер бита K

int bit_value_at_position(unsigned N, unsigned K){
    return (N >> K) & 1;
}



int main(int argc, char const *argv[])
{
    unsigned number =  0;
    cin >> number;
    unsigned bit_number = 0;
    cin >> bit_number;

    
    cout << bit_value_at_position(number, bit_number) << endl;

    return 0;
}
