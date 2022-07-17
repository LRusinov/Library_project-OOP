#ifndef _BOOK_H_
#define _BOOK_H_

#include <vector>
#include "String.h"
#include "LibraryItem.h"
#include "Article.h"

class Book : public LibraryItem {

private:
    size_t year;
public:
    Book();

    Book(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
         const std::string &publisher, Genre genre, const std::string &shortDescription, double rating,
         size_t year,const std::string &isbn = "");

    Book(const Book &other);

    Book &operator=(const Book &other);

    void printInfo() const override;

    LibraryItem *clone() const override;

    size_t getYear() const;

    void fullInfo() const override;
    std::string type()const override;
};


#endif // !_BOOK_H_

