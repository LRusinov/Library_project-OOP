
#include <vector>
#include <fstream>
#include"Series.h"

Series::Series() : LibraryItem() {
    num = 0;
}

Series::Series(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
               const std::string &publisher, Genre genre, const std::string &shortDescription, double rating,
               const Date &published, int num, const std::vector<Article *> &content, const std::string &isbn) :
        LibraryItem(title, author, keyWords, publisher, genre, shortDescription, rating, isbn),
        published(published), content(content) {
    setNum(num);
}

Series::~Series() {
    size_t numOfArticles = content.size();
    for (size_t i = 0; i <numOfArticles ; ++i) {
        delete content[i];
    }
}

void Series::setNum(int newNum) {
    if (newNum > 0) {
        this->num = newNum;
    } else {
        std::cout << "Invalid num!It's set to 1!\n";
        this->num = 1;
    }
}

void Series::setPublished(const Date &newPublished) {
    this->published = newPublished;
}

void Series::setContent(const std::vector<Article *>& newContent) {
    this->content = newContent;
}

Series &Series::operator=(const Series &other) {
    if (this != &other) {
        this->content = other.content;
        this->genre = other.genre;
        this->isbn = other.isbn;
        this->publisher = other.publisher;
        this->rating = other.rating;
        this->shortDescription = other.shortDescription;
        this->title = other.title;
        this->published = other.published;
        this->num = other.num;
    }
    return *this;
}

LibraryItem *Series::clone() const {
    return new Series(*this);
}

void Series::printInfo() const {
    std::cout << "Series title: " << title;
    std::cout << "\nGenre: ";
    switch (genre) {
        case Genre::historical:
            std::cout << "historical\n";
            break;
        case Genre::adventure:
            std::cout << "adventure\n";
            break;
        case Genre::fantasy:
            std::cout << "fantasy\n";
            break;
        case Genre::comedy:
            std::cout << "comedy\n";
            break;
    }
    std::cout << "ID: " << ID << std::endl;
}

void Series::fullInfo() const {
    printInfo();
    std::cout << "Author: " << author << std::endl;
    std::cout << "Num: " << num << std::endl;
    std::cout << "Publisher: " << publisher << std::endl;
    std::cout << "Published: " << published << std::endl;
    std::cout << "Description: " << shortDescription << std::endl;
    std::cout << "Rating: " << rating << std::endl;
    keyWordsPrint();
    size_t numOfArticles = content.size();
    for (size_t i = 0; i < numOfArticles; ++i) {
        content[i]->print();
    }
}

std::string Series::type() const {
    return typeid(Series).name();
}

void Series::writeToFile(const std::string &fileName, const std::string &fileNameArt) const {
    static int count = 1;
    static bool flag = false, flag2 = false;
    std::ofstream myFile, file2;
    if (flag) {             //проверява дали файлът се отваря за първи път
        myFile.open(fileName, std::ios::app);
    } else {
        myFile.open(fileName, std::ios::out);
    }
    if (myFile.is_open()) {
        myFile << title << '\t' << author << '\t';
        myFile << num << '\t' << publisher << '\t' << get_genreToString() << '\t';
        myFile << rating << '\t' << shortDescription << '\t';
        myFile<<published.getYear()<<"-"<<published.getMonth()<<"\t";
        keyWordsToFile(myFile);
        myFile << "\t";
        myFile << content.size() << "\t";
        myFile << isbn << std::endl;
        myFile.close();
        if (flag2) {             //проверява дали файлът се отваря за първи път
            file2.open(fileNameArt, std::ios::app);
        } else {
            file2.open(fileNameArt, std::ios::out);
        }
        if (file2.is_open()) {
            file2 << count << "\n";
            count++;
            file2.close();
            size_t numOfArticles = content.size();
            for (int i = 0; i < numOfArticles; ++i) {
                content[i]->writeArticleToFile(fileNameArt);
            }
            flag2 = true;
        }
        flag = true;
    } else {
        throw "File could not be opened for writing!";
    }
}