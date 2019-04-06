#ifndef RESPONSES_H
#define RESPONSES_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

using std::string;
using std::vector;
using std::map;
using std::ostream;
using std::pair;

struct BusesForStopResponse {
  vector<string> buses;
};

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stops_for_buses;
};

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

ostream& operator << (ostream& os, const StopsForBusResponse& r);

ostream& operator << (ostream& os, const AllBusesResponse& r);

#endif // RESPONSES_H
