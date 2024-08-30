#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Vaishnav Gupta 


using namespace std;


struct Bus {
    int id;
    int capacity;
    string status; 
};


struct Route {
    int id;
    string start_location;
    string end_location;
    int distance; 
    int demand;   
};


struct Schedule {
    int bus_id;
    int route_id;
    string departure_time;
    string arrival_time;
};


string calculateTravelTime(int distance) {
    int hours = distance / 50;  //speed of 50 km/h
    int minutes = (distance % 50) * 60 / 50;
    return to_string(hours) + "h " + to_string(minutes) + "m";
}


vector<Schedule> assignBusesToRoutes(vector<Bus>& buses, vector<Route>& routes) {
    vector<Schedule> schedules;
    for (auto& route : routes) {
        int min=INT_MAX;
        auto it=buses.end();
        for (auto bus_it = buses.begin(); bus_it != buses.end(); ++bus_it) {
            if (bus_it->capacity >= route.demand && bus_it->status == "Available" && bus_it->capacity - route.demand < min) {
                it = bus_it;
                min = bus_it->capacity - route.demand;
            }
        }
        if (it != buses.end()) {
            // Found
            Schedule schedule;
            schedule.bus_id = it->id;
            schedule.route_id = route.id;
            schedule.departure_time = "08:00 AM"; 
            schedule.arrival_time = calculateTravelTime(route.distance);

            schedules.push_back(schedule);
            
            
            it->status = "In Use";
        } else {
            cout << "No available bus for route " << route.id << endl;
        }
    }
    return schedules;
}


void printSchedule(const vector<Schedule>& schedules) {
    cout << "Bus Schedule:\n";
    for (const auto& schedule : schedules) {
        cout << "Bus ID: " << schedule.bus_id 
             << ", Route ID: " << schedule.route_id 
             << ", Departure: " << schedule.departure_time 
             << ", Arrival: " << schedule.arrival_time << endl;
    }
}

int main() {
    
    vector<Bus> buses = {
        {1, 50, "Available"},
        {2, 40, "Available"},
        {3, 30, "Available"}
    };
    
    vector<Route> routes = {
        {1, "A", "B", 120,5},
        {2, "B", "C", 80, 30},
        {3, "C", "D", 60, 45}
    };

    
    vector<Schedule> schedules = assignBusesToRoutes(buses, routes);

    
    printSchedule(schedules);

    return 0;
}








