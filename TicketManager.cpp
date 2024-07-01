#include "TicketManager.h"
TicketManager::TicketManager()
{
    loadTicketsFromFile("data/tickets.txt");
}

TicketManager::~TicketManager()
{
    for (auto& ticket : tickets) {
        delete ticket.second;
       }
}

void TicketManager::loadTicketsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string ticketId, username, flightId, clientName, seatNumber;

        if (getline(iss, ticketId, ',') &&
            getline(iss, username, ',') &&
            getline(iss, flightId, ',') &&
            getline(iss, clientName, ',') &&
            getline(iss, seatNumber)) {

            tickets[ticketId] = new Ticket(ticketId, username, flightId, clientName, seatNumber);
            flightSeats[flightId].insert(seatNumber);
        }
        else {
            cerr << "Invalid line format in file: " << filename << endl;
        }
    }

    file.close();
}


void TicketManager::saveTicketsToFile(const string& filename)
{
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }
    for (const auto& ticket : tickets) {
        file << ticket.second->getTicketId() << ","
            << ticket.second->getUsername() << ","
            << ticket.second->getFlightId() << ","
            << ticket.second->getClientName() << ","
            << ticket.second->getSeatNumber() << endl;
    }
}

void TicketManager::addTicket(User *user , unordered_map<string, Flight*>& flights) {
    string flightId, seatNumber, clientName;
    cin.ignore();
    while (true) {
        cout << "Enter flight Id: "; getline(cin, flightId);
        if (flights.find(flightId) != flights.end()) {
            break;
        }
        else {
            cout << "Flight Id does not exist. Please enter a valid flight Id." << endl;
        }
    }
    if (flights[flightId]->getAvailableSeats() == 0) {
        cout << "This flight has no seat available!" << endl;
        return;
    }


    cout << "Enter client name: ";
    getline(cin, clientName);


    while (true) {
        cout << "Enter seat number: ";
        getline(cin, seatNumber);
        if (flightSeats[flightId].find(seatNumber) == flightSeats[flightId].end()) {
            break;
        }
        else {
            cout << "Seat number is already taken. Please enter a different seat number." << endl;
        }
    }


    string ticketId = flightId.substr(0, 3) + seatNumber + user->getUsername().substr(0, 3);

    Ticket* newTicket = new Ticket(ticketId, user->getUsername(), flightId, clientName, seatNumber);
    tickets[ticketId] = newTicket;
    flightSeats[flightId].insert(seatNumber);

    int newAvailableSeats = flights[flightId]->getAvailableSeats() - 1;
    flights[flightId]->setAvailableSeats(newAvailableSeats);

    cin.ignore();
    cout << "Ticket added successfully with ID: " << ticketId << endl;
    saveTicketsToFile("data/tickets.txt");
}


bool TicketManager::removeTicket(const string& ticketId)
{
	return false;
}

Ticket* TicketManager::getTicket(const string& ticketId) const
{
	return nullptr;
}

void TicketManager::displayUserTicket(User* user, unordered_map<string, Flight*>& flights)
{
    string username = user->getUsername();
    cout << left << setw(15) << "Ticket ID"
        << setw(20) << "Passenger Name"
        << setw(10) << "Flight ID"
        << setw(15) << "Aircraft"
        << setw(15) << "Department"
        << setw(15) << "Destination"
        << setw(20) << "Departure Time"
        << setw(20) << "Arrival Time"
        << setw(10) << "Seat Number"
        << endl;
    for (const auto& ticket : tickets) {
        if (ticket.second->getUsername() == username && checkTime(flights[ticket.second->getFlightId()]->getDeparttime())) {
            cout << left << setw(15) << ticket.second->getTicketId()
                << setw(20) << ticket.second->getClientName()
                << setw(10) << ticket.second->getFlightId()
                << setw(15) << flights[ticket.second->getFlightId()]->getAircraft()
                << setw(15) << flights[ticket.second->getFlightId()]->getDepartment()
                << setw(15) << flights[ticket.second->getFlightId()]->getDestination()
                << setw(20) << flights[ticket.second->getFlightId()]->getDeparttime()
                << setw(20) << flights[ticket.second->getFlightId()]->getArrivetime()
                << setw(10) << ticket.second->getSeatNumber()
                << endl;
        }
    }
}

void TicketManager::displayAllTicket(unordered_map<string, Flight*>& flights) const {
    cout << left << setw(15) << "Ticket ID"
        << setw(20) << "Passenger Name"
        << setw(10) << "Flight ID"
        << setw(15) << "Aircraft"
        << setw(15) << "Department"
        << setw(15) << "Destination"
        << setw(20) << "Departure Time"
        << setw(20) << "Arrival Time"
        << setw(10) << "Seat Number"
        << endl;
    for (const auto& ticket : tickets) {
        cout << left << setw(15) << ticket.second->getTicketId()
            << setw(20) << ticket.second->getClientName()
            << setw(10) << ticket.second->getFlightId()
            << setw(15) << flights[ticket.second->getFlightId()]->getAircraft()
            << setw(15) << flights[ticket.second->getFlightId()]->getDepartment()
            << setw(15) << flights[ticket.second->getFlightId()]->getDestination()
            << setw(20) << flights[ticket.second->getFlightId()]->getDeparttime()
            << setw(20) << flights[ticket.second->getFlightId()]->getArrivetime()
            << setw(10) << ticket.second->getSeatNumber()
            << endl;

    }
}

bool TicketManager::checkTime(const string& departTime)
{
    tm departT = {};
    istringstream ss(departTime);
    ss >> get_time(&departT, "%H:%M %Y-%m-%d");

    time_t now = time(nullptr);
    
    if (difftime(mktime(&departT),now) > 0)
    {
        return true;
    }
    return false;
}
