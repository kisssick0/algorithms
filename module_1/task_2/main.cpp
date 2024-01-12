#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>

// 2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
// Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i].
// Если такого элемента нет, выведите n. n, m ≤ 10000.
// Требования: Время работы поиска k для каждого элемента B[i]: O(log(k)).
// Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
// Формат входных данных.
// В первой строчке записаны числа n и m. Во второй и третьей массивы A и B соответственно.

using namespace std;

int binarySearch(int* arr, int sizeArr, int downLimit, int upperLimit, int number){
    assert(downLimit <= upperLimit);
    
    if (arr[upperLimit] < number)
        return sizeArr;
    
    int minIndex = upperLimit;
    while(downLimit <= upperLimit){
        int mid = downLimit + (upperLimit - downLimit) / 2;
        if (arr[mid] < number)
            downLimit = mid + 1;
        else {
            if (arr[mid] <= arr[minIndex])
                minIndex = mid;
            upperLimit -= 1;
        }
    }
    return minIndex;
}

int min(int a, int b){
    if (a < b)
        return a;
    else
        return b;
}

int expSearch(int number, int* arr, int size){
    assert(size > 0);

    int downLimit = 0;
    int upperLimit = 1;
    while((upperLimit < size) & (arr[upperLimit] < number)){
        upperLimit *= 2;
    }
    downLimit = upperLimit / 2;
    
    return binarySearch(arr, size, downLimit, min(upperLimit, size-1), number); // arrIndexes;
}


int main(int argc, char const *argv[]){
    int arrSizeA, arrSizeB;
    cin >> arrSizeA >> arrSizeB;
    
    int* arrA = new int[arrSizeA];
    for (int i = 0; i < arrSizeA; i++){
            int num = 0;
            cin >> num;
            arrA[i] = num;
    }
    
    int* arrB = new int[arrSizeB];
    for (int i = 0; i < arrSizeB; i++){
            int num = 0;
            cin >> num;
            arrB[i] = num;
    }

    for (int i = 0; i < arrSizeB; i++){
        cout << expSearch(arrB[i], arrA, arrSizeA) << ' ';
    }
    
    delete [] arrA;
    delete [] arrB;

    return 0;
}
