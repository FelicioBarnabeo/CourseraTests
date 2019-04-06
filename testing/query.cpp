#include "query.h"

using std::cout;
using std::cin;
using std::endl;

std::istream &operator >>(std::istream &is, Query &q) {
    string type;
    is >> type;
    if(type == "NEW_BUS") q.type = QueryType::NewBus;
    else if(type == "BUSES_FOR_STOP") q.type=QueryType::BusesForStop;
    else if(type == "STOPS_FOR_BUS") q.type=QueryType::StopsForBus;
    else if(type == "ALL_BUSES") q.type=QueryType::AllBuses;
    else{
        cout<<"WRONG_COMMAND"<<endl;
        return is;
    }
    switch (q.type)
    {
    case QueryType::NewBus :
        is>>q.bus;
        int stop_count;
        is>>stop_count;
        q.stops.resize(stop_count);
        for(auto & s : q.stops)
            cin>>s;
        break;
    case QueryType::BusesForStop :
        is>>q.stop;
        break;
    case QueryType::StopsForBus :
        is>>q.bus;
        break;
    case QueryType::AllBuses :
        break;
    default:
        break;
    }
    return is;
}
