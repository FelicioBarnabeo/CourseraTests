#include "test_runner.h"
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <set>
#include <deque>

using namespace  std;

//Разработайте класс Translator, позволяющий сохранять двуязычные пары слов и затем переводить слова
//с одного языка на другой с использованием уже добавленных пар

//1.Создание с помощью конструктора по умолчанию. В этом случае база переводов пуста.
//2.Добавление двуязычной пары: t.Add(source, target). После такого вызова считается, что слово source
//    на языке 1 соответствует слову target на языке 2. Переданные в метод Add строки могут быть уничтожены раньше объекта t.
//3.Перевод с языка 1 на язык 2: t.TranslateForward(source). Если ранее уже был вызов t.Add(source_copy, target)для
//  некоторой строки target и строки source_copy, равной source (или являющейся ей), нужно вернуть target.
//    Если такого вызова не было, нужно вернуть пустую строку. Если таких вызовов было несколько, нужно вернуть target для последнего из них.
//4Перевод с языка 2 на язык 1: t.TranslateBackward(target). Если ранее уже был вызов t.Add(source, target_copy)для
//  некоторой строки source и строки target_copy, равной target (или являющейся ей), нужно вернуть source.
//    Если такого вызова не было, нужно вернуть пустую строку. Если таких вызовов было несколько, нужно вернуть source для последнего из них.
//Ограничения
//Каждая строка должна храниться в экземпляре класса Translator не более одного раза.
//При нарушении этого ограничения вы получите ошибку «Memory limit exceeded».


//class Translator{
//public:
//    void Add(string_view source, string_view target);
//    string_view TranslateForward(string_view source) const;
//    string_view TranslateBackward(string_view target) const;
//private:
//    static string_view Translate(const map<string_view,string_view> &dict, string_view s);
//    set<string> dictS;
//    set<string> dictT;
//    map<string_view, string_view> forward_dict;
//    map<string_view, string_view> backward_dict;
//};

//void Translator::Add(string_view source, string_view target)
//{
//    auto it = dictS.insert(string(source));
//    auto it2 = dictT.insert(string(target));
//    if(!it.second && !it2.second)
//        return;
//    forward_dict[*it.first] = *it2.first;
//    backward_dict[*it2.first] = *it.first;
//}

//string_view Translator::Translate(const map<string_view,string_view> &dict, string_view s)
//{
//    if(const auto it = dict.find(s); it!=dict.end()){
//        return it->second;
//    }else {
//        return {};
//    }
//}

//string_view Translator::TranslateForward(string_view source) const
//{
//    return Translate(forward_dict, source);
//}

//string_view Translator::TranslateBackward(string_view target) const
//{
//    return Translate(backward_dict, target);
//}


class Translator {
public:
  void Add(string_view source, string_view target) {
    const string_view source_view = GetClonedView(source);
    const string_view target_view = GetClonedView(target);
    forward_dict[source_view] = target_view;
    backward_dict[target_view] = source_view;
  }
  string_view TranslateForward(string_view source) const {
    return Translate(forward_dict, source);
  }
  string_view TranslateBackward(string_view target) const {
    return Translate(backward_dict, target);
  }

private:
  string_view GetClonedView(string_view s) {
    for (const auto* map_ptr : {&forward_dict, &backward_dict}) {
      const auto it = map_ptr->find(s);
      if (it != map_ptr->end()) {
        return it->first;
      }
    }
    return data.emplace_back(s);
  }

  static string_view Translate(const map<string_view, string_view>& dict, string_view s) {
    if (const auto it = dict.find(s); it != dict.end()) {
      return it->second;
    } else {
      return {};
    }
  }

  map<string_view, string_view> forward_dict;
  map<string_view, string_view> backward_dict;
  deque<string> data;
};


void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));
  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
  translator.Add(string("stol"), string("MYtable"));
  ASSERT_EQUAL(translator.TranslateBackward("MYtable"), "stol");
  ASSERT_EQUAL(translator.TranslateForward("stol"), "MYtable");
  translator.Add(string("stol2"), string("MYtable"));
  ASSERT_EQUAL(translator.TranslateBackward("MYtable"), "stol2");
  ASSERT_EQUAL(translator.TranslateForward("stol2"), "MYtable");
  translator.Add(string("okno"), string("DOOR"));
  ASSERT_EQUAL(translator.TranslateBackward("window"), "okno");
  ASSERT_EQUAL(translator.TranslateBackward("DOOR"), "okno");
}

//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestSimple);
//  return 0;
//}

