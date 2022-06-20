#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

template<typename T>
class Vector {
private:
    size_t size;
    size_t capacity;
    T *data;
    static const size_t DEFAULT_CAPACITY = 8;
    static const size_t RESIZE_FACTOR = 2;

    void copy(const Vector<T> &other) {

        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }

    }

    void destroy() {
        delete[] data;
        data = nullptr;
    }

public:
    Vector() {
        size = 0;
        data = nullptr;
        capacity = DEFAULT_CAPACITY;
    }

    Vector(const Vector<T> &other) {
        copy(other);
    }

    Vector(const T *data) {
        size_t buff_size = 0;
        size_t buff_capacity = DEFAULT_CAPACITY;
        while (data[buff_size] != NULL) {
            buff_size++;
        }
        while (buff_capacity < buff_size) {
            buff_capacity *= RESIZE_FACTOR;
        }
        size = buff_size;
        capacity = buff_capacity;
        this->data = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            this->data[i] = data[i];
        }
    }

    ~Vector() {
        destroy();
    }


    size_t get_size() const {
        return size;
    }


    size_t get_capacity() const {
        return capacity;
    }

    const bool isEmpty() const {
        return size == 0;
    }

    void resize(size_t capacity) {
        if (capacity <= this->capacity) {
            return;
        }
        if (this->capacity == 0) {
            this->capacity = DEFAULT_CAPACITY;
        }
        while (capacity >= this->capacity) {
            this->capacity *= RESIZE_FACTOR;
        }

        T *newData = new T[this->capacity];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        destroy();
        data = newData;
    }

    void pushBack(const T &element)//adding element at the end of arr
    {
        T *newData = new T[size + 1];
        if (size + 1 > capacity) {
            resize(RESIZE_FACTOR * capacity);
        }
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        newData[size] = element;
        destroy();
        size++;
        data = newData;
    }

    void pushBack(T &element)//adding element at the end of arr
    {
        T *newData = new T[size + 1];
        if (size + 1 > capacity) {
            resize(RESIZE_FACTOR * capacity);
        }
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        newData[size] = element;
        destroy();
        size++;
        data = newData;
    }

    void insert(size_t index, const T &element)//inserting element at arr[index]
    {
        size++;
        T *newData = new T[size];
        if (size > capacity) {
            resize(RESIZE_FACTOR * capacity);
        }
        for (size_t i = 0; i < index; i++) {
            newData[i] = data[i];
        }
        newData[index] = element;

        for (size_t i = index + 1; i < size; i++) {
            newData[i] = data[i];
        }

        destroy();
        data = newData;
    }

    void erase(size_t index)//erasing element arr[index]
    {
        T temp;
        for (size_t i = index; i < size - 1; i++) {
            temp = data[i];
            data[i] = data[i + 1];
            data[i + 1] = temp;
        }
        size--;
    }

    T &operator[](size_t index) {
        return data[index];
    }

    const T &operator[](size_t index) const {
        return data[index];
    }

    Vector<T> &operator+=(const T &element) {
        pushBack(element);
        return *this;
    }

    Vector<T> &operator+=(const Vector<T> &other) {
        for (size_t i = 0; i < other.size; i++) {
            *this += other[i];
        }
        return *this;
    }

    Vector<T> &operator=(const Vector<T> &other) {
        if (this != &other) {
            destroy();
            copy(other);
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector<T> vector) {
        for (int i = 0; i < vector.size; ++i) {
            os << vector.data[i];
        }
        return os;
    }

};

#endif
