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

    std::string get_genreToString()const;

    std::string get_description() const;

    std::string get_isbn() const;

    void setPublisher(const std::string &publisher);

    void setGenre(const std::string& str);

    void setShortDescription(const std::string &shortDescription);

    void setRating(double rating);

    void setIsbn(const std::string &isbn);

    bool getIfTaken() const;

    void set_ifTaken(bool ifTaken);

    void setTakingDate(const Date &takingDate);

    void setReturnDate(const Date &returnDate);

    bool cmp(const std::string &comp, const LibraryItem *item) const;

    virtual LibraryItem *clone() const = 0;

    virtual void printInfo() const = 0;

    virtual void fullInfo() const = 0;

};

#endif
