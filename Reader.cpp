#include "Reader.h"

Reader::Reader(const String &username, const String &password) {
    this->username = username;
    this->password = password;
    numOfItems = 0;
}

size_t Reader::get_numOfItems() const {
    return numOfItems;
}

void Reader::addItem( LibraryItem *newItem) {
    BooksAndArticles temp(newItem);
    listOfItems.pushBack(reinterpret_cast<BooksAndArticles &>(temp.item));
    numOfItems++;
}

void Reader::print() const {
    std::cout << "Username: " << username << std::endl;
    std::cout << "Taken items:\n";

    for (int i = 0; i < numOfItems; ++i) {
        listOfItems[i].item->printInfo();
    }
    std::cout << "Last seen: " << lastSeenDate << std::endl;
}

Vector<BooksAndArticles> Reader::get_items() const {
    return listOfItems;
}

void Reader::takingItem(LibraryItem *newItem) {
    BooksAndArticles itemToAdd(newItem);
    listOfItems.pushBack(itemToAdd);
    numOfItems++;
}


