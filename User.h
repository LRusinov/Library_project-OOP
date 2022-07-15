#ifndef _USER_H_
#define _USER_H_

#include "String.h"
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
    username(username),
    password(password),
    registrationDate(registrationDate),
    adminRights(false)
    {}
virtual ~User();

    bool getAdminRights()const{
        return adminRights;
    }
    void setRegistrationDate(const Date &registrationDate) {
        this->registrationDate = registrationDate;
    }

    void setLastSeenDate(const Date &lastSeenDate) {
        this->lastSeenDate = lastSeenDate;
    }

    std::string get_username() const {
        return username;
    }

    std::string get_password() const {
        return password;
    }

    void set_password(const std::string &password) {
        this->password = password;
    }
virtual void takingItem(LibraryItem *newItem){};
    virtual void print() const = 0;

};

User::~User() {}


#endif