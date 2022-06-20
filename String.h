#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _STRING_H_
#define _STRING_H_

#include<iostream>
#include <string>
#include <cstring>

class String {
private:
    char *str;
    size_t size;

    void copy(const String &other);

    void destroy();

public:

    //Constructors
    String();

    String(const char *_str, size_t size = 0);

    String(const String &other);

    ~String();

    // Methods
    void resize(size_t size);

    void Concat(const String &other);

    void pushBack(char element);

    size_t get_length() const;

    bool isEmpty() const;

    char *toCharArray() const;

    // Operators
    char &operator[](size_t index);

    const char &operator[](size_t index) const;

    String &operator=(const String &other);

    String &operator+(const String &other);

    String &operator+(char *other);

    bool operator==(const String &other) const;

    bool operator==(const char *str) const;

    bool operator!=(const String &other) const;

    bool operator>(const String &other) const;

    bool operator<(const String &other) const;


    friend std::ostream &operator<<(std::ostream &os, String &output) {
        for (size_t i = 0; i < output.size; i++) {
            os << output.str[i];
        }
        return os;
    }

    friend std::ostream &operator<<(std::ostream &os, const String &output) {
        for (size_t i = 0; i < output.size; i++) {
            os << output.str[i];
        }
        return os;
    }

    friend std::istream &operator>>(std::istream &in, String &input) {
        input.destroy();
        char *my_str = new char[100];
        in.getline(my_str, 100);
        size_t length = strlen(my_str);
        input.str = new char[length + 1];
        input.size = strlen(my_str);
        for (size_t i = 0; i < length; i++) {
            input.str[i] = my_str[i];
        }
        input.str[length] = '\0';
        delete[] my_str;
        return in;
    }
};

#endif
