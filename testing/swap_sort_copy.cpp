#include "test_runner.h"

#include <algorithm>
#include <numeric>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;


//template <typename T> void Swap(T* first, T* second) — обменивает местами значения, на которые указывают указатели first и second
//template <typename T> void SortPointers(vector<T*>& pointers) — сортирует указатели по значениям, на которые они указывают
//template <typename T> void ReversedCopy(T* src, size_t count, T* dst) — копирует в обратном порядке count элементов,
//начиная с адреса в указателе src, в область памяти, начинающуюся по адресу dst. При этом
//1)каждый объект из диапазона [src; src + count) должен быть скопирован не более одного раза;
//2)диапазоны [src; src + count) и [dst; dst + count) могут пересекаться;
//3)элементы в части диапазона [src; src + count), которая не пересекается с [dst; dst + count), должны остаться неизменными.


template <typename T>
void Swap(T* first, T* second)
{
    T temp = *first;
    *first = *second;
    *second = temp;
}

template <typename T>
void SortPointers(vector<T*>& pointers)
{
    T* tmp;
    for(int i=1, j; i<pointers.size(); ++i)
    {
        tmp = pointers[i];
        for(j = i-1; j>=0 && *pointers[j]>*tmp; --j)
            pointers[j+1] = pointers[j];
        pointers[j+1] = tmp;
    }
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination)
{
    //if((destination>=source && destination<=source+count) || (destination+count>=source && destination+count<=source+count))
    if(abs(source-destination) < count)
    {
        T *temp = new T[count]();
        memcpy(temp,source,count*sizeof(T));
        T* first = temp;
        T* last = temp+count;
        T* d_last = destination+count;
        while (first != last) {
            *(--d_last) = *(first++);
        }
    }
    else {
        T* first = source;
        T* last = source+count;
        T* d_last = destination+count;
        while (first != last) {
            *(--d_last) = *(first++);
        }
    }
}

void TestSwap() {
  int a = 1;
  int b = 2;
  Swap(&a, &b);
  ASSERT_EQUAL(a, 2);
  ASSERT_EQUAL(b, 1);

  string h = "world";
  string w = "hello";
  Swap(&h, &w);
  ASSERT_EQUAL(h, "hello");
  ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
  int one = 1;
  int two = 2;
  int three = 3;

  vector<int*> pointers;
  pointers.push_back(&two);
  pointers.push_back(&three);
  pointers.push_back(&one);

  SortPointers(pointers);

  ASSERT_EQUAL(pointers.size(), 3u);
  ASSERT_EQUAL(*pointers[0], 1);
  ASSERT_EQUAL(*pointers[1], 2);
  ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, count, dest);
  const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

  // РћР±Р»Р°СЃС‚Рё РїР°РјСЏС‚Рё РјРѕРіСѓС‚ РїРµСЂРµРєСЂС‹РІР°С‚СЊСЃСЏ
  ReversedCopy(source, count - 1, source + 1);
  const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(source, source + count), expected2);

  delete[] dest;
  delete[] source;
}

//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestSwap);
//  RUN_TEST(tr, TestSortPointers);
//  RUN_TEST(tr, TestReverseCopy);
//  return 0;
//}
