#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <ctime>
#include "Flight.h"

class FlightManager
{
private:
	unordered_map <string, Flight*> flights;
public:
	FlightManager();
	~FlightManager();
    void loadFlightsFromFile(const string& filename);
    void saveFlightsToFile(const string& filename);

    void addFlight();
    bool removeFlight(const string& flightId);
    Flight* getFlight(const string& flightId) const;
    void displayAvailableFlights() const;
    void displayAllFlights() const;
    unordered_map<string, Flight*>& getFlights();
    bool checkTime(const string& departTime) const;
};

