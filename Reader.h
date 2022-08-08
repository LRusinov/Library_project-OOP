#ifndef _READER_H_
#define _READER_H_

#include"Date.h"
#include"Series.h"

#include "User.h"

class Reader : public User {

private:
    std::vector<LibraryItem *> listOfItems;
    int numOfItems;

public:

    Reader(const std::string &username, const std::string &password, const Date &registrationDate);

    void takingItem(LibraryItem *newItem) override; //читателя взима книга или печатно издание

};


#endif
