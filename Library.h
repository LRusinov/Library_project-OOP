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
    void passwordCheck();
    std::string passwordChange();
bool rightsCheck()const;
    bool loginCheck() const;//помощна функция която проверява дали имаме логнат потребител
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

    void booksFind(const std::string &option, const std::string &str, bool sort = false,
                   bool key = false,
                   bool asc = false);


    void user_add(const std::string &username, const std::string &password, bool admin = false);

    void user_remove(const std::string &username);

    void user_change(const std::string& username="" );


    void take(size_t id);

    void returnItem(size_t id);

    void menu(); //меню, което съчетава в себе си всички функционалности

    static void help(); // принтира всички възможни команди
};


#endif
