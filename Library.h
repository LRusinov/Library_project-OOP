#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include"Vector.h"
#include"User.h"
#include"LibraryItem.h"
#include"Series.h"
#include"Admin.h"
#include"Reader.h"

class Library {
private:
    Vector<Book> booksList;
    size_t numOfBooks;
    Vector<Series> seriesList;
    size_t numOfSeries;
    Vector<Admin *> adminsList;
    size_t numOfAdmins;
    Vector<Reader *> readersList;
    size_t numOfReader;
    bool loggedIn;
    bool adminRights{};
    size_t currentUser;
    Date currentDate;

public:
    Library();

    ~Library();

    void login();//

    void logout();//

    void series_all() const;//

    void list_all() const;//

    void book_all() const;//

    void bookAdd(const Book &book);//

    void seriesAdd(const Series &series);//

    void list_info(const String &isbn) const;//

    void booksFind(const String &option, const String &str, const String &sort = "", const String &key = "",
                   const String &asc = "asc");//

    void user_find(const String &option, const String &str) const;

    void user_add(const String &username, const String &password, const String &admin = "");//

    void user_remove(const String &username);//

    void user_change(const String &username = "");//


    void take(size_t id);//

    void returnItem(size_t id);//

    void menu();

    static void help();//

    static int exit();
};


#endif
