#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Contact {
private:
    string name;
    string phone;
    string email;

public:
    void addContact();
    void viewContacts();
    void searchContact();
    void deleteContact();
};

// Add new contact
void Contact::addContact() {
    ofstream file("contacts.txt", ios::app);

    cin.ignore();

    cout << "\nEnter Name: ";
    getline(cin, name);

    cout << "Enter Phone Number: ";
    getline(cin, phone);

    cout << "Enter Email: ";
    getline(cin, email);

    file << name << "|" << phone << "|" << email << endl;

    file.close();

    cout << "\nContact Saved Successfully!\n";
}

// View all contacts
void Contact::viewContacts() {
    ifstream file("contacts.txt");

    if (!file) {
        cout << "\nNo contacts found!\n";
        return;
    }

    string line;

    cout << "\n========== CONTACT LIST ==========\n";
    cout << left << setw(25) << "Name"
         << setw(20) << "Phone"
         << setw(30) << "Email" << endl;

    cout << "--------------------------------------------------------------\n";

    while (getline(file, line)) {
        string name, phone, email;

        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);

        name = line.substr(0, pos1);
        phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
        email = line.substr(pos2 + 1);

        cout << left << setw(25) << name
             << setw(20) << phone
             << setw(30) << email << endl;
    }

    file.close();
}

// Search contact
void Contact::searchContact() {
    ifstream file("contacts.txt");

    if (!file) {
        cout << "\nNo contacts found!\n";
        return;
    }

    string searchName;
    string line;
    bool found = false;

    cin.ignore();

    cout << "\nEnter Name to Search: ";
    getline(cin, searchName);

    while (getline(file, line)) {
        string name, phone, email;

        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);

        name = line.substr(0, pos1);
        phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
        email = line.substr(pos2 + 1);

        if (name == searchName) {
            cout << "\nContact Found!\n";
            cout << "Name  : " << name << endl;
            cout << "Phone : " << phone << endl;
            cout << "Email : " << email << endl;

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nContact Not Found!\n";
    }

    file.close();
}

// Delete contact
void Contact::deleteContact() {
    ifstream file("contacts.txt");
    ofstream temp("temp.txt");

    if (!file) {
        cout << "\nNo contacts found!\n";
        return;
    }

    string deleteName;
    string line;
    bool found = false;

    cin.ignore();

    cout << "\nEnter Name to Delete: ";
    getline(cin, deleteName);

    while (getline(file, line)) {
        string name;

        int pos1 = line.find('|');
        name = line.substr(0, pos1);

        if (name == deleteName) {
            found = true;
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if (found) {
        cout << "\nContact Deleted Successfully!\n";
    } else {
        cout << "\nContact Not Found!\n";
    }
}

// Main function
int main() {
    Contact c;
    int choice;

    do {
        cout << "\n\n========= CONTACT MANAGEMENT SYSTEM =========\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            c.addContact();
            break;

        case 2:
            c.viewContacts();
            break;

        case 3:
            c.searchContact();
            break;

        case 4:
            c.deleteContact();
            break;

        case 5:
            cout << "\nThank You for Using Contact Management System!\n";
            break;

        default:
            cout << "\nInvalid Choice! Please Try Again.\n";
        }

    } while (choice != 5);

    return 0;
}