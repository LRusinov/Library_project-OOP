#include "Admin.h"

Admin::Admin(const std::string &username, const std::string &password, const Date &registrationDate,
             const std::string &email, const std::string &sector) :
        User(username, password, registrationDate), email(email), sector(sector) {
    adminRights = true;
}


void Admin::print() const {
    std::cout << "Username: " << username << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Sector: " << sector << std::endl;
    std::cout << "Last seen: " << lastSeenDate << std::endl;
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


