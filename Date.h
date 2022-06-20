#ifndef _DATE_H_
#define _DATE_H_

#include<iostream>

class Date {  //yyyy-mm-dd
private:
    size_t day;
    size_t month;
    size_t year;

    //helper function which validates the date
    void dateValidation();

public:
    //Constructors
    Date();

    Date(size_t day, size_t month, size_t year);

    Date(const Date &other);

    //Setters
    void set_day(size_t day);

    void set_month(size_t month);

    void set_year(size_t year);

    //Operators
    Date &operator=(const Date &other);

    bool operator>=(const Date &other) const;

    bool operator<=(const Date &other) const;

    //Functions
    void printDate() const;

    static Date addYears(Date &date, size_t yearsToAdd);

    Date nextMonth() const;

    friend std::ostream &operator<<(std::ostream &os, const Date &date) {
        os << date.year << "-" << date.month << "-" << date.day;

        return os;
    }
};


#endif

