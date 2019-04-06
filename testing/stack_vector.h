#ifndef STACK_VECTOR_H
#define STACK_VECTOR_H

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0);

    T& operator[](size_t index) {return m_data[index];}
    const T& operator[](size_t index) const {return m_data[index];}

    T* begin() {return m_data.begin();}
    T* end() {return m_data.begin()+m_size;}
    const T* begin() const {return m_data.cbegin();}
    const T* end() const {return m_data.cbegin()+m_size;}

    size_t Size() const {return m_size;}
    size_t Capacity() const{return N;}

    void PushBack(const T& value);
    T PopBack();

private:
    array<T,N> m_data;
    size_t m_size = 0;
};

template<typename T, size_t N>
StackVector<T,N>::StackVector(size_t a_size) : m_size(a_size)
{
    if(a_size > N){
        throw invalid_argument("Too much");
    }
}

template<typename T, size_t N>
void StackVector<T,N>::PushBack(const T &value)
{
    if(m_size<N){
        m_data[m_size++]=value;
        return;
    }
    throw overflow_error("Full");
}

template<typename T, size_t N>
T StackVector<T,N>::PopBack()
{
    if(m_size){
        return m_data[--m_size];
    }
    throw underflow_error("Empty");
}


#endif // STACK_VECTOR_H
