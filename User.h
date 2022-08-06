#ifndef _USER_H_
#define _USER_H_

#include <fstream>
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

    User(const std::string &username, const std::string &password, const Date &registrationDate);

    virtual ~User() = default;

    bool getAdminRights() const;

    const Date &getLastSeenDate() const;

    std::string get_username() const;

    std::string get_password() const;

    void setLastSeenDate(const Date &newLastSeenDate);

    void set_password(const std::string &newPassword);

    virtual void takingItem(LibraryItem *newItem) {};

    void writeToFile(const std::string &filename) const;


};

#endif