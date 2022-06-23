#ifndef _BOOK_H_
#define _BOOK_H_

#include "String.h"
#include "Vector.h"
#include "LibraryItem.h"
#include "Article.h"

class Book : public LibraryItem {

private:
    size_t year;
public:
    Book();
Book(    const String& title, const String& author, const Vector<String>& keyWords,
         const String& publisher, const Genre& genre,
    const String& shortDescription, double rating,const String& isbn, size_t year);
    Book(const Book &other);

    Book &operator=(const Book &other);

    void printInfo() const override;

    LibraryItem *clone() const override;

    size_t getYear() const;

    void fullInfo() const override;
};


#endif // !_BOOK_H_

