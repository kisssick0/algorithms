/*
 4.3 Планировщик процессов
В операционной системе Technux есть планировщик процессов. Каждый процесс характеризуется:
- приоритетом P
- временем, которое он уже отработал t
- временем, которое необходимо для завершения работы процесса T
Планировщик процессов выбирает процесс с минимальным значением P * (t + 1), выполняет его время P и кладет обратно в очередь процессов.
Если выполняется условие t >= T, то процесс считается завершенным и удаляется из очереди.
Требуется посчитать кол-во переключений процессора.
Формат входных данных: Сначала вводится кол-во процессов. После этого процессы в формате P T
 Формат выходных данных: Кол-во переключений процессора.
 */


#include <iostream>
#include <string.h>

using namespace std;

struct Process{
    int priority = 0;
    int timePassed = 0;
    int timeToEndProcess = 0;
    int newPriority = priority*(timePassed+1);
};

template <class T> class CmpSmth{
public:
    bool operator()(const T& left, const T& right){
        return left < right;
    }
};

class CmpProcess{
public:
    bool operator()(const Process& proc1, const Process& proc2){
        return proc1.newPriority < proc2.newPriority;
    }
};

template <typename T, class Compare = CmpSmth<T>> class Heap{
public:
    void siftDown(int index){
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;
        
        if (left < heapSize && cmp(arr[left], arr[index]))
            largest = left;
        if (right < heapSize && cmp(arr[right], arr[largest]))
            largest = right;
        if (largest != index){
            swap(arr[index], arr[largest]);
            siftDown(largest);
        }
    }
    
    void siftUp(int index){
        while(index > 0) {
            int parent = (index - 1) / 2;
            
            if (cmp(arr[index], arr[parent])){
                swap(arr[index], arr[parent]);
                siftUp(parent);
            }
            else
                break;
        }
    }
    
    int getSize(){
        return heapSize;
    }
    
    Heap(){
        heapSize = 0;
        arrSize = 2;
        arr = new T[2];
    }
    
    Heap(const Heap& heap) {
        arrSize = heap.arrSize;
        heapSize = heap.heapSize;
        arr = new T[heap.arrSize];
        memcpy(arr, heap.array, sizeof(T) * heap.arrSize);
    }
    
    Heap& operator=(const Heap &heap) {
        arrSize = heap.arrSize;
        heapSize = heap.heapSize;
        
        delete[] arr;
        arr = new int[heap.arrSize];
        memcpy(arr, heap.arr, sizeof(T) * heap.arrSize);
        return *this;
    }
    
    ~Heap(){
        delete[] arr;
    }

    void push(const T& t){
        if (!heapSize){
            arr[0] = t;
            heapSize++;
            return;
        }
        if (heapSize == arrSize){
            grow();
        }
        arr[heapSize] = t;
        siftUp(heapSize);
        heapSize++;
    };
    
    T pop(){
        heapSize--;
        T proc = arr[0];
        arr[0] = arr[heapSize];
        siftDown(0);
        return proc;
    }

    void out(){
        cout << arr[0]  << " ";
        for (int i = 1; i < heapSize; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
private:
    T* arr;
    int heapSize;
    int arrSize;
    Compare cmp;
    
    void grow(){
        arrSize *= 2;
        T* newArr = new T[arrSize];
        memcpy(newArr, arr, sizeof(T) * arrSize);
        delete[] arr;
        arr = newArr;
    }
};

int countSwitch(Heap<Process, CmpProcess> &heap){
    int count = 0;
    Process proc{};
    
    while (heap.getSize() != 0){
        proc = heap.pop();
        proc.timePassed += proc.priority;
        if (proc.timePassed < proc.timeToEndProcess){
            heap.push(proc);
        }
        count++;
    }
    return count;
}

int main(int argc, const char * argv[]){
    Heap<Process, CmpProcess> heap;
        int countProcess;
        cin >> countProcess;

        for (int i = 0; i < countProcess; ++i){
            int priority, timeNeeded;
            Process proc = Process();
            cin >> priority >> timeNeeded;
            proc.priority = priority;
            proc.timeToEndProcess = timeNeeded;
            heap.push(proc);
        }

    cout << countSwitch(heap) << endl;
    
    return 0;
}
