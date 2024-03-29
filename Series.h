#ifndef _SERIES_H_
#define _SERIES_H_

#include "LibraryItem.h"
#include "Article.h"

class Series : public LibraryItem {

private:
    Date published;
    int num;
    std::vector<Article*> content;

public:
    Series();

    Series(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
           const std::string &publisher, Genre genre, const std::string &shortDescription, double rating,
           const Date &published, int num, const std::vector<Article*> &content, const std::string &isbn = "");

    ~Series()override;

    void setPublished(const Date &published);

    void setNum(int num);

    void setContent(const std::vector<Article *>& content);

    LibraryItem *clone() const override;

    void printInfo() const override;

    void fullInfo() const override;

    std::string type() const override;

    Series &operator=(const Series &other);

    void writeToFile(const std::string& fileName,const std::string& fileNameArt) const override;
};


#endif