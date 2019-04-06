#ifndef BUS_MANAGER_H
#define BUS_MANAGER_H

#include <map>
#include <string>
#include "responses.h"
using std::map;
using std::string;

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops);
  BusesForStopResponse GetBusesForStop(const string& stop) const;
  StopsForBusResponse GetStopsForBus(const string& bus) const;
  AllBusesResponse GetAllBuses() const;

private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};

#endif // BUS_MANAGER_H
