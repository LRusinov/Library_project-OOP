#ifndef _READER_H_
#define _READER_H_

#include"Date.h"
#include"Series.h"

#include "User.h"
#include "Vector.h"


class Reader : public User {
private:
    Vector<BooksAndArticles> listOfItems;
    size_t numOfItems;
public:
    Reader(const String &username, const String &password);

    size_t get_numOfItems() const;

    void addItem( LibraryItem *newItem);

    void print() const override;

    Vector<BooksAndArticles> get_items() const;

    void takingItem( LibraryItem *newItem);

};


#endif
