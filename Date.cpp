
#include "Date.h"


//helper function which validates the date
void Date::dateValidation() {
//
    if (month == 2) {
        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
            if (day > 29) {
                std::cout << "Invalid date! Month " << month << " has 29 days!";
                day = 29;
            }
        } else {
            if (day > 28) {
                std::cout << "Invalid date! Month " << month << " has 29 days!";
                day = 28;
            }
        }
    } else {
        if (day > 30) {
            std::cout << "Invalid date! Month " << month << " has 30 days!";
            day = 30;
        }
    }
}

//Constructors
Date::Date() {
    day = 1;
    month = 1;
    year = 2020;
}

Date::Date(const size_t day, const size_t month, const size_t year) {
    set_day(day);
    set_month(month);
    set_year(year);
    dateValidation();
}

Date::Date(const Date &other) {
    set_day(other.day);
    set_month(other.month);
    set_year(other.year);
    dateValidation();
}

//Setters
void Date::set_day(const size_t day) {
    if (day < 1 || day > 31) {
        std::cout << "Invalid day!";
        this->day = 1;
    } else {
        this->day = day;
    }
}

void Date::set_month(const size_t month) {
    if (month < 1 || month > 12) {
        std::cout << "Invalid month!";
        this->month = 1;
    } else {
        this->month = month;
    }
}

void Date::set_year(const size_t year) {
    if (year < 1) {
        std::cout << "Invalid year!";
        this->year = 2020;
    } else {
        this->year = year;
    }
}

//Operators
Date &Date::operator=(const Date &other) {
    if (this != &other) {
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
    }
    return *this;
}

bool Date::operator>=(const Date &other) const {

    if (this->year > other.year) {
        return true;
    } else if (this->year == other.year && this->month > other.month) {
        return true;
    } else if (this->year == other.year && this->month == other.month && this->day > other.day) {
        return true;
    } else {
        return false;
    }
}

bool Date::operator<=(const Date &other) const {
    if (this->year < other.year) {
        return true;
    } else if (this->year == other.year && this->month < other.month) {
        return true;
    } else if (this->year == other.year && this->month == other.month && this->day < other.day) {
        return true;
    } else {
        return false;
    }
}

//Functions
void Date::printDate() const {
    std::cout << day << "." << month << "." << year;
}

Date Date::addYears(Date &date, const size_t yearsToAdd) {
    date.year += yearsToAdd;
    return date;
}

