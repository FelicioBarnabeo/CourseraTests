#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

/*
На практике часто возникают объекты, создание которых занимает значительное время, например, потоки (threads),
TCP-соединения или подключения к базе данных. Поэтому, когда такой объект становится не нужен, его не разрушают,
а откладывают в сторону, чтобы потом переиспользовать.
В этой задаче вам предстоит реализовать такую схему — вам надо написать шаблон класса ObjectPool:

Объект класса ObjectPool должен поддерживать два набора объектов: выделенные и освобождённые, — изначально оба набора пусты.
Метод Allocate должен работать так:
если есть хотя бы один освобождённый объект, то его надо перенести в множество выделенных и вернуть указатель на него в качестве результата функции
если же освобождённых объектов нет, то создаётся новый объект, помещается в множество выделенных, и указатель на него возвращается в качестве результата функции
Метод TryAllocate работает аналогично, однако если освобождённых объектов нет, он должен просто возвращать nullptr.
Метод Deallocate переносит объект из множества выделенных в множество освобождённых; если переданный объект не содержится в множестве выделенных,
метод Deallocate должен бросать исключение invalid_argument.
Методы Allocate и TryAllocate должны возвращать объекты в порядке FIFO, т.е. множество освобождённых объектов должно представлять собой очередь:
методы [Try]Allocate должны извлекать объекты из её начала, а метод Deallocate должен помещать освобождаемый объект в её конец.
Деструктор объекта ObjectPool должен уничтожать все объекты пула, как выделенные, так и освобождённые.
*//////



//template <class T>
//class ObjectPool{
//public:
//    T* Allocate();
//    T* TryAllocate();
//    void Deallocate(T* object);
//    ~ObjectPool()
//    {
//        clear();
//    }
//    void clear();
//private:
//    deque<T*> free;
//    set<T*> allocated;
//};

//template<class T>
//T * ObjectPool<T>::Allocate()
//{
//    T* ret = nullptr;
//    if(free.size())
//    {
//        ret = free.front();
//        free.pop_front();
//    }
//    else {
//        ret = new T;
//    }
//    allocated.insert(ret);
//    return ret;
//}

//template<class T>
//T *ObjectPool<T>::TryAllocate()
//{
//    T* ret = nullptr;
//    if(free.size())
//    {
//        ret = free.front();
//        allocated.insert(ret);
//        free.pop_front();
//        return ret;
//    }
//    return ret;
//}

//template<class T>
//void ObjectPool<T>::Deallocate(T *object)
//{
//    auto it = allocated.find(object);
//    if(it != end(allocated))
//    {
//        free.push_back(object);
//        allocated.erase(it);
//    }
//    else {
//        throw invalid_argument("");
//    }
//}

//template<class T>
//void ObjectPool<T>::clear()
//{
//    for(auto v : allocated)
//    {
//        delete v;
//    }
//    for(auto v: free)
//    {
//        delete v;
//    }
//    free = {};
//    allocated = {};
//}


//queue и  с deque в free одинаковы по времени для пула
template <class T>
class ObjectPool{
public:
    T* Allocate();
    T* TryAllocate();
    void Deallocate(T* object);
    ~ObjectPool()
    {
        clear();
    }
    void clear();
private:
    queue<T*> free;
    set<T*> allocated;
};

template<class T>
T * ObjectPool<T>::Allocate()
{
    if(free.empty()) {
        free.push(new T);
    }
    auto ret = free.front();
    free.pop();
    allocated.insert(ret);
    return ret;
}

template<class T>
T *ObjectPool<T>::TryAllocate()
{
    if(free.empty())
        return nullptr;
    return Allocate();
}

template<class T>
void ObjectPool<T>::Deallocate(T *object)
{
    if(allocated.find(object) == allocated.end()) {
        throw invalid_argument("");
    }
    free.push(object);
    allocated.erase(object);
}

template<class T>
void ObjectPool<T>::clear()
{
    for(auto v : allocated) {
        delete v;
    }
    while(!free.empty()) {
        delete free.front();
        free.pop();
    }
}




void TestObjectPool()
{
    ObjectPool<string> pool;
    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();
    *p1 = "first";
    *p2 = "second";
    *p3 = "third";
    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");
    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");
    pool.Deallocate(p3);
    pool.Deallocate(p1);
//    ASSERT_EQUAL(pool.TryAllocate(), nullptr);
//    ASSERT_EQUAL(pool.TryAllocate(), nullptr);
}



//int main()
//{
//    TestRunner tr;
//    RUN_TEST(tr, TestObjectPool);
//    return 0;
//}

