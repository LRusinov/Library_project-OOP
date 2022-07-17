#include "LibraryItem.h"

int LibraryItem::nextLibItemID = 0;

LibraryItem::LibraryItem():
Article(),
ifTaken(false),
genre(Genre::g1),
rating(0.0) {}

LibraryItem::LibraryItem(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
                         const std::string &publisher, Genre genre, const std::string &shortDescription, double rating,
                         const std::string &isbn) : Article(title, author, keyWords),
                                                                                publisher(publisher), genre(genre),
                                                                                shortDescription(shortDescription),
                                                                                rating(rating), isbn(isbn),
                                                                                ifTaken(false) {}

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

bool LibraryItem::cmp(const std::string& comp, const LibraryItem *item) const {
    if(comp=="title"){
        return item->title > title;
    }else if(comp=="author"){
        return item->author > author;
    }
    else if(comp=="id"){
        return item->ID > ID;
    } else if(comp=="genre"){
        return item->genre > genre;
    }
    else{
        return false;
    }
}

void LibraryItem::swap(LibraryItem *item,LibraryItem *item2) {
    LibraryItem* temp = item;
    item = item2;
    item2 = temp;
}




