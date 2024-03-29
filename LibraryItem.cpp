#include "LibraryItem.h"

int LibraryItem::nextLibItemID = 0;

LibraryItem::LibraryItem() :
        Article(),
        ifTaken(false),
        genre(Genre::historical),
        rating(0.0) {}

LibraryItem::LibraryItem(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
                         const std::string &publisher, Genre genre, const std::string &shortDescription, double rating,
                         const std::string &isbn) : Article(title, author, keyWords),
                                                    publisher(publisher), genre(genre),
                                                    shortDescription(shortDescription),
                                                    isbn(isbn), ifTaken(false) {
    setRating(rating);
}

int LibraryItem::get_ID() const {
    return ID;
}

std::string LibraryItem::get_isbn() const {
    return isbn;
}

bool LibraryItem::getIfTaken() const {
    return ifTaken;
}

std::string LibraryItem::get_genreToString() const {
    switch (genre) {
        case Genre::historical:
            return "historical";
        case Genre::adventure:
            return "adventure";
        case Genre::fantasy:
            return "fantasy";
        case Genre::comedy:
            return "comedy";
        default:
            return "historical";
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
    if (rating > 5 || rating < 0) {
        std::cout << "Invalid rating value!\n";
        this->rating = 0.0;
    } else {
        this->rating = newRating;
    }
}

void LibraryItem::setIsbn(const std::string &newIsbn) {
    this->isbn = newIsbn;
}

void LibraryItem::setGenre(const std::string &str) {
    if (str == "adventure") {
        this->genre = Genre::adventure;
    } else if (str == "fantasy") {
        this->genre = Genre::fantasy;
    } else if (str == "comedy") {
        this->genre = Genre::comedy;
    } else {
        this->genre = Genre::historical;
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





