#ifndef _BOOK_H_
#define _BOOK_H_

#include <vector>


#include "LibraryItem.h"
#include "Article.h"

class Book : public LibraryItem {

private:
    int year;

public:
    Book();

    Book(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
         const std::string &publisher, Genre genre, const std::string &shortDescription, double rating,
         int year, const std::string &isbn = "");

    Book(const Book &other);

    void setYear(int year);

    LibraryItem *clone() const override;

    void printInfo() const override;

    void fullInfo() const override;

    std::string type() const override;

    Book &operator=(const Book &other);

    void writeToFile(const std::string& fileName, const std::string& fileNameArt)const override;
};


#endif // !_BOOK_H_

