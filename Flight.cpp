#include "Flight.h"

Flight::Flight(const string& flightId, const string& aircraft, const string& department, const string& destination, const string& departtime, const string& arrivetime, const int& totalSeats, const int& availableSeats)
	:flightId(flightId), aircraft(aircraft), department(department), destination(destination), departtime(departtime), arrivetime(arrivetime), totalSeats(totalSeats), availableSeats(availableSeats) {}

string Flight::getFlightId() const
{
	return flightId;
}

string Flight::getAircraft() const
{
	return aircraft;
}

string Flight::getDepartment() const
{
	return department;
}

string Flight::getDestination() const
{
	return destination;
}

string Flight::getDeparttime() const
{
	return departtime;
}

string Flight::getArrivetime() const
{
	return arrivetime;
}

int Flight::getTotalSeats() const
{
	return totalSeats;
}

int Flight::getAvailableSeats() const
{
	return availableSeats;
}

void Flight::setAvailableSeats(int &newAvailableSeats) {
	this->availableSeats = newAvailableSeats;
}