#include <fstream>
#include "Article.h"

Article::Article() = default;

std::string Article::get_title() const {
    return title;
}

std::string Article::get_author() const {
    return author;
}

std::vector<std::string> Article::get_keyWords() const {
    return keyWords;
}

Article::Article(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords) {
    this->title = title;
    this->author = author;
    this->keyWords = keyWords;
}

void Article::setTitle(const std::string &newTitle) {
    this->title = newTitle;
}

void Article::setAuthor(const std::string &newAuthor) {
    this->author = newAuthor;
}

void Article::setKeyWords(const std::vector<std::string> &keyWords) {
    this->keyWords = keyWords;
}

void Article::print() const {
    std::cout << "\t" << "Article title: " << title << std::endl;
    std::cout << "\t" << "Author: " << author << std::endl;
    std::cout << "\t";
    keyWordsPrint();
}

void Article::keyWordsPrint() const {
    size_t numOfKeyWords = keyWords.size();
    std::cout << "Key words: ";
    for (size_t i = 0; i < numOfKeyWords; ++i) {
        std::cout << keyWords[i] << " ";
    }
    std::cout << std::endl;
}

void Article::writeArticleToFile(const std::string &fileName) const {
    std::ofstream myFile;
    myFile.open(fileName, std::ios::app);
    if (myFile.is_open()) {
        myFile << title << "\t" << author << "\t";
        keyWordsToFile(myFile);
        myFile << "\n";
    }
}

void Article::keyWordsToFile(std::ostream &file) const {
    int numOfKeyWords = keyWords.size();
    for (int i = 0; i < numOfKeyWords; ++i) {
        if (i + 1 == numOfKeyWords) {
            file << keyWords[i];
            break;
        }
        file << keyWords[i] << ",";
    }
}
