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

    Date(const size_t day, const size_t month, const size_t year);

    Date(const Date& other) ;

    //Setters
    void set_day(const size_t day);

    void set_month(const size_t month) ;

    void set_year(const size_t year) ;

    //Operators
    Date& operator = (const Date& other) ;

    bool operator >= (const Date& other)const ;

    bool operator <= (const Date& other)const ;

    //Functions
    void printDate() const ;

    static Date addYears(Date& date, const size_t yearsToAdd) ;

    friend std::ostream& operator<<(std::ostream& os,const Date& date){
        os<<date.year<<"-"<<date.month<<"-"<<date.day;

        return os;
    }
};


#endif

