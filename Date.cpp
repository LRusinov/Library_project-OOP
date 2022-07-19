
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

Date::Date(const int day, const int month, const int year) {
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
void Date::set_day(const int newDay) {
    if (newDay < 1 || newDay > 31) {
        std::cout << "Invalid day!";
        this->day = 1;
    } else {
        this->day = newDay;
    }
}

void Date::set_month(const int newMonth) {
    if (newMonth < 1 || newMonth > 12) {
        std::cout << "Invalid month!";
        this->month = 1;
    } else {
        this->month = newMonth;
    }
}

void Date::set_year(const int newYear) {
    if (newYear < 1) {
        std::cout << "Invalid year!";
        this->year = 2020;
    } else {
        this->year = newYear;
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

Date Date::nextMonth() const {

    if (month == 12) {
        return Date(day, 1, year + 1);
    } else {
        return Date(day, month + 1, year);
    }
}

