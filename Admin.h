#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "User.h"


class Admin : public User {
private:
    std::string email;
    std::string sector;
public:
    Admin(const std::string &username, const std::string &password, const Date &registrationDate,
          const std::string &email="", const std::string &sector="");

    void print() const override;

    Admin &operator=(const Admin &other);
};


#endif // !_ADMIN_H_

