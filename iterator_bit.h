#ifndef ITERATOR_BIT_H
#define ITERATOR_BIT_H
#include <QByteArray>
#include "utils_iterator.h"

class itr_tool_bit;

class iterator_bit
{
    friend itr_tool_bit;
public:
    iterator_bit(const iterator_bit& obj);
    iterator_bit(QByteArray& arr, size_t index);

    itr_tool_bit operator*();
    iterator_bit operator++(int);
    iterator_bit& operator++();
    iterator_bit operator+(size_t index);
    bool operator!=(const iterator_bit& another);
    iterator_bit& operator=(iterator_bit& itr);

private:
    QByteArray& m_byte_array;
    size_t m_index;
};

class itr_tool_bit
{
public:
    itr_tool_bit(iterator_bit& itr);
    operator uint8_t();
    itr_tool_bit& operator=(uint8_t bit);

private:
    iterator_bit& m_itr;
    const size_t LENGTH_BIT = 8;

};

class const_iterator_bit
{
public:
    const_iterator_bit(const const_iterator_bit& another);
    const_iterator_bit(const QByteArray& arr, size_t index);

    uint8_t operator*() const;
    const_iterator_bit& operator++();
    const_iterator_bit operator++(int);
    bool operator!=(const const_iterator_bit& another) const;

private:
    const QByteArray& m_byte_array;
    size_t m_index;
    const size_t LENGTH_BIT = 8;
};


#endif // ITERATOR_BIT_H
