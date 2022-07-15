#ifndef _JOURNAL_H_
#define _JOURNAL_H_

#include "String.h"

#include "LibraryItem.h"
#include "Article.h"

class Series : public LibraryItem {
private:

    Date published;
    size_t num;
    std::vector<Article> content;
public:
    Series();

    Series(const std::string &title, const std::string &author, const std::vector<std::string> &keyWords,
           const std::string &publisher, Genre genre, const std::string &shortDescription, double rating, int id,
           const std::string &isbn, bool ifTaken, const Date &published, size_t num,
           const std::vector<Article> &content);

    Date get_published() const;

    size_t get_num() const;

    std::vector<Article> get_content() const;

    Series &operator=(const Series &other);

    void printInfo() const override;

    LibraryItem *clone() const override;

    void fullInfo() const override;
};


#endif