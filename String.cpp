#include "String.h"

String::String() {
    str = nullptr;
    size = 0;
}

String::String(const char* str, size_t size) {
    if (size == 0) {
        size = strlen(str);
    }
    this->size = size;
    this->str = new char[size+1];
    strcpy(this->str, str);
}

String::String(const String& other) {
    copy(other);
}

String::~String() {
    destroy();
}

void String::destroy() {
    delete[] str;
    str = nullptr;
}

void String::copy(const String& other) {

    if (this != &other) {
        if (this->str != nullptr) {
            destroy();
        }
        str = new char[other.size + 1];
        strcpy(this->str, other.str);
        size = other.size;
    }
}

void String::resize(const size_t size) {
    size_t oldSize = this->size;

    this->size = size;
    if (oldSize > 0) {
        char* buffer = new char[size + 1];
        strcpy(buffer, str);
        delete[] str;
        str = new char[size + 1];
        strcpy(str, buffer);
        delete[] buffer;
    }
    else {
        str = new char[size + 1];
    }
}

void String::Concat(const String& other) {

    resize(size + other.size);
    strcat(str, other.str);
}

void String::pushBack(const char element) {//adding element at the end of str
    resize(size+1);
    str[size - 1] = element;
    str[size] = '\0';
}

size_t String::get_length()const {
    return this->size;
}

bool String:: isEmpty()const {
    return size == 0;
}


char& String::operator [](const size_t index) {
    return this->str[index];

}

const char& String::operator [](const size_t index)const {
    return this->str[index];

}

String& String::operator =(const String& other) {
    copy(other);
    return *this;
}

String& String::operator +(const String& other) {
    Concat(other);
    return *this ;
}

bool String::operator==(const String& other) const
{
    return !strcmp(this->str, other.str);
}

bool String::operator==(const char* str)const
{
    return !strcmp(this->str,str);
}

bool String::operator!=(const String& other) const
{
    return !(*this==other);
}

char *String::toCharArray() const {
    char* charArr = new char[size+1];
    for (int i = 0; i < size+1; ++i) {
        charArr[i] = str[i];
    }
    return charArr;
}

bool String::operator>(const String &other) const {
    return strcmp(this->str,other.str)>0;
}

bool String::operator<(const String &other) const {
    return strcmp(this->str,other.str)<0;
}



