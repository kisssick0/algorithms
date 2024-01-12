#include <iostream>
#include <cassert>

using namespace std;

// Реализовать очередь с динамическим зацикленным буфером.
// Обрабатывать команды push back и pop front.

// В первой строке количество команд n. n ≤ 1000000.
// Каждая команда задаётся как 2 целых числа: a b.
// a = 2 - pop front
// a = 3 - push back
// Если дана команда pop front, то число b - ожидаемое значение. Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.

//Требуется напечатать YES - если все ожидаемые значения совпали.
// Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.


// Очередь целых чисел, реализованная с помощью массива.
class Queue{
public:
    explicit Queue(int size) : bufferSize(size), realSize(0), head(0), tail(0)
    { buffer = new int[bufferSize]; };  // Создаем буфер.

    ~Queue() { delete[] buffer; }
    
    // Добавление элемента.
    void Enqueue(int a){
        if ((realSize + 1) == bufferSize){
            GrowBuffer();
        }
        buffer[tail] = a;
        realSize++;
        tail = (tail + 1) % bufferSize;
    }
    
    // Извлечение элемента.
    int Dequeue(){
        if (IsEmpty())
            return -1;
        int result = buffer[head];
        head = (head + 1) % bufferSize;
        realSize--;
        return result;
    }
    
    void GrowBuffer(){
        int newBufferSize = bufferSize * 2;
        int* newBuffer = new int[newBufferSize];
        
        int j = 0;
        for (int i = head; i != tail; i = (i + 1) % bufferSize){
            newBuffer[j] = buffer[i];
            j++;
        }
        newBuffer[j] = buffer[tail];
        head = 0;
        tail = j;
        delete[] buffer;
        buffer = newBuffer;
        bufferSize = newBufferSize;
    }
    
    // Проверка на пустоту.
    bool IsEmpty() const {
        if (realSize == 0)
            return true;
        //if (head == tail)
            //return true;
        return false;
    }
    
private:
    int* buffer;
    int bufferSize; // Размер буффера
    int realSize;   // Количество элементов в массиве
    int head; // Указывает на первый элемент очереди.
    int tail; // Указывает на следующий после последнего.
};


void run(int numberOfCommands){
    Queue queue(2);
    
    int command, expectedValue;
    for (int i = 0; i < numberOfCommands; i++){
        cin >> command >> expectedValue;
    
        switch (command){
            case 2:
            {
                int tmpVal = queue.Dequeue();
                if (tmpVal != expectedValue)
                {
                    cout << "NO" << endl;
                    return;
                }
                break;
            }
            case 3:
            {
                queue.Enqueue(expectedValue);
                break;
            }
            
        }
    }
    cout << "YES" << endl;
    return;
}

int main(int argc, const char * argv[]){
    int numberOfCommands;
    cin >> numberOfCommands;
    
    run(numberOfCommands);
    
    return 0;
}
