#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>

using namespace std;

//Реализуйте шаблонный контейнер PriorityCollection, позволяющий хранить объекты некопируемого типа, а также совершать с ними следующие операции:

//добавить элемент с нулевым приоритетом;
//добавить набор элементов с нулевыми приоритетами;
//увеличить на 1 приоритет заданного элемента;
//извлечь из контейнера элемент с максимальным приоритетом.
//Поскольку добавление элемента заключается в его перемещении в контейнер, метод увеличения приоритета не может принимать сам элемент.
//Поэтому метод, добавляющий элементы, для каждого из них должен вернуть некий идентификатор, который затем можно использовать для вызова других методов.

//Тип идентификатора — PriorityCollection::Id — вы должны выбрать самостоятельно.
//Он должен быть легко копируемым: например, числом, указателем или итератором.
//Примеры определения и использования типа Id вы можете найти в шаблоне решения.

//Гарантии
//Вы можете полагаться на то, что для элементов типа T определены перемещение и сравнение на ==, != и <. Все операции над элементами имеют константную сложность.
//Гарантируется, что все добавляемые элементы различны, однако добавленный и затем извлечённый элемент может быть добавлен вновь.
//Методы Get и Promote всегда вызываются от валидных с точки зрения метода IsValid идентификаторов.
//Методы GetMax и PopMax вызываются только при наличии элементов в контейнере.
//При наличии нескольких элементов с одинаковым максимальным приоритетом необходимо выбирать и извлекать тот, который был добавлен позже остальных.

//Ограничения
//Контейнер должен обрабатывать 10^6 запросов не более чем за 1 секунду.
//Гарантируется, что суммарная длина диапазонов, с которыми вызывается вторая версия метода Add, также не превосходит 10^6.

template <typename T>
class PriorityCollection{
public:
    using Id = int;//;выбрать тип
    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object)
    {
        auto &list = priorities[0];
        list.push_back(move(object));
        id_s[++id] = make_pair(0, prev(list.end()));
        return id;
    }
    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template<typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin)
    {
        for(auto it = range_begin; it!= range_end; it++)
        {
            Id id = Add(*it);
            *ids_begin++ = id;
        }
    }
    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const
    {
        return id_s.count(id);
    }
    // Получить объект по идентификатору
    const T& Get(Id id) const
    {
        auto it = id_s[id];
        return *it->second;
    }
    int GetPriority(Id id) const
    {
        auto it = id_s[id];
        return it->first;
    }
    // Увеличить приоритет объекта на 1
    void Promote(Id id)
    {
        auto &obj = Get(id);
        list<T> &list = priorities[GetPriority(id)+1];
        list.push_back(move(obj));
        //нужно ли удаление из приоритис?
        id_s[id].second = list.back();

        //priorities
    }
    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const
    {
        return prev(priorities.end())->second.back();
    }
    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax()
    {
        int priority = priorities.end()->first;
        auto &list = prev(priorities.end())->second;
        auto p = make_pair(move(list.back()),priority);
        return move(p);
    }
private:
    int id = 0;

    using PriorityObjectAddress = pair<int, typename list<T>::iterator>;
    map<int, list<T>> priorities;
    map<Id, PriorityObjectAddress> id_s;
};

class StringNonCopyable : public string {
public:
  using string::string;  // РџРѕР·РІРѕР»СЏРµС‚ РёСЃРїРѕР»СЊР·РѕРІР°С‚СЊ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂС‹ СЃС‚СЂРѕРєРё
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
