#include "Reader.h"

Reader::Reader(const std::string &username, const std::string &password, const Date &registrationDate) :
        User(username, password, registrationDate), numOfItems(0) {}

void Reader::takingItem(LibraryItem *newItem) {
    listOfItems.push_back(newItem);
    numOfItems++;
}






