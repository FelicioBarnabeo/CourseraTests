#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

//slow

//class RouteManager {
//public:
//  void AddRoute(int start, int finish) {
//    reachable_lists_[start].push_back(finish);    //o(1)
//    reachable_lists_[finish].push_back(start);    //o(1)
//  }
//  int FindNearestFinish(int start, int finish) const {
//    int result = abs(start - finish);
//    if (reachable_lists_.count(start) < 1) {      //o(n)+log(n)
//        cout<<"Count >=1 "<<start<<endl;
//        return result;
//    }
//    const vector<int>& reachable_stations = reachable_lists_.at(start);   //o(log(n))
//    if (!reachable_stations.empty()) {
//      result = min(
//          result,
//          abs(finish - *min_element(
//              begin(reachable_stations), end(reachable_stations),
//              [finish](int lhs, int rhs) { return abs(lhs - finish) < abs(rhs - finish); }    //o(n)
//          ))
//      );
//    }
//    return result;
//  }
//private:
//  map<int, vector<int>> reachable_lists_;
//};

//set<int>::const_iterator FindNearestElement(const set<int>& numbers,int border)
//{
//    auto first_not_less = numbers.lower_bound(border);  //o(log(n))
//    if(first_not_less == numbers.begin())
//        return first_not_less;
//    const auto last_less = prev(first_not_less);
//    if(first_not_less == numbers.end())
//        return last_less;
//    const bool isLeft = abs(border - *last_less) < abs(border - *first_not_less);
//    return isLeft ? last_less : first_not_less;
//}

class RouteManager {
public:
    void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
    }
    int FindNearestFinish(int start, int finish) const
    {
        int result = abs(start - finish);
        if (reachable_lists_.count(start) < 1) {
            return result;
        }
        const set<int>& reachable_stations = reachable_lists_.at(start);
        const auto finish_pos = reachable_stations.lower_bound(finish);
        if(finish_pos != end(reachable_stations)) {
            result = min(result, abs(finish - *finish_pos));
        }
        if(finish_pos != begin(reachable_stations)) {
            result = min(result, abs(finish - *prev(finish_pos)));
        }
        return result;
    }
private:
    map<int, set<int>> reachable_lists_;
};

//int main() {
//  RouteManager routes;

//  int query_count;
//  cin >> query_count;

//  for (int query_id = 0; query_id < query_count; ++query_id) {
//    string query_type;
//    cin >> query_type;
//    int start, finish;
//    cin >> start >> finish;
//    if (query_type == "ADD") {
//      routes.AddRoute(start, finish);
//    } else if (query_type == "GO") {
//      cout << routes.FindNearestFinish(start, finish) << "\n";
//    }
//  }

//  return 0;
//}


//7
//ADD -2 5
//ADD 10 4
//ADD 5 8
//GO 4 10
//GO 4 -2
//GO 5 1
//GO 5 100

//0
//6
//2
//92
