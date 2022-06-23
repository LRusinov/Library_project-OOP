#include<iostream>
#include "Library.h"

int main() {



    std::string s = "ads sd aas";
    Library l;
    Vector<String> vec, vec2;
    Vector<Article> content;
    Article article1("Article title", "Article author", vec2);
    Article article2("Article title2", "Article author2", vec);
    content.pushBack(article1);
    content.pushBack(article2);
    vec.pushBack("word");
    vec.pushBack("word2");
    vec2.pushBack("word3");
    vec2.pushBack("word4");
    Book book1("title1", "author1", vec, "publisher1",
               Genre::g1, "descrb1", 2.0, "isbn1", 12);
    Book book2("title2", "author2", vec, "publisher2",
               Genre::g1, "descrb2", 8.2, "isbn2", 15);
    Book book3("title3", "author2", vec, "publisher3",
               Genre::g3, "descrb3", 6.0, "isbn3", 10);
    Book book4("title4", "author2", vec, "publisher4",
               Genre::g1, "descrb4", 3.1, "isbn4", 100);
    Series series1("series Title", "author1", vec, "publisher1",
                   Genre::g2, "descrb1", 2.0, "isbn5",
                   Date(15,2,2022),2,content);
    Series series2("series Title2", "author2", vec, "publisher1",
                   Genre::g4, "descrb2", 2.0, "isbn6",
                   Date(4,3,2022),2,content);
    Series series3("series Title3", "author3", vec, "publisher1",
                   Genre::g1, "descrb3", 2.0, "isbn7",
                   Date(7,8,2022),2,content);
    l.bookAdd(book1);
    l.bookAdd(book2);
    l.bookAdd(book3);
    l.bookAdd(book4);
    l.seriesAdd(series1);
    l.seriesAdd(series2);
    l.seriesAdd(series3);
    //l.list_info("isbn3");


    l.user_add("r1","abv");
    l.user_add("r2","a34");
    l.user_add("r3","aqq");
    l.user_add("r4","aff");
    l.user_add("admin","i<3c++","admin");
//l.login();
//l.booksFind("author","author2","sort","year","asc");
//    l.take(15);
//    l.returnItem(15);
//    l.take(15);
//
//
//    l.list_all();
//    l.series_all();
//    l.book_all();
//l.menu();
std::string ssss;
std::cin>>s;
std::cout<<s.find("book all");
    return 0;
}