#ifndef SIMPLE_VECTOR_2_H
#define SIMPLE_VECTOR_2_H

#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

//Метод PushBack должен позволять добавить элемент в вектор с помощью перемещения;
//никакие методы вектора не должны осуществлять копирование элементов.
//Таким образом, должен получиться вектор, позволяющий хранить некопируемые объекты.

using namespace  std;
template<typename T>
class SimpleVector
{
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size);
    SimpleVector(const SimpleVector<T> &rhs);
    SimpleVector& operator=(const SimpleVector<T> &rhs);
    SimpleVector(SimpleVector<T> &&rhs);
    SimpleVector& operator=(SimpleVector<T> &&rhs);
    //void operator=(const SimpleVector<T> &rhs);
    ~SimpleVector();
    T& operator[](size_t index);
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
    size_t Size() const;
    size_t Capacity() const;
    //void PushBack(const T& value);
    void PushBack(T value);
private:
    size_t m_size = 0;
    size_t m_capacity = 0;
    T* m_data = nullptr;
};

template<typename T>
SimpleVector<T>::SimpleVector(size_t size) :
    m_size(size), m_capacity(size), m_data(new T[size])
{
}

template<typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T> &rhs)
    : m_data(new T[rhs.Capacity()]),
      m_size(rhs.Size()),
      m_capacity(rhs.Capacity())
{
    copy(rhs.begin(), rhs.end(), begin());
}

template<typename T>
SimpleVector<T>& SimpleVector<T>::operator=(const SimpleVector<T> &rhs)
{
    if(&rhs == this){
        return *this;
    }
    if(m_size != rhs.Size()){
        delete[] m_data;
        m_data = new T[rhs.Capacity()];
        m_size = rhs.Size();
        m_capacity = rhs.Capacity();
    }
    copy(rhs.begin(), rhs.end(), begin());
    return *this;
}

template<typename T>
SimpleVector<T>::SimpleVector(SimpleVector<T> &&rhs)
    : m_data(rhs.m_data),
      m_size(rhs.m_size),
      m_capacity(rhs.m_capacity)
{
    rhs.m_data = nullptr;
    rhs.m_size = rhs.m_capacity = 0;
}

template<typename T>
SimpleVector<T> &SimpleVector<T>::operator=(SimpleVector<T> &&rhs)
{
    delete[] m_data;
    m_data = rhs.m_data;
    m_size = rhs.m_size;
    m_capacity = rhs.m_capacity;
    rhs.m_data = nullptr;
    rhs.m_size = rhs.m_capacity = 0;
}

//версия авторов
//void operator=(const SimpleVector& rhs) {
//  if (rhs.size <= capacity) {
//    // У нас достаточно памяти - просто копируем элементы
//    copy(rhs.begin(), rhs.end(), begin());
//    size = rhs.size;
//  } else {
//    // Это так называемая идиома copy-and-swap.
//    // Мы создаём временный вектор с помощью
//    // конструктора копирования, а затем обмениваем его поля со своими.
//    // Так мы достигаем двух целей:
//    //  - избегаем дублирования кода в конструкторе копирования
//    //    и операторе присваивания
//    //  - обеспечиваем согласованное поведение конструктора копирования
//    //    и оператора присваивания
//    SimpleVector<T> tmp(rhs);
//    swap(tmp.data, data);
//    swap(tmp.size, size);
//    swap(tmp.capacity, capacity);
//  }
//}


template<typename T>
SimpleVector<T>::~SimpleVector()
{
    delete[] m_data;
}

template<typename T>
T &SimpleVector<T>::operator[](size_t index)
{
    return m_data[index];
}

template<typename T>
T *SimpleVector<T>::begin()
{
    return m_data;
}

template<typename T>
T *SimpleVector<T>::end()
{
    return m_data+m_size;
}

template<typename T>
const T *SimpleVector<T>::begin() const
{
    return m_data;
}

template<typename T>
const T *SimpleVector<T>::end() const
{
    return m_data+m_size;
}

template<typename T>
size_t SimpleVector<T>::Size() const
{
    return m_size;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const
{
    return m_capacity;
}

//template<typename T>
//void SimpleVector<T>::PushBack(const T &value)
//{
//    if(m_size >= m_capacity)
//    {
//        auto new_cap = m_capacity==0 ? 1 : 2* m_capacity;
//        T* newData = new T[new_cap];
//        for(auto i = 0; i<m_size; i++) cout<<m_data[i]<< " " << &m_data[i]<<" ";
//        cout<<endl<<"after copy" << endl;
//        copy(begin(), end(), newData);
//        delete[] m_data;
//        m_data = newData;
//        for(auto i = 0; i<m_size; i++) cout<<m_data[i]<< " " << &m_data[i]<<" ";
//        m_capacity = new_cap;
//    }
//    m_data[m_size++] = value;
//}

template<typename T>
void SimpleVector<T>::PushBack(T value)
{
    if(m_size >= m_capacity)
    {
        auto new_cap = m_capacity==0 ? 1 : 2* m_capacity;
        T* newData = new T[new_cap];
        move(begin(), end(), newData);
        delete[] m_data;
        m_data = newData;
        m_capacity = new_cap;
    }
    m_data[m_size++] = move(value);
}




#endif // SIMPLE_VECTOR_2_H
