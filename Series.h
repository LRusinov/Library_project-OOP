#ifndef _JOURNAL_H_
#define _JOURNAL_H_

#include "String.h"
#include "Vector.h"
#include "LibraryItem.h"
#include "Article.h"

class Series : public LibraryItem {
private:

    Date published;
    size_t num;
    Vector<Article> content;
public:
    Series();
    Series(  const String& title, const String& author, const Vector<String>& keyWords,
             const String& publisher, const Genre& genre,
             const String& shortDescription, double rating,const String& isbn, const Date& published,
             size_t num, const Vector<Article>& content);

    Date get_published() const;

    size_t get_num() const;

    Vector<Article> get_content() const;

    Series &operator=(const Series &other);

    void printInfo() const override;

    LibraryItem *clone() const override;

    void fullInfo() const override;
};


#endif