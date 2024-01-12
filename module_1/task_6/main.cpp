// 6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

#include <iostream>
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());

template<class T>
class CmpSmth{
public:
    bool operator()(const T& left, const T& right){
        return left > right;
    }
};

template<class T, class Compare = CmpSmth<T>>
int partition(T array[], int left, int right, Compare cmp = CmpSmth<T>()){
    uniform_int_distribution<int> dis(left, right);
    int pivot = dis(gen);
    swap(array[pivot], array[right]);
    pivot = right;
    int i = left;
    int j = left;
    while (j < right){
        if (cmp(array[j], array[pivot])){
            j++;
        }
        else{
            swap(array[j], array[i]);
            j++;
            i++;
        }
    }
    swap(array[i], array[j]);
    return i;
}

template<class T, class Compare = CmpSmth<T>>
int kStat(T array[], int left, int right, int k, Compare cmp = CmpSmth<T>()){
    int pos = right + 1;
    while (pos != k){
        pos = partition(array, left, right, cmp);
        if (pos < k){
            left = pos;
        }
        else{
            right = pos - 1;
        }
    }
    return array[pos];
}

int main(int argc, const char * argv[]) {
    int n = 0;
    cin >> n;
    
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    cout << kStat(arr, 0, n - 1, n * 0.1, [](const int& l, const int& r) { return l > r; }) << endl
            << kStat(arr, 0, n - 1, n * 0.5) << endl
            << kStat(arr, 0, n - 1, n * 0.9);
    
    delete[] arr;
    
    return 0;
}
