#ifndef _LIBRARY_H_
#define _LIBRARY_H_


#include"User.h"
#include"LibraryItem.h"
#include"Series.h"
#include"Admin.h"
#include"Reader.h"

class Library {
private:
    std::vector<LibraryItem *> listOfLibItems;
    int numOfLibItems;
    std::vector<User *> listOfUsers;
    int numOfUsers;
    bool adminRights;
    int currentUser;
    Date currentDate;

    void passwordCheck(); //проверява дали въведената парола е правилна

    static std::string passwordChange();// помощна функция за промяна на паролата

    bool rightsCheck() const;//проверява дали логнатия потребител има администраторски права

    bool loginCheck() const;//проверява дали имаме логнат потребител
public:

    Library();

    ~Library();

    void login();

    void logout();

    template<typename T>
    void item_all() const;

    void list_all() const;

    void itemAdd(LibraryItem *libItem);

    void bookAdd(Book &book);

    void seriesAdd(Series &series);

    void list_info(const std::string &isbn) const;

    template<typename T>
    void find(const std::string &option, const std::string &str, bool sort = false,
              const std::string &key = "",
              bool asc = true);


    void user_add(const std::string &username, const std::string &password, bool admin = false,
                  const std::string &email = "", const std::string &sector = "");

    void user_remove(const std::string &username);

    void user_change(const std::string &username = "");


    void take(size_t id);

    void returnItem(size_t id);
    void users_list();
void addUsersFromFile(const std::string& fileName);
    void menu(); //меню, което съчетава в себе си всички функционалности

    static void help(); // принтира всички възможни команди


};


#endif
