#include "LibraryItem.h"

int LibraryItem::nextLibItemID = 0;

LibraryItem::LibraryItem() :
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

std::string LibraryItem::get_description() const {
    return shortDescription;
}

std::string LibraryItem::get_isbn() const {
    return isbn;
}

bool LibraryItem::getIfTaken() const {
    return ifTaken;
}

std::string LibraryItem::get_genreToString() const {
    switch (genre) {
        case Genre::g1:
            return "g1";
        case Genre::g2:
            return "g2";
        case Genre::g3:
            return "g3";
        case Genre::g4:
            return "g4";
    }

}

void LibraryItem::set_ifTaken(const bool newIfTaken) {
    this->ifTaken = newIfTaken;
}

void LibraryItem::setTakingDate(const Date &newTakingDate) {
    this->takingDate = newTakingDate;
}

void LibraryItem::setReturnDate(const Date &newReturnDate) {
    this->returnDate = newReturnDate;
}

void LibraryItem::setPublisher(const std::string &newPublisher) {
    this->publisher = newPublisher;
}

void LibraryItem::setShortDescription(const std::string &newShortDescription) {
    this->shortDescription = newShortDescription;
}

void LibraryItem::setRating(double newRating) {
    this->rating = newRating;
}

void LibraryItem::setIsbn(const std::string &newIsbn) {
    this->isbn = newIsbn;
}

void LibraryItem::setGenre(const std::string &str) {
    if (str == "g2") {
        this->genre = Genre::g2;
    } else if (str == "g3") {
        this->genre = Genre::g3;
    } else if (str == "g4") {
        this->genre = Genre::g4;
    } else {
        this->genre = Genre::g1;
    }
}

bool LibraryItem::cmp(const std::string &comp, const LibraryItem *item) const {
    if (comp == "title") {
        return item->title > title;
    } else if (comp == "author") {
        return item->author > author;
    } else if (comp == "id") {
        return item->ID > ID;
    } else if (comp == "genre") {
        return item->genre > genre;
    } else {
        throw "Invalid key for comparison!";
    }
}





