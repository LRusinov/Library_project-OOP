
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
    void setTitle(const std::string &title);

    void setAuthor(const std::string &author);

    void setKeyWords(const std::vector<std::string> &keyWords);

public:
    Article();

    Article(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords);

    std::string get_title() const;

    std::string get_author() const;

    std::vector<std::string> get_keyWords() const;

    void print()const ;

    void keyWordsPrint()const;

    virtual void keyWordsToFile(std::ostream& file) const;

    void writeArticleToFile(const std::string& fileName) const;
};

#endif //_ARTICLE_H_
