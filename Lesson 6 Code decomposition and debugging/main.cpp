#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    // Реализуйте эту функцию
    q.bus = ""s;
    q.stop = ""s;
    q.stops.clear();

    string type_in;
    int stops_count;
    string stop;
    is >> type_in;

    if(type_in == "NEW_BUS"s)
    {
        q.type = QueryType::NewBus;
        is >> q.bus;
        is >> stops_count;

        for(int i = 0; i < stops_count; ++i)
        {
            is >> stop;
            q.stops.push_back(stop);
        }
    }
    else if(type_in == "BUSES_FOR_STOP"s)
    {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if(type_in == "STOPS_FOR_BUS"s)
    {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if(type_in == "ALL_BUSES")
    {
        q.type = QueryType::AllBuses;
    }

    return is;
}

struct BusesForStopResponse {
    // Наполните полями эту структуру
    string stop;
    vector<string> buses;
    bool no_stop = false;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    if(r.no_stop)
    {
        os << "No stop"s;
    }
    else
    {
        os << "Stop "s << r.stop << ':';

        for(auto& bus : r.buses)
        {
            os << " "s << bus;
        }

    }
    
    return os;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
    string bus;
    vector<string> stops;
    bool no_bus = false;
    bool no_interchange = false;
    vector<string> other_buses;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    if(r.no_bus)
    {
        os << "No bus"s;
    }
    else
    {
        int i = r.stops.size();
        for(auto& stop : r.stops)
        {
            --i;
            os << "Stop "s << stop << ": "s;
            
            if(r.no_interchange)
            {
                os << " no interchange"s;
            }
            else
            {
                for(auto& other_bus : r.other_buses)
                {
                    os << other_bus << " "s;
                }
            }
            if(i != 0) os << endl;
            
        }
        
    }

    return os;
}

struct AllBusesResponse {
    // Наполните полями эту структуру
    map<string, vector<string>> all_buses;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    if(r.all_buses.empty())
    {
        os << "No buses"s;
    }

    for(const auto& [bus, stops] : r.all_buses)
    {
        os << "Bus " << bus << ':';
        for(const auto& stop : stops)
        {
            os << " " << stop;
        }

        os << endl;
    }

    return os;
}

class BusManager 
{
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод
        for (auto& stop : stops)
        {
            stops_to_buses_[bus].push_back(stop);
            buses_to_stops_[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
        BusesForStopResponse buses_for_stop_response;
        if(buses_to_stops_.count(stop) <= 0)
        {
            buses_for_stop_response.no_stop = true;
        }
        else
        {
            buses_for_stop_response.stop = stop;
            buses_for_stop_response.buses = buses_to_stops_.at(stop);
        }
        return buses_for_stop_response;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
        StopsForBusResponse stops_for_bus_response;

        if(stops_to_buses_.count(bus) <= 0)
        {
            stops_for_bus_response.no_bus = true;
        }
        else
        {
            for(auto& stop : stops_to_buses_.at(bus))
            {
                if(buses_to_stops_.at(stop).size() == 1)
                {
                    stops_for_bus_response.no_interchange = true;
                }
                else
                {
                    stops_for_bus_response.stops = stops_to_buses_.at(bus);

                    for (const string& other_bus : buses_to_stops_.at(stop)) 
                    {
                        if (bus != other_bus) 
                        {
                            stops_for_bus_response.other_buses.push_back(other_bus);
                        }
                    }
                }
            }
            
        }
        return stops_for_bus_response;
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
        AllBusesResponse all_buses_response;
        all_buses_response.all_buses = stops_to_buses_;
        return all_buses_response;
    }

private:
    map<string, vector<string>> buses_to_stops_, stops_to_buses_;

};

// Реализуйте функции и классы, объявленные выше, чтобы эта функция main
// решала задачу "Автобусные остановки"

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) 
        {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }
}