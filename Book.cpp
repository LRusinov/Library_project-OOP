#include <fstream>
#include "Book.h"

Book::Book() : LibraryItem(), year(0) {}

Book::Book(const Book &other) : LibraryItem(other.title, other.author, other.keyWords,
                                            other.publisher, other.genre,
                                            other.shortDescription, other.rating, other.isbn) {
    setYear(other.year);
}

Book::Book(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
           const std::string &publisher, Genre genre, const std::string &shortDescription, double rating,
           int year, const std::string &isbn) :
        LibraryItem(title, author, keyWords, publisher, genre, shortDescription, rating, isbn) {
    setYear(year);
}

int Book::getYear() const {
    return year;
}

void Book::setYear(int newYear) {
    if (newYear > 0) {
        this->year = newYear;
    } else {
        std::cout << "Invalid year!It's set to 2000!\n";
        this->year = 2000;
    }
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

void Book::fullInfo() const {
    printInfo();
    std::cout << "Author: " << author << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "Publisher: " << publisher << std::endl;
    std::cout << "Description: " << shortDescription << std::endl;
    std::cout << "Rating: " << rating << std::endl;
    keyWordsPrint();
}

LibraryItem *Book::clone() const {
    return new Book(*this);
}

std::string Book::type() const {
    return typeid(Book).name();
}

Book &Book::operator=(const Book &other) {
    if (this != &other) {
        this->author = other.author;
        this->genre = other.genre;
        this->isbn = other.isbn;
        this->keyWords = other.keyWords;
        this->publisher = other.publisher;
        this->rating = other.rating;
        this->shortDescription = other.shortDescription;
        this->title = other.title;
        this->year = other.year;
    }
    return *this;
}

void Book::writeToFile(const std::string& fileName,const std::string& fileNameArt) const {
    static bool flag = false;
    std::ofstream myFile;
    if (flag) {                                             //проверява дали файлът се отваря за първи път
        myFile.open(fileName, std::ios::app);
    } else {
        myFile.open(fileName, std::ios::out);
        flag = true;
    }
    if (myFile.is_open()) {
        myFile << title << '\t' << author << '\t';
        myFile << year << '\t' << publisher << '\t' << get_genreToString() << '\t';
        myFile << rating << '\t' << shortDescription << '\t';
        keyWordsToFile(myFile);
        myFile<<"\t";
        myFile<< isbn << std::endl;
        myFile.close();
    }else{
        throw "File could not be opened for writing!";
    }
}





