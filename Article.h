
#ifndef _ARTICLE_H_
#define _ARTICLE_H_

#include "String.h"
#include "Vector.h"
#include "Date.h"

class Article {
protected:
    String title;
    String author;
    Vector<String> keyWords;
public:
    Article();

    String get_title() const;

    String get_author() const;

    Vector<String> get_keyWords() const;
};

#endif //_ARTICLE_H_
