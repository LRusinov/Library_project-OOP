
#ifndef _ARTICLE_H_
#define _ARTICLE_H_


#include <vector>
#include "Date.h"

class Article {
protected:
    std::string title;
    std::string author;
    std::vector<std::string> keyWords;
public:
    Article();

    Article(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords);

    std::string get_title() const;

    std::string get_author() const;

    std::vector<std::string> get_keyWords() const;
};

#endif //_ARTICLE_H_
