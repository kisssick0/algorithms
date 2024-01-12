// Дан отсортированный по возрастанию массив попарно различных целых чисел A[0..n-1]. На вход также подается некоторое целое число k. Необходимо вернуть индекс элемента k в массиве A, если он там присутствует, либо вернуть позицию, куда его следовало бы вставить, чтобы массив остался отсортированным.
// Требование: сложность O(logN)

// В первой строчке записано число n – размерность массива A. Во второй строчке перечислены элементы массива A. В третьей строчке записано значение k.

#include <iostream>

using namespace std;

int insertion_position(int* arr, int size, int num){
    int first = 0;
    int last = size;
    while( first < last ) {
    int mid = ( first + last ) / 2; if( arr[mid] < num )
    first = mid + 1;
    else
        last = mid;
    }
    return first;
}


int main(int argc, const char * argv[]) {
    int arrASize;
    cin >> arrASize;
    
    int* arrA = new int[arrASize];
    for (int i = 0; i < arrASize; i++){
        cin >> arrA[i];
    }
    
    int number;
    cin >> number;
    
    cout << insertion_position(arrA, arrASize, number);
    
    return 0;
}
