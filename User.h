#ifndef _USER_H_
#define _USER_H_

#include "String.h"
#include "Date.h"
#include"LibraryItem.h"
#include"Book.h"

struct BooksAndArticles {
public:
    bool isItBook;
    LibraryItem *item;
    Date takingDate;
    Date returnDate;

    BooksAndArticles() {
        item = nullptr;
        isItBook = true;
    }

    explicit BooksAndArticles(const LibraryItem *item) {
        this->item = item->clone();
        if (typeid(&item) == typeid(Book)) {
            isItBook = true;
        } else {
            isItBook = false;
        }
    }

};

class User {
protected:
    String username;
    String password;
    Date registrationDate;
    Date lastSeenDate;
public:
    User() = default;

    void setRegistrationDate(const Date &registrationDate) {
        this->registrationDate = registrationDate;
    }

    void setLastSeenDate(const Date &lastSeenDate) {
        this->lastSeenDate = lastSeenDate;
    }

    String get_username() const {
        return username;
    }

    String get_password() const {
        return password;
    }

    void set_password(const String &password) {
        this->password = password;
    }

    virtual void print() const = 0;
    //virtual Vector<BooksAndArticles> get_items()const=0;

};


#endif