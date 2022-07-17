#ifndef _LIBRARY_ITEM_
#define _LIBRARY_ITEM_

#include "Genre.h"
#include "Article.h"

class LibraryItem : public Article {


protected:
    static int nextLibItemID;
    std::string publisher;
    Genre genre;
    std::string shortDescription;
    double rating;
    const int ID = ++nextLibItemID;
    std::string isbn;
    bool ifTaken;
    Date takingDate;
    Date returnDate;

public:
    LibraryItem();

    LibraryItem(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
                const std::string &publisher, Genre genre, const std::string &shortDescription, double rating,
                const std::string &isbn = "");

    virtual ~LibraryItem() = default;

    int get_ID() const;

    virtual std::string type() const = 0;

    double get_rating() const;

    std::string get_publisher() const;

    Genre get_genre() const;

    std::string get_description() const;

    std::string get_isbn() const;

    bool getIfTaken() const;

    void set_ifTaken(bool ifTaken);

    void setTakingDate(const Date &takingDate);

    void setReturnDate(const Date &returnDate);

    static void swap(LibraryItem *item, LibraryItem *item2);

    bool cmp(const std::string &comp, const LibraryItem *item) const;

    virtual LibraryItem *clone() const = 0;

    virtual void printInfo() const = 0;

    virtual void fullInfo() const = 0;

};

#endif
