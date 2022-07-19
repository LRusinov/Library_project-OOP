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
