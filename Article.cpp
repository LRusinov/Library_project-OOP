#include "Article.h"

Article::Article() = default;

String Article::get_title() const {
    return title;
}

String Article::get_author() const {
    return author;
}

Vector<String> Article::get_keyWords() const {
    return keyWords;
}

Article::Article(const String &title, const String &author, const Vector<String> &keyWords) {
this->title = title;
this->author = author;
this->keyWords = keyWords;
}
