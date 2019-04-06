#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <list>
#include <deque>

using namespace std;

//0.19 time
//template<typename RandomIt>
//void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
//    vector<typename RandomIt::value_type> pool;
//    move(first, last, std::back_inserter(pool));
//    vector<bool> killed(distance(first,last),false);
//    size_t cur_pos = 0;

//    int count = 0;
//    for (auto it = first; it != last; it++) {
//        *first++ = move(pool[cur_pos]);
//        killed[cur_pos] = true;
//        if (++count == killed.size()) {
//            break;
//        }
//        for(int i = 0; i < step_size; ){
//            cur_pos++;
//            if (cur_pos == pool.size()) {
//                cur_pos = 0;
//            }
//            if (!killed[cur_pos]) {
//                i++;
//            }
//        }
//    }
//}

//0.10 time
// Вспомогательная функция, позволяющая «зациклить» список
//template <typename Container, typename ForwardIt>
//ForwardIt LoopIterator(Container& container, ForwardIt pos) {
//  return pos == container.end() ? container.begin() : pos;
//}

//template <typename RandomIt>
//void MakeJosephusPermutation(RandomIt first, RandomIt last,
//                             uint32_t step_size) {
//  list<typename RandomIt::value_type> pool;
//  for (auto it = first; it != last; ++it) {
//    pool.push_back(move(*it));
//  }
//  auto cur_pos = pool.begin();
//  while (!pool.empty()) {
//    *(first++) = move(*cur_pos);
//    if (pool.size() == 1) {
//      break;
//    }
//    const auto next_pos = LoopIterator(pool, next(cur_pos));
//    pool.erase(cur_pos);
//    cur_pos = next_pos;
//    for (uint32_t step_index = 1; step_index < step_size; ++step_index) {
//      cur_pos = LoopIterator(pool, next(cur_pos));
//    }
//  }
//}

//0.06 - time
//хитровыдуманный алгоритм
template<typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size)
{
    const uint32_t range_size = last-first;
    if(range_size <= 2){return ;}
    vector<uint32_t> next_alive_positions(range_size);
    iota(begin(next_alive_positions), end(next_alive_positions), 1);
    next_alive_positions.back() = 0;

    vector<typename RandomIt::value_type> permutation;
    uint32_t current_position = 0;
    uint32_t prev_alive_position = range_size - 1;
    for(uint32_t step_index = 0; step_index < range_size; ++step_index)
    {
        for(auto a : next_alive_positions) cout<<a<<" ";
        cout<<endl;
        cout<<" copy "<<*(first + current_position)<<endl;
        permutation.push_back(move(*(first + current_position)));
        next_alive_positions[prev_alive_position] = next_alive_positions[current_position];
        for(uint32_t i=0; i<step_size; ++i){
            if(i>0){
                prev_alive_position = current_position;
            }
            current_position = next_alive_positions[current_position];
        }
    }
    for(uint32_t i=0; i<range_size; ++i, ++first){
        *first = move(permutation[i]);
    }
    //Цикл перемещения по одному можно заменить командой move
    //move(begin(permutation), end(permutation), first);
}

vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}

//void TestIntVector() {
//  const vector<int> numbers = MakeTestVector();
//  {
//    vector<int> numbers_copy = numbers;
//    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
//    ASSERT_EQUAL(numbers_copy, numbers);
//  }
//  {
//    vector<int> numbers_copy = numbers;
//    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
//    ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
//  }
//}



struct NoncopyableInt {
  int value;

  NoncopyableInt(const NoncopyableInt&) = delete;
  NoncopyableInt& operator=(const NoncopyableInt&) = delete;

  NoncopyableInt(NoncopyableInt&&) = default;
  NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
  return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
  return os << v.value;
}

void TestAvoidsCopying() {
  vector<NoncopyableInt> numbers;
  numbers.push_back({1});
  numbers.push_back({2});
  numbers.push_back({3});
  numbers.push_back({4});
  numbers.push_back({5});

  MakeJosephusPermutation(begin(numbers), end(numbers), 2);

  vector<NoncopyableInt> expected;
  expected.push_back({1});
  expected.push_back({3});
  expected.push_back({5});
  expected.push_back({4});
  expected.push_back({2});

  ASSERT_EQUAL(numbers, expected);
}

//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestIntVector);
//  RUN_TEST(tr, TestAvoidsCopying);
//  return 0;
//}
