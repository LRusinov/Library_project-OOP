#ifndef _TEST_H_
#define _TEST_H_

#include "Library.h"

class Test {
public:
    static void dataLoad(Library &library) { //добавяне на данните в библиотеката

        std::vector<std::string> vec, vec2;
        std::vector<Article> content;
        Article article1("Article title", "Article author", vec2);
        Article article2("Article title2", "Article author2", vec);
        content.push_back(article1);
        content.push_back(article2);
        vec.push_back("word");
        vec.push_back("word2");
        vec2.push_back("word3");
        vec2.push_back("word4");
        Book book1("title1", "author1", vec, "publisher1",
                   Genre::g1, "descrb1", 2.0, 12, "isbn1");
        Book book2("title2", "author2", vec, "publisher2",
                   Genre::g1, "descrb2", 8.2, 15, "isbn2");
        Book book3("title3", "author2", vec, "publisher3",
                   Genre::g3, "descrb3", 6.0, 10, "isbn3");
        Book book4("title4", "author2", vec, "publisher4",
                   Genre::g1, "descrb4", 3.1, 100, "isbn4");
        Series series1("series Title", "author1", vec, "publisher1",
                       Genre::g2, "descrb1", 2.0,
                       Date(15, 2, 2022), 2, content, "isbn5");
        Series series2("series Title2", "author1", vec, "publisher1",
                       Genre::g4, "descrb2", 2.0,
                       Date(4, 3, 2022), 2, content, "isbn6");
        Series series3("series Title3", "author3", vec, "publisher1",
                       Genre::g1, "descrb3", 2.0,
                       Date(7, 8, 2022), 2, content, "isbn7");

        //ADDING BOOKS AND SERIES
        library.bookAdd(book1);
        library.bookAdd(book2);
        library.bookAdd(book3);
        library.bookAdd(book4);
        library.seriesAdd(series1);
        library.seriesAdd(series2);
        library.seriesAdd(series3);

        //ADDING USERS
        library.user_add("admin", "i<3c++", "admin","email","sector");
        library.user_add("r1", "abv");
        library.user_add("r2", "a34");
        library.user_add("r3", "aqq");
        library.user_add("r4", "aff");


    }

    static void funcTests(Library &l) { //тестване на функционалностите
        l.list_all();
        l.item_all<Series>();
        l.item_all<Book>();
        l.list_info("isbn3");
        l.login();
        l.find<Book>("author", "author2", "sort", "year", "asc");
        l.take(15);
        l.returnItem(15);
        l.take(15);

    }
};

#endif
