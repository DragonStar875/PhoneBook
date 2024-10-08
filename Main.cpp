#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;

struct personInfo {
    string firstName;
    string lastName;
    long long phoneNumber;
} contact;

void getName() {
    cout << "First Name: ";
    cin >> contact.firstName;
    cout << "Last Name: ";
    cin >> contact.lastName;
}

bool compareNames(const personInfo& a, const personInfo& b) {
    return a.lastName < b.lastName;
}

int main() {
    vector<personInfo> phoneBook;
    int option;
    string line;
    string fileLocation = "C:\\Users\\Public\\Documents\\PhoneBookData.txt";
    char answer;

    cout << "Would you like to retrieve data from a file(y/n)? ";
    cin >> answer;

    while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N') {
        cout << "Invalid input. Please try again: ";
        cin >> answer;
    }

    if (answer == 'y' || answer == 'Y') {
        cout << "Please enter the location of the file: ";
        cin >> fileLocation;
    }

    ifstream inFile(fileLocation);

    while (getline(inFile, contact.firstName)) {
        getline(inFile, contact.lastName);
        getline(inFile, line);
        contact.phoneNumber = stoll(line);
        phoneBook.push_back(contact);
    }

    inFile.close();

    for (;;) {
        cout << "Phone Book Application:\n"
             << "(1) Add friend\n"
             << "(2) Delete friend\n"
             << "(3) Sort phonebook alphabetically\n"
             << "(4) Find a phone number for a given name.\n"
             << "(5) Randomly call someone\n"
             << "(6) Show phonebook\n"
             << "(7) Clear phonebook\n"
             << "(8) Exit\n"
             << "What would you like to do: ";
        cin >> option;

        while (option < 1 || option > 8) {
            cout << "Incorrect input. Please try again.";
            cout << "What would you like to do: ";
            cin >> option;
        }

        switch (option) {
            case 1:  // Add friend
                getName();
                cout << "Phone Number: ";
                cin >> contact.phoneNumber;
                phoneBook.push_back(contact);
                cout << "\nContact added successfully\n\n";
                break;
            case 2:  // Delete contact
                if (phoneBook.empty()) {
                    cout << "Phonebook is empty";
                } else {
                    getName();
                    for (auto i = phoneBook.begin(); i != phoneBook.end();) {
                        if (i->firstName == contact.firstName && i->lastName == contact.lastName) {
                            i = phoneBook.erase(i);
                            cout << "\nContact deleted successfully\n\n";
                        } else {
                            ++i;
                        }
                    }
                }
                break;
            case 3:  // Sort phonebook
                if (phoneBook.empty()) {
                    cout << "Phonebook is empty";
                } else {
                    sort(phoneBook.begin(), phoneBook.end(), compareNames);
                    cout << "\nPhonebook successfully sorted\n\n";
                }
                break;
            case 4:  // Find phone number based on name
                if (phoneBook.empty()) {
                    cout << "Phonebook is empty";
                } else {
                    getName();
                    bool printed = false;
                    for (const auto& i : phoneBook) {
                        if (i.firstName == contact.firstName && i.lastName == contact.lastName) {
                            cout << "\n" << i.firstName << " " << i.lastName << " : " << i.phoneNumber << "\n";
                            printed = true;
                        }
                    }
                    if (!printed) {
                        cout << "Contact not found\n";
                    }
                    cout << "\n";
                }
                break;
            case 5:  // Randomly call someone
                if (phoneBook.empty()) {
                    cout << "Phonebook is empty";
                } else {
                    int random;
                    srand(static_cast<unsigned int>(time(0)));
                    random = rand() % phoneBook.size();
                    cout << "\n" << phoneBook[random].firstName << " " << phoneBook[random].lastName << " : " << phoneBook[random].phoneNumber;
                    cout << "\n\n";
                }
                break;
            case 6:  // Print out the phonebook
                if (phoneBook.empty()) {
                    cout << "\nPhonebook is empty\n\n";
                } else {
                    for (const auto& i : phoneBook) {
                        cout << "\n" << right << setw(10) << i.firstName << " " << left << setw(10) << i.lastName << " : " << i.phoneNumber;
                    }
                    cout << "\n\n";
                }
                break;
            case 7:  // Clear the phonebook
                phoneBook.clear();
                cout << "Phonebook cleared successfully\n\n";
                break;
            case 8:  // Exit
                cout << "Would you like to store the phonebook(y/n): ";
                cin >> answer;

                while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N') {
                    cout << "Invalid input. Please try again.";
                    cin >> answer;
                }

                if (answer == 'y' || answer == 'Y') {
                    cout << "Please enter the location of the file: ";
                    cin >> fileLocation;
                }

                ofstream outFile(fileLocation);

                for (const auto& i : phoneBook) {
                    outFile << i.firstName << "\n";
                    outFile << i.lastName << "\n";
                    outFile << i.phoneNumber << "\n";
                }
                outFile.close();
                return 0;
        }
    }
}
