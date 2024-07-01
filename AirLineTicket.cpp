#include "UserManager.h"
#include "FlightManager.h"
#include "TicketManager.h"

using namespace std;

int main() {
    
    while (true) {
        cout << "1. Log in" << endl;
        cout << "2. Register" << endl;  
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        string input;
        getline(cin, input);

        int choice;
        try {
            choice = stoi(input);  
        }
        catch (const invalid_argument& ) {
            cerr << "Invalid input. Please enter a number." << endl;
            continue;  
        }
        catch (const out_of_range& ) {
            cerr << "Input out of range. Please enter a valid number." << endl;
            continue;  
        }

        switch (choice) {
        case 1: {
            system("cls");
            UserManager userManager;
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            // User interaction
            if (userManager.login(username, password)) {
                FlightManager flightManager;
                TicketManager ticketManager;
                if (userManager.getLoggedInUser()->getRole() == "customer") 
                {
                    while (true)
                    {
                        cout << "1. Buy ticket" << endl;
                        cout << "2. Show my ticket" << endl;  
                        cout << "3. Logout" << endl;
                        cout << "Enter your choice: ";

                        int userInteraction;
                        cin >> userInteraction;
                            switch (userInteraction) {

                            case 1: 
                                system("cls");
                                flightManager.displayAvailableFlights();
                                ticketManager.addTicket(userManager.getLoggedInUser(), flightManager.getFlights());
                                flightManager.saveFlightsToFile("data/flights.txt");
                                break;
                            case 2:
                                system("cls");
                                ticketManager.displayUserTicket(userManager.getLoggedInUser(), flightManager.getFlights());
                                break;
                            case 3:
                                cout << "Logging out ...\n";
                                break;
                            default:
                                cout << "Invalid choice." << endl;
                                break;
                            }
                     
                            if (userInteraction == 3)
                            {
                               
                                break;
                            }
                            cin.ignore();
                            cout << endl;
                    }
                }
                else
                {
                    while (true)
                    {
                        cout << "1. Add admin" << endl;
                        cout << "2. Show all flight" << endl;
                        cout << "3. Add flight" << endl;
                        cout << "4. Show all ticket" << endl;
                        cout << "5. Logout" << endl;
                        cout << "Enter your choice: ";

                        int userInteraction;
                        cin >> userInteraction;
                        string username, password;
                        switch (userInteraction) {
                        
                        case 1:
                            system("cls");
                            cout << "Enter username: ";
                            cin >> username;
                            cout << "Enter password: ";
                            cin >> password;
                            userManager.registerUser(username, password, "admin");
                            break;
                        case 2:
                            system("cls");
                            flightManager.displayAllFlights();
                            break;
                        case 3:
                            system("cls");
                            flightManager.addFlight();
                            break;
                        case 4:
                            system("cls");
                            ticketManager.displayAllTicket(flightManager.getFlights());
                            break;
                        case 5:
                            system("cls");
                            cout << "Logging out ...\n";
                            break;
                        default:
                            cout << "Invalid choice." << endl;
                            break;
                        }

                        if (userInteraction == 5)
                        {

                            break;
                        }
                        cin.ignore();
                        cout << endl;
                    }
                }
            }

            userManager.logout();
            break;
        }


        case 2: {
            system("cls");
            UserManager userManager;
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            userManager.registerUser(username, password, "customer");
            break;
        }


        case 3:
            system("cls");
            cout << "Exiting the program now\n";
            break;

        default:
            cout << "Invalid choice." << endl;
            break;
        }


        if (choice == 3)
        {
            break;
        }

        cin.ignore();
        cout << endl;
    }
    cout << "You have exited the program" << endl;
    return 0;
}
