#include "Reader.h"

Reader::Reader(const std::string &username, const std::string &password, const Date &registrationDate) :
        User(username, password,registrationDate),
        numOfItems(0)
        {}

void Reader::print() const {
    std::cout << "Username: " << username << std::endl;
    std::cout << "Taken items:\n";

    for (int i = 0; i < numOfItems; ++i) {
        listOfItems[i]->printInfo();
    }
    std::cout << "Last seen: " << lastSeenDate << std::endl;
}

void Reader::takingItem(LibraryItem *newItem) {
    listOfItems.push_back(newItem);
    numOfItems++;
}




