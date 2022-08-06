
#include "User.h"

User::User(const std::string &username, const std::string &password, const Date &registrationDate) :
        username(username), password(password), registrationDate(registrationDate),
        lastSeenDate(registrationDate), adminRights(false) {}

bool User::getAdminRights() const {
    return adminRights;
}

const Date &User::getLastSeenDate() const {
    return lastSeenDate;
}

std::string User::get_username() const {
    return username;
}

std::string User::get_password() const {
    return password;
}

void User::setLastSeenDate(const Date &newLastSeenDate) {
    this->lastSeenDate = newLastSeenDate;
}

void User::set_password(const std::string &newPassword) {
    this->password = newPassword;
}

void User::writeToFile(const std::string &filename) const {
    static bool flag = false;
    std::ofstream myFile;
    if (flag) {                             //проверява дали файлът се отваря за първи път
        myFile.open(filename, std::ios::app);
    } else {
        myFile.open(filename, std::ios::out);

    }
    if (myFile.is_open()) {
        myFile << username << "\t" << password << "\t" << adminRights << "\n";
        flag = true;
        myFile.close();
    } else {
        throw "File could not be opened for writing!";
    }
}

