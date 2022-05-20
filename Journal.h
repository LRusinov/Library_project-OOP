#ifndef _JOURNAL_H_
#define _JOURNAL_H_
#include "String.h"
#include "Vector.h"
#include "LibraryItem.h"
#include "Article.h"

class Journal :  public LibraryItem{
private:

    String published;
    size_t num;
    Vector<Article> content;
public:
    Journal() ;
    String get_published() const ;
    size_t get_num() const;
    Vector<Article> get_content() const ;
    Journal& operator=(const Journal& other) ;
    void printInfo()const override;
    LibraryItem* clone()const override ;
};



#endif