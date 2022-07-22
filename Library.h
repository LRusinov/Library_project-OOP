#ifndef _LIBRARY_H_
#define _LIBRARY_H_



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

    std::vector<std::string > keyWordsHelper(const std::string& str);
public:

    Library();

    ~Library();

    void login();

    void logout();

    template<typename T>
    void item_all() const;//използва се за командите book/series all

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

    void users_list();

    void take(int id);

    void returnItem(int id);

    void addBookFromFile(const std::string &fileName);

    void addSeriesFromFile(const std::string &fileName, const std::string &articlesFilename);

    void addUsersFromFile(const std::string &fileName);

    std::vector<Article*> articlesFromFile(int n, const std::string& fileName);

    void menu(); //меню, което съчетава в себе си всички функционалности

    static void help(); // принтира всички възможни команди

    void dataLoad(const std::string& uFilename, const std::string& aFileName,const std::string& bFileName,const std::string& sFileName);

    void dataSave(const std::string& uFilename, const std::string& aFileName,const std::string& bFileName,const std::string& sFileName);
};


#endif
