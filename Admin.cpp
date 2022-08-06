#include "Admin.h"

Admin::Admin(const std::string &username, const std::string &password, const Date &registrationDate,
             const std::string &email, const std::string &sector) :
        User(username, password, registrationDate), email(email), sector(sector) {
    adminRights = true;
}

Admin &Admin::operator=(const Admin &other) {
    if (this != &other) {
        this->username = other.username;
        this->password = other.password;
        this->email = other.email;
        this->sector = other.sector;
    }
    return *this;
}


