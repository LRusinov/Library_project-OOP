
#include"Series.h"

Series::Series() {
    num = 0;
}

Date Series::get_published() const {
    return published;
}

size_t Series::get_num() const {
    return num;
}

Vector<Article> Series::get_content() const {
    return content;
}

Series &Series::operator=(const Series &other) {
    this->content = other.content;
    this->genre = other.genre;
    this->isbn = other.isbn;
    this->publisher = other.publisher;
    this->rating = other.rating;
    this->shortDescription = other.shortDescription;
    this->title = other.title;
    this->published = other.published;
    this->num = other.num;
    return *this;
}

LibraryItem *Series::clone() const {
    return new Series(*this);
}

void Series::printInfo() const {
    std::cout << "Series title: " << title;
    std::cout<<"\nGenre: ";
    switch (genre) {
        case Genre::g1:
            std::cout << "g1\n";
            break;
        case Genre::g2:
            std::cout << "g2\n";
            break;
        case Genre::g3:
            std::cout << "g3\n";
            break;
        case Genre::g4:
            std::cout << "g4\n";
            break;
    }
    std::cout << "ID: " << ID << std::endl;
}

void Series::fullInfo() const {
    printInfo();
    std::cout << "Author: " << author << std::endl;
    std::cout << "Publisher: " << publisher << std::endl;
    std::cout << "Published: " << std::endl;
    std::cout << "Description: " << shortDescription << std::endl;
    std::cout << "Rating: " << rating << std::endl;
}

Series::Series(const String &title, const String &author, const Vector<String> &keyWords, const String &publisher,
               const Genre &genre, const String &shortDescription, double rating, const String &isbn,
               const Date &published, size_t num, const Vector<Article> &content) {
    this->title = title;
    this->author = author;
    this->keyWords = keyWords;
    this->publisher = publisher;
    this->genre = genre;
    this->shortDescription = shortDescription;
    this->rating = rating;
    this->isbn = isbn;
    ifTaken = false;
    this->published = published;
    this->num = num;
    this->content = content;

}
