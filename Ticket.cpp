#include "Ticket.h"

Ticket::Ticket(const string& ticketId, const string& username, const string& flightId, const string& clientName, const string& seatNumber)
	:ticketId(ticketId), username(username), flightId(flightId), clientName(clientName), seatNumber(seatNumber) {}

string Ticket::getTicketId()
{
	return ticketId;
}


string Ticket::getUsername()
{
	return username;
}

string Ticket::getClientName()
{
	return clientName;
}

string Ticket::getFlightId()
{
	return flightId;
}

string Ticket::getSeatNumber()
{
	return seatNumber;
}
