#include "FlightManager.h"

FlightManager::FlightManager()
{
    loadFlightsFromFile("data/flights.txt");
}

FlightManager::~FlightManager()
{
	for (auto& flight : flights) {
		delete flight.second;
	}
}

void FlightManager::loadFlightsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string flightId, aircraft, department, destination, totalSeatsStr, availableSeatsStr, departtime, arrivetime;
        int availableSeats, totalSeats;

        if (!getline(iss, flightId, ',') ||
            !getline(iss, aircraft, ',') ||
            !getline(iss, department, ',') ||
            !getline(iss, destination, ',') ||
            !getline(iss, departtime, ',') ||
            !getline(iss, arrivetime, ',') ||
            !getline(iss, totalSeatsStr, ',') ||
            !getline(iss, availableSeatsStr)) {
            cerr << "Error reading line: " << line << endl;
            continue; 
        }

        try {
            totalSeats = stoi(totalSeatsStr);
            availableSeats = stoi(availableSeatsStr);
        }
        catch (const invalid_argument& ) {
            cerr << "Invalid number for total or available seats: " << availableSeatsStr << " " << totalSeatsStr << endl;
            continue; 
        }

        flights[flightId] = new Flight(flightId, aircraft, department, destination, departtime, arrivetime, totalSeats, availableSeats);
    }

    file.close();
}


void FlightManager::saveFlightsToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }

    for (const auto& flight : flights) {
        file << flight.second->getFlightId() << ","
            << flight.second->getAircraft() << ","
            << flight.second->getDepartment() << ","
            << flight.second->getDestination() << ","
            << flight.second->getDeparttime() << ","
            << flight.second->getArrivetime() << ","
            << flight.second->getTotalSeats() << ","
            << flight.second->getAvailableSeats() << endl;
    }

    file.close();
}


void FlightManager::addFlight()
{
    string flightId, aircraft, department, destination, arrivetime, departtime;
     int totalSeats;
    tm checkTime = {};
    cin.ignore();

    cout << "Enter flight Id: "; getline(cin, flightId); 
    cout << "Enter aircraft: "; getline(cin, aircraft); 
    cout << "Enter department: "; getline(cin, department); 
    cout << "Enter destination: "; getline(cin, destination); 
    while(true) {

        cout << "Enter departtime follow format \"HH:MM YYYY-MM-DD\": " ; getline(cin, departtime);
        istringstream ss(departtime);
        ss >> get_time(&checkTime, "%H:%M %Y-%m-%d");
        if (ss.fail()) {
            cout << "Error reading date and time\n";
            continue;
        }
        cout << "Enter arrivetime follow format \"HH:MM YYYY-MM-DD\":  "; getline(cin, arrivetime);
        istringstream sss(arrivetime);
        sss >> get_time(&checkTime, "%H:%M %Y-%m-%d");
        if (sss.fail()) {
            cout << "Error reading date and time\n";
            continue;
        }
        break;
    }
    cout << "Enter total seats: "; cin >> totalSeats; 
    
    cin.ignore();

    flights[flightId] = new Flight(flightId, aircraft, department, destination, departtime, arrivetime, totalSeats, totalSeats);

    saveFlightsToFile("data/flights.txt");
}

bool FlightManager::removeFlight(const string& flightId)
{
    auto it = flights.find(flightId);
    if (it == flights.end()) {
        return false; 
    }
    delete it->second;
    flights.erase(it);
    return true;
}

Flight* FlightManager::getFlight(const string& flightId) const
{
    auto it = flights.find(flightId);
    if (it != flights.end()) {
        return it->second;
    }
    return nullptr;
}

void FlightManager::displayAvailableFlights() const
{
    cout << left << setw(10) << "Flight ID"
        << setw(15) << "Aircraft"
        << setw(15) << "Department"
        << setw(15) << "Destination"
        << setw(20) << "Departure Time"
        << setw(20) << "Arrival Time"
        << setw(20) << "Seats (Available/Total)"
        << endl;
    for (const auto& flight : flights) {
        if (checkTime(flight.second->getDeparttime()) && (flight.second->getAvailableSeats() > 0)) {
            cout << left << setw(10) << flight.second->getFlightId()
                << setw(15) << flight.second->getAircraft()
                << setw(15) << flight.second->getDepartment()
                << setw(15) << flight.second->getDestination()
                << setw(20) << flight.second->getDeparttime()
                << setw(20) << flight.second->getArrivetime()
                << setw(20) << to_string(flight.second->getAvailableSeats()) + "/" + to_string(flight.second->getTotalSeats())
                << endl;
        }
    }
}

void FlightManager::displayAllFlights() const
{
    cout << left << setw(10) << "Flight ID"
        << setw(15) << "Aircraft"
        << setw(15) << "Department"
        << setw(15) << "Destination"
        << setw(20) << "Departure Time"
        << setw(20) << "Arrival Time"
        << setw(20) << "Seats (Available/Total)"
        << endl;
    for (const auto& flight : flights) {
        cout << left << setw(10) << flight.second->getFlightId()
            << setw(15) << flight.second->getAircraft()
            << setw(15) << flight.second->getDepartment()
            << setw(15) << flight.second->getDestination()
            << setw(20) << flight.second->getDeparttime()
            << setw(20) << flight.second->getArrivetime()
            << setw(20) << to_string(flight.second->getAvailableSeats()) + "/" + to_string(flight.second->getTotalSeats())
            << endl;
    }
}

unordered_map<string, Flight*>& FlightManager::getFlights()
{
    return flights;
}

bool FlightManager::checkTime(const string& departTime) const
{
    tm departT = {};
    istringstream ss(departTime);
    ss >> get_time(&departT, "%H:%M %Y-%m-%d");

    time_t now = time(nullptr);

    if (difftime(mktime(&departT), now) > 86400)
    {
        return true;
    }
    return false;
}
