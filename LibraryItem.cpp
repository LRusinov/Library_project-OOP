#include "LibraryItem.h"

int LibraryItem::nextLibItemID = 0;

LibraryItem::LibraryItem():
Article(),
ifTaken(false),
genre(Genre::g1),
rating(0.0) {}

LibraryItem::LibraryItem(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
                         const std::string &publisher, Genre genre, const std::string &shortDescription, double rating,
                         const int id, const std::string &isbn, bool ifTaken) : Article(title, author, keyWords),
                                                                                publisher(publisher), genre(genre),
                                                                                shortDescription(shortDescription),
                                                                                rating(rating), ID(id), isbn(isbn),
                                                                                ifTaken(ifTaken) {}

int LibraryItem::get_ID() const {
    return ID;
}

double LibraryItem::get_rating() const {
    return rating;
}

std::string LibraryItem::get_publisher() const {
    return publisher;
}

Genre LibraryItem::get_genre() const {
    return genre;
}

std::string LibraryItem::get_description() const {
    return shortDescription;
}

std::string LibraryItem::get_isbn() const {
    return isbn;
}

void LibraryItem::set_ifTaken(const bool ifTaken) {

    this->ifTaken = ifTaken;
}

bool LibraryItem::getIfTaken() const {
    return ifTaken;
}

void LibraryItem::setTakingDate(const Date &takingDate) {
    this->takingDate = takingDate;
}

void LibraryItem::setReturnDate(const Date &returnDate) {
    this->returnDate = returnDate;
}

LibraryItem::~LibraryItem() {}



