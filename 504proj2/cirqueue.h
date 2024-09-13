#ifndef CIRQUEUE_H
#define CIRQUEUE_H

#include <cstdlib>
#include <cstring>
#include <stdexcept>

#include <QObject>
#include <QString>
#include <QDebug>

template<typename T, int MAX_ELEMENT_NUM>
class CirQueue{
private:
    T* queue;
    int head, tail, element_num;
public:
    CirQueue();
    ~CirQueue();
    void Push(T element);
    void Pushes(const T* elements, int len);
    bool Empty();
    int Size();
    T At(int position);
    void SetAt(int position, T value);
    void Clear();
    void CopyTo(T* target, int start, int length);
    T PopFront();
    T PopBack();
    T Front();
    T Tail();
    void Print();
};

template<typename T, int MAX_ELEMENT_NUM>
CirQueue<T, MAX_ELEMENT_NUM>::CirQueue()
{
    queue = static_cast<T*>(malloc(MAX_ELEMENT_NUM + 1024));
    head = 0;
    tail = 0;
    element_num = 0;
}

template<typename T, int MAX_ELEMENT_NUM>
CirQueue<T, MAX_ELEMENT_NUM>::~CirQueue() {
    if (queue != NULL) {
        free(queue);
    }

}

template<typename T, int MAX_ELEMENT_NUM>
void CirQueue<T, MAX_ELEMENT_NUM>::Push(T element) {
    if (element_num >= MAX_ELEMENT_NUM) {
        throw std::length_error("Element num exceed the queue size.");
        return ;
    }
    queue[tail++] = element;
    while (tail > MAX_ELEMENT_NUM) {
        tail -= MAX_ELEMENT_NUM;
    }
    ++element_num;
}

template<typename T, int MAX_ELEMENT_NUM>
void CirQueue<T, MAX_ELEMENT_NUM>::Pushes(const T* elements, int len)
{
    for (int i = 0; i < len; ++i) {
        this->Push(elements[i]);
    }
}

template<typename T, int MAX_ELEMENT_NUM>
bool CirQueue<T, MAX_ELEMENT_NUM>::Empty()
{
    return (element_num == 0);
}

template<typename T, int MAX_ELEMENT_NUM>
int CirQueue<T, MAX_ELEMENT_NUM>::Size()
{
    return element_num;
}

template<typename T, int MAX_ELEMENT_NUM>
T CirQueue<T, MAX_ELEMENT_NUM>::At(int position)
{
    if (position >= 0) {
        if (position >= element_num) {
            throw std::range_error("Request element out of range.");
        }
        return (queue[(head + position) % MAX_ELEMENT_NUM]);
    } else {
        if ((- position) > element_num) {
            throw std::range_error("Request element out of range.");
        }
        return (queue[(tail + position + MAX_ELEMENT_NUM) % MAX_ELEMENT_NUM]);
    }
}

template<typename T, int MAX_ELEMENT_NUM>
void CirQueue<T, MAX_ELEMENT_NUM>::SetAt(int position, T value)
{
    if (position >= 0) {
        if (position >= element_num) {
            throw std::range_error("Request element out of range.");
        }
        queue[(head + position) % MAX_ELEMENT_NUM] = value;
    } else {
        if (position >= element_num) {
            throw std::range_error("Request element out of range.");
        }
        queue[(tail + position + MAX_ELEMENT_NUM) % MAX_ELEMENT_NUM] = value;
    }
}

template<typename T, int MAX_ELEMENT_NUM>
void CirQueue<T, MAX_ELEMENT_NUM>::Clear()
{
    head = 0;
    tail = 0;
    element_num = 0;
}

template<typename T, int MAX_ELEMENT_NUM>
void CirQueue<T, MAX_ELEMENT_NUM>::CopyTo(T *target, int start, int length)
{
    if (start + length > element_num) {
        throw std::range_error("Try to copy elements out of queue range.");
    }
    if (head + start + length > MAX_ELEMENT_NUM) {
        int fir_length = head + start + length - MAX_ELEMENT_NUM;
        int sec_length = length - fir_length;
        memcpy(target, queue + head + start, sizeof(T) * fir_length);
        memcpy(target, queue, sizeof(T) * sec_length);
    } else {
        memcpy(target, queue + head + start, sizeof(T) * length);
    }
}

template<typename T, int MAX_ELEMENT_NUM>
T CirQueue<T, MAX_ELEMENT_NUM>::PopFront()
{
    if (element_num <= 0) {
        throw std::range_error("No element to pop.");
    }
    T ret = queue[head];
    ++head;
    while (head >= MAX_ELEMENT_NUM) {
        head -= MAX_ELEMENT_NUM;
    }
    --element_num;
    return ret;
}

template<typename T, int MAX_ELEMENT_NUM>
T CirQueue<T, MAX_ELEMENT_NUM>::PopBack()
{
    if (element_num <= 0) {
        throw std::range_error("No element to pop.");
    }
    T ret = queue[tail - 1];
    --tail;
    while (tail < 0) {
        tail += MAX_ELEMENT_NUM;
    }
    --element_num;
    return ret;
}

template<typename T, int MAX_ELEMENT_NUM>
T CirQueue<T, MAX_ELEMENT_NUM>::Front()
{
    if (element_num <= 0) {
        throw std::range_error("No element to return.");
    }
    return queue[head];
}

template<typename T, int MAX_ELEMENT_NUM>
T CirQueue<T, MAX_ELEMENT_NUM>::Tail()
{
    if (element_num <= 0) {
        throw std::range_error("No element to return.");
    }
    return queue[tail - 1];
}

template<typename T, int MAX_ELEMENT_NUM>
void CirQueue<T, MAX_ELEMENT_NUM>::Print() {
//    for (int i = head; i < head + element_num; ++i) {
//        printf("%c ", static_cast<char>(queue[i % MAX_ELEMENT_NUM]));
//    }
//    printf("\n");
    QString q_str("");
    for (int i = head; i < head + element_num; ++i) {
        q_str.append(static_cast<char>(queue[i % MAX_ELEMENT_NUM]));
    }
    qDebug()<<q_str;
}

#endif // CIRQUEUE_H
