#include "test_runner.h"
#include <stdexcept>
#include <vector>

using namespace std;

template<typename T>
class Deque
{
public:
    Deque()= default;
    bool Empty() const {return tail.empty() && head.empty();}
    size_t Size() const {return tail.size() + head.size();}

    void PushBack(T value){tail.push_back(value);}
    void PushFront(T value){head.push_back(value);}
    T& operator [](size_t idx)
    {
        return idx < head.size() ? head[head.size()-1-idx] : tail[idx-head.size()];
    }
    const T& operator [](size_t idx) const
    {
        return idx < head.size() ? head[head.size()-1-idx] : tail[idx-head.size()];
    }
    T& At(size_t idx)
    {
        if(idx >= Size())
            throw out_of_range("out ");
        return operator[](idx);
    }
    const T& At(size_t idx) const
    {
        if(idx >= Size())
            throw out_of_range("out");
        return operator[](idx);
    }
    T& Front() {
        return operator[](0);
    }
    const T& Front() const {
        return operator[](0);
    }
    T& Back() {
        return operator[](Size() - 1);
    }
    const T& Back() const {
        return operator[](Size() - 1);
    }
private:
    vector<T> tail;
    vector<T> head;
};

void TestDeque()
{
    Deque<int> d;
    ASSERT_EQUAL(d.Empty(),true);
    ASSERT_EQUAL(d.Size(),0);
    d.PushBack(1);
    d.PushBack(2);
    d.PushFront(3);
    d.PushBack(4);
    d.PushFront(7);
    ASSERT_EQUAL(d.Size(), 5);
    ASSERT_EQUAL(d[1],3);
    ASSERT_EQUAL(d[2],1);
    ASSERT_EQUAL(d[3],2);
    ASSERT_EQUAL(d[4],4);
    ASSERT_EQUAL(d.At(0),7);
    ASSERT_EQUAL(d.At(2),1);
    d.PushFront(5);
    ASSERT_EQUAL(d.Front(),5);
    ASSERT_EQUAL(d.Back(),4);
    d.PushBack(11);
    ASSERT_EQUAL(d.Back(),11);
}

//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestDeque);
//  return 0;
//}
