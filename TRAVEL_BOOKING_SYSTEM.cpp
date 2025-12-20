#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <limits>
#include <vector>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string.h>
#include <conio.h>
#include<sstream>
#include<ctime>
#include <Windows.h>


using namespace std;

// User database to store username and password
map<string, string> userDatabase;

// hotel

struct Room
{
    string Type;
    int Price;
    int Quantity;
    string Description;
};

struct Hotel
{
    string Name;
    string Address;
    long long int Mob;
    int FP; // Food Price
    vector<Room> rooms;
};


struct User
{
    int UserID = 1000;
    std::string Name;
    long long int Adhar;
    long long int Mob;
    char Food_option;
    std::string Bed_option;
    int Days;
    std::string Date;
    double Totalprice;
};

vector<Room> rooms;
vector<Hotel> hotels;

void SaveHotelDetails(const Hotel &hotel);
void LoadHotels();
void AddHotel();
void DeleteHotel();
void ViewHotelDetails(const Hotel &hotel);
void HotelDashboard();
void UserDashboard();
int InitializeUserID();
void SaveUserID(int userID);
void Booking();
void DisplayAdditionalRoomDetails();
void SortRooms();
void FilterRoomsByType();
void DisplayAllUsers();
void ApproveRoom();
void CheckBooking();
void CancleBooking();
void SearchUser();
void CheckCancelList();
void AvailableRooms();
void ProvideFeedback();
void InitializeUserIDFile();
void UpdateUserDetails(int userID);

struct Price
{
    double DisplayPrice(const string &roomType, char foodOption, int days, int foodPrice)
    {
        double price = 0;

        // Find the room price based on room type
        for (const Hotel &hotel : hotels)
        {
            for (const Room &room : hotel.rooms)
            {
                if (room.Type == roomType)
                {
                    price += room.Price;
                    break;
                }
            }
        }

        // Calculate total price for the number of days
        price *= days;

        // Add food service price if applicable
        if (foodOption == 'y' || foodOption == 'Y')
        {
            price += foodPrice * days;
        }

        return price;
    }
};

// Function to register a new user
void registerUser () {
    string username, password;
    cout << "\n--- Register ---" << endl;
    cout << "Enter username: ";
    cin >> username;
    if (userDatabase.find(username) != userDatabase.end()) {
        cout << "Username already exists. Try logging in.\n";
        return;
    }
    cout << "Enter password: ";

    // Read password without echoing
    char ch;
    while ((ch = getch()) != '\r') { // '\r' is the Enter key
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Move back, print space, move back again
            }
        } else {
            password.push_back(ch);
            cout << '*'; // Print asterisk for each character
        }
    }
    cout << endl;

    userDatabase[username] = password;
    cout << "Registration successful!\n";
}

// Function to log in
bool loginUser () {
    string username, password;
    cout << "\n--- Login ---" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";

    // Read password without echoing
    char ch;
    while ((ch = getch()) != '\r') { // '\r' is the Enter key
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Move back, print space, move back again
            }
        } else {
            password.push_back(ch);
            cout << '*'; // Print asterisk for each character
        }
    }
    cout << endl;

    if (userDatabase.find(username) != userDatabase.end() && userDatabase[username] == password) {
        cout << "Login successful!\n";
        return true;
    }
    cout << "Invalid username or password.\n";
    return false;
}
// BUS RESERVATION
void busReservation()
{
    cout << "\n--- Bus Reservation ---\n";

    // Class Definitions
    class Route
    {
    public:
        Route(const string &name, const string &source, const string &destination, double distance)
            : name(name), source(source), destination(destination), distance(distance) {}

        string getName() const { return name; }
        string getSource() const { return source; }
        string getDestination() const { return destination; }
        double getDistance() const { return distance; }

    private:
        string name;
        string source;
        string destination;
        double distance;
    };

    class Bus
    {
    public:
        Bus(const string &busNumber, const Route &route, int totalSeats)
            : busNumber(busNumber), route(route), totalSeats(totalSeats)
        {
            seats.resize(totalSeats, false);
        }

        bool reserveSeat(int seatNumber)
        {
            if (seatNumber >= 1 && seatNumber <= totalSeats && !seats[seatNumber - 1])
            {
                seats[seatNumber - 1] = true;
                return true;
            }
            return false;
        }

        bool cancelSeat(int seatNumber)
        {
            if (seatNumber >= 1 && seatNumber <= totalSeats && seats[seatNumber - 1])
            {
                seats[seatNumber - 1] = false;
                return true;
            }
            return false;
        }

        void displayBusInfo() const
        {
            cout << "\nBus Number: " << busNumber << endl;
            cout << "Route: " << route.getName() << " (" << route.getSource() << " to " << route.getDestination() << ")\n";
            cout << "Distance: " << route.getDistance() << " km" << endl;
            cout << "Total Seats: " << totalSeats << "\nAvailable Seats:\n";
            for (int i = 0; i < totalSeats; ++i)
            {
                cout << "Seat " << i + 1 << ": " << (seats[i] ? "Booked" : "Available") << "\n";
            }
        }

        int getTotalSeats() const { return totalSeats; }
        string getBusNumber() const { return busNumber; }
        const Route &getRoute() const { return route; }
        bool isSeatReserved(int seatNumber) const { return seats[seatNumber - 1]; }

    private:
        string busNumber;
        Route route;
        int totalSeats;
        vector<bool> seats;
    };

    class Ticket
    {
    public:
        Ticket(const string &passengerName, int seatNumber, const Bus &bus)
            : passengerName(passengerName), seatNumber(seatNumber), bus(bus) {}

        string getPassengerName() const { return passengerName; }
        int getSeatNumber() const { return seatNumber; }
        const Bus &getBus() const { return bus; }

    private:
        string passengerName;
        int seatNumber;
        Bus bus;
    };

    class BusReservationSystem
    {
    public:
        BusReservationSystem()
        {
            // Sample routes
            routes.push_back(Route("R001", "Belgavi", "Panji", 112.5));
            routes.push_back(Route("R002", "Bengaluru", "Kerala", 553.2));
            routes.push_back(Route("R003", "Belgavi", "Mumbai", 484.3));
            routes.push_back(Route("R004", "Hubali", "Hampi", 165.9));
            routes.push_back(Route("R005", "Belgavi", "Bagalkote", 474.6));
            routes.push_back(Route("R006", "Bengaluru", "Ramdurg", 553.2));
            routes.push_back(Route("R007", "Belgavi", "Hyderbad", 617.5));
            routes.push_back(Route("R008", "Hubali", "Mangaluru", 361.8));

            // Sample buses
            buses.push_back(Bus("B001", routes[0], 20));
            buses.push_back(Bus("B002", routes[1], 15));
            buses.push_back(Bus("B003", routes[2], 18));
            buses.push_back(Bus("B004", routes[3], 14));
            buses.push_back(Bus("B005", routes[4], 20));
            buses.push_back(Bus("B006", routes[5], 15));
            buses.push_back(Bus("B007", routes[6], 18));
            buses.push_back(Bus("B008", routes[7], 20));
        }

        void displayRoutes() const
        {
            cout << "\nAvailable Routes:\n";
            for (const auto &route : routes)
            {
                cout << "Route Name: " << route.getName() << " (" << route.getSource() << " to " << route.getDestination() << ")\n";
                cout << "Distance: " << route.getDistance() << " km\n";
            }
        }

        void displayBuses() const
        {
            cout << "\nAvailable Buses:\n";
            for (const auto &bus : buses)
            {
                bus.displayBusInfo();
            }
        }

        void bookTicket()
        {
            displayRoutes();
            cout << "\nEnter Route Name: ";
            string routeName;
            cin >> routeName;

            auto routeIt = find_if(routes.begin(), routes.end(), [&](const Route &r)
                                   { return r.getName() == routeName; });

            if (routeIt == routes.end())
            {
                cout << "Invalid Route Name!\n";
                return;
            }

            displayBuses();
            cout << "\nEnter Bus Number: ";
            string busNumber;
            cin >> busNumber;

            auto busIt = find_if(buses.begin(), buses.end(), [&](const Bus &b)
                                 { return b.getBusNumber() == busNumber && b.getRoute().getName() == routeName; });

            if (busIt == buses.end())
            {
                cout << "Invalid Bus Number!\n";
                return;
            }

            cout << "\nEnter Seat Number to Book: ";
            int seatNumber;
            cin >> seatNumber;

            // Attempt to reserve the seat
            if (busIt->reserveSeat(seatNumber))
            {
                cout << "\nSeat " << seatNumber << " booked successfully on Bus " << busNumber << ".\n";
            }
            else
            {
                cout << "\nSeat " << seatNumber << " is either invalid or already reserved!\n";
            }
        }

        void cancelTicket()
        {
            displayBuses();
            cout << "\nEnter Bus Number: ";
            string busNumber;
            cin >> busNumber;

            auto busIt = find_if(buses.begin(), buses.end(), [&](const Bus &b)
                                 { return b.getBusNumber() == busNumber; });

            if (busIt == buses.end())
            {
                cout << "Invalid Bus Number!\n";
                return;
            }

            cout << "\nEnter Seat Number to Cancel: ";
            int seatNumber;
            cin >> seatNumber;

            if (busIt->cancelSeat(seatNumber))
            {
                cout << "Seat Cancellation Successful!\n";
            }
            else
            {
                cout << "Seat was not reserved or invalid!\n";
            }
        }

        void run()
        {
            while (true)
            {
                cout << "\n--- Bus Reservation System ---\n";
                cout << "1. Display Routes\n2. Display Buses\n3. Book Ticket\n4. Cancel Ticket\n5. Exit\n";
                cout << "Enter your choice: ";
                int choice;
                cin >> choice;

                switch (choice)
                {
                case 1:
                    displayRoutes();
                    break;
                case 2:
                    displayBuses();
                    break;
                case 3:
                    bookTicket();
                    break;
                case 4:
                    cancelTicket();
                    break;
                case 5:
                    cout << "Exiting...\n";
                    return;
                default:
                    cout << "Invalid choice!\n";
                }
            }
        }

    private:
        vector<Route> routes;
        vector<Bus> buses;
    };

    BusReservationSystem system;
    system.run();
}

// Train Reservation


    struct node {
	int ticketID;
	string Name, Age, NIC, Contact, BookedClass, BookedTName, BookedTID, BookedDest, BookedSource, BookedDate, DeptTime, ArrTime, BookedSeatNum;
	float PRICE;
	node* next;
};

struct trains
{
	string TName, TID, TDest, TSource, TDate, arriveTime, departTime, TClasses;
	int TSeats;
};

struct SeatRecord {
	string RowA;
	string RowB;
	string RowC;
};

node* head = NULL;
node* tail = NULL;

void admin();
int main();

string Name, Age, NIC, Contact, Dest, Source, SeatNum, Class, TID, Date, ATime, DTime, TName;
bool trainCheck = false;
float PRICE;
string BookedID;
int currentID;
trains availTrains[10];
int noOfTrains = 5;

void Payment()
{
	string cc, cvv, dob, payChoice;
	string accNum, accHolderFName, accHolderLName;
	cout << endl << endl;
	cout << "\n\n\t\t\t\t\t===============PAYMENT DETIALS===============" << endl;
	cout << "\t\t\t\t\tChoose Payment Method. \n";
	cout << "\t\t\t\t\t1. JazzCash. \n";
	cout << "\t\t\t\t\t2. EasyPaisa. \n";
	cout << "\t\t\t\t\t3. Credit/Debit Card. \n";
	cout << "\n\n\t\t\t\t\tEnter Choice (1-3): ";
	cin >> payChoice;
	if (payChoice == "1")
	{
	phoneCheck:
		cout << "\n\n\t\t\t\t\tEnter JazzCash Mobile Account Number: ";
		cin >> accNum;
		if (accNum.length() != 11 || accNum.length() > 11)
		{
			cout << endl;
			cout << "\n\n\t\t\t\t\tEnter a Valid 11 Digit Mobile Phone Number!" << endl << endl;
			goto phoneCheck;
		}
		cout << "\t\t\t\t\tEnter Account Holder's First Name: ";
		cin >> accHolderFName;
		cout << "\t\t\t\t\tEnter Account Holder's Last Name: ";
		cin >> accHolderLName;
	}
	else if (payChoice == "2")
	{
		cout << "\n\n\t\t\t\t\tEnter EasyPaisa Mobile Account Number: ";
		cin >> accNum;
		cout << "\n\n\t\t\t\t\tEnter Account Holder's First Name: ";
		cin >> accHolderFName;
		cout << "\n\n\t\t\t\t\tEnter Account Holder's Last Name: ";
		cin >> accHolderLName;
	}
	else if (payChoice == "3")
	{
	check:
		cout << "\n\n\t\t\t\t\tEnter Credit/Debit Card Number (16 digits): ";
		cin >> cc;
		if (cc.length() != 16)
		{
			cout << "\n\n\t\t\t\t\tCC number must have a length of 16 only! \n";
			goto check;
		}
		else
			check2:
		cout << "\n\n\t\t\t\t\tEnter CVV (3 digits): ";
		for (int i = 0; i > -1; i++)
		{
			char temp;
			temp = _getch();
			if (temp != 13 && temp != 8)
			{
				_putch('*');
			}
			if (temp == 13)
			{
				break;
			}
			if (temp == 8 || temp == 127 && !cvv.empty())
			{
				cout << "\b \b";
				cvv.erase(cvv.size() - 1);
			}
			else
				cvv += temp;
		}
		if (cvv.length() != 3)
		{
			cout << "\n\n\t\t\t\t\tCVV number must have a length of 3 only! \n";
			cvv = "";
			goto check2;
		}
		else
		{
			cout << "\n\n\t\t\t\t\tEnter Date Of Expiry(DD/MM/YYYY): ";
			cin >> dob;
		}
	}
	else
	{
		cout << "\t\t\t\t\tInvalid Choice. Please try again. \n";
	}
	cout << "\n\n\t\t\t\t\t";
}

void trainSort() {
	string temp, temp2, temp3, temp4, temp5, temp6, temp7, temp9;
	int temp8, j;
	for (int i = 0; i < noOfTrains; i++)
	{
		temp = availTrains[i].arriveTime;
		temp2 = availTrains[i].departTime;
		temp3 = availTrains[i].TClasses;
		temp4 = availTrains[i].TDate;
		temp5 = availTrains[i].TDest;
		temp6 = availTrains[i].TID;
		temp7 = availTrains[i].TName;
		temp8 = availTrains[i].TSeats;
		temp9 = availTrains[i].TSource;
		j = i - 1;
		while (j >= 0 && availTrains[j].TName > temp7)
		{
			availTrains[j + 1].arriveTime = availTrains[j].arriveTime;
			availTrains[j + 1].departTime = availTrains[j].departTime;
			availTrains[j + 1].TClasses = availTrains[j].TClasses;
			availTrains[j + 1].TDate = availTrains[j].TDate;
			availTrains[j + 1].TDest = availTrains[j].TDest;
			availTrains[j + 1].TID = availTrains[j].TID;
			availTrains[j + 1].TName = availTrains[j].TName;
			availTrains[j + 1].TSeats = availTrains[j].TSeats;
			availTrains[j + 1].TSource = availTrains[j].TSource;
			j--;
		}
		availTrains[j + 1].arriveTime = temp;
		availTrains[j + 1].departTime = temp2;
		availTrains[j + 1].TClasses = temp3;
		availTrains[j + 1].TDate = temp4;
		availTrains[j + 1].TDest = temp5;
		availTrains[j + 1].TID = temp6;
		availTrains[j + 1].TName = temp7;
		availTrains[j + 1].TSeats = temp8;
		availTrains[j + 1].TSource = temp9;
	}
}

string SeatChoose() {
    fstream Seat;
    int count = 0;
    string line;
    SeatRecord Seats[10];

    // Open the file to count the lines
    Seat.open("Seat_Details.txt");
    if (!Seat.is_open()) {
        cout << "Error: Could not open Seat_Details.txt" << endl;
        return "";
    }

    // Read seat details into the Seats array
    while (getline(Seat, line) && count < 10) {
        size_t pos1 = line.find('-');
        size_t pos2 = line.find('-', pos1 + 1);
        size_t pos3 = line.find('-', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            Seats[count].RowA = line.substr(0, pos1);
            Seats[count].RowB = line.substr(pos1 + 1, pos2 - pos1 - 1);
            Seats[count].RowC = line.substr(pos2 + 1, pos3 - pos2 - 1);
            count++;
        }
    }
    Seat.close();

    // Display seat options
    cout << "\n\n\t\t\t\t\t\t\tA" << "\t" << "B" << "\t" << "C" << "\n";
    for (int i = 0; i < count; i++) {
        cout << "\n\n\t\t\t\t\t\t\t" << Seats[i].RowA << "\t" << Seats[i].RowB << "\t" << Seats[i].RowC << "\n";
    }

    // Choose row and seat
    string RowName, SeatNum, FinalSeatNum;
    bool Flag = false;

    while (true) {
        cout << "\n\n\t\t\t\t\tEnter the row name that you chose (A, B, or C): ";
        cin >> RowName;
        if (RowName == "A" || RowName == "B" || RowName == "C") break;
        cout << "\nInvalid row, please try again.";
    }

    while (true) {
        cout << "\n\n\t\t\t\t\tEnter the seat number that you chose: ";
        cin >> SeatNum;

        Flag = false;
        for (int i = 0; i < count; i++) {
            if (RowName == "A" && Seats[i].RowA == SeatNum) {
                Seats[i].RowA = "XX";
                Flag = true;
                break;
            } else if (RowName == "B" && Seats[i].RowB == SeatNum) {
                Seats[i].RowB = "XX";
                Flag = true;
                break;
            } else if (RowName == "C" && Seats[i].RowC == SeatNum) {
                Seats[i].RowC = "XX";
                Flag = true;
                break;
            }
        }

        if (Flag) break;
        cout << "\nSeat number not found, please try again.";
    }

    // Update the seat details file
    ofstream Del("Seat_Details.txt", ios::trunc);
    if (!Del.is_open()) {
        cout << "Error: Could not open Seat_Details.txt for writing" << endl;
        return "";
    }
    for (int i = 0; i < count; i++) {
        Del << Seats[i].RowA << "-" << Seats[i].RowB << "-" << Seats[i].RowC << "-\n";
    }
    Del.close();

    FinalSeatNum = RowName + SeatNum;
    return FinalSeatNum;
}


void iniTrain()
{
	availTrains[0].TName = "Shalimar Express";
	availTrains[0].TID = "SHE753";
	availTrains[0].TSource = "Karachi";
	availTrains[0].TDest = "Lahore";
	availTrains[0].TDate = "24-Dec-2020";
	availTrains[0].arriveTime = "20:00 (8:00 PM)";
	availTrains[0].departTime = "16:40 (4:40 PM)";
	availTrains[0].TClasses = "Economy, AC Lower, AC Business";
	availTrains[0].TSeats = 30;

	availTrains[1].TName = "Karakoram Express";
	availTrains[1].TID = "KKE694";
	availTrains[1].TSource = "Karachi";
	availTrains[1].TDest = "Faisalabad";
	availTrains[1].TDate = "26-Dec-2020";
	availTrains[1].arriveTime = "08:00 (8:00 AM)";
	availTrains[1].departTime = "04:40 (4:40 AM)";
	availTrains[1].TClasses = "Economy, AC Lower, AC Business";
	availTrains[1].TSeats = 30;

	availTrains[2].TName = "Green Line Express";
	availTrains[2].TID = "GLE400";
	availTrains[2].TSource = "Karachi";
	availTrains[2].TDest = "Islamabad";
	availTrains[2].TDate = "05-Jan-2021";
	availTrains[2].arriveTime = "12:00 (12:00 PM)";
	availTrains[2].departTime = "10:00 (10:00 AM)";
	availTrains[2].TClasses = "Economy, AC Lower, AC Business";
	availTrains[2].TSeats = 30;


	availTrains[3].TName = "Tezgam Express";
	availTrains[3].TID = "TEZ123";
	availTrains[3].TSource = "Karachi";
	availTrains[3].TDest = "Faisalabad";
	availTrains[3].TDate = "01-Jan-2021";
	availTrains[3].arriveTime = "15:00 (03:00 PM)";
	availTrains[3].departTime = "9:00 (09:00 AM)";
	availTrains[3].TClasses = "Economy, AC Lower, AC Business";
	availTrains[3].TSeats = 30;

	availTrains[4].TName = "Karachi Express";
	availTrains[4].TID = "KHE123";
	availTrains[4].TSource = "Karachi";
	availTrains[4].TDest = "Lahore";
	availTrains[4].TDate = "31-Dec-2000";
	availTrains[4].arriveTime = "12:00 (12:00 AM)";
	availTrains[4].departTime = "12:00 (09:00 PM)";
	availTrains[4].TClasses = "Economy, AC Lower, AC Business";
	availTrains[4].TSeats = 30;

}

string trainFill()
{
	bool check = false;
	bool check2 = false;
	trainCheck = true;

flag:
	cout << "\t\t\t\t\tEnter Your Departure City: ";
	cin >> Dest;
	cin.ignore();
	cout << "\t\t\t\t\tEnter Your Arrival City: ";
	cin >> Source;
	cin.ignore();

	trainSort();

	cout << "\n\n\t\t\t\t\tAVAILABLE TRAINS ON THAT DAY IN THIS ROUTE ARE AS FOLLOWS (IF ANY): \n\n" << endl;

	for (int i = 0; i < noOfTrains; i++)
	{
		if (availTrains[i].TSource == Dest && availTrains[i].TDest == Source)
		{
			cout << "\t\t\t\t\tTrain Name: " << availTrains[i].TName << endl;
			cout << "\t\t\t\t\tTrain ID: " << availTrains[i].TID << endl;
			cout << "\t\t\t\t\tTrain Source: " << availTrains[i].TSource << endl;
			cout << "\t\t\t\t\tTrain Destination: " << availTrains[i].TDest << endl;
			cout << "\t\t\t\t\tTrain Departure Date: " << availTrains[i].TDate << endl;
			cout << "\t\t\t\t\tTrain Arrival Time: " << availTrains[i].arriveTime << endl;
			cout << "\t\t\t\t\tTrain Departure Time: " << availTrains[i].departTime << endl;
			cout << "\t\t\t\t\tAvailable Train Classes: " << availTrains[i].TClasses << endl;
			cout << "\t\t\t\t\tSeats Available: " << availTrains[i].TSeats << endl;
			cout << endl << endl;
			check = true;
		}
	}
	if (check == false) {
		cout << "\t\t\t\t\tNo trains available on this route. Re-enter your details. \n";
		goto flag;
	}
	else {
	redo:
		cout << "\t\t\t\t\tInput Train ID that you wish to book: ";
		cin >> BookedID;
		for (int i = 0; i < noOfTrains; i++)
		{
			if (BookedID == availTrains[i].TID)
			{
				availTrains[i].TSeats--;
				return BookedID;
				check2 = true;
			}
		}
		if (check2 == false)
		{
			cout << "\t\t\t\t\tInput correct train ID! \n";
			goto redo;
		}
	}
}

void trainPrice()
{
	int choice = 0;
	cout << "\t\t\t\t\tPrices based on classes are as follows: \n";
	cout << "\t\t\t\t\t1. Economy \t\t 2500 PKR \n";
	cout << "\t\t\t\t\t2. AC Lower \t\t 3500 PKR \n";
	cout << "\t\t\t\t\t3. AC Business \t\t 4500 PKR \n\n";
	cout << "\t\t\t\t\tInput Choice (1-3): ";
	cin >> choice;
	if (choice == 1) {
		PRICE = 2500;
		Class = "Economy [No Berth]";
	}
	else if (choice == 2) {
		PRICE = 3500;
		Class = "AC Lower [Berth Included]";
	}
	else if (choice == 3) {
		PRICE = 4500;
		Class = "AC Business [Berth Included]";
	}
}

void reserveTicket()
{
	string fName, lName;
	node *obj = new node();
	node* temp = tail;
	if (head == NULL && tail == NULL) {
		obj->next = NULL;
		head = obj;
		tail = obj;
	}
	else
	{
		temp->next = obj;
		tail = obj;
	}

	cout << endl << endl << endl << endl << endl;
	cout << "\t\t\t\t\tEnter First Name of Passenger: ";
	cin >> fName;
	cout << "\t\t\t\t\tEnter Last Name of Passenger: ";
	cin >> lName;
	Name = fName + " " + lName;

	cout << "\t\t\t\t\tEnter Age: ";
	cin >> Age;

nicCheck:
	cout << "\t\t\t\t\tEnter CNIC Number: ";
	cin >> NIC;

	if (NIC.length() != 5 || NIC.length() > 5)
	{
		cout << endl;
		cout << "\t\t\t\t\tEnter a Valid 5 digit CNIC Number!" << endl << endl;
		goto nicCheck;
	}

phoneCheck:
	cout << "\t\t\t\t\tEnter Contact Number: ";
	cin >> Contact;

	if (Contact.length() != 10 || Contact.length() > 10)
	{
		cout << endl;
		cout << "\t\t\t\t\tEnter a Valid 10 digit Mobile Phone Number!" << endl << endl;
		goto phoneCheck;
	}
	cin.clear();

	trainFill();
	int seatCheck;
	for (int i = 0; i < noOfTrains; i++)
	{
		if (availTrains[i].TID == BookedID)
		{
			TName = availTrains[i].TName;
			TID = BookedID;
			Date = availTrains[i].TDate;
			ATime = availTrains[i].arriveTime;
			DTime = availTrains[i].departTime;
		}
	}

	trainPrice();

	SeatNum = SeatChoose();

	Payment();

	system("cls");

	cout << "\n\n\t\t\t\t\t Your payment is successfully processed!" << endl;
	cout << "\t\t\t\t\t PKR " << PRICE << " has been deducted from your Account." << endl;

	srand(time(0));

	//Randomly Generated Ticket ID:
	obj->ticketID = (rand());
	cout << endl << endl;
	cout << "\t\t\t\t\tTicket Generated! Your ID is: " << obj->ticketID << endl;
	currentID = obj->ticketID;

	obj->Name = Name;
	obj->NIC = NIC;
	obj->Age = Age;
	obj->Contact = Contact;
	obj->BookedTName = TName;
	obj->BookedDest = Dest;
	obj->BookedSource = Source;
	obj->BookedSeatNum = SeatNum;
	obj->PRICE = PRICE;
	obj->BookedClass = Class;
	obj->BookedTID = TID;
	obj->BookedDate = Date;
	obj->DeptTime = DTime;
	obj->ArrTime = ATime;

	cout << endl << endl;
}

void viewTicket()
{
	int search;
	string choice;
	bool check = false;
	node *temp = head;
	cin.clear();
	cout << endl << endl << endl << endl << endl;
jump:
	cout << "\t\t\t\t\tDo You Want to View Most Recent Booking? If so, Press 1\n";
	cout << "\t\t\t\t\t Do You Want to Search on Older Booking? If so, Press 2\n";
	cout << "\t\t\t\t\tEnter Choice (1-2): ";
	cin >> choice;
	cin.ignore();
	if (choice == "1")
	{
		search = currentID;
		check = true;
	}
	else if (choice == "2")
	{
		cout << "\t\t\t\t\tEnter Your Booking ID: ";
		cin >> search;
		cout << endl << endl;
		check = true;
	}
	else
	{
		cout << "\t\t\t\t\tInvalid input. Retry! \n";
		goto jump;
	}
	do
	{
		if (temp != NULL)
		{
			if (temp->ticketID == search && check == true)
			{
				cout << "\t\t\t\t\tBooking ID: " << temp->ticketID << endl;
				cout << "\t\t\t\t\tName: " << temp->Name << endl;
				cout << "\t\t\t\t\tAge: " << temp->Age << endl;
				cout << "\t\t\t\t\tNIC: " << temp->NIC << endl;
				cout << "\t\t\t\t\tContact: " << temp->Contact << endl;
				cout << "\t\t\t\t\tTrain ID: " << temp->BookedTID << endl;
				cout << "\t\t\t\t\tTrain Name: " << temp->BookedTName << endl;
				cout << "\t\t\t\t\tTrain Class: " << temp->BookedClass << endl;
				cout << "\t\t\t\t\tSeat Number: " << temp->BookedSeatNum << endl;
				cout << "\t\t\t\t\tDate of Booking: " << temp->BookedDate << endl;
				cout << "\t\t\t\t\tSource: " << temp->BookedDest << endl;
				cout << "\t\t\t\t\tDestination: " << temp->BookedSource << endl;
				cout << "\t\t\t\t\tDeparture TIme: " << temp->DeptTime << endl;
				cout << "\t\t\t\t\tArrival Time: " << temp->ArrTime << endl;
				cout << endl << endl;
				break;
				main();
			}
			else
			{
				temp = temp->next;
			}
		}
		else
			cout << "\t\t\t\t\tNo Bookings Exist. \n";
	} while (temp);
}

void display()
{
	cout << endl << endl << endl << endl << endl;
	if (head != NULL && tail != NULL)
	{
		cout << "\t\t\t\t\tList is as follows: \n";
		node *temp = head;
		do {
			cout << "\t\t\t\t\tTicket ID: " << temp->ticketID << endl;
			cout << "\t\t\t\t\tName: " << temp->Name << endl;
			cout << "\t\t\t\t\tAge: " << temp->Age << endl;
			cout << "\t\t\t\t\tNIC: " << temp->NIC << endl;
			cout << "\t\t\t\t\tContact: " << temp->Contact << endl;
			cout << "\t\t\t\t\tTrain ID: " << temp->BookedTID << endl;
			cout << "\t\t\t\t\tTrain Name: " << temp->BookedTName << endl;
			cout << "\t\t\t\t\tTrain Class: " << temp->BookedClass << endl;
			cout << "\t\t\t\t\tSeat Number: " << temp->BookedSeatNum << endl;
			cout << "\t\t\t\t\tDate of Booking: " << temp->BookedDate << endl;
			cout << "\t\t\t\t\tSource: " << temp->BookedSource << endl;
			cout << "\t\t\t\t\tDestination: " << temp->BookedDest << endl;
			cout << "\t\t\t\t\tDeparture TIme: " << temp->DeptTime << endl;
			cout << "\t\t\t\t\tArrival Time: " << temp->ArrTime << endl;
			cout << endl;
			temp = temp->next;
		} while (temp);
	}
	else
		cout << "List is empty, nothing to display. \n";
}

void removeTicket(int remTicket) {
	node* prev = head;
	node* delNode = head;
	while (delNode != NULL) {
		if (delNode->ticketID == remTicket) {
			break;
		}
		else {
			prev = delNode;
			delNode = delNode->next;
		}
	}
	if (delNode == NULL) {
		cout << "Ticket ID Not Found!" << endl;
	}
	else {
		cout << "\t\t\t\t\tDeleted Ticket ID: " << delNode->ticketID << "\n";
		prev->next = delNode->next; // unlink the node you remove
		delete delNode; // delete the node
	}
}

void editDetais() {

	string fName, lName;

	cout << "\t\t\t\t\tEDIT DETAILS:" << endl << endl;
	int search;
	node *temp = head;
	cin.clear();
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t\t\t\tEnter ticket ID: ";
	cin >> search;

	while (temp != NULL)
	{
		if (temp->ticketID == search)
		{
			cout << "\t\t\t\t\tEnter First Name of Passenger: ";
			cin >> fName;
			cout << "\t\t\t\t\tEnter Last Name of Passenger: ";
			cin >> lName;
			Name = fName + " " + lName;

			cout << "\t\t\t\t\tEnter CNIC Number: ";
			cin >> NIC;
			cin.ignore();
			cout << "\t\t\t\t\tEnter Contact Number: ";
			cin >> Contact;
			cin.ignore();

			temp->Name = Name;
			temp->NIC = NIC;
			temp->Age = Age;
			temp->Contact = Contact;
		}
		temp = temp->next;
	}

}

void addTrains()
{
	string choice;
	do {
		cin.ignore();
		cout << endl << endl << endl << endl << endl;
		cout << "\t\t\t\t\tEnter Train Name: ";
		getline(cin, availTrains[noOfTrains].TName);
		cout << "\t\t\t\t\tEnter Train ID: ";
		getline(cin, availTrains[noOfTrains].TID);
		cout << "\t\t\t\t\tEnter Train Source: ";
		getline(cin, availTrains[noOfTrains].TSource);
		cout << "\t\t\t\t\tEnter Train Destination: ";
		getline(cin, availTrains[noOfTrains].TDest);
		cout << "\t\t\t\t\tEnter Train Departure Date: ";
		getline(cin, availTrains[noOfTrains].TDate);
		cout << "\t\t\t\t\tEnter Train Departure Time [HH:MM (MM:HH AM/PM)]: ";
		getline(cin, availTrains[noOfTrains].departTime);
		cout << "\t\t\t\t\tEnter Train Arrival Time [HH:MM (MM:HH AM/PM)]: ";
		getline(cin, availTrains[noOfTrains].arriveTime);
		cout << "\t\t\t\t\tEnter Available Train Classes: ";
		getline(cin, availTrains[noOfTrains].TClasses);
		cout << "\t\t\t\t\tEnter Seats Available: ";
		cin >> availTrains[noOfTrains].TSeats;
		noOfTrains++;
		cin.clear();
		cout << "\t\t\t\t\tDo you want to add more trains? (Y/N): ";
		cin >> choice;

		if (choice != "Y" && choice != "N")
			cout << "\t\t\t\t\tInvalid input. Enter choice again. ";
		else if (choice == "N") {
			system("cls");
			cout << "\n\n\n\n\n\t\t\t\t\tTrain added! \n";
			cout << "\t\t\t\t\tSession logged out. Please login again. \n";
			Sleep(1500);
			system("cls");
			main();
		}

	} while (choice != "N");
}

void admin()
{
	string choice, user, password;
	system("cls");
	cin.clear();
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t\t\t\tWELCOME TO ADMIN PORTAL!\n\n";

	cout << "\t\t\t\t\tEnter your login credentials below! \n";
login:
	cout << "\t\t\t\t\tEnter your Username: ";
	cin >> user;
	cout << "\t\t\t\t\tEnter your Password: ";
	cin >> password;

	if (user == "Shradha" && password == "Shradha" || user == "Bhakoji" && password == "Bhakoji")
	{
		cout << "\t\t\t\t\tLogged in Successfully!\n";
		cin.clear();
		system("cls");
		cout << endl << endl << endl << endl << endl;
		cout << "\t\t\t\t\tSelect 1 to View all Booked Tickets. \n";
		cout << "\t\t\t\t\tSelect 2 to add Trains. \n";
		cout << "\t\t\t\t\tSelect 3 to Exit\n";
		do
		{
			cout << "\t\t\t\t\tEnter Choice To Proceed (1-2): ";
			cin >> choice;
			if (choice == "1")
				display();
			else if (choice == "2") {
				cin.clear();
				addTrains();
				if (trainCheck == false)
					trainFill();
			}
			else if (choice == "3") {
				system("cls");
				main();
			}
			else
				cout << "\t\t\t\t\tEnter correct choice. Try again. \n";
		} while (choice != "3");
	}
	else
	{
		cout << "\t\t\t\t\tInvalid credentials. Please login again. \n";
		goto login;
	}
}

void trainReservation()
{
	iniTrain();
relog:
	cin.clear();
	string check;
	cout << endl << endl << endl << endl << endl;
	cout << "\t\t\t\t\t WELCOME TO RAILWAY BOOKING SYSTEM!\n\n\n"; Sleep(300);
	cout << "\n\n\t\t\t\t\t\tProject Prepared by:"; Sleep(400);
	cout << "\n\n\t\t\t\t\t\t--------------------"; Sleep(500);
	cout << endl;
	system("cls");
log:
	cout << "\n\n\n\n\n\t\t\t\tIf you are a user looking to book a ticket, type 1 \n";
	cout << "\t\t\t\tIf you are an admin, type 2 \n";
	cout << "\n\n\t\t\t\t\t\tChoice: ";
	cin >> check;
	if (check == "1") {
		int tickID;
		string choice;
		system("cls");
		cout << endl << endl << endl << endl << endl;
		do
		{
			cout << "\t\t\t\t     -----------------------------------------\n";
			cout << "\t\t\t\t\tSelect 1 to Reserve a Ticket. \n";
			cout << "\t\t\t\t\tSelect 2 to View your Reservation. \n";
			cout << "\t\t\t\t\tSelect 3 to Display all tickets. \n";
			cout << "\t\t\t\t\tSelect 4 to Delete a ticket. \n";
			cout << "\t\t\t\t\tSelect 5 to Edit Details. \n";
			cout << "\t\t\t\t\tSelect 6 to Log Out of Session. \n";
			cout << "\t\t\t\t\tSelect 7 to Exit\n";
			cout << endl << endl;
			cout << "\t\t\t\t\tEnter Choice To Proceed (1-7): ";
			cin >> choice;

			if (choice == "1") {
				system("cls");
				cin.clear();
				reserveTicket();
			}
			else if (choice == "2") {
				system("cls");
				viewTicket();
			}
			else if (choice == "3") {
				system("cls");
				display();
			}
			else if (choice == "4") {
				cout << "\t\t\t\t\tEnter your Ticket ID: ";
				cin >> tickID;
				removeTicket(tickID);
			}
			else if (choice == "5") {
				system("cls");
				editDetais();
			}
			else if (choice == "6") {
				goto relog;
			}
			else if (choice == "7") {
				Sleep(300);
				cout << "\t\t\t\t\tTHANKYOU FOR USING OUR SOFTWARE! \n";

				Sleep(300);
				exit(0);
			}
			else
				cout << "\t\t\t\t\tEnter correct choice. Try again. \n";
		} while (choice != "7");
	}
	else if (check == "2")
		admin();
	else
	{
		cout << "Invalid input. Try again. \n";
		goto log;
	}
}



// Flight Reservation

    //cout << "\n--- Flight Reservation ---\n";

     int glob=0;
int global=10;

class d_booking
{
protected:
    int pnr;
    char f_d[10],toja[7],tojd[7];
    long int doj;
    int choice,src,dest;
public:
    void d_pnr()
    {
        glob++;
        pnr=glob;
    }
    int j_detail()
    {
        cout << "\nEnter Date of Flight(DDMMYY)." << "Please enter a valid date." <<  endl;
        cin >> doj;
        cout << "1.New York(1) \t2.New Jersey(2) \t3.Sydney(3) \t4.Los Angeles(4)" << endl << endl;
        cout << "\tEnter Source" << endl;
        cin >> src;
        cout << "\tEnter destination" << endl;
        cin >> dest;
        if((src==1 && dest==2) || (src==2 && dest==1))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Eagle(1)\t08:00\t\t11:05\t\t$100\t\tRefundable\n";
            cout << "2.Falcon(2)\t14:00\t\t17:05\t\t$100\t\tRefundable\n";
            cout << "3.Jet Speed(3)\t19:00\t\t22:05\t\t$100\t\tRefundable\n";
        }

        else if((src==1 && dest==3) || (src==3 && dest==1))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Eagle(1)\t08:00\t\t11:05\t\t$100\t\tRefundable\n";
            cout << "2.Falcon(2)\t14:00\t\t17:05\t\t$100\t\tRefundable\n";
            cout << "3.Jet Speed(3)\t19:00\t\t22:05\t\t$100\t\tRefundable\n";
        }

        else if((src==1 && dest==4) || (src==4 && dest==1))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Eagle(1)\t08:00\t\t11:05\t\t$200\t\tRefundable\n";
            cout << "2.Falcon(2)\t14:00\t\t17:05\t\t$250\t\tRefundable\n";
            cout << "3.Jet Speed(3)\t19:00\t\t22:05\t\t$300\t\tRefundable\n";
        }

        else if((src==2 && dest==3) || (src==3 && dest==2))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Eagle(1)\t08:00\t\t11:05\t\t$140\t\tRefundable\n";
            cout << "2.Falcon(2)\t14:00\t\t17:05\t\t$150\t\tRefundable\n";
            cout << "3.Jet Speed(3)\t19:00\t\t22:05\t\t$180\t\tRefundable\n";
        }

        else if((src==2 && dest==4) || (src==4 && dest==2))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Eagle(1)\t08:00\t\t11:05\t\t$200\t\tRefundable\n";
            cout << "2.Falcon(2)\t14:00\t\t17:05\t\t$150\t\tRefundable\n";
            cout << "3.Jet Speed(3)\t19:00\t\t22:05\t\t$200\t\tRefundable\n";
        }
        else if((src==3 && dest==4) || (src==4 && dest==3))//condition
         {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Eagle(1)\t08:00\t\t11:05\t\t$180\t\tRefundable\n";
            cout << "2.Falcon(2)\t14:00\t\t17:05\t\t$50\t\tRefundable\n";
            cout << "3.Jet Speed(3)\t19:00\t\t22:05\t\t$150\t\tRefundable\n";
        }
        else if(src==dest)//condition
        {
            cout << "\nDestination can't be same.\nTry again\n\n\n" << endl;
            return j_detail();
        }
        else
        {
            cout <<"\nWrong input entered\nTry again\n\n\n" << endl;
            return j_detail();
        }

    }

    int  select_flight()
    {   cout << "\nEnter your choice" << endl;
        cin >> choice;
        switch(choice)
        {
          case 1:
                cout << "\nFlight selected:"<<endl;
                cout << "Eagle"<<endl;
                strcpy(f_d,"Eagle");
                cout << "Departure Time : 08:00"<<endl;
                cout<<"Arrival Time: 11:05"<<endl;
                strcpy(tojd,"8:00");
                strcpy(toja,"11:05");
                break;
          case 2:
                cout << "\nFlight selected:"<<endl;
                cout << "Falcon"<<endl;
                strcpy(f_d,"Falcon");
                cout << "Departure Time : 14:00"<<endl;
                cout<<"Arrival Time: 17:05"<<endl;
                strcpy(tojd,"14:00");
                strcpy(toja,"17:05");
                break;
          case 3:
                cout << "\nFlight selected:" << endl;
                cout << "Jet Speed" << endl;
                strcpy(f_d,"Jet Speed");
                cout << "Departure Time : 19:00" << endl;
                cout<<"Arrival Time: 22:05" << endl;
                strcpy(tojd,"19:00");
                strcpy(toja,"22:05");
                break;
          default:
                cout << "Wrong input entered.\nTry again" << endl;
                return select_flight();
        }
    }
};

class i_booking
{
protected:
    int pnri;
    char f_i[10],tojai[7],tojdi[7];
    long int doji;
    int srci,desti,choicei;
public:
    void i_pnr()
    {
        global++;
        pnri=global;
    }

    int j_detaili()
    {
        cout << "Enter Date of Flight(DDMMYY)." << "Please enter a valid date." << endl;;
        cin >> doji;
        cout << "1.Delhi(1) \2.Hyderabad(2) \3.Kochi(3) \4.Bengaluru(4) \5.Lucknow(5) " << endl << endl;
        cout << "\tEnter Source" << endl;
        cin >> srci;
        cout << "\nEnter destination" ;
        cin >> desti;
        cout << "\t \t \tFlights Found" << endl << endl;

        if((srci==1 && desti==3) || (srci==3 && desti==1))//condition
        {
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Speed(1)\t10:00\t\t14:05\t\t2500\tRefundable\n";
            cout << "2.Zoom(2)\t14:00\t\t18:05\t\t2150\tRefundable\n";
            cout << "3.Fly Away(3)\t18:00\t\t22:05\t\t2400\tRefundable\n";
        }

        else if((srci==1 && desti==4) || (srci==4 && desti==1))//condition
        {
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Speed(1)\t10:00\t\t14:05\t\t25500\tRefundable\n";
            cout << "2.Zoom(2)\t14:00\t\t18:05\t\t21300\tRefundable\n";
            cout << "3.Fly Away(3)\t18:00\t\t22:05\t\t24600\t\tRefundable\n";
        }

        else if((srci==1 && desti==5) || (srci==5 || desti==1))//condition
        {
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Speed(1)\t10:00\t\t14:05\t\t25000\tRefundable\n";
            cout << "2.Zoom(2)\t14:00\t\t18:05\t\t2900\tRefundable\n";
            cout << "3.Fly Away(3)\t18:00\t\t22:05\t\t42000\tRefundable\n";
        }

        else if((srci==2 && desti==3) || (srci==3 && desti==2))//condition
        {
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Speed(1)\t10:00\t\t14:05\t\t17000\tRefundable\n";
            cout << "2.Zoom(2)\t14:00\t\t18:05\t\t14000\tRefundable\n";
            cout << "3.Fly Away(3)\t18:00\t\t22:05\t\t1700\tRefundable\n";
        }

        else if((srci==2 && desti==4) || (srci==4 && desti==2))//condition
        {
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Speed(1)\t10:00\t\t14:05\t\t$100\tRefundable\n";
            cout << "2.Zoom(2)\t14:00\t\t18:05\t\t$120\tRefundable\n";
            cout << "3.Fly Away(3)\t18:00\t\t22:05\t\t$250\tRefundable\n";        }

        else if(srci==2 && desti==5 || (srci==5 && desti==2))//condition
        {
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\n";
            cout << "1.Speed(1)\t10:00\t\t14:05\t\t14000\tRefundable\n";
            cout << "2.Zoom(2)\t14:00\t\t18:05\t\t12000\tRefundable\n";
            cout << "3.Fly Away(3)\t18:00\t\t22:05\t\t14000\tRefundable\n";

        }
        else if(srci==desti)//condition
        {
            cout << "wrong input entered.\nTry again\n\n\n"<< endl;
            return j_detaili();
        }
        else//condition
            {
            cout << "Wrong input entered.\nTry again\n\n\n";
            return j_detaili();
        }

    }

    int select_flighti()
    {
        cout << "\nEnter your choice" << endl;
        cin >> choicei;
        switch(choicei)
        {
        case 1:
            cout << "\nFlight selected:" <<endl;
            cout << "Speed" << endl;
            strcpy(f_i,"Speed");
            cout << "Departure Time: 10:00" << endl;
            cout << "Arrival Time: 14:05" << endl;
            strcpy(tojdi,"10:00");
            strcpy(tojai,"14:05");
            break;
        case 2:
               cout << "\nFlight selected:" << endl;
               cout << "Zoom" << endl;
               strcpy(f_i,"Zoom");
               cout << "Departure Time: 14:00" << endl;
               cout << "Arrival Time: 18:05" << endl;
               strcpy(tojdi,"14:00");
                strcpy(tojai,"18:05");
                break;
        case 3:
            cout << "\nFlight selected:" << endl;
            cout << "Fly Away" << endl;
            strcpy(f_i,"Fly Away");
            cout << "Departure Time : 18:00" << endl;
            cout << "Arrival Time: 22:05" << endl;
            strcpy(tojdi,"18:00");
            strcpy(tojai,"22:05");
            break;
        default:
            cout << "Wrong input entered" << endl;
            return select_flighti();
        }
    }
};


class passenger: public d_booking,public i_booking
{
protected:
    char f_name[20],l_name[20],email[50];
    int age,gender;
    long int c_no;
public:
    void p_detail(int x)
    {   if(x==1)
        { j_detail();
          select_flight();
        }
          else
          {  j_detaili();
             select_flighti();
          }
        cout << "\n\n\nEnter passenger details";
        cout << "\nFirst Name:";
        cin >> f_name;
        cout << "Last Name:";
        cin >> l_name;
    }
    int gender_check()
    {
        cout << "\nGender:\nMale-press:1::\nFemale-press:2::";
        cin >> gender;
        if(gender>2)
        {
            cout << "\n\nWrong input entered.\nTry again\n\n" << endl;
            return gender_check();
        }
    }
       void more_details()
       {
        cout << "Age:";
        cin >> age;
        cout << "Email Id:";
        cin >> email;
        cout << "Contact no.(6 digits):";
        cin >> c_no;
        cout << "\n\nDetails Entered:\n";
        cout << "Name:" << f_name << " " << l_name << endl;
        cout << "Gender:" << gender << endl;
        cout << "Age:" << age << endl;
        cout << "Email id:" << email << endl;
        cout << "Contact No.:" << c_no << endl;
    }


     int getpnr()
        {
            return pnr;
        }

     int getpnri()
     {
         return pnri;
     }

     void disp()
     {
         cout<<"PNR:" << pnr << endl;
         cout<<"Flight:" << f_d << endl;
         cout<<"Name:" << f_name << " " << l_name << endl;
         cout<<"DOJ:" << doj << endl;
         cout<<"Departure Time:" << tojd << endl;
         cout<<"Arrival Time:" << toja;
     }

      void dispi()
     {
         cout<<"PNR:" << pnri << endl;
         cout<<"Flight:" << f_i << endl;
         cout<<"Name:" << f_name << " " << l_name << endl;
         cout<<"DOJ:" << doji << endl;
         cout<<"Departure Time:" << tojdi << endl;
         cout<<"Arrival Time:" << tojai;
     }
};



class payment
{
protected:
    long
    int choice1,bank,card,date,cvv,user_id;
    char password[10];
public:
    void pay_detail()
    {     cout << "\n\n\nHow would you like to pay?:\n";
        cout << "\n1.Debit Card(1) \n2.Credit Card(2) \n3.Net Banking(3)";
        cout << "\n\nEnter your choice";
        cin >> choice1;
        switch(choice1)
        {
        case 1:
            cout << "\nEnter card no.:";
            cin >> card;
            cout << "\nEnter expiry date:";
            cin >> date;
            cout << "\nEnter CVV no.:";
            cin >> cvv;
            cout << "\nTransaction Successful\n";
            break;
        case 2://condition
            cout << "\nEnter card no.:";
            cin >> card;
            cout << "\nEnter expiry date:";
            cin >> date;
            cout << "\nEnter password:";
            cin >> password;
            cout << "\nTransaction Successful\n";
            break;
        case 3://condition
            cout << "Banks Available: 1.West Blue Bank(1) 2.Naga Bank(2) 3.Standard Bank(3) 4.Personal Bank(4) 5.Others(5)";
            cout << "\nSelect your bank:";
            cin >> bank;
            cout << "\nYou have selected:" << bank;
            cout << "\nEnter user id:";
            cin >> user_id;
            cout << "\nEnter password:";
            cin >> password;
            cout << "\nTransaction Successful\n";
            break;
        default://condition
            cout << "\nWrong input entered.\nTry again\n\n";
            return pay_detail();
        }
    }

};

void createfile(passenger p)
{  ofstream fin("domestic.txt",ios::binary|ios::app);
   fin.write((char*)&p,sizeof(p));
   fin.close();
}

void cancelticket(int x)
{  passenger p;
    int f=0;
   ifstream fout("domestic.txt",ios::binary|ios::app);
   ofstream fin("domestic1.txt",ios::binary|ios::app);
   fout.read((char *)&p,sizeof(p));
   while(fout)
   {
     if(p.getpnr()!=x)
      fin.write((char *)&p,sizeof(p));
      else
     {
         p.disp();
         cout<<"\nYour Above ticket is being canceled:\n" << "Amount refunded: $100\n";
         f++;
     }
     fout.read((char *)&p,sizeof(p));
   }
   if(f==0)
    cout<<"Ticket not found\n";
   fout.close();
   fin.close();
   remove("domestic.txt");
   rename("domestic1.txt","domestic.txt");

}

void checkticket(int x)
{  passenger p;
   int f=0;
   ifstream fout("domestic.txt",ios::binary);
   fout.read((char *)&p,sizeof(p));
   while(fout)
   {
     if(p.getpnr()==x)
     {p.disp();
      cout<<"\nYour ticket"<<endl;
      f++;
      break;
     }
     fout.read((char *)&p,sizeof(p));

   }
   fout.close();
   if(f==0)
   cout<<"Ticket not found"<<endl;

}
void createfilei(passenger p)
{  ofstream fin("international.txt",ios::binary|ios::app);
   fin.write((char*)&p,sizeof(p));
   fin.close();
}
void cancelticketi(int x)
{  passenger p;
   int f=0;
   ifstream fout("international.txt",ios::binary|ios::app);
   ofstream fin("international1.txt",ios::binary|ios::app);
   fout.read((char *)&p,sizeof(p));
   while(fout)
   {
     if(p.getpnri()!=x)
      fin.write((char *)&p,sizeof(p));
      else
     {
         p.dispi();
         cout<<"Your Above ticket is being deleted:\n"<<"Amount refunded: $100\n";
         f++;
     }
     fout.read((char *)&p,sizeof(p));
   }
   if(f==0)
    cout<<"\nTicket not found\n";
   fout.close();
   fin.close();
   remove("international.txt");
   rename("international1.txt","international.txt");

}
void checkticketi(int x)
{  passenger p;
   int f=0;
   ifstream fout("international.txt",ios::binary);
   fout.read((char *)&p,sizeof(p));
   while(fout)
   {
     if(p.getpnri()==x)
     {p.dispi();
      cout<<"\nYour ticket"<<endl;
      f++;
      break;
     }
     fout.read((char *)&p,sizeof(p));

   }
   fout.close();
   if(f==0)
   cout<<"Ticket not found"<<endl;

}

void flightReservation()
{

    class d_booking d1;
    class i_booking i1;
    class passenger p1;
    class payment p2;
    int ch,ch1,n;
    char input;
    do
    {
    	system("CLS");
    cout << "\n\n \t\tWelcome To Airline Flight Booking System" << endl << endl;

    cout << "\n\n\t\t\t1.Book Flight(1) \n\t\t\t2.Cancel Fight(2) \n\t\t\t3.Check Ticket(3) \n\t\t\t4.Exit(4)" << endl;
    cout << "\n\t\t Please enter your choice:";
    cin >> ch;
      switch(ch)
      {
          case 1:
          system("CLS");
              cout << "\n\n1.Domestic Fights(1) \n2.International Flights(2)" << endl;
              cout << "\nPlease enter your option" << endl;
              cin >> ch1;
              switch(ch1)
              {
                   case 1:
                        p1.d_pnr();
                        p1.p_detail(1);
                        p1.gender_check();
                        p1.more_details();
                        p2.pay_detail();
                        p1.disp();
                        createfile(p1);
                        break;
                   case 2:
                           p1.p_detail(2);
                           p1.i_pnr();
                           p1.gender_check();
                           p1.more_details();
                           p2.pay_detail();
                           p1.dispi();
                           createfilei(p1);
                           break;
                   default:
                    cout << "Wrong input entered\nTry again\n\n\n" << endl;
                    return  flightReservation();
              }
          break;
          case 2:

              system("CLS");
              cout << "1.Domestic Fights(1) \n2.International Flights(2)" << endl;
                 cout << "\nPlease enter your option" << endl;
                 cin >> ch1;
                  if(ch1==1)
                {
                   cout << "Please enter your PNR no.:" << endl;
                   cin>>n;
                   cancelticket(n);
                }
                 else if(ch1==2)
               {  cout << "Please enter your PNR no.:" << endl;
                  cin>>n;
                  cancelticketi(n);
               }
               else
               {
                   cout << "Wrong input entered\nTry again\n\n\n";
                   return flightReservation();
               }
               break;
          case 3:
          system("CLS");
                  cout << "1.Domestic Fights(1) \n2.International Flights(2)" << endl;
                  cout << "\nPlease enter your option" << endl;
                  cin >> ch1;
                  if(ch1==1)
                  {cout << "Please enter your PNR no.:" << endl;
                  cin>>n;
                  checkticket(n);}
                  else if(ch1==2)
                  {  cout << "Please enter your PNR no.:" << endl;
                     cin>>n;
                     checkticketi(n);
                  }
                   else
               {
                   cout << "Wrong input entered.\nTry again\n\n\n";
                   return flightReservation();
               }
               break;
            case 4:
			system("CLS");
			return;
          default:
            cout << "Wrong input entered\nTry again.\n\n\n\n" << endl;
            return  flightReservation();
      }
    cout<<"\n\n\nDo you wish to continue:(y/Y)" << endl;
    cin >> input;
  }while(input=='Y' || input=='y');
}


// Function for Hotel Reservation
void HotelDashboard()
{
    int option;

    do
    {
        cout << "------------------------------------------------\n";
        cout << "                Hotel Dashboard                 \n";
        cout << "------------------------------------------------\n\n";
        cout << "1. Add Hotel\n";
        cout << "2. Delete Hotel\n";
        cout << "3. View Hotel Details\n";
        cout << "4. Exit\n";
        cout << "Select an option: ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option)
        {
        case 1:
            AddHotel();
            break;
        case 2:
            DeleteHotel();
            break;
        case 3:
            if (hotels.empty())
            {
                cout << "No hotels available.\n";
            }
            else
            {
                cout << "Available Hotels:\n";
                for (size_t i = 0; i < hotels.size(); ++i)
                {
                    cout << i + 1 << ". " << hotels[i].Name << endl;
                }
                int hotelOption;
                cout << "Select a hotel to view details: ";
                cin >> hotelOption;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (hotelOption > 0 && hotelOption <= hotels.size())
                {
                    ViewHotelDetails(hotels[hotelOption - 1]);
                }
                else
                {
                    cout << "Invalid option.\n";
                }
            }
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option. Please select a valid option.\n";
        }
    } while (option != 4);
}

void SaveHotelDetails(const Hotel &hotel)
{
    ofstream file("HotelDetails.txt", ios::app);
    if (file.is_open())
    {
        file << hotel.Name << "\n";
        file << hotel.Address << "\n";
        file << hotel.Mob << "\n";
        file << hotel.FP << "\n";

        for (const Room &room : hotel.rooms)
        {
            file << room.Type << "\n"
                 << room.Price << "\n"
                 << room.Quantity << "\n";
            file << room.Description << "\n";
        }
        file << "END_HOTEL\n"; // Add delimiter to separate hotels
        file.close();
    }
    else
    {
        cout << "Error opening file to save hotel details." << endl;
    }
}

void FilterHotelsByPlaceAndPrice(const string &place, int maxPrice)
{
    vector<Hotel> filteredHotels;
    for (const Hotel &hotel : hotels)
    {
        if (hotel.Address.find(place) != string::npos)
        {
            for (const Room &room : hotel.rooms)
            {
                if (room.Price <= maxPrice)
                {
                    filteredHotels.push_back(hotel);
                    break;
                }
            }
        }
    }

    if (filteredHotels.empty())
    {
        cout << "No hotels found matching the criteria.\n";
    }
    else
    {
        cout << "Filtered Hotels:\n";
        for (const Hotel &hotel : filteredHotels)
        {
            cout << "Hotel Name: " << hotel.Name << "\n";
            cout << "Address: " << hotel.Address << "\n";
            cout << "Customer Care Mob No.: " << hotel.Mob << "\n";
            cout << "Food Service Price: " << hotel.FP << "\n";
            for (const Room &room : hotel.rooms)
            {
                cout << "Room Type: " << room.Type << " | Price: " << room.Price << " | Quantity: " << room.Quantity << " | Description: " << room.Description << "\n";
            }
            cout << "------------------------------------------------\n";
        }
    }
}

void LoadHotels()
{
    ifstream file("HotelDetails.txt");
    if (!file.is_open())
    {
        cout << "Error opening HotelDetails.txt" << endl;
        return;
    }

    hotels.clear();
    while (!file.eof())
    {
        Hotel hotel;
        getline(file, hotel.Name);
        if (hotel.Name.empty())
            break;
        getline(file, hotel.Address);
        file >> hotel.Mob;
        file >> hotel.FP;
        file.ignore();

        hotel.rooms.clear();
        while (true)
        {
            Room room;
            if (!getline(file, room.Type) || room.Type.empty())
                break;
            file >> room.Price;
            file >> room.Quantity;
            file.ignore();
            getline(file, room.Description);
            hotel.rooms.push_back(room);
        }
        hotels.push_back(hotel);
        string endMarker;
        getline(file, endMarker); // Read the "END_HOTEL" marker
    }
    file.close();
}

void AddHotel()
{
    Hotel hotel;
    int roomCount;

    cout << "Enter Hotel Name: ";
    getline(cin, hotel.Name);
    cout << "Enter Address: ";
    getline(cin, hotel.Address);
    cout << "Enter Customer Care Mob No.: ";
    cin >> hotel.Mob;
    if (to_string(hotel.Mob).length() == 10)
    {
        cout << " Mob No.: " << hotel.Mob<< endl;
    }
    else
    {
        cout << " Mob No.: Invalid (not a 10-digit number)" << endl;
    }
    cin.ignore();
    cout << "Enter number of room types: ";
    cin >> roomCount;
    cin.ignore();

    while (roomCount <= 0)
    {
        cout << "Please enter a valid number of room types: ";
        cin >> roomCount;
        cin.ignore();
    }

    for (int i = 0; i < roomCount; ++i)
    {
        Room room;
        cout << "Enter room type (e.g., Deluxe, Suite): ";
        getline(cin, room.Type);
        cout << "Enter price for " << room.Type << " room: ";
        cin >> room.Price;
        while (room.Price <= 0)
        {
            cout << "Invalid price. Please re-enter the price for " << room.Type << " room: ";
            cin >> room.Price;
        }
        cout << "Enter quantity for " << room.Type << " room: ";
        cin >> room.Quantity;
        while (room.Quantity <= 0)
        {
            cout << "Invalid quantity. Please re-enter the quantity for " << room.Type << " room: ";
            cin >> room.Quantity;
        }
        cin.ignore();
        cout << "Enter description for " << room.Type << " room: ";
        getline(cin, room.Description);
        hotel.rooms.push_back(room);
    }

    cout << "Enter Food Service Price: ";
    cin >> hotel.FP;
    cin.ignore();

    hotels.push_back(hotel);
    SaveHotelDetails(hotel);

    cout << "\n\nData Saved Successfully!" << endl;
}

void DeleteHotel()
{
    if (hotels.empty())
    {
        cout << "No hotels available to delete.\n";
        return;
    }

    cout << "Available Hotels:\n";
    for (size_t i = 0; i < hotels.size(); i++)
    {
        cout << i + 1 << ". " << hotels[i].Name << endl;
    }

    int hotelOption;
    cout << "Select a hotel to delete: ";
    cin >> hotelOption;
    cin.ignore();

    if (hotelOption > 0 && hotelOption <= hotels.size())
    {
        hotels.erase(hotels.begin() + (hotelOption - 1));
        ofstream file("HotelDetails.txt", ios::trunc);
        file.close();
        for (const Hotel &hotel : hotels)
        {
            SaveHotelDetails(hotel);
        }
        cout << "Hotel deleted successfully.\n";
    }
    else
    {
        cout << "Invalid option.\n";
    }
}

void ViewHotelDetails(const Hotel &hotel)
{
    cout << "Hotel Name: " << hotel.Name << endl;
    cout << "Address: " << hotel.Address << endl;
    cout << "Customer Care Mob No.: " << hotel.Mob << endl;
    cout << "Food Service Price: " << hotel.FP << endl;

    for (const Room &room : hotel.rooms)
    {
        cout << "Room Type: " << room.Type << " | Available: " << room.Quantity << " | Price: " << room.Price << " | Description: " << room.Description << endl;
    }
    cout << "------------------------------------------------" << endl;
}

int InitializeUserID()
{
    ifstream file("UserID.txt");
    int userID;
    if (file.is_open())
    {
        file >> userID;
        file.close();
    }
    return userID;
}

void SaveUserID(int userID)
{
    ofstream file("UserID.txt", ios::trunc); // Open file in truncate mode to overwrite
    if (file.is_open())
    {
        file << userID << endl;
        file.close();
    }
}

void InitializeUserIDFile()
{
    ifstream file("UserID.txt");
    if (!file.is_open())
    {
        ofstream outFile("UserID.txt");
        if (outFile.is_open())
        {
            outFile << 1000 << endl;
            outFile.close();
        }
    }
}

bool isValidDate(const string &date)
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.length(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            return false;
    }
    return true;
}

void Booking()
{
    if (hotels.empty())
    {
        cout << "No hotels available for booking.\n";
        return;
    }

    cout << "Available Hotels:\n";
    for (size_t i = 0; i < hotels.size(); ++i)
    {
        cout << i + 1 << ". " << hotels[i].Name << endl;
    }

    int hotelOption;
    cout << "Select a hotel to book: ";
    cin >> hotelOption;
    cin.ignore();

    if (hotelOption <= 0 || hotelOption > hotels.size())
    {
        cout << "Invalid hotel selection.\n";
        return;
    }

    Hotel &selectedHotel = hotels[hotelOption - 1];

    InitializeUserIDFile(); // Ensure the UserID file is initialized
    int userID = InitializeUserID();
    User user;
    Price price;

    user.UserID = userID;

    cout << "Enter Your Name: ";
    cin.ignore();
    getline(cin, user.Name);
    cout << "Enter Your Aadhaar No.: ";
    cin >> user.Adhar;
    while (to_string(user.Adhar).length() != 12)
    {
        cout << "Invalid Aadhaar No. Please enter a 12-digit Aadhaar number: ";
        cin >> user.Adhar;
    }
    cout << "Enter Mob No.: ";
    cin >> user.Mob;
    while (to_string(user.Mob).length() != 10)
    {
        cout << "Invalid Mob No. Please enter a 10-digit mobile number: ";
        cin >> user.Mob;
    }
    cout << "Food Service (Y/N): ";
    cin >> user.Food_option;

    while (user.Food_option != 'Y' && user.Food_option != 'y' && user.Food_option != 'N' && user.Food_option != 'n')
    {
        cout << "Invalid input. Please enter 'Y' or 'N' for Food Service: ";
        cin >> user.Food_option;
    }

    cout << "Enter Room Type (e.g., Deluxe, Suite): ";
    cin.ignore();
    getline(cin, user.Bed_option);

    bool validRoomType = false;
    for (const Room &room : selectedHotel.rooms)
    {
        if (room.Type == user.Bed_option)
        {
            validRoomType = true;
            break;
        }
    }
    while (!validRoomType)
    {
        cout << "Invalid Room Type. Please enter a valid room type (e.g., Deluxe, Suite): ";
        getline(cin, user.Bed_option);
        for (const Room &room : selectedHotel.rooms)
        {
            if (room.Type == user.Bed_option)
            {
                validRoomType = true;
                break;
            }
        }
    }

    cout << "Enter Days to Stay: ";
    cin >> user.Days;
    cout << "Enter Booking Date (YYYY-MM-DD): ";
    cin.ignore();
    getline(cin, user.Date);

    while (!isValidDate(user.Date))
    {
        cout << "Invalid date format. Please enter the date in YYYY-MM-DD format: ";
        getline(cin, user.Date);
    }

    user.Totalprice = price.DisplayPrice(user.Bed_option, user.Food_option, user.Days, selectedHotel.FP);
    cout << "Total Price: " << user.Totalprice << endl;

    bool roomUpdated = false;
    for (Room &room : selectedHotel.rooms)
    {
        if (room.Type == user.Bed_option)
        {
            if (room.Quantity > 0)
            {
                room.Quantity--;
                roomUpdated = true;
            }
            else
            {
                cout << "Sorry, no " << room.Type << " rooms available." << endl;
                return;
            }
        }
    }

    if (!roomUpdated)
    {
        cout << "Room type not found. Please try again." << endl;
        return;
    }

    ofstream roomFile("Room.txt", ios::app);
    for (const Room &room : selectedHotel.rooms)
    {
        roomFile << room.Type << "\n"
                 << room.Quantity << "\n";
    }
    roomFile.close();

    ofstream file("UserData.txt", ios::app);
    file << user.UserID << "\n";
    file << user.Name << "\n";
    file << user.Adhar << "\n";
    file << user.Mob << "\n";
    file << user.Food_option << "\n";
    file << user.Bed_option << "\n";
    file << user.Days << "\n";
    file << user.Date << "\n";
    file << user.Totalprice << "\n";
    file.close();

    cout << "Booking completed successfully!\n";
    cout << "\nBooking Summary:\n";
    cout << "Hotel: " << selectedHotel.Name << "\n";
    cout << "Room Type: " << user.Bed_option << "\n";
    cout << "Total Price: " << user.Totalprice << "\n";
    cout << "Days: " << user.Days << "\n";
    cout << "Booking Date (yyyy-mm-dd): " << user.Date << "\n";
    cout << "Your User ID: " << user.UserID << "\n\n";
    cout << "Please keep your User ID safe for future reference.\n";
    cout << "If you have any questions, feel free to contact our customer care at " << selectedHotel.Mob << ".\n";
    cout << "Additional Information: \n";
    cout << "1. Check-in time: 2 PM\n";
    cout << "2. Check-out time: 12 PM\n";
    cout << "3. Breakfast is complimentary\n";
    cout << "4. Free cancellation within 24 hours of booking\n";
    cout << "5. For any issues, contact: support@hotelbooking.com\n";
    cout << "6. Enjoy your stay at " << selectedHotel.Name << "!\n";

    SaveUserID(userID + 1); // Save the incremented UserID
}

void DisplayAllUsers()
{
    ifstream file("UserData.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Error opening UserData.txt" << endl;
        return;
    }

    User user;
    int n = 1;
    while (file >> user.UserID)
    {
        file.ignore();
        getline(file, user.Name);
        file >> user.Adhar;
        file >> user.Mob;
        file >> user.Food_option;
        file.ignore();
        getline(file, user.Bed_option);
        file >> user.Days;
        file.ignore();
        getline(file, user.Date);
        file >> user.Totalprice;

        cout << "\n Customer -> " << n << "\n";
        cout << "\tID: " << user.UserID << endl;
        cout << "\tName: " << user.Name << endl;
        cout << "\tAadhaar No.: " << user.Adhar << endl;
        cout << "\tMob No.: " << user.Mob << endl;
        cout << "\tFood Option: " << user.Food_option << endl;
        cout << "\tRoom Type: " << user.Bed_option << endl;
        cout << "\tDays: " << user.Days << endl;
        cout << "\tBooking Date: " << user.Date << endl;
        cout << "\tTotal Price: " << user.Totalprice << endl;

        n++;
    }
    file.close();

    cout << "Total Users Displayed: " << n - 1 << endl;
}

void ApproveRoom()
{
    int UserID;
    cout << "\nEnter Customer ID: ";
    cin >> UserID;

    ifstream file;
    User user;
    bool found = false;

    file.open("UserData.txt", ios::in);
    if (!file.good())
    {
        cout << " No Data Available... ";
        return;
    }
    while (file >> user.UserID >> user.Name >> user.Adhar >> user.Mob >> user.Food_option >> user.Bed_option >> user.Days >> user.Date >> user.Totalprice)
    {
        file.ignore();
        if (user.UserID == UserID)
        {
            found = true;
            cout << "\n\n-----------------------------------------------------------------";
            cout << "\n                             RECORD                                ";
            std::cout << "\n\n------------------------------------------------------------------\n\n";

            cout << "Customer Information - \n\n";
            cout << " Name: " << user.Name << endl;
            cout << " Aadhaar No.: " << user.Adhar << endl;
            if (to_string(user.Mob).length() == 10)
            {
                cout << " Mob No.: " << user.Mob << endl;
            }
            else
            {
                cout << " Mob No.: Invalid (not a 10-digit number)" << endl;
            }
            cout << " Food Option: " << user.Food_option << std::endl;
            cout << " Room Type: " << user.Bed_option << endl;
            cout << " Days: " << user.Days << endl;
            cout << " Booking Date: " << user.Date << endl;
            cout << " Total Price: " << user.Totalprice << endl;

            ofstream File;
            File.open("Allotment.txt", ios::app);
            if (!File.is_open())
            {
                cout << "\n\nError opening file. " << endl;
                return;
            }

            int RoomNo;
            cout << "\nEnter Room No. to Allot: ";
            cin >> RoomNo;

            while (RoomNo <= 0)
            {
                cout << "Invalid Room No. Please enter a valid room number: ";
                cin >> RoomNo;
            }

            cout << "Room Allotted Successfully! " << endl;

            File << RoomNo << "\n"
                 << user.UserID << "\n"
                 << user.Name << "\n"
                 << user.Totalprice << "\n"
                 << user.Bed_option << "\n";
            File.close();
            break;
        }
    }

    if (!found)
    {
        cout << "\n\nRecord with User ID " << UserID << " not found." << endl;
    }

    file.close();
}

void CheckBooking()
{
    User user;
    ifstream file("UserData.txt", ios::in);

    int userID;
    cout << "Enter Your User ID : ";
    cin >> userID;

    bool found = false;
    while (file >> user.UserID)
    {
        file.ignore();
        getline(file, user.Name);
        file >> user.Adhar;
        file >> user.Mob;
        file >> user.Food_option;
        file.ignore();
        getline(file, user.Bed_option);
        file >> user.Days;
        file.ignore();
        getline(file, user.Date);
        file >> user.Totalprice;

        if (user.UserID == userID)
        {
            found = true;
            cout << "Great! Your Room is allotted.\n"
                 << endl;
            cout << "Room Type: " << user.Bed_option << endl;
            cout << "Total Price: " << user.Totalprice << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Invalid User ID or Your Application is pending.\n";
    }

    file.close();
}

void SearchUser()
{
    int UserID;
    cout << "\nEnter Customer ID: ";
    cin >> UserID;

    ifstream file("UserData.txt");
    User user;
    bool found = false;

    if (!file.is_open())
    {
        cout << " No Data Available... ";
        return;
    }

    while (file >> user.UserID >> user.Name >> user.Adhar >> user.Mob >> user.Food_option >> user.Bed_option >> user.Days >> user.Date >> user.Totalprice)
    {
        if (user.UserID == UserID)
        {
            found = true;
            cout << "\n\n-----------------------------------------------------------------------------------";
            cout << "\n                                        RECORD                                       ";
            cout << "\n\n-----------------------------------------------------------------------------------\n\n";

            cout << "Customer Information - \n\n";
            cout << " Name: " << user.Name << endl;
            cout << " Aadhaar No.: " << user.Adhar << endl;
            cout << " Mob No.: " << user.Mob << endl;
            cout << " Food Option: " << user.Food_option << endl;
            cout << " Room Type: " << user.Bed_option << endl;
            cout << " Days: " << user.Days << endl;
            cout << " Booking Date: " << user.Date << endl;
            cout << " Total Price: " << user.Totalprice << endl;
        }
    }

    if (!found)
    {
        cout << "\n\nRecord with User ID " << UserID << " not found." << endl;
    }

    file.close();
}

void CheckCancelList()
{
    ifstream file("CancelData.txt", ios::in);
    if (!file.good())
    {
        cout << "No Data Available... ";
        return;
    }

    User user;
    int RoomNo;
    char Cancel[7];
    string reason;
    double cancelFee;

    int n = 1;

    while (!file.eof())
    {
        file >> RoomNo;
        file >> user.UserID;
        file >> user.Name;
        file >> Cancel;
        file >> reason;
        file >> cancelFee;

        cout << "\nCustomer -> " << n << "\n";
        cout << "\tRoom No.: " << RoomNo << endl;
        cout << "\tID: " << user.UserID << endl;
        cout << "\tName: " << user.Name << endl;
        cout << "\tCancelled: " << Cancel << endl;
        cout << "\tReason: " << reason << endl;
        cout << "\tCancellation Fee: " << cancelFee << endl;

        // Additional details
        cout << "\tCancellation Date: " << __DATE__ << endl; // Adding current date as cancellation date
        cout << "\tCancellation Time: " << __TIME__ << endl; // Adding current time as cancellation time
        cout << "\tProcessed by: System Admin" << endl;      // Adding a placeholder for processed by

        n++;
    }
    file.close();

    cout << "\nTotal number of cancellations: " << n - 1 << endl;
    cout << "End of cancellation list.\n"; // Adding end of list message
}

void AvailableRooms()
{
    ifstream file;
    file.open("Room.txt", ios::in);

    if (!file.is_open())
    {
        cout << "No Data Available..." << endl;
        return;
    }
    else
    {
        rooms.clear();

        while (!file.eof())
        {
            Room room;
            file >> room.Type >> room.Quantity;
            rooms.push_back(room);
        }
        file.close();

        if (rooms.empty())
        {
            cout << "No rooms available at the moment." << endl;
            return;
        }

        cout << "Available Rooms:\n\n";
        for (const Room &room : rooms)
        {
            cout << "Room Type: " << room.Type << " | Available: " << room.Quantity << endl;
        }

        DisplayAdditionalRoomDetails();
        SortRooms();

        cout << "\nSorted Available Rooms:\n\n";
        for (const Room &room : rooms)
        {
            cout << "Room Type: " << room.Type << " | Available: " << room.Quantity << endl;
        }

        FilterRoomsByType();
    }
}

void DisplayAdditionalRoomDetails()
{
    cout << "\nRoom Details:\n";
    for (const Room &room : rooms)
    {
        cout << "Type: " << room.Type << endl;
        cout << "Quantity: " << room.Quantity << endl;
        cout << "---------------------------------" << endl;
    }
}

void SortRooms()
{
    sort(rooms.begin(), rooms.end(), [](const Room &a, const Room &b)
         {
        if (a.Type != b.Type)
        {
            return a.Type < b.Type;
        }
        return a.Quantity < b.Quantity; });
}

void FilterRoomsByType()
{
    string filterType;
    cout << "\nEnter room type to filter (or 'all' to show all rooms): ";
    getline(cin, filterType);

    if (filterType == "all")
    {
        cout << "\nAll Available Rooms:\n\n";
        for (const Room &room : rooms)
        {
            cout << "Room Type: " << room.Type << " | Available: " << room.Quantity << endl;
        }
    }
    else
    {
        cout << "\nFiltered Available Rooms for type '" << filterType << "':\n\n";
        for (const Room &room : rooms)
        {
            if (room.Type == filterType)
            {
                cout << "Room Type: " << room.Type << " | Available: " << room.Quantity << endl;
            }
        }
    }
}

void CancleBooking()
{
    int userID;
    cout << "Enter your User ID to cancel booking: ";
    cin >> userID;

    ifstream userFile("UserData.txt");
    ofstream tempUserFile("TempUserData.txt");
    bool found = false;
    User user;

    // Remove booking from UserData.txt
    while (userFile >> user.UserID >> user.Name >> user.Adhar >> user.Mob >> user.Food_option >> user.Bed_option >> user.Days >> user.Date >> user.Totalprice)
    {
        if (user.UserID == userID)
        {
            found = true;
            cout << "Booking found and cancelled for User ID: " << userID << endl;
        }
        else
        {
            tempUserFile << user.UserID << "\n"
                         << user.Name << "\n"
                         << user.Adhar << "\n"
                         << user.Mob << "\n"
                         << user.Food_option << "\n"
                         << user.Bed_option << "\n"
                         << user.Days << "\n"
                         << user.Date << "\n"
                         << user.Totalprice << "\n";
        }
    }

    userFile.close();
    tempUserFile.close();

    remove("UserData.txt");
    rename("TempUserData.txt", "UserData.txt");

    if (!found)
    {
        cout << "No booking found for User ID: " << userID << endl;
        return;
    }

    // Remove booking from Allotment.txt
    ifstream allotmentFile("Allotment.txt");
    ofstream tempAllotmentFile("TempAllotment.txt");
    int roomNo;
    while (allotmentFile >> roomNo >> user.UserID >> user.Name >> user.Totalprice >> user.Bed_option)
    {
        if (user.UserID != userID)
        {
            tempAllotmentFile << roomNo << "\n"
                              << user.UserID << "\n"
                              << user.Name << "\n"
                              << user.Totalprice << "\n"
                              << user.Bed_option << "\n";
        }
    }

    allotmentFile.close();
    tempAllotmentFile.close();

    remove("Allotment.txt");
    rename("TempAllotment.txt", "Allotment.txt");

    // Add cancelled booking to CancelData.txt
    ofstream cancelFile("CancelData.txt", ios::app);
    if (cancelFile.is_open())
    {
        cancelFile << roomNo << "\n"
                   << user.UserID << "\n"
                   << user.Name << "\n"
                   << "Cancelled" << "\n"
                   << "User requested cancellation" << "\n"
                   << 0.0 << "\n";
        cancelFile.close();
    }
    else
    {
        cout << "Unable to open file to save cancellation details." << endl;
    }

    cout << "Booking successfully cancelled and updated" << endl;
}

void UserDashboard()
{
    int option1;
    do
    {
        cout << "------------------------------------------------\n";
        cout << "                USER DASHBOARD                  \n";
        cout << "------------------------------------------------\n\n";
        cout << "1. View Hotel Details\n";
        cout << "2. Available Rooms\n";
        cout << "3. Book Here!\n";
        cout << "4. Check Status of Booking\n";
        cout << "5. Cancel Your Booking\n";
        cout << "6. Provide Feedback\n";
        cout << "7. Search Hotel by Place or Price\n";
        cout << "8. Exit\n";
        cout << "Select an option: ";
        cin >> option1;
        cin.ignore();

        switch (option1)
        {
        case 1:
            if (hotels.empty())
            {
                cout << "No hotels available.\n";
            }
            else
            {
                cout << "Available Hotels:\n";
                for (size_t i = 0; i < hotels.size(); i++)
                {
                    cout << i + 1 << ". " << hotels[i].Name << endl;
                }
                int hotelOption;
                cout << "Select a hotel to view details: ";
                cin >> hotelOption;
                cin.ignore();
                if (hotelOption > 0 && hotelOption <= hotels.size())
                {
                    ViewHotelDetails(hotels[hotelOption - 1]);
                }
                else
                {
                    cout << "Invalid option.\n";
                }
            }
            break;
        case 2:
            AvailableRooms();
            break;
        case 3:
            Booking();
            break;
        case 4:
            CheckBooking();
            break;
        case 5:
            CancleBooking();
            break;
        case 6:
            ProvideFeedback();
            break;
        case 7:
        {
            string place;
            int maxPrice;
            cout << "Enter place to search hotels: ";
            getline(cin, place);
            cout << "Enter maximum price: ";
            cin >> maxPrice;
            cin.ignore();
            FilterHotelsByPlaceAndPrice(place, maxPrice);
            break;
        }
        case 8:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option. Please select a valid option.\n";
        }
    } while (option1 != 8);
}

void ProvideFeedback()
{
    string feedback;
    cout << "Please provide your feedback: ";
    cin.ignore();
    getline(cin, feedback);
    ofstream feedbackFile("feedback.txt", ios::app);
    if (feedbackFile.is_open())
    {
        feedbackFile << feedback << endl;
        feedbackFile.close();
        cout << "Thank you for your feedback!" << endl;
    }
    else
    {
        cout << "Unable to open file to save feedback." << endl;
    }
}

void UserManagement()
{
    int option;
    do
    {
        cout << "------------------------------------------------\n";
        cout << "                     Admin                       \n";
        cout << "------------------------------------------------\n\n";
        cout << "1. Display All Users\n";
        cout << "2. Search User\n";
        cout << "3. Update User Details\n";
        cout << "4. Exit\n";
        cout << "Select an option: ";
        cin >> option;
        cin.ignore();

        switch (option)
        {
        case 1:
            DisplayAllUsers();
            break;
        case 2:
            SearchUser();
            break;
        case 3:
        {
            int userID;
            cout << "Enter User ID to update details: ";
            cin >> userID;
            UpdateUserDetails(userID);
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option. Please select a valid option.\n";
        }
    } while (option != 4);
}

void UpdateUserDetails(int userID)
{
    ifstream file("UserData.txt");
    ofstream tempFile("TempUserData.txt");
    bool found = false;
    User user;

    while (file >> user.UserID)
    {
        file.ignore();
        getline(file, user.Name);
        file >> user.Adhar;
        file >> user.Mob;
        file >> user.Food_option;
        file.ignore();
        getline(file, user.Bed_option);
        file >> user.Days;
        file.ignore();
        getline(file, user.Date);
        file >> user.Totalprice;

        if (user.UserID == userID)
        {
            found = true;
            cout << "Enter new details -\n";
            cout << "Name: ";
            cin.ignore();
            getline(cin, user.Name);
            cout << "Aadhaar No.: ";
            cin >> user.Adhar;
            cout << "Mob No.: ";
            cin >> user.Mob;
            cout << "Food Option (Y/N): ";
            cin >> user.Food_option;
            cout << "Room Type: ";
            cin.ignore();
            getline(cin, user.Bed_option);
            cout << "Days: ";
            cin >> user.Days;
            cout << "Booking Date (YYYY-MM-DD): ";
            cin.ignore();
            getline(cin, user.Date);
            cout << "Total Price: ";
            cin >> user.Totalprice;
        }

        tempFile << user.UserID << "\n";
        tempFile << user.Name << "\n";
        tempFile << user.Adhar << "\n";
        tempFile << user.Mob << "\n";
        tempFile << user.Food_option << "\n";
        tempFile << user.Bed_option << "\n";
        tempFile << user.Days << "\n";
        tempFile << user.Date << "\n";
        tempFile << user.Totalprice << "\n";
    }

    file.close();
    tempFile.close();

    remove("UserData.txt");
    rename("TempUserData.txt", "UserData.txt");

    if (found)
    {
        cout << "User details updated successfully!\n";
    }
    else
    {
        cout << "User ID not found.\n";
    }
}

// Invalid choice.\n";

hotelreserv()
{
    InitializeUserIDFile();
    LoadHotels();
    int option;

    do
    {
        cout << "------------------------------------------------\n";
        cout << "            Hotel Booking Application           \n";
        cout << "------------------------------------------------\n\n";
        cout << "1. Hotel\n";
        cout << "2. User\n";
        cout << "3. Admin\n";
        cout << "4. Exit\n";
        cout << "Select an option: ";
        cin >> option;
        cin.ignore();

        switch (option)
        {
        case 1:
            HotelDashboard();
            break;
        case 2:
            UserDashboard();
            break;
        case 3:
            UserManagement();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option. Please select a valid option.\n";
        }
    } while (option != 4);

    return 0;
}

// Function for Vehicle Rental
class Cars
{
protected:
    char name[30];
    int ID;      // format 4 digit
    bool booked; // 1 or 0
public:
    void getdata();
    void putdata();
    void modify();
    bool booked_status()
    {
        return booked;
    }
    int get_ID()
    {
        return ID;
    }
    char *get_name()
    {
        return name;
    }
    void bookit()
    {
        this->booked = 1;
    }
    void unbookit()
    {
        this->booked = 0;
    }
} c;
class Login
{
protected:
    char username[100];
    char password[50];
};
class Login_user : public Login
{
public:
    void Register();
    int check_user_existence(char[]);
    void login(char user_n[], char pass[]);
    // display available cars
    int show_hatchback();
    int show_sedan();
    int show_suv();
    int show_luxury();
    // book the available cars
    void book_hatchback();
    void book_sedan();
    void book_suv();
    void book_luxury();
    // invoices
    // void invoice(int);
    void bill(int); // void bill(float,int,char*);
    // do work function
    void do_user_work();
    void unbook();
    int search_car_hatchback(int);
    int search_car_sedan(int);
    int search_car_suv(int);
    int search_car_luxury(int);
};
class Login_admin : public Login
{
public:
    void login_admin(char user_n[], char pass[]);
    // void register_admin();
    void Export_user_data(); // exporting user data to csv
    void Read_user_data();
    // this is file class in original code
    void search_car();
    void delete_c();
    void Export();
    void modify_car();
    void add_car_hatchback();
    void add_car_luxury();
    void add_car_sedan();
    void add_car_suv();
    // display versions
    void display_car_hatchback();
    void display_car_luxury();
    void display_car_sedan();
    void display_car_suv();
    // do work function
    void do_work();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************* STRING OPERATIONS ********************************************/
int str_len(char c[])
{
    int length = 0;
    while (c[length] != '\0')
    {
        length++;
    }
    return length;
}
string conv_to_str(char *a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++)
    {
        s = s + a[i];
    }
    return s;
}
int isSubstring(string s1, string s2)
{
    int M = s1.length();
    int N = s2.length();
    for (int i = 0; i <= N - M; i++)
    { // A loop to slide pat[] one by one
        int j;
        for (j = 0; j < M; j++) // For current index i, check for pattern match
            if (s2[i + j] != s1[j])
                break;
        if (j == M)
            return i;
    }
    return -1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************CAR CLASS FUNCTIONS****************************************************/
void Cars::getdata()
{
    cout << "Enter name of car: ";
    scanf(" %[^\n]s", name);
    while (1)
    {
        cout << "Enter ID of the car: ";
        cin >> ID;
        if (ID / 10000 == 0 && ID / 1000 != 0)
            break;
        else
            cout << "4 Digit please" << endl;
    }
    while (1)
    {
        cout << "Booked status(1 for yes/0 for no): ";
        cin >> booked;
        if (booked == 1 || booked == 0)
            break;
        else
            cout << "Enter (1 for yes/0 for no)" << endl;
    }
}
void Cars::putdata()
{
    if (booked == 1)
        cout << "\t" << "|" << setw(20) << name << " |" << setw(5) << ID << " |" << setw(4) << "Yes" << " |" << endl;
    else
        cout << "\t" << "|" << setw(20) << name << " |" << setw(5) << ID << " |" << setw(4) << "No" << " |" << endl;
}
void Cars::modify() // function to modify the records
{
    int ch;
    cout << "Current details are" << endl;
    putdata();
    cout << "Modify:\n 1.Name\n 2.ID\n 3.Booked?\n 4.All\n Your choie: ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        cout << "Enter new name of the Car: ";
        cin >> name;
        break;
    case 2:
        cout << "Enter new ID: ";
        cin >> ID;
        break;
    case 3:
        cout << "Booking status?(1 for yes/0 for no): ";
        cin >> booked;
        break;
    case 4:
        getdata();
        break;
    default:
        cout << "Wrong option selected, refer menu" << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************LOGIN ADMIN CODES****************************************************/
void Login_admin::login_admin(char user_n[], char pass[])
{
    string name;
    int ch = 0, round = 0;
    ifstream fin("admin_data.txt", ios::in);
    if (!(fin)) // check if the file is empty
    {
        cout << "No admin Data Available!" << endl;
        fin.close();
        return;
    }
    else
    {
        while (fin >> username >> password)
        {
            if (strcmp(user_n, username) == 0 && strcmp(pass, password) == 0)
            {
                name = conv_to_str(user_n, str_len(user_n));
                size_t found = name.find("@cadmin.ac.in");
                cout << "Hello " << name.substr(0, found) << endl;
                round = 1;
                do_work();
            }
            else if (strcmp(user_n, username) == 0)
            {
                cout << "Entered password is incorrect" << endl;
                round = 1;
                /*cout<<"You might want to consider registering(y/n): ";
                cin>>ans;
                if(ans=='y'||ans=='Y'){
                    this->register_admin();
                }
                else{
                    cout<<"Allright see ya!"<<endl;
                }*/
            }
        }
        fin.close();
        if (round == 0)
        {
            cout << "This User does not exist!" << endl;
        }
    }
}
/*void Login_admin :: register_admin()
{
    ofstream fout("admin_data.txt",ios::app);
    cout<<"Enter username(mail): ";
    cin>>username;
    cout<<"Enter your preferred password: ";
    cin>>password;
    fout<<username<<" "<<password<<endl;
    fout.close();
}*/
void Login_admin::Read_user_data()
{
    ifstream fin("login_data.txt", ios::in);
    if (!(fin)) // check if the file is empty
    {
        cout << "No User Data Available!" << endl;
        fin.close();
        return;
    }
    while (fin >> username >> password)
    {
        cout << "|" << setw(20) << username << "|" << setw(10) << password << "|" << endl;
    }
    fin.close();
}
void Login_admin::Export_user_data()
{
    ifstream fin("login_data.txt", ios::in);
    if (!(fin)) // check if the file is empty
    {
        cout << "No User Data Available!" << endl;
        fin.close();
        return;
    }
    ofstream fout("Login_data.csv", ios::out);
    fout << "USERNAME" << "," << "PASSWORD" << endl;
    while (fin >> username >> password)
    {
        fout << username << "," << password << endl;
    }
    fin.close();
    fout.close();
}
void Login_admin::add_car_hatchback()
{
    char ch = 'y';
    ofstream fout("HATCHBACK.txt", ios::out | ios::app);
    while (ch == 'y' | ch == 'Y')
    {
        c.getdata();
        fout.write((char *)&c, sizeof(c));
        cout << "\nDo you wish to add more(y/n): ";
        cin >> ch;
    }
    cout << "\nData added to file\n"
         << endl;
    fout.close();
}
void Login_admin::add_car_luxury()
{
    char ch = 'y';
    ofstream fout("LUXURY.txt", ios::out | ios::app);
    while (ch == 'y' | ch == 'Y')
    {
        c.getdata();
        fout.write((char *)&c, sizeof(c));
        cout << "\nDo you wish to add more(y/n): ";
        cin >> ch;
    }
    cout << "\nData added to file\n"
         << endl;
    fout.close();
}
void Login_admin::add_car_sedan()
{
    char ch = 'y';
    ofstream fout("SEDAN.txt", ios::out | ios::app);
    while (ch == 'y' | ch == 'Y')
    {
        c.getdata();
        fout.write((char *)&c, sizeof(c));
        cout << "\nDo you wish to add more(y/n): ";
        cin >> ch;
    }
    cout << "\nData added to file\n"
         << endl;
    fout.close();
}
void Login_admin::add_car_suv()
{
    char ch = 'y';
    ofstream fout("SUV.txt", ios::out | ios::app);
    while (ch == 'y' | ch == 'Y')
    {
        c.getdata();
        fout.write((char *)&c, sizeof(c));
        cout << "\nDo you wish to add more(y/n): ";
        cin >> ch;
    }
    cout << "\nData added to file\n"
         << endl;
    fout.close();
}
void Login_admin::display_car_hatchback()
{
    ifstream fin("HATCHBACK.txt", ios::in);
    if (!(fin)) // check if the file is empty
    {
        cout << "No HATCHBACK Data Available!" << endl;
        fin.close();
        return;
    }
    cout << "\t" << "|" << setw(20) << "NAME" << " |" << setw(5) << "ID" << " |" << setw(4) << "BOOKED" << " |\n"
         << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        c.putdata();
        cout << endl;
    }
    fin.close();
}
void Login_admin::display_car_luxury()
{
    ifstream fin("LUXURY.txt", ios::in);
    if (!(fin)) // check if the file is empty
    {
        cout << "No LUXURY Data Available!" << endl;
        fin.close();
        return;
    }
    cout << "\t" << "|" << setw(20) << "NAME" << " |" << setw(5) << "ID" << " |" << setw(4) << "BOOKED" << " |\n"
         << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        c.putdata();
        cout << endl;
    }
    fin.close();
}
void Login_admin::display_car_sedan()
{
    ifstream fin("SEDAN.txt", ios::in);
    if (!(fin)) // check if the file is empty
    {
        cout << "No SEDAN Data Available!" << endl;
        fin.close();
        return;
    }
    cout << "\t" << "|" << setw(20) << "NAME" << " |" << setw(5) << "ID" << " |" << setw(4) << "BOOKED" << " |\n"
         << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        c.putdata();
        cout << endl;
    }
    fin.close();
}
void Login_admin::display_car_suv()
{
    ifstream fin("SUV.txt", ios::in);
    if (!(fin)) // check if the file is empty
    {
        cout << "No SUV Data Available!" << endl;
        fin.close();
        return;
    }
    cout << "\t" << "|" << setw(20) << "NAME" << " |" << setw(5) << "ID" << " |" << setw(4) << "BOOKED" << " |\n"
         << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        c.putdata();
        cout << endl;
    }
    fin.close();
}
void Login_admin::Export()
{
    ofstream fout("cars.csv");
    // writing hatchback file to excel cars file
    ifstream fin1("HATCHBACK.txt", ios::in); // open hatchback
    fout << "HATCHBACK" << endl;
    while (fin1.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 0)
            fout << c.get_name() << "," << c.get_ID() << "," << "Yes" << endl;
        else
            fout << c.get_name() << "," << c.get_ID() << "," << "No" << endl;
    }
    fout << endl;
    fin1.close(); // close hatchback

    // writing Sedan file to excel cars file
    ifstream fin2("SEDAN.txt", ios::in); // open hatchback
    fout << "SEDAN" << endl;
    while (fin2.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 0)
            fout << c.get_name() << "," << c.get_ID() << "," << "Yes" << endl;
        else
            fout << c.get_name() << "," << c.get_ID() << "," << "No" << endl;
    }
    fout << endl;
    fin2.close(); // close Sedan

    // writing Suv file to excel cars file
    ifstream fin3("SUV.txt", ios::in); // open hatchback
    fout << "SUV" << endl;
    while (fin3.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 0)
            fout << c.get_name() << "," << c.get_ID() << "," << "Yes" << endl;
        else
            fout << c.get_name() << "," << c.get_ID() << "," << "No" << endl;
    }
    fout << endl;
    fin3.close(); // close Suv

    // writing luxury file to excel cars file
    ifstream fin4("LUXURY.txt", ios::in); // open hatchback
    fout << "LUXURY" << endl;
    while (fin4.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 0)
            fout << c.get_name() << "," << c.get_ID() << "," << "Yes" << endl;
        else
            fout << c.get_name() << "," << c.get_ID() << "," << "No" << endl;
    }
    fout << endl;
    fin4.close(); // close luxury
    fout.close(); // close the excel file
}
void Login_admin::search_car()
{
    int entered_id;
    char found = 'n';
    cout << "\nEnter the ID to be searched: ";
    cin >> entered_id;
    // searching the hatchback file
    ifstream fin1("HATCHBACK.txt", ios::in);
    while (fin1.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == entered_id)
        {
            c.putdata();
            found = 'y';
        }
    }
    fin1.close();
    if (found == 'y')
    {
        return;
    }

    // searching the sedan file
    ifstream fin2("SEDAN.txt", ios::in);
    while (fin2.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == entered_id)
        {
            c.putdata();
            found = 'y';
        }
    }
    fin2.close();
    if (found == 'y')
    {
        return;
    }

    // searching the suv file
    ifstream fin3("SUV.txt", ios::in);
    while (fin3.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == entered_id)
        {
            c.putdata();
            found = 'y';
        }
    }
    fin3.close();
    if (found == 'y')
    {
        return;
    }

    // searching the luxury file
    ifstream fin4("LUXURY.txt", ios::in);
    while (fin4.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == entered_id)
        {
            c.putdata();
            found = 'y';
        }
    }
    fin4.close();
    if (found == 'n')
    {
        cout << "\nCar of ID " << entered_id << "is not in the file.\n";
    }
    return;
}
void Login_admin::modify_car() // fuction to modify the records of file
{
    int entered_id;
    char found = 'n';
    cout << "\nEnter the ID to be searched: ";
    cin >> entered_id;

    // searching and modifying the hatchback file
    fstream fio1("HATCHBACK.txt", ios::in | ios::out);
    fio1.seekg(0);
    while (!fio1.eof())
    {
        int loc = fio1.tellg(); // storing the current location in loc
        fio1.read((char *)&c, sizeof(c));
        if (c.get_ID() == entered_id)
        {
            c.modify();
            found = 'y';
            fio1.seekg(loc); // moving the pointer to current location
            fio1.write((char *)&c, sizeof(c));
            cout << "\nYour record of ID " << entered_id << " has been updated" << endl;
            break;
        }
    }
    fio1.close();
    if (found == 'y')
    {
        return;
    }

    // searching and modifying the sedan file
    fstream fio2("SEDAN.txt", ios::in | ios::out);
    fio2.seekg(0);
    while (!fio2.eof())
    {
        int loc = fio2.tellg(); // storing the current location in loc
        fio2.read((char *)&c, sizeof(c));
        if (c.get_ID() == entered_id)
        {
            c.modify();
            found = 'y';
            fio2.seekg(loc); // moving the pointer to current location
            fio2.write((char *)&c, sizeof(c));
            cout << "\nYour record of ID " << entered_id << " has been updated" << endl;
        }
    }
    fio2.close();
    if (found == 'y')
    {
        return;
    }

    // searching and modifying the suv file
    fstream fio3("SUV.txt", ios::in | ios::out);
    fio3.seekg(0);
    while (!fio3.eof())
    {
        int loc = fio3.tellg(); // storing the current location in loc
        fio3.read((char *)&c, sizeof(c));
        if (c.get_ID() == entered_id)
        {
            c.modify();
            found = 'y';
            fio3.seekg(loc); // moving the pointer to current location
            fio3.write((char *)&c, sizeof(c));
            cout << "\nYour record of ID " << entered_id << " has been updated" << endl;
        }
    }
    fio3.close();
    if (found == 'y')
    {
        return;
    }

    // searching and modifying the hatchback file
    fstream fio4("LUXURY.txt", ios::in | ios::out);
    fio4.seekg(0);
    while (!fio4.eof())
    {
        int loc = fio4.tellg(); // storing the current location in loc
        fio4.read((char *)&c, sizeof(c));
        if (c.get_ID() == entered_id)
        {
            c.modify();
            found = 'y';
            fio4.seekg(loc); // moving the pointer to current location
            fio4.write((char *)&c, sizeof(c));
            cout << "\nYour record of ID " << entered_id << " has been updated" << endl;
        }
    }
    fio4.close();
    if (found == 'n')
    {
        cout << "\nCar of ID " << entered_id << "is not in the file.\n";
    }
    return;
}
void Login_admin::delete_c() // function to delete the records of file
{
    int entered_id;
    char found = 'n';
    cout << "\nEnter the ID to be deleted: ";
    cin >> entered_id;

    // fstream fio1("HATCHBACK.txt",ios::in|ios::out|ios::app);
    ifstream fin1("HATCHBACK.txt", ios::in);
    ofstream fout1("temp1.txt", ios::out | ios::app);
    while (fin1.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == entered_id)
        {
            found = 'y';
        }
        else
        {
            fout1.write((char *)&c, sizeof(c)); // writing to temp file
        }
    }
    fin1.close();
    fout1.close();
    remove("HATCHBACK.txt");
    rename("temp1.txt", "HATCHBACK.txt");
    if (found == 'y')
    {
        cout << "Record successfully deleted" << endl;
        return;
    }

    // fstream fio2("SEDAN.txt",ios::in|ios::out|ios::app);
    ifstream fin2("SEDAN.txt", ios::in);
    ofstream fout2("temp2.txt", ios::out | ios::app);
    while (fin2.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == entered_id)
        {
            found = 'y';
        }
        else
        {
            fout2.write((char *)&c, sizeof(c)); // writing to temp file
        }
    }
    fin2.close();
    fout2.close();
    remove("SEDAN.txt");
    rename("temp2.txt", "SEDAN.txt");
    if (found == 'y')
    {
        cout << "Record successfully deleted" << endl;
        return;
    }

    // fstream fio3("SUV.txt",ios::in|ios::out|ios::app);
    ifstream fin3("SUV.txt", ios::in);
    ofstream fout3("temp3.txt", ios::out | ios::app);
    while (fin3.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == entered_id)
        {
            found = 'y';
        }
        else
        {
            fout3.write((char *)&c, sizeof(c)); // writing to temp file
        }
    }
    fin3.close();
    fout3.close();
    remove("SUV.txt");
    rename("temp3.txt", "SUV.txt");
    if (found == 'y')
    {
        cout << "Record successfully deleted" << endl;
        return;
    }

    ifstream fin4("LUXURY.txt", ios::in);
    ofstream fout4("temp4.txt", ios::out | ios::app);
    while (fin4.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == entered_id)
        {
            found = 'y';
        }
        else
        {
            fout4.write((char *)&c, sizeof(c)); // writing to temp file
        }
    }
    fin4.close();
    fout4.close();
    remove("LUXURY.txt");
    rename("temp4.txt", "LUXURY.txt");
    if (found == 'y')
    {
        cout << "Record successfully deleted" << endl;
        return;
    }
    else
    {
        cout << "Record not found" << endl;
    }
}
void Login_admin::do_work()
{
    int ch, op;
    int choose;
    do
    {
        cout << "\nChoose option \n 1.Add Data \n 2.Display Data \n 3.Search Data \n 4.Modify Data \n 5.Delete Data\n 6.Export Car data\n 7.To see all the users\n 8.Export user data\n 9.Exit" << endl;
        cout << "Enter choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Add Car Data\n";
            cout << "Enter\n 1.Hatchback\n 2.Sedan\n 3.SUV\n 4.Luxury\n Your choice: ";
            cin >> choose;
            switch (choose)
            {
            case 1:
                add_car_hatchback();
                break;
            case 2:
                add_car_sedan();
                break;
            case 3:
                add_car_suv();
                break;
            case 4:
                add_car_luxury();
                break;
            default:
                cout << "Wrong option selected" << endl;
            }
            break;
        case 2:
            choose = 0;
            cout << "Display Record\n";
            cout << "Enter\n 1.Hatchback\n 2.Sedan\n 3.SUV\n 4.Luxury\n 5.All\n Your choice: ";
            cin >> choose;
            switch (choose)
            {
            case 1:
                display_car_hatchback();
                break;
            case 2:
                display_car_sedan();
                break;
            case 3:
                display_car_suv();
                break;
            case 4:
                display_car_luxury();
                break;
            case 5:
                display_car_hatchback();
                display_car_sedan();
                display_car_suv();
                display_car_luxury();
                break;
            default:
                cout << "Wrong option selected" << endl;
            }
            break;
        case 3:
            cout << "Search Record\n";
            search_car();
            break;
        case 4:
            cout << "Modify Record\n";
            modify_car();
            break;
        case 5:
            cout << "Delete Record\n";
            delete_c();
            break;
        case 6:
            cout << "Export car data in process" << endl;
            Export();
            break;
        case 7:
            cout << "User Data" << endl;
            Read_user_data();
            break;
        case 8:
            cout << "Export file in process" << endl;
            Export_user_data();
            break;
        case 9:
            cout << "Thank You for using the program :)" << endl;
            break;
        default:
            cout << "Wrong choice\n";
        }
    } while (ch != 9);
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/****************************************** LOGIN USER CODES **************************************************/
int Login_user::check_user_existence(char uname[])
{
    int flag = 0;
    ifstream fin("login_data.txt", ios::in);
    while (fin >> username >> password)
    {
        if (strcmp(uname, username) == 0)
        {
            flag = 1;
        }
    }
    fin.close();
    if (flag == 1)
    {
        return 1;
    }
    return 0;
}
void Login_user ::Register()
{
    char new_name[100];
    char pass[50];
    int val;
    ofstream fout("login_data.txt", ios::app);
    do
    {
        cout << "Enter username(mail): ";
        cin >> new_name;
        // check username exists or not
        val = check_user_existence(new_name);
        if (val == 1)
        {
            cout << "Username already exists use another one " << endl;
        }
    } while (val == 1);
    cout << "Enter your preferred password: ";
    cin >> pass;
    fout << new_name << " " << pass << endl;
    fout.close();
}
int Login_user ::show_hatchback()
{
    ifstream fin("HATCHBACK.txt", ios::in);
    if (!(fin)) // check if the file is empty
    {
        cout << "No HATCHBACK Data Available!" << endl;
        fin.close();
        return 1;
    }
    cout << "\tFORMAT" << endl;
    cout << "\t" << "|" << setw(20) << "NAME" << " |" << setw(5) << "ID" << " |" << setw(4) << "BOOKED" << " |" << endl;
    cout << "\n\tAvailable hatchback cars are\n"
         << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 0)
        {
            c.putdata();
        }
    }
    fin.close();
    fin.open("HATCHBACK.txt", ios::in);
    cout << "\n\tUnvailable hatchback cars are\n"
         << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 1)
        {
            c.putdata();
        }
    }
    fin.close();
    return 0;
}
int Login_user ::show_sedan()
{
    ifstream fin("SEDAN.txt", ios::in);
    if (!(fin)) // check if the file is empty
    {
        cout << "No SEDAN Data Available!" << endl;
        fin.close();
        return 1;
    }
    cout << "FORMAT" << endl;
    cout << "\t" << "|" << setw(20) << "NAME" << " |" << setw(5) << "ID" << " |" << setw(4) << "BOOKED" << " |" << endl;
    cout << "Available SEDAN cars are" << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 0)
        {
            c.putdata();
        }
    }
    fin.close();
    fin.open("SEDAN.txt", ios::in);
    cout << "\nUnvailable SEDAN cars are" << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 1)
        {
            c.putdata();
        }
    }
    fin.close();
    return 0;
}
int Login_user ::show_suv()
{
    ifstream fin("SUV.txt", ios::in);
    if (!(fin)) // check if the file is empty
    {
        cout << "No SUV Data Available!" << endl;
        fin.close();
        return 1;
    }
    cout << "FORMAT" << endl;
    cout << "\t" << "|" << setw(20) << "NAME" << " |" << setw(5) << "ID" << " |" << setw(4) << "BOOKED" << " |" << endl;
    cout << "Available SUV cars are" << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 0)
        {
            c.putdata();
        }
    }
    fin.close();
    fin.open("SUV.txt", ios::in);
    cout << "\nUnvailable SUV cars are" << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 1)
        {
            c.putdata();
        }
    }
    fin.close();
    return 0;
}
int Login_user ::show_luxury()
{
    ifstream fin("LUXURY.txt", ios::in);
    if (!(fin)) // check if the file is empty
    {
        cout << "No LUXURY Data Available!" << endl;
        fin.close();
        return 1;
    }
    cout << "FORMAT" << endl;
    cout << "\t" << "|" << setw(20) << "NAME" << " |" << setw(5) << "ID" << " |" << setw(4) << "BOOKED" << " |" << endl;
    cout << "Available LUXURY cars are" << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 0)
        {
            c.putdata();
        }
    }
    fin.close();
    fin.open("LUXURY.txt", ios::in);
    cout << "\nUnvailable LUXURY cars are" << endl;
    while (fin.read((char *)&c, sizeof(c)))
    {
        if (c.booked_status() == 1)
        {
            c.putdata();
        }
    }
    fin.close();
    return 0;
}
void Login_user ::book_hatchback()
{
    int car_to_book;
    char found = 'n';
    int check;
    do
    {
        cout << "Enter the ID of car to book: ";
        cin >> car_to_book;
        check = search_car_hatchback(car_to_book);
        if (check == 0)
        {
            cout << "ID is wrong :( refer menu" << endl;
        }
    } while (check == 0);
    fstream fio("HATCHBACK.txt", ios::in | ios::out);
    // check valid id
    fio.seekg(0);
    while (!fio.eof())
    {
        int loc = fio.tellg();
        fio.read((char *)&c, sizeof(c));
        if (c.get_ID() == car_to_book && c.booked_status() == 0)
        {
            c.bookit();
            found = 'y';
            fio.seekg(loc);
            fio.write((char *)&c, sizeof(c));
        }
        else if (c.get_ID() == car_to_book && c.booked_status() == 1)
        {
            cout << "Sorry its Already booked" << endl;
            found = 'y';
        }
    }
    fio.close();
    if (found == 'n')
    {
        cout << "Not Available!" << endl;
        return;
    }
    else if (found == 'y')
    {
        // invoice function
        cout << "You've chosen a hatchback car" << endl;
        bill(car_to_book); // this->invoice(car_to_book,name_of_car);
        // cout<<"Thank You for Booking!"<<endl;
        return;
    }
}
void Login_user ::book_sedan()
{
    int car_to_book;
    char found = 'n';
    int check;
    do
    {
        cout << "Enter the ID of car to book: ";
        cin >> car_to_book;
        check = search_car_sedan(car_to_book);
        if (check == 0)
        {
            cout << "ID is wrong :( refer menu" << endl;
        }
    } while (check == 0);
    fstream fio("SEDAN.txt", ios::in | ios::out);
    fio.seekg(0);
    while (!fio.eof())
    {
        int loc = fio.tellg();
        fio.read((char *)&c, sizeof(c));
        if (c.get_ID() == car_to_book && c.booked_status() == 0)
        {
            c.bookit();
            found = 'y';
            fio.seekg(loc);
            fio.write((char *)&c, sizeof(c));
        }
        else if (c.get_ID() == car_to_book && c.booked_status() == 1)
        {
            cout << "Sorry its Already booked" << endl;
            found = 'y';
        }
    }
    fio.close();
    if (found == 'n')
    {
        cout << "Not Available!" << endl;
        return;
    }
    else if (found == 'y')
    {
        // invoice function
        cout << "You've chosen a sedan car" << endl;
        bill(car_to_book);
        // cout<<"Thank You for Booking!"<<endl;
        return;
    }
}
void Login_user ::book_suv()
{
    int car_to_book;
    char found = 'n';
    int check;
    do
    {
        cout << "Enter the ID of car to book: ";
        cin >> car_to_book;
        check = search_car_suv(car_to_book);
        if (check == 0)
        {
            cout << "ID is wrong :( refer menu" << endl;
        }
    } while (check == 0);
    fstream fio("SUV.txt", ios::in | ios::out);
    fio.seekg(0);
    while (!fio.eof())
    {
        int loc = fio.tellg();
        fio.read((char *)&c, sizeof(c));
        if (c.get_ID() == car_to_book && c.booked_status() == 0)
        {
            c.bookit();
            found = 'y';
            fio.seekg(loc);
            fio.write((char *)&c, sizeof(c));
        }
        else if (c.get_ID() == car_to_book && c.booked_status() == 1)
        {
            cout << "Sorry its Already booked" << endl;
            found = 'y';
        }
    }
    fio.close();
    if (found == 'n')
    {
        cout << "Not Available!" << endl;
        return;
    }
    else if (found == 'y')
    {
        // invoice function
        cout << "You've chosen a SUV car" << endl;
        bill(car_to_book);
        return;
    }
}
void Login_user ::book_luxury()
{
    int car_to_book;
    char found = 'n';
    int check;
    do
    {
        cout << "Enter the ID of car to book: ";
        cin >> car_to_book;
        check = search_car_luxury(car_to_book);
        if (check == 0)
        {
            cout << "ID is wrong :( refer menu" << endl;
        }
    } while (check == 0);
    fstream fio("LUXURY.txt", ios::in | ios::out);
    fio.seekg(0);
    while (!fio.eof())
    {
        int loc = fio.tellg();
        fio.read((char *)&c, sizeof(c));
        if (c.get_ID() == car_to_book && c.booked_status() == 0)
        {
            c.bookit();
            found = 'y';
            fio.seekg(loc);
            fio.write((char *)&c, sizeof(c));
        }
        else if (c.get_ID() == car_to_book && c.booked_status() == 1)
        {
            cout << "Sorry its Already booked" << endl;
            found = 'y';
        }
    }
    fio.close();
    if (found == 'n')
    {
        cout << "Not Available!" << endl;
        return;
    }
    else if (found == 'y')
    {
        // invoice function
        cout << "You've chosen a Luxury car" << endl;
        bill(car_to_book);
        return;
    }
}
void Login_user::unbook()
{
    char *name_of_car;
    int id_car;
    do
    {
        cout << "Enter the ID of car you want to submit: ";
        cin >> id_car;
        if (id_car / 10000 != 0 && id_car / 1000 == 0)
        {
            cout << "ID is of 4 digit please check your bill" << endl;
        }
    } while (id_car / 10000 != 0 && id_car / 1000 == 0);
    char found = 'n';
    fstream fio1("HATCHBACK.txt", ios::in | ios::out);
    fio1.seekg(0);
    while (!fio1.eof())
    {
        int loc = fio1.tellg();
        fio1.read((char *)&c, sizeof(c));
        if (c.get_ID() == id_car && c.booked_status() == 1)
        {
            c.unbookit();
            name_of_car = c.get_name();
            found = 'y';
            fio1.seekg(loc);
            fio1.write((char *)&c, sizeof(c));
        }
        else if (c.get_ID() == id_car && c.booked_status() == 0)
        {
            name_of_car = c.get_name();
            cout << "This ID is of " << name_of_car << "\nPlease enter the correct ID of Your car" << endl;
            found = 'j';
        }
    }
    fio1.close();
    if (found == 'j')
    {
        return;
    }
    if (found == 'y')
    {
        cout << "Hope You liked Our Hatchback Car - " << name_of_car << " :)" << endl;
        cout << "Thank You for using our services!!" << endl;
        return;
    }

    fstream fio2("SEDAN.txt", ios::in | ios::out);
    fio2.seekg(0);
    while (!fio2.eof())
    {
        int loc = fio2.tellg();
        fio2.read((char *)&c, sizeof(c));
        if (c.get_ID() == id_car && c.booked_status() == 1)
        {
            c.unbookit();
            name_of_car = c.get_name();
            found = 'y';
            fio2.seekg(loc);
            fio2.write((char *)&c, sizeof(c));
        }
        else if (c.get_ID() == id_car && c.booked_status() == 0)
        {
            name_of_car = c.get_name();
            cout << "This ID is of " << name_of_car << "\nPlease enter the correct ID of Your car" << endl;
            found = 'j';
        }
    }
    fio2.close();
    if (found == 'j')
    {
        return;
    }
    if (found == 'y')
    {
        cout << "Hope You liked Our Sedan Car - " << name_of_car << " :)" << endl;
        cout << "Thank You for using our services!!" << endl;
        return;
    }

    fstream fio3("SUV.txt", ios::in | ios::out);
    fio3.seekg(0);
    while (!fio3.eof())
    {
        int loc = fio3.tellg();
        fio3.read((char *)&c, sizeof(c));
        if (c.get_ID() == id_car)
        {
            c.unbookit();
            name_of_car = c.get_name();
            found = 'y';
            fio3.seekg(loc);
            fio3.write((char *)&c, sizeof(c));
        }
        else if (c.get_ID() == id_car && c.booked_status() == 0)
        {
            name_of_car = c.get_name();
            cout << "This ID is of " << name_of_car << "\nPlease enter the correct ID of Your car" << endl;
            found = 'j';
        }
    }
    fio3.close();
    if (found == 'j')
    {
        return;
    }
    if (found == 'y')
    {
        cout << "Hope You liked Our SUV Car - " << name_of_car << " :)" << endl;
        cout << "Thank You for using our services!!" << endl;
        return;
    }

    fstream fio4("HATCHBACK.txt", ios::in | ios::out);
    fio4.seekg(0);
    while (!fio4.eof())
    {
        int loc = fio4.tellg();
        fio4.read((char *)&c, sizeof(c));
        if (c.get_ID() == id_car)
        {
            c.unbookit();
            name_of_car = c.get_name();
            found = 'y';
            fio4.seekg(loc);
            fio4.write((char *)&c, sizeof(c));
        }
        else if (c.get_ID() == id_car && c.booked_status() == 0)
        {
            name_of_car = c.get_name();
            cout << "This ID is of " << name_of_car << "\nPlease enter the correct ID of Your car" << endl;
            found = 'j';
        }
    }
    fio4.close();
    if (found == 'j')
    {
        return;
    }
    if (found == 'y')
    {
        cout << "Hope You liked Our Luxury Car -  " << name_of_car << " :)" << endl;
        cout << "Thank You for using our services!!" << endl;
        return;
    }
    else if (found == 'n')
    {
        cout << "OOPS! The Car you are submitting does not belong to us!!" << endl;
    }
}
int Login_user::search_car_hatchback(int id_car)
{
    char found = 'n';
    ifstream fio1("HATCHBACK.txt", ios::in);
    while (fio1.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == id_car)
        {
            found = 'y';
        }
    }
    fio1.close();
    if (found == 'y')
    {
        return 1;
    }
    return 0;
}
int Login_user::search_car_sedan(int id_car)
{
    char found = 'n';
    ifstream fio2("SEDAN.txt", ios::in);
    while (fio2.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == id_car)
        {
            found = 'y';
        }
    }
    fio2.close();
    if (found == 'y')
    {
        return 1;
    }
    return 0;
}
int Login_user::search_car_suv(int id_car)
{
    char found = 'n';
    ifstream fio3("SUV.txt", ios::in);
    while (fio3.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == id_car)
        {
            found = 'y';
        }
    }
    fio3.close();
    if (found == 'y')
    {
        return 1;
    }
    return 0;
}
int Login_user::search_car_luxury(int id_car)
{
    char found = 'n';
    ifstream fio4("LUXURY.txt", ios::in);
    while (fio4.read((char *)&c, sizeof(c)))
    {
        if (c.get_ID() == id_car)
        {
            found = 'y';
        }
    }
    fio4.close();
    if (found == 'y')
    {
        return 1;
    }
    return 0;
}
void Login_user::bill(int carid) //(float rate,int carid,char* name_of_car)
{
    int see_car, rate;
    string namethecar;
    int choice, n, bill_id;
    float pay, min_pay, penalty_rate;
    see_car = search_car_hatchback(carid);
    if (see_car == 1)
    {
        rate = 50;
        ifstream fin("HATCHBACK.txt", ios::in);
        while (fin.read((char *)&c, sizeof(c)))
        {
            if (c.get_ID() == carid)
            {
                namethecar = c.get_name();
            }
        }
        fin.close();
    }
    see_car = search_car_sedan(carid);
    if (see_car == 1)
    {
        rate = 75;
        ifstream fin("SEDAN.txt", ios::in);
        while (fin.read((char *)&c, sizeof(c)))
        {
            if (c.get_ID() == carid)
            {
                namethecar = c.get_name();
            }
        }
        fin.close();
    }
    see_car = search_car_suv(carid);
    if (see_car == 1)
    {
        rate = 85;
        ifstream fin("SUV.txt", ios::in);
        while (fin.read((char *)&c, sizeof(c)))
        {
            if (c.get_ID() == carid)
            {
                namethecar = c.get_name();
            }
        }
        fin.close();
    }
    see_car = search_car_luxury(carid);
    if (see_car == 1)
    {
        rate = 220;
        ifstream fin("LUXURY.txt", ios::in);
        while (fin.read((char *)&c, sizeof(c)))
        {
            if (c.get_ID() == carid)
            {
                namethecar = c.get_name();
            }
        }
        fin.close();
    }
    system("cls");
    cout << "Thank You for Booking! Please enter following info" << endl;
    cout << "Enter Time for which you want the car for rent" << endl;
    cout << " (1)Less than a day\n (2)Min 1 whole day\n Your choice: ";
    cin >> choice;
    fstream file1("Invoice.txt", ios::in);
    file1 >> bill_id;
    bill_id = bill_id + 1;
    file1.seekg(0);
    file1 << bill_id;
    file1.close();
    switch (choice)
    {
    case 1:
        // while(1)
        //{
        cout << "Enter number of hours for which u want to get car on rent: ";
        cin >> n;
        // if(n>0&&n<25){break;}
        // else{cout<<"Hrs between [1,24]"<<endl;}
        //}
        pay = n * rate;
        min_pay = 0.3 * pay;
        penalty_rate = 0.1 * rate + rate;
        cout << endl;
        system("cls");
        cout << "************************ BILL ********************************" << endl;
        cout << "|" << setw(30) << "Invoice Number" << "|" << setw(30) << bill_id << endl;
        cout << "|" << setw(30) << "Customer Name" << "|" << setw(30) << username << endl;
        cout << "|" << setw(30) << "Car Name" << "|" << setw(30) << namethecar << endl;
        cout << "|" << setw(30) << "Car ID" << "|" << setw(30) << carid << endl;
        cout << "|" << setw(30) << "Numbers of Hours" << "|" << setw(30) << n << endl;
        cout << "|" << setw(30) << "Total Pay" << "|" << setw(30) << pay << endl;
        cout << "|" << setw(30) << "Advance Pay " << "|" << setw(30) << min_pay << endl;
        cout << "|" << setw(30) << "After use Pay" << "|" << setw(30) << pay - min_pay << endl;
        cout << "|" << setw(30) << "Penalty per hour" << "|" << setw(30) << penalty_rate << endl;
        cout << "***************************************************************" << endl;
        break;
    case 2:
        // while(1)
        //{
        cout << "Enter number of days for which u want to get car on rent(max a month): ";
        cin >> n;
        // if(n>0&&n<32){break;}
        // else{cout<<"Days between [1,31]"<<endl;}
        //}
        pay = n * rate * 18; // 18 = hours driven per day
        min_pay = 0.3 * pay;
        penalty_rate = 0.1 * rate + rate;
        cout << endl;
        system("cls");
        cout << "************************** BILL ******************************" << endl;
        cout << "|" << setw(30) << "Invoice Number" << "|" << setw(30) << bill_id << endl;
        cout << "|" << setw(30) << "Customer Name" << "|" << setw(30) << username << endl;
        cout << "|" << setw(30) << "Car Name" << "|" << setw(30) << namethecar << endl;
        cout << "|" << setw(30) << "Car ID" << "|" << setw(30) << carid << endl;
        cout << "|" << setw(30) << "Numbers of Hours" << "|" << setw(30) << n << endl;
        cout << "|" << setw(30) << "Total Pay" << "|" << setw(30) << pay << endl;
        cout << "|" << setw(30) << "Advance Pay " << "|" << setw(30) << min_pay << endl;
        cout << "|" << setw(30) << "After use Pay" << "|" << setw(30) << pay - min_pay << endl;
        cout << "|" << setw(30) << "Penalty per hour" << "|" << setw(30) << penalty_rate << endl;
        cout << "**************************************************************" << endl;
        break;
    default:
        cout << "Wrong option selected" << endl;
    }
}
void Login_user ::do_user_work()
{
    int choice;
    cout << "Menu\n 1.Book a car\n 2.Submit the car\n Your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        int ch;
        int collect;
        cout << setw(30) << "QUICK INFO" << endl;
        cout << "|" << setw(10) << "TYPE" << " |" << setw(15) << "RATE(per hr)" << " |" << setw(20) << "PENALTY RATE(per hr)" << " |" << endl;
        cout << "|" << setw(10) << "HATCHBACK" << " |" << setw(15) << 50 << " |" << setw(20) << 50 * (0.1) + 50 << " |" << endl;
        cout << "|" << setw(10) << "SEDAN" << " |" << setw(15) << 75 << " |" << setw(20) << 75 * (0.1) + 75 << " |" << endl;
        cout << "|" << setw(10) << "SUV" << " |" << setw(15) << 85 << " |" << setw(20) << 85 * (0.1) + 85 << " |" << endl;
        cout << "|" << setw(10) << "LUXURY" << " |" << setw(15) << 220 << " |" << setw(20) << 220 * (0.1) + 220 << " |" << endl;
        cout << "\nBooking Point\n 1.Hatchback\n 2.Sedan\n 3.Suv\n 4.Luxury\n Your Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            collect = show_hatchback();
            if (collect == 0)
                book_hatchback();
            break;
        case 2:
            collect = show_sedan();
            if (collect == 0)
                book_sedan();
            break;
        case 3:
            collect = show_suv();
            if (collect == 0)
                book_suv();
            break;
        case 4:
            collect = show_luxury();
            if (collect == 0)
                book_suv();
            break;
        default:
            cout << "Seems You selected wrong option" << endl;
        }
        break;
    case 2:
        unbook();
        break;
    }
}
void Login_user ::login(char user_n[], char pass[])
{
    string name;
    int round = 0;
    ifstream fin("login_data.txt", ios::in);
    while (fin >> username >> password)
    {
        if (strcmp(user_n, this->username) == 0 && strcmp(pass, this->password) == 0)
        {
            name = conv_to_str(user_n, str_len(user_n));
            size_t found = name.find("@");
            cout << "Welcome back " << name.substr(0, found) << endl;
            round = 1;
            do_user_work();
        }
        else if (strcmp(user_n, this->username) == 0)
        {
            cout << "Entered Password is incorret" << endl;
            round = 1;
        }
    }

    fin.close();
    if (round == 0)
    {
        char ans;
        cout << "You might want to consider registering(y/n): ";
        cin >> ans;
        if (ans == 'y' || ans == 'Y')
        {
            this->Register();
        }
        else
        {
            cout << "Allright see ya!" << endl;
        }
    }
}

// vehicle renting
vehiclerenting()
{
    Login_user l;
    Login_admin la;
    char username[100], password[50];
    int choosing;
    string user;
    string line;
    ifstream fin("decorate.txt");
    while (getline(fin, line))
    {
        cout << line << endl;
    }
    do
    {
        cout << "\n\t\t\tEnter:\n \t\t\t[1]Login\n \t\t\t[2]User Registeration\n \t\t\t[3]Exit Program\n \t\t\tYour Choice: ";
        cin >> choosing;
        switch (choosing)
        {
        case 1: // login function will seperate the user and admin.
            system("cls");
            cout << "------------------------------------------------------------" << endl;
            cout << "\t\t\tLogin" << endl;
            cout << "------------------------------------------------------------" << endl;
            cout << "\n\tUsername - ";
            cin >> username;
            cout << "\tPassword - ";
            cin >> password;
            user = conv_to_str(username, str_len(username));
            if (isSubstring("@cadmin.ac.in", user) != -1)
            {
                la.login_admin(username, password);
                choosing = 3;
            }
            else
            {
                l.login(username, password);
                choosing = 3;
            }
            break;
        case 2: // user registeration
            l.Register();
            cout << "Thank You For Registering, We won't let you down!" << endl;
            break;
        case 3:
            cout << "Thank You for checking in, Have an Awesome Day!" << endl;
            break;
        default:
            cout << "Wrong option selected please refer menu" << endl;
            exit(1);
        }
    } while (choosing != 3);
    return 0;
}

// Function to handle "Book Seat" option
void bookSeatMenu()
{
    int choice;
    cout << "\n--- Travel Booking Menu ---\n";
    cout << "1. Bus Reservation\n";
    cout << "2. Train Reservation\n";
    cout << "3. Flight Reservation\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        busReservation();
        break;
    case 2:
        trainReservation();
        break;
    case 3:
        flightReservation();
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

// Main menu after login
void reservationMenu()
{
    int choice;
    do
    {
        cout << "\n--- Reservation Menu ---\n";
        cout << "1. Hotel Reservation\n";
        cout << "2. Book Seat\n";
        cout << "3. Vehicle Renting\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            hotelreserv();
            // busReservation();
            break;
        case 2:
            bookSeatMenu();

            // trainReservation();
            break;
        case 3:
            vehiclerenting();
            // flightReservation();
            break;
            // case 4:
            // cout << "Logging out...\n";
            // break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

int main()
{
    int choice;
    do
    {
        cout << "\n--- Welcome to the Reservation System ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            if (loginUser())
            {
                reservationMenu();
            }
            break;
        case 3:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
    return 0;
}
