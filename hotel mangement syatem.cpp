#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Hotel {
private:
    int roomNumber;
    string customerName;
    int days;
    float roomCharge;
    float foodCharge;
    float totalBill;

public:
    void bookRoom();
    void displayRecord();
    void saveToFile();
    void readFromFile();
    void checkout();
};

// Function to book room
void Hotel::bookRoom() {
    cout << "\n===== ROOM BOOKING =====\n";

    cout << "Enter Room Number: ";
    cin >> roomNumber;

    cin.ignore();
    cout << "Enter Customer Name: ";
    getline(cin, customerName);

    cout << "Enter Number of Days: ";
    cin >> days;

    cout << "Enter Room Charge Per Day: ";
    cin >> roomCharge;

    cout << "Enter Food Charges: ";
    cin >> foodCharge;

    totalBill = (days * roomCharge) + foodCharge;

    cout << "\nRoom Booked Successfully!\n";
    cout << "Total Bill: Rs. " << totalBill << endl;

    saveToFile();
}

// Function to display customer record
void Hotel::displayRecord() {
    cout << left << setw(15) << roomNumber
         << setw(25) << customerName
         << setw(10) << days
         << setw(15) << totalBill << endl;
}

// Function to save data into file
void Hotel::saveToFile() {
    ofstream file("hotel_records.txt", ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file << roomNumber << "|"
         << customerName << "|"
         << days << "|"
         << roomCharge << "|"
         << foodCharge << "|"
         << totalBill << endl;

    file.close();
}

// Function to read records from file
void Hotel::readFromFile() {
    ifstream file("hotel_records.txt");

    if (!file) {
        cout << "\nNo records found!\n";
        return;
    }

    string line;

    cout << "\n========== HOTEL RECORDS ==========\n";
    cout << left << setw(15) << "Room No"
         << setw(25) << "Customer Name"
         << setw(10) << "Days"
         << setw(15) << "Total Bill" << endl;

    cout << "-------------------------------------------------------------\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// Function for checkout
void Hotel::checkout() {
    int searchRoom;
    bool found = false;

    cout << "\nEnter Room Number for Checkout: ";
    cin >> searchRoom;

    ifstream file("hotel_records.txt");
    ofstream temp("temp.txt");

    string line;

    while (getline(file, line)) {
        size_t pos = line.find('|');
        int room = stoi(line.substr(0, pos));

        if (room == searchRoom) {
            found = true;
            cout << "\nCustomer Checked Out Successfully!\n";
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("hotel_records.txt");
    rename("temp.txt", "hotel_records.txt");

    if (!found) {
        cout << "Room Record Not Found!\n";
    }
}

int main() {
    Hotel h;
    int choice;

    do {
        cout << "\n\n=========== HOTEL MANAGEMENT SYSTEM ===========\n";
        cout << "1. Book Room\n";
        cout << "2. View Records\n";
        cout << "3. Checkout Customer\n";
        cout << "4. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            h.bookRoom();
            break;

        case 2:
            h.readFromFile();
            break;

        case 3:
            h.checkout();
            break;

        case 4:
            cout << "\nThank You for Using Hotel Management System!\n";
            break;

        default:
            cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 4);

    return 0;
}