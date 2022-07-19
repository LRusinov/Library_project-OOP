#ifndef _DATE_H_
#define _DATE_H_

#include<iostream>

class Date {  //yyyy-mm-dd
private:
    int day;
    int month;
    int year;

    //helper function which validates the date
    void dateValidation();

public:
    //Constructors
    Date();

    Date(int day, int month, int year);

    Date(const Date &other);

    //Setters
    void set_day(int day);

    void set_month(int month);

    void set_year(int year);

    //Operators
    Date &operator=(const Date &other);

    bool operator>=(const Date &other) const;

    bool operator<=(const Date &other) const;

    //Functions

    Date nextMonth() const;

    friend std::ostream &operator<<(std::ostream &os, const Date &date) {
        os << date.year << "-" << date.month << "-" << date.day;

        return os;
    }
};


#endif

