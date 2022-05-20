#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "User.h"
#include "String.h"

class Admin : public User {
private:
    String email;
    String sector;
public:
    Admin(const String &username, const String &password,
          const String &email, const String &sector) {
        this->username = username;
        this->password = password;
        this->email = email;
        this->sector = sector;
    }

    void print() const override {
        std::cout << "Username: " << username << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "Sector: " << sector << std::endl;
        std::cout << "Last seen: " << lastSeenDate << std::endl;
    }
    Admin& operator=(const Admin& other){
        this->username = other.username;
        this->password = other.password;
        this->email = other.email;
        this->sector = other.sector;

        return *this;
    }
//    Vector<BooksAndArticles> get_items()const override;
};


#endif // !_ADMIN_H_

