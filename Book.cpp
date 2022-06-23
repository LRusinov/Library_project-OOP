#include "Book.h"

Book::Book() {
    year = 0;
}

Book::Book(const Book &other) : LibraryItem(other) {
    this->author = other.author;
    this->isbn = other.isbn;
    this->keyWords = other.keyWords;
    this->publisher = other.publisher;
    this->shortDescription = other.shortDescription;
    this->title = other.title;
    this->year = other.year;
}

Book &Book::operator=(const Book &other) {
    this->author = other.author;
    this->genre = other.genre;
    this->isbn = other.isbn;
    this->keyWords = other.keyWords;
    this->publisher = other.publisher;
    this->rating = other.rating;
    this->shortDescription = other.shortDescription;
    this->title = other.title;
    this->year = other.year;
    return *this;
}

void Book::printInfo() const {

    std::cout << "Book title: " << title;
    std::cout<<"\nGenre: ";
    switch (genre) {
        case Genre::g1:
            std::cout << " g1\n";
            break;
        case Genre::g2:
            std::cout << " g2\n";
            break;
        case Genre::g3:
            std::cout << " g3\n";
            break;
        case Genre::g4:
            std::cout << " g4\n";
            break;
    }
    std::cout << "ID: " << ID << std::endl;

}

LibraryItem *Book::clone() const {
    return new Book(*this);
}

size_t Book::getYear() const {
    return year;
}

void Book::fullInfo() const {
    printInfo();
    std::cout << "Author: " << author << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "Publisher: " << publisher << std::endl;
    std::cout << "Description: " << shortDescription << std::endl;
    std::cout << "Rating: " << rating << std::endl;
}

Book::Book(const String &title, const String &author, const Vector<String> &keyWords, const String &publisher,
           const Genre &genre, const String &shortDescription, double rating, const String &isbn, size_t year) {
    this->title = title;
    this->author = author;
    this->keyWords = keyWords;
    this->publisher = publisher;
    this->genre = genre;
    this->shortDescription = shortDescription;
    this->rating = rating;
    this->isbn = isbn;
    ifTaken = false;
    this->year = year;
}





