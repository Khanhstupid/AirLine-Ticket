#pragma once

#include <iostream>
#include <string>

using namespace std;


class Flight
{
private:
	string flightId;
	string aircraft;
	string department;
	string destination;
	string departtime;
	string arrivetime;
	int totalSeats;
	int availableSeats;
public:
	Flight(const string& flightId, const string& aircraft, const string& department, const string& destination, const string& departtime, const string& arrivetime, const int& totalSeats, const int& availableSeats);

	string getFlightId() const;
	string getAircraft() const;
	string getDepartment() const;
	string getDestination() const;
	string getDeparttime() const;
	string getArrivetime() const;
	int getTotalSeats() const;
	int getAvailableSeats() const;
	void setAvailableSeats(int &newAvailableSeats);
};

