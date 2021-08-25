#ifndef ITERATOR_IMAGE_H
#define ITERATOR_IMAGE_H
#include <QImage>
#include "utils_iterator.h"

class itr_tool_img;

class iterator_image
{
    friend itr_tool_img;
public:
    iterator_image();
    iterator_image(QImage* obj, size_t index);
    iterator_image(const iterator_image& itr);

    itr_tool_img operator*();
    iterator_image operator++(int);
    iterator_image& operator++();
    iterator_image operator+(size_t index);
    bool operator !=(const iterator_image& second) const;
    iterator_image& operator=(const iterator_image& itr);

private:
    QImage* m_img;
    size_t m_index;
    size_t m_width;
    const size_t LENGTH_RGB = 3;
};

class itr_tool_img
{
public:
    itr_tool_img(iterator_image& img);

    operator uint8_t();
    itr_tool_img& operator=(uint8_t value);

private:
    iterator_image& m_itr;
};

#endif // ITERATOR_IMAGE_H
