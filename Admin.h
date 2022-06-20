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
          const String &email, const String &sector);

    void print() const override;

    Admin &operator=(const Admin &other);
//    Vector<BooksAndArticles> get_items()const override;
};


#endif // !_ADMIN_H_

