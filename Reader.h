#ifndef _READER_H_
#define _READER_H_

#include"Date.h"
#include"Series.h"

#include "User.h"


class Reader : public User {
private:

    std::vector<LibraryItem *> listOfItems;
    size_t numOfItems;
public:


    Reader(const std::string &username, const std::string &password, const Date &registrationDate);

    ~Reader() override;

    void print() const override;

    void takingItem(LibraryItem *newItem) override;

};


#endif
