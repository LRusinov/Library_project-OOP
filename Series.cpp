
#include <vector>
#include <fstream>
#include"Series.h"

Series::Series() : LibraryItem() {
    num = 0;
}

Series::Series(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
               const std::string &publisher, Genre genre, const std::string &shortDescription, double rating,
               const Date &published, int num, const std::vector<Article> &content, const std::string &isbn) :
        LibraryItem(title, author, keyWords, publisher, genre, shortDescription, rating, isbn),
        published(published), content(content) {
    setNum(num);
}

Date Series::get_published() const {
    return published;
}

int Series::get_num() const {
    return num;
}

std::vector<Article> Series::get_content() const {
    return content;
}

void Series::setNum(int newNum) {
    if (newNum > 0) {
        this->num = newNum;
    } else {
        std::cout << "Invalid num!It's set to 1!\n";
        this->num = 1;
    }
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
    std::cout << "Num: " << num << std::endl;
    std::cout << "Publisher: " << publisher << std::endl;
    std::cout << "Published: " << published << std::endl;
    std::cout << "Description: " << shortDescription << std::endl;
    std::cout << "Rating: " << rating << std::endl;
    keyWordsPrint();
    size_t numOfArticles = content.size();
    for (size_t i = 0; i < numOfArticles; ++i) {
        content[i].print();
    }
}

std::string Series::type() const {
    return typeid(Series).name();
}

void Series::setContent(const std::vector<Article> &content) {
    Series::content = content;
}

void Series::writeToFile(const std::string& fileName,const std::string& fileNameArt) const{
    static bool flag = false;
    std::ofstream myFile;
    if (flag) {             //проверява дали файлът се отваря за първи път
        myFile.open(fileName, std::ios::app);
    } else {
        myFile.open(fileName, std::ios::out);
        flag = true;
    }
    if (myFile.is_open()) {
        myFile << title << '\t' << author << '\t';
        myFile << num << '\t' << publisher << '\t' << get_genreToString() << '\t';
        myFile << rating << '\t' << shortDescription << '\t';
        keyWordsToFile(myFile);
        myFile<<"\t";
        myFile<< isbn << std::endl;
        myFile.close();
        int numOfArticles = content.size();
        for (int i = 0; i <numOfArticles ; ++i) {
            content[i].writeArticleToFile(fileNameArt);
        }
    }else{
        throw "File could not be opened for writing!";
    }
}




