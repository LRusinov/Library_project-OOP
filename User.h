#ifndef _USER_H_
#define _USER_H_

#include "Date.h"
#include"LibraryItem.h"
#include"Book.h"

class User {

protected:
    std::string username;
    std::string password;
    bool adminRights;
    Date registrationDate;
    Date lastSeenDate;

public:
    User() = default;

    User(const std::string &username, const std::string &password, const Date &registrationDate) :
            username(username),password(password),registrationDate(registrationDate),
            lastSeenDate(registrationDate),adminRights(false) {}

    virtual ~User() = default;

    bool getAdminRights() const {
        return adminRights;
    }

    std::string get_username() const {
        return username;
    }

    std::string get_password() const {
        return password;
    }

    void setLastSeenDate(const Date &newLastSeenDate) {
        this->lastSeenDate = newLastSeenDate;
    }

    void set_password(const std::string &newPassword) {
        this->password = newPassword;
    }

    virtual void takingItem(LibraryItem *newItem) {};

    virtual void print() const = 0;

};


#endif