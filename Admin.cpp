//
// Created by Lyubo on 6/9/2022.
//
#include "Admin.h"

Admin::Admin(const String &username, const String &password, const String &email, const String &sector) {
    this->username = username;
    this->password = password;
    this->email = email;
    this->sector = sector;
}

void Admin::print() const {
    std::cout << "Username: " << username << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Sector: " << sector << std::endl;
    std::cout << "Last seen: " << lastSeenDate << std::endl;
}

Admin &Admin::operator=(const Admin &other) {
    this->username = other.username;
    this->password = other.password;
    this->email = other.email;
    this->sector = other.sector;

    return *this;
}

