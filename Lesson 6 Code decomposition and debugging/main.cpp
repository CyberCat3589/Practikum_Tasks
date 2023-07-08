#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include  <algorithm>

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
        //os << "Stop "s << r.stop << ':';

        for(auto& bus : r.buses)
        {
            os << bus  << " "s;
        }

    }
    
    return os;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
    vector<pair<string, vector<string>>> stop_for_bus_;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    if( r.stop_for_bus_.empty() )
    {
        os << "No bus";
        return os;
    }
 
    int size = r.stop_for_bus_.size();
    for(const auto &[stop, buses] : r.stop_for_bus_)
    {
        os << "Stop " << stop << ": ";
 
        for(const auto &bus : buses)
        {
            os << bus << " ";   
        }
        --size;
        if( size != 0)
        {
            os << endl;
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

    int i = r.all_buses.size();
    for(const auto& [bus, stops] : r.all_buses)
    {
        --i;
        os << "Bus " << bus << ':';
        for(const auto& stop : stops)
        {
            os << " " << stop;
        }

        if(i != 0) os << endl;
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
            buses_[bus].push_back(stop);
            stops_[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
        BusesForStopResponse buses_for_stop_response;
        if(stops_.count(stop) <= 0)
        {
            buses_for_stop_response.no_stop = true;
        }
        else
        {
            buses_for_stop_response.stop = stop;
            buses_for_stop_response.buses = stops_.at(stop);
        }
        return buses_for_stop_response;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        
        StopsForBusResponse stops_for_bus_response;
        
        if( buses_.count(bus) )
        {
            for( const auto &stop : buses_.at(bus) )
            {
                if( stops_.at(stop).size() == 1)
                {
                    stops_for_bus_response.stop_for_bus_.push_back({stop, {"no interchange"}});
                }
                else
                {
                    auto m_buses_of_stop = stops_.at(stop);
                    vector<string> m_buses;
                    for_each(m_buses_of_stop.begin(), m_buses_of_stop.end(), [&bus, &m_buses, &stop](const string &data) {
                        if( data != bus )
                        {
                            m_buses.push_back(data);
                        }
                    });
                    stops_for_bus_response.stop_for_bus_.push_back({stop, m_buses});
                }
            }
        }
 
        return stops_for_bus_response;
 
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
        AllBusesResponse all_buses_response;
        all_buses_response.all_buses = buses_;
        return all_buses_response;
    }

private:
    map<string, vector<string>> buses_, stops_;

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