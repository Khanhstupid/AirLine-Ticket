#pragma once
#include <string>

using namespace std;
class Ticket
{
private:
	string ticketId;
	string username; // account book ticket
	string clientName;
	string flightId;
	string seatNumber;
public:
	Ticket(const string& ticketId, const string& username, const string &flightId, const string& clientName, const string &seatNumber);

	string getTicketId();
	string getUsername();
	string getClientName();
	string getFlightId();
	string getSeatNumber();
};


