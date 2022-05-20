
#include"Journal.h"

Journal::Journal() {
    num = 0;
}

String Journal::get_published() const {
    return published;
}

size_t Journal::get_num() const {
    return num;
}

Vector <Article> Journal::get_content() const {
    return content;
}

Journal& Journal::operator=(const Journal &other) {
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

LibraryItem *Journal::clone() const {
    return new Journal(*this);
}

void Journal::printInfo() const {
    std::cout << title << "Journal  ";
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
