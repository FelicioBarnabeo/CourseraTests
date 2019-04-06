#include <iostream>
#include "test_runner.h"
#include <queue>
#include <map>
#include <cstdint>

using namespace std;

/********************
Разработайте систему бронирования отелей, позволяющую бронировать номера клиентами и контролировать спрос владельцами отелей.
Ваша программа должна обрабатывать следующие события:

BOOK time hotel_name client_id room_count — забронировать клиентом client_id room_count номеров в отеле hotel_name в момент времени time.
Время измеряется в секундах, отсчитываемых от некоторого момента.
CLIENTS hotel_name — вывести количество различных клиентов, бронировавших номера в отеле hotel_name за последние сутки.
Более формально интересующий диапазон времени описывается следующим образом: пусть current_time — время последнего события BOOK,
тогда в данном запросе нужно учесть все события с current_time − 86400 < time ⩽ current_time, где 86400 — количество секунд в сутках.
Обратите внимание, что последнее бронирование должно учитываться, а бронирование, случившееся ровно за сутки до него, учитываться не должно.
ROOMS hotel_name — вывести количество номеров, забронированных за последние сутки в отеле hotel_name.
Формат входных данных
В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^5.
В следующих Q строках в соответствии с описанным выше форматом вводятся запросы. Гарантируется, что:

time — целое число в диапазоне от −10^18 до 10^18 и не убывает от события к событию.
hotel_name — строка из латинских букв и цифр, имеющая длину не более 12 символов.
client_id — натуральное число, не превосходящее 10^9.
room_count — целое положительное число, не превосходящее 1000.
Формат выходных данных
Для каждого запроса CLIENTS и ROOMS выведите единственное целое число — ответ на запрос.
Если указанный в запросе отель пока не имеет ни одного бронирования, выведите 0.

Ограничения
1 секунда на выполнение всех запросов. Все описанные в условии гарантии действительно справедливы для всех тестов,
на которых будет запускаться ваша программа. Проверять корректность тестов не нужно.
*/

//struct BookEntry
//{
//    long time;
//    string hotel;
//    int client_id;
//    int room_count;
//};

//class BookManager
//{
//public:
//    void removeBook(const BookEntry &be)
//    {
//        dayStat & ds = hotelDayStat[be.hotel];
//        if(--ds.clientIdBookCount[be.client_id] == 0)
//            ds.clientIdBookCount.erase(be.client_id);
//        ds.roomCount -= be.room_count;
//    }

//    void inline updateHotelStat(const string &hotel, int client_id, int room_count)
//    {
//        dayStat & ds = hotelDayStat[hotel];
//        ++ds.clientIdBookCount[client_id];
//        ds.roomCount+=room_count;
//    }

//    void book(long time, string hotel_name, int client_id, int room_count)
//    {
//        //cout<<time<<" "<<hotel_name<<" "<<client_id<<" "<<room_count<<endl;
//        bookingHistory.push({time,hotel_name,client_id,room_count});
//        dayStat & ds = hotelDayStat[hotel_name];
//        while(bookingHistory.size() && bookingHistory.front().time + SEC_IN_DAY <= time )
//        {
//            removeBook(bookingHistory.front());
//            bookingHistory.pop();
//        }
//        updateHotelStat(hotel_name, client_id, room_count);
//    }

//    int inline clients(const string &hotel_name)
//    {
//        return hotelDayStat[hotel_name].clientIdBookCount.size();
//    }
//    int inline rooms(const string &hotel_name)
//    {
//        return hotelDayStat[hotel_name].roomCount;
//    }
//private:
//    static const int SEC_IN_DAY = 86400;
//    queue<BookEntry> bookingHistory;
//    struct dayStat
//    {
//        map<int,int> clientIdBookCount;
//        int roomCount;
//    };
//    map<string, dayStat> hotelDayStat;
//};

//void ProcessInput(istream &is, ostream &os)
//{
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    BookManager manager;

//    string line; getline(is, line);
//    istringstream istr(line);
//    int query_count;
//    istr >> query_count;
//    for (int query_id = 0; query_id < query_count; ++query_id)
//    {
//        string line;
//        getline(is, line);
//        istringstream istr(line);
//        string query_type, hotel_name;
//        istr >> query_type;

//        if (query_type == "BOOK") {
//            long time;
//            istr >> time;
//            istr>>hotel_name;
//            int client_id;
//            istr>>client_id;
//            int room_count;
//            istr>>room_count;
//            manager.book(time,hotel_name,client_id,room_count);
//        } else if (query_type == "CLIENTS") {
//            istr>>hotel_name;
//            os << manager.clients(hotel_name) << endl;
//        } else if(query_type == "ROOMS") {
//            istr >> hotel_name;
//            os << manager.rooms(hotel_name) << endl;
//        }
//        else
//        {
//            os<<"Unknown command : "<<query_type<<endl;
//        }
//    }
//}

////void redirect(std::istream &is, std::stringstream &os)
////{
////    is >> std::noskipws;
////    std::istream_iterator<char> begin(is);
////    std::istream_iterator<char> end;
////    std::ostream_iterator<char> out(os);
////    std::copy(begin, end, out);
////}

//void TestDefault()
//{
//    istringstream is(
//                "11\n"
//                "CLIENTS Marriott\n"
//                "ROOMS Marriott\n"
//                "BOOK 10 FourSeasons 1 2\n"
//                "BOOK 10 Marriott 1 1\n"
//                "BOOK 86409 FourSeasons 2 1\n"
//                "CLIENTS FourSeasons\n"
//                "ROOMS FourSeasons\n"
//                "CLIENTS Marriott\n"
//                "BOOK 86410 Marriott 2 10\n"
//                "ROOMS FourSeasons\n"
//                "ROOMS Marriott\n");
//    ostringstream os;
//    ProcessInput(is,os);
//    ASSERT_EQUAL(os.str(),"0\n"
//                          "0\n"
//                          "2\n"
//                          "3\n"
//                          "1\n"
//                          "1\n"
//                          "10\n");
//}

//int main()
//{
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    BookManager manager;

//    int query_count;
//    cin >> query_count;
//    for (int query_id = 0; query_id < query_count; ++query_id)
//    {
//        string query_type, hotel_name;
//        cin >> query_type;

//        if (query_type == "BOOK") {
//            long time;
//            cin >> time;
//            cin>>hotel_name;
//            int client_id;
//            cin>>client_id;
//            int room_count;
//            cin>>room_count;
//            manager.book(time,hotel_name,client_id,room_count);
//        } else if (query_type == "CLIENTS") {
//            cin>>hotel_name;
//            cout << manager.clients(hotel_name) << '\n';
//        } else if(query_type == "ROOMS") {
//            cin >> hotel_name;
//            cout << manager.rooms(hotel_name) << '\n';
//        }
//    }
//    //ProcessInput(cin,cout);
////    TestRunner tr;
////    RUN_TEST(tr, TestDefault);
////    cin.get();
////    system("pause");
//    return 0;
//}




class HotelManager {//QLlogQ
public:
  void Book(int64_t time, const string& hotel_name,
            int client_id, int room_count) {
    current_time_ = time;
    hotels_[hotel_name].Book({time, client_id, room_count});    //logQ*L + logC
  }
  int ComputeClientCount(const string& hotel_name) {
    return hotels_[hotel_name].ComputeClientCount(current_time_);   //logQ*L +W*logC
  }
  int ComputeRoomCount(const string& hotel_name) {
    return hotels_[hotel_name].ComputeRoomCount(current_time_); //logQ*L +W*logC
  }

private:
  struct Booking {
    int64_t time;
    int client_id;
    int room_count;
  };

  class HotelInfo {
  public:
    void Book(const Booking& booking) {             //QLogQ
      last_bookings_.push(booking);
      room_count_ += booking.room_count;
      ++client_booking_counts_[booking.client_id];
    }
    int ComputeClientCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return client_booking_counts_.size();
    }
    int ComputeRoomCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return room_count_;
    }
  private:
    static const int TIME_WINDOW_SIZE = 86400;
    queue<Booking> last_bookings_;
    int room_count_ = 0;
    map<int, int> client_booking_counts_;

    void PopBooking() {     //QlogQ
      const Booking& booking = last_bookings_.front();
      room_count_ -= booking.room_count;
      const auto client_stat_it =
          client_booking_counts_.find(booking.client_id);
      if (--client_stat_it->second == 0) {
        client_booking_counts_.erase(client_stat_it);
      }
      last_bookings_.pop();
    }
    void RemoveOldBookings(int64_t current_time) {
      while (
          !last_bookings_.empty()
          && last_bookings_.front().time <= current_time - TIME_WINDOW_SIZE
      ) {
        PopBooking();
      }
    }
  };

  int64_t current_time_ = 0;
  map<string, HotelInfo> hotels_;
};


//int main() {
//  ios::sync_with_stdio(false);
//  cin.tie(nullptr);

//  HotelManager manager;

//  int query_count;
//  cin >> query_count;

//  for (int query_id = 0; query_id < query_count; ++query_id) {
//    string query_type;
//    cin >> query_type;

//    if (query_type == "BOOK") {
//      int64_t time;
//      cin >> time;
//      string hotel_name;
//      cin >> hotel_name;
//      int client_id, room_count;
//      cin >> client_id >> room_count;
//      manager.Book(time, hotel_name, client_id, room_count);
//    } else {
//      string hotel_name;
//      cin >> hotel_name;
//      if (query_type == "CLIENTS") {
//        cout << manager.ComputeClientCount(hotel_name) << "\n";
//      } else if (query_type == "ROOMS") {
//        cout << manager.ComputeRoomCount(hotel_name) << "\n";
//      }
//    }
//  }

//  return 0;
//}

//11
//CLIENTS Marriott
//ROOMS Marriott\n
//BOOK 10 FourSeasons 1 2
//BOOK 10 Marriott 1 1
//BOOK 86409 FourSeasons 2 1
//CLIENTS FourSeasons
//ROOMS FourSeasons
//CLIENTS Marriott
//BOOK 86410 Marriott 2 10
//ROOMS FourSeasons
//ROOMS Marriott
