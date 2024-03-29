#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include<ctime>
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

    //HELPER FUNCTIONS
    void passwordCheck(); //проверява дали въведената парола е правилна

    static std::string passwordChange();// помощна функция за промяна на паролата

    bool rightsCheck() const;//проверява дали логнатия потребител има администраторски права

    bool loginCheck() const;//проверява дали имаме логнат потребител

    static std::vector<std::string> keyWordsHelper(const std::string &str);//преобразува стринг от ключови думи
    // във вектор от кличови думи
    static Date stringToDate(const std::string &str);//преобразува дата формат ISO8601 във Date

    template<typename T>
    void swap(T &obj1, T &obj2); //размяна на два обекта

public:
    //CONSTRUCTORS
    Library();

    ~Library();

    //MENU FUNCTIONS
    void login();

    void logout();

    template<typename T>
    void item_all() const;//използва се за командите book/series all

    void list_all() const;

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

    //MENU AND HELP
    void menu(); //меню, което съчетава в себе си всички функционалности

    static void help(); // принтира всички възможни команди

    //FILES
    void addBookFromFile(const std::string &fileName);

    void addSeriesFromFile(const std::string &fileName, const std::string &articlesFilename);

    void addUsersFromFile(const std::string &fileName);

    static std::vector<Article *> articlesFromFile(int n, const std::string &fileName);

    void dataLoad(const std::string &uFilename, const std::string &aFileName, const std::string &bFileName,
                  const std::string &sFileName);//зарежда данните на библиотеката от файл

    void dataSave(const std::string &uFilename, const std::string &aFileName, const std::string &bFileName,
                  const std::string &sFileName);//запазване на данните на библиотеката във файлове
};
#endif