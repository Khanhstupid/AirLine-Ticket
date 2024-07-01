#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <string>
#include "Ticket.h"
#include "Flight.h"
#include "User.h"
#include <iomanip>
#include <ctime>

using namespace std;

class TicketManager {
private:
    unordered_map<string, Ticket*> tickets;
    unordered_map<string, unordered_set<string>> flightSeats; // Map from flight ID to set of occupied seats

public:
    TicketManager();
    ~TicketManager();

    void loadTicketsFromFile(const string& filename);
    void saveTicketsToFile(const string& filename);

    void addTicket(User *user, unordered_map<string, Flight*>& flights);
    bool removeTicket(const string& ticketId);
    Ticket* getTicket(const string& ticketId) const;
    void displayUserTicket(User* user, unordered_map<string, Flight*>& flights);
    void displayAllTicket(unordered_map<string, Flight*>& flights) const;
    bool checkTime(const string& departTime);
};
