#ifndef _READER_H_
#define _READER_H_

#include"Date.h"
#include"Journal.h"

#include "User.h"
#include "Vector.h"


class Reader : public User {
private:
    Vector<BooksAndArticles> listOfItems;
    size_t numOfItems;
public:
    Reader(const String &username, const String &password) {
        this->username = username;
        this->password = password;
        numOfItems = 0;
    }

    size_t get_numOfItems() const {
        return numOfItems;
    }

    void addItem(const LibraryItem *newItem) {
        BooksAndArticles temp(newItem);
        listOfItems.pushBack(reinterpret_cast<BooksAndArticles &>(temp.item));
        numOfItems++;
    }

    void print() const override {
        std::cout << "Username: " << username << std::endl;
        std::cout << "Taken items:\n";

        for (int i = 0; i < numOfItems; ++i) {
            listOfItems[i].item->printInfo();
        }
        std::cout << "Last seen: " << lastSeenDate << std::endl;
    }

    Vector<BooksAndArticles> get_items() const {
        return listOfItems;
    }
};


#endif
