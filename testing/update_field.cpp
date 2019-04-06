#include "airline_ticket.h"
#include "test_runner.h"
#include <tuple>
#include <ostream>

using namespace std;

bool operator <(const Date & d1, const Date &d2)
{
    return tie(d1.year, d1.month, d1.day) < tie(d2.year, d2.month, d2.day);
}
bool operator ==(const Date & d1, const Date &d2)
{
    return tie(d1.year, d1.month, d1.day) == tie(d2.year, d2.month, d2.day);
}
bool operator !=(const Date & d1, const Date &d2)
{
    return tie(d1.year, d1.month, d1.day) != tie(d2.year, d2.month, d2.day);
}

ostream & operator <<(ostream &os, const Date &d1)
{
    os<<d1.year<<" "<<d1.month<<" "<<d1.day;
    return os;
}

istream & operator >>(istream &is, Date &d1)
{
    char d;
    is >> d1.year >> d >> d1.month >> d >> d1.day;
    return is;
}

bool operator <(const Time & t1, const Time & t2)
{
    return tie(t1.hours, t1.minutes) < tie(t2.hours, t2.minutes);
}
bool operator ==(const Time & t1, const Time & t2)
{
    return tie(t1.hours, t1.minutes) == tie(t2.hours, t2.minutes);
}
bool operator !=(const Time & t1, const Time & t2)
{
    return tie(t1.hours, t1.minutes) != tie(t2.hours, t2.minutes);
}

ostream & operator <<(ostream &os, const Time &t1)
{
    os<<t1.hours<<" "<<t1.minutes;
    return os;
}
istream & operator >>(istream &is, Time &t1)
{
    char d;
    is >> t1.hours >>d>> t1.minutes;
    return is;
}


//void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
//  map<string, string>::const_iterator it;

//  it = updates.find("to");
//  if (it != updates.end()) {
//    ticket.to = it->second;
//  }

//  it = updates.find("from");
//  if (it != updates.end()) {
//    ticket.from = it->second;
//  }

//  it = updates.find("price");
//  if (it != updates.end()) {
//    istringstream is(it->second);
//    is >> ticket.price;
//  }

//  ...
//}

//void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
//  UPDATE_FIELD(ticket, to, updates);
//  UPDATE_FIELD(ticket, from, updates);
//  UPDATE_FIELD(ticket, price, updates);
//  UPDATE_FIELD(ticket, airline, updates);
//  ...
//}

#define UPDATE_FIELD(ticket, field, values) {   \
    auto it = values.find(#field);   \
    if(it!=values.end()) {  \
        istringstream is(it->second);   \
        is >> ticket.field;  \
}   \
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestUpdate);
//}
