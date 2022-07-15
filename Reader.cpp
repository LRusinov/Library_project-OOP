#include "Reader.h"

Reader::Reader(const std::string &username, const std::string &password, const Date &registrationDate) :
        User(username, password,registrationDate),
        numOfItems(0)
        {}

size_t Reader::get_numOfItems() const {
    return numOfItems;
}

void Reader::print() const {
    std::cout << "Username: " << username << std::endl;
    std::cout << "Taken items:\n";

    for (int i = 0; i < numOfItems; ++i) {
        listOfItems[i]->printInfo();
    }
    std::cout << "Last seen: " << lastSeenDate << std::endl;
}

std::vector<LibraryItem*> Reader::get_items() const {
    return listOfItems;
}

void Reader::takingItem(LibraryItem *newItem) {
    listOfItems.push_back(newItem);
    numOfItems++;
}

Reader::~Reader() {
    for (int i = 0; i < numOfItems; ++i) {
        delete listOfItems[i];
    }

}




