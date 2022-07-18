#include "Book.h"

Book::Book() : LibraryItem(), year(0) {}

Book::Book(const Book &other) : LibraryItem(other.title,other.author,other.keyWords,other.publisher,other.genre,
                                            other.shortDescription,other.rating,
                                            other.isbn) {
    this->year = other.year;
}
Book::Book(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
           const std::string &publisher, Genre genre, const std::string &shortDescription,
           double rating, size_t year, const std::string &isbn) :
        LibraryItem(title, author, keyWords, publisher, genre, shortDescription, rating, isbn),
        year(year) {}

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
    std::cout << "\nGenre: ";
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
void Book::setYear(size_t newYear) {
    this->year = newYear;
}

void Book::fullInfo() const {
    printInfo();
    std::cout << "Author: " << author << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "Publisher: " << publisher << std::endl;
    std::cout << "Description: " << shortDescription << std::endl;
    std::cout << "Rating: " << rating << std::endl;
}

std::string Book::type()const {
    return typeid(Book).name();
}






