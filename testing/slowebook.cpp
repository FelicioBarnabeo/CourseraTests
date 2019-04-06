/*#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
//#include "test_runner.h"


using namespace std;

Q — количество запросов
U — максимальный номер пользователя
P — максимальное значение номера страницы

//Медленный метод
//class ReadingManager {
//public:
//  ReadingManager()
//      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),    //O(U)
//        sorted_users_(),
//        user_positions_(MAX_USER_COUNT_ + 1, -1) {}

//  void Read(int user_id, int page_count) {            //O(Q^2)
//    if (user_page_counts_[user_id] == 0) {
//      AddUser(user_id);
//    }
//    user_page_counts_[user_id] = page_count;
//    int& position = user_positions_[user_id];
//    while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
//      SwapUsers(position, position - 1);
//    }
//  }

//  double Cheer(int user_id) const {           O(Q^2) worst case
//    if (user_page_counts_[user_id] == 0) {
//      return 0;
//    }
//    const int user_count = GetUserCount();
//    if (user_count == 1) {
//      return 1;
//    }
//    const int page_count = user_page_counts_[user_id];
//    int position = user_positions_[user_id];
//    while (position < user_count &&
//      user_page_counts_[sorted_users_[position]] == page_count) {
//      ++position;
//    }
//    if (position == user_count) {
//        return 0;
//    }
//    // По умолчанию деление целочисленное, поэтому
//    // нужно привести числитель к типу double.
//    // Простой способ сделать это — умножить его на 1.0.
//    return (user_count - position) * 1.0 / (user_count - 1);
//  }

//private:
//  // Статическое поле не принадлежит какому-то конкретному
//  // объекту класса. По сути это глобальная переменная,
//  // в данном случае константная.
//  // Будь она публичной, к ней можно было бы обратиться снаружи
//  // следующим образомReadingManager::MAX_USER_COUNT.
//  static const int MAX_USER_COUNT_ = 100'000;

//  vector<int> user_page_counts_;
//  vector<int> sorted_users_; // отсортированы по убыванию количества страниц
//  vector<int> user_positions_; // позиции в векторе sorted_users_

//  int GetUserCount() const {
//    return sorted_users_.size();
//  }
//  void AddUser(int user_id) {
//    sorted_users_.push_back(user_id);
//    user_positions_[user_id] = sorted_users_.size() - 1;
//  }
//  void SwapUsers(int lhs_position, int rhs_position) {
//    const int lhs_id = sorted_users_[lhs_position];
//    const int rhs_id = sorted_users_[rhs_position];
//    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
//    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
//  }
//};

//Мое решение
class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        page_user_counts_(MAX_PAGE_COUNT_ + 1, 0) {}

    void Read(int user_id, int page_count)
    {
        int current_page = user_page_counts_[user_id];
        if(current_page == 0) user_counts++;
        else  page_user_counts_[current_page]--;
        user_page_counts_[user_id] = page_count;
        page_user_counts_[page_count]++;
    }

    double Cheer(int user_id) const {
        if (user_page_counts_[user_id] == 0) {
            return 0;
        }
        if (user_counts == 1) {
            return 1;
        }
        int page = user_page_counts_[user_id];
        int usersLessReadCount = 0;
        for(int i=0; i<page; i++)
        {
            usersLessReadCount+=page_user_counts_[i];
        }
        // По умолчанию деление целочисленное, поэтому
        // нужно привести числитель к типу double.
        // Простой способ сделать это — умножить его на 1.0.
        return (usersLessReadCount) * 1.0 / (user_counts - 1);
    }

private:
    // Статическое поле не принадлежит какому-то конкретному
    // объекту класса. По сути это глобальная переменная,
    // в данном случае константная.
    // Будь она публичной, к ней можно было бы обратиться снаружи
    // следующим образомReadingManager::MAX_USER_COUNT.
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1000;

    vector<int> user_page_counts_;
    vector<int> page_user_counts_;
    int user_counts = 0;
};


//void ProcessInput(istringstream &is, ostringstream &os)
//{
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    ReadingManager manager;
//    int query_count;
//    is >> query_count;

//    for (int query_id = 0; query_id < query_count; ++query_id)
//    {
//        string query_type;
//        is >> query_type;
//        int user_id;
//        is >> user_id;

//        if (query_type == "READ") {
//        int page_count;
//        is >> page_count;
//        manager.Read(user_id, page_count);
//        } else if (query_type == "CHEER") {
//        os << setprecision(6) << manager.Cheer(user_id) << "\n";
//        }
//    }
//}

//void TestDefault()
//{
//    istringstream is(
//                    "12\n"
//                    "CHEER 5\n"
//                    "READ 1 10\n"
//                    "CHEER 1\n"
//                    "READ 2 5\n"
//                    "READ 3 7\n"
//                    "CHEER 2\n"
//                    "CHEER 3\n"
//                    "READ 3 10\n"
//                    "CHEER 3\n"
//                    "READ 3 11\n"
//                    "CHEER 3\n"
//                    "CHEER 1\n");
//    ostringstream os;
//    ProcessInput(is,os);
//    ASSERT_EQUAL(os.str(),"0\n"
//                          "1\n"
//                          "0\n"
//                          "0.5\n"
//                          "0.5\n"
//                          "1\n"
//                          "0.5\n");
//}

//int main()
//{
//    TestRunner tr;
//    RUN_TEST(tr,TestDefault);
//    return 0;
//}


//Конструктор ReadingManager работает O(U). Конечно, в коде этот вектор имеет константный размер, но при увеличении U вектор тоже пришлось бы увеличить.
//Все запросы Cheer в худшем случае работают O(Q^2): если в некоторый момент все добавленные пользователи имеют одинаковое количество прочитанных страниц,
//обработка Cheer для самого левого из них потребует линейного прохода.
//Все запросы Read работают не больше O(Q^2).
//Итого получаем U + Q^2.
*/


#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class ReadingManager {
public:
  ReadingManager()                                                         //O(U+P)
        // -1 значит, что не случилось ни одного READ
      : user_page_counts_(MAX_USER_COUNT_ + 1, -1),
        page_achieved_by_count_(MAX_PAGE_COUNT_ + 1, 0) {}

  void Read(int user_id, int page_count) {                              //O(UP+Q)
    UpdatePageRange(user_page_counts_[user_id] + 1, page_count + 1);
    user_page_counts_[user_id] = page_count;
  }

  double Cheer(int user_id) const {                                     //O(1)
    const int pages_count = user_page_counts_[user_id];
    if (pages_count == -1) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    return (user_count - page_achieved_by_count_[pages_count]) * 1.0
           / (user_count - 1);
  }

private:
  // Статическое поле не принадлежит какому-либо конкретному объекту класса.
  // По сути это глобальная переменная, в данном случае - константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1'000;

  // Номер страницы, до которой дочитал пользователь <ключ>
  vector<int> user_page_counts_;
  // Количество пользователей, дочитавших (как минимум) до страницы <индекс>
  vector<int> page_achieved_by_count_;

  int GetUserCount() const {
    return page_achieved_by_count_[0];
  }

  // lhs включительно, rhs не включительно
  void UpdatePageRange(int lhs, int rhs) {          //O(UP)
    for (int i = lhs; i < rhs; ++i) {
      ++page_achieved_by_count_[i];
    }
  }
};

//Конструктор работает за U + P.
//Суммарно все методы Read работают за UP + Q: сами вызовы требуют O(Q), а суммарное время работы UpdatePageRange не превосходит UP.
//Можно даже упростить до UP, поскольку по условию в методах Read номера страниц в рамках одного пользователя возрастают.
//Каждый вызов Cheer работает O(1).
//Итого, получаем сложность O(UP + Q). При этом нельзя сказать, что это эквивалентно O(UP), поскольку вызовов Cheer может быть существенное количество.

//int main() {
//  // Для ускорения чтения данных отключается синхронизация
//  // cin и cout с stdio,
//  // а также выполняется отвязка cin от cout
//  ios::sync_with_stdio(false);
//  cin.tie(nullptr);

//  ReadingManager manager;

//  int query_count;
//  cin >> query_count;

//  for (int query_id = 0; query_id < query_count; ++query_id) {
//    string query_type;
//    cin >> query_type;
//    int user_id;
//    cin >> user_id;

//    if (query_type == "READ") {
//      int page_count;
//      cin >> page_count;
//      manager.Read(user_id, page_count);
//    } else if (query_type == "CHEER") {
//      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
//    }
//  }

//  return 0;
//}
