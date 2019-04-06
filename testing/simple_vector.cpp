#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//void TestConstruction() {
//  SimpleVector<int> empty;
//  ASSERT_EQUAL(empty.Size(), 0u);
//  ASSERT_EQUAL(empty.Capacity(), 0u);
//  ASSERT(empty.begin() == empty.end());

//  SimpleVector<string> five_strings(5);
//  ASSERT_EQUAL(five_strings.Size(), 5u);
//  ASSERT(five_strings.Size() <= five_strings.Capacity());
//  for (auto& item : five_strings) {
//    ASSERT(item.empty());
//  }
//  five_strings[2] = "Hello";
//  ASSERT_EQUAL(five_strings[2], "Hello");
//}

//void TestPushBack() {
//  SimpleVector<int> v;
//  for (int i = 10; i >= 1; --i) {
//    v.PushBack(i);
//    ASSERT(v.Size() <= v.Capacity());
//  }
//  sort(begin(v), end(v));

//  const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//  ASSERT_EQUAL(v.Size(), expected.size());
//  ASSERT(equal(begin(v), end(v), begin(expected)));

//}

//void MyTest()
//{
//    SimpleVector<int> v(0);
//    v.PushBack(0);
//    SimpleVector<int> v1(1);
//    v1.PushBack(1);
//    SimpleVector<int> v2(2);
//    v2.PushBack(2);
//    v.PushBack(v1[1]);
//    v.PushBack(v2[2]);
//    v[2] = v[1]+v[0];
//    const vector<int> exp = {0,1,1};
//    ASSERT_EQUAL(v.Size(),exp.size());
//    ASSERT(equal(begin(v),end(v), begin(exp)));

//    SimpleVector<int> c(3);
//    c[0]=0;c[1]=1;c[2]=2;
//    c.PushBack(3);c.PushBack(4);c.PushBack(5);c.PushBack(6);c.PushBack(7);c.PushBack(8);c.PushBack(9);c.PushBack(10);
//    const vector<int> exp2 = {0,1,2,3,4,5,6,7,8,9,10};
//    ASSERT(equal(begin(c),end(c), begin(exp2)));
//}


//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestConstruction);
//  RUN_TEST(tr, TestPushBack);
//  RUN_TEST(tr, MyTest);
//  return 0;
//}


