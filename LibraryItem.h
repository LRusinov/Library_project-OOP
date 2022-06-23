#ifndef _LIBRARY_ITEM_
#define _LIBRARY_ITEM_

#include "Vector.h"
#include "Genre.h"
#include "Article.h"

class LibraryItem : public Article {


protected:
    static int nextLibItemID;
    String publisher;
    Genre genre;
    String shortDescription;
    double rating;
    const int ID = nextLibItemID++;
    String isbn;
    bool ifTaken;

public:
    LibraryItem();

    int get_ID() const;

    double get_rating() const;

    String get_publisher() const;

    Genre get_genre() const;

    String get_description() const;

    String get_isbn() const;

    bool getIfTaken() const;

    void set_ifTaken(bool ifTaken);

    virtual LibraryItem *clone() const = 0;

    virtual void printInfo() const = 0;

    virtual void fullInfo() const = 0;

};

#endif
