#ifndef _BOOK_H_
#define _BOOK_H_

#include "String.h"
#include "Vector.h"
#include "LibraryItem.h"
#include "Article.h"

class Book : public LibraryItem {

private:
    size_t year;
public:
    Book() {
        year = 0;
    }

    Book(const Book &other)  : LibraryItem(other) {
        this->author = other.author;
        this->isbn = other.isbn;
        this->keyWords = other.keyWords;
        this->publisher = other.publisher;
        this->shortDescription = other.shortDescription;
        this->title = other.title;
        this->year = other.year;
    }

    Book &operator=(const Book &other) {
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

    void printInfo()const override {
        std::cout << title << "Book  ";
        switch (genre) {
            case Genre::g1:
                std::cout << "g1  ";
            case Genre::g2:
                std::cout << "g2  ";
            case Genre::g3:
                std::cout << "g3  ";
            case Genre::g4:
                std::cout << "g4  ";
        }
        std::cout << ID << std::endl;
    }

    LibraryItem *clone() const override {
        return new Book(*this);
    }
};


#endif // !_BOOK_H_

