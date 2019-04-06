#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

//Дан набор строк. Необходимо разбить их на группы, в каждой из которых все строки имеют одинаковый набор символов.
//Слова в каждой группе должны располагаться в том же порядке, что и в исходном наборе. При этом порядок самих групп значения не имеет.
//Строка типа String не обязана состоять из символов типа char
//Сам тип String может быть, например, обычной строкой (string) или вектором символов.

//Про тип Char<String> известно следующее:
//Объекты этого типа можно сравнивать с помощью операторов == и <.
//«Тяжёлыми» могут быть не только сами строки, но и отдельные символы. Поэтому их можно свободно перемещать,
//но скопировать каждый символ в функции можно не более одного раза (без учёта копирования при передаче аргумента strings по значению).
//В противном случае вы получите вердикт «неправильный ответ» с соответствующим комментарием.

//Ограничения
//За 1 секунду функция должна обработать максимум 100000 строк длины не более 100.
//При оценке сложности можете считать, что копирование каждого символа стоит порядка 100 элементарных операций.

template <typename String>
using Group = vector<String>;


template <typename String>
using Char = typename String::value_type;

//Должно быть не более 1 копирования каждого символа

//Мое решение 4.37/8.00 - time
//template <typename String>
//vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
//    map< set<Char<String>>, Group<String> > dict;
//    for(auto &s : strings)
//    {
//        dict[set<Char<String>>(s.begin(),s.end())].push_back(move(s));
//    }
//    vector<Group<String>> groups;
//    for(auto& [key,group] : dict)
//    {
//        groups.push_back(move(group));
//    }
//    return groups;
//}

//решение авторов 3.31/8.00
template <typename String>
using Key = String;


template <typename String>
Key<String> ComputeStringKey(const String& string) {
  String chars = string;
  sort(begin(chars), end(chars));
  chars.erase(unique(begin(chars), end(chars)), end(chars));
  return chars;
}


template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  map<Key<String>, Group<String>> groups_map;
  for (String& string : strings) {
    groups_map[ComputeStringKey(string)].push_back(move(string));
  }
  vector<Group<String>> groups;
  for (auto& [key, group] : groups_map) {
    groups.push_back(move(group));
  }
  return groups;
}


void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestGroupingABC);
//  RUN_TEST(tr, TestGroupingReal);
//  return 0;
//}
