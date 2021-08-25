#include "iterator_image.h"

iterator_image::iterator_image()
    : m_img(nullptr), m_index(0), m_width(0)
{

}

iterator_image::iterator_image(QImage* obj, size_t index)
               : m_img(obj),  m_index(index), m_width(obj->width())
{

}

iterator_image::iterator_image(const iterator_image& itr)
               : m_img(itr.m_img), m_index(itr.m_index), m_width (itr.m_width)
{

}

itr_tool_img iterator_image::operator*()
{
    return { *this };
}

iterator_image iterator_image::operator++(int)
{
    iterator_image temp(*this);
    ++m_index;

    return temp;
}

iterator_image& iterator_image::operator++()
{
    ++m_index;

    return *this;
}

iterator_image iterator_image::operator+(size_t index)
{
    iterator_image temp(*this);
    temp.m_index += index;

    return temp;
}

bool iterator_image::operator!=(const iterator_image& second) const
{
    return m_index != second.m_index;
}

iterator_image& iterator_image::operator=(const iterator_image& itr)
{
    m_img = itr.m_img;
    m_index = itr.m_index;
    m_width = itr.m_width;

    return *this;
}

itr_tool_img::itr_tool_img(iterator_image& itr)
             : m_itr(itr)
{

}

itr_tool_img::operator uint8_t()
{
    utils_itr::x_y_c coordinats = utils_itr::calculate_coordinat(m_itr.m_index, m_itr.LENGTH_RGB, m_itr.m_width);
    QColor colors = m_itr.m_img->pixelColor(coordinats.m_x, coordinats.m_y);

    switch (coordinats.m_color)
    {
        case 0 :
        return colors.red();

        case 1 :
        return colors.green();

        case 2 :
        return colors.blue();
    }

    assert(false);
}

itr_tool_img& itr_tool_img::operator=(uint8_t value)
{
    utils_itr::x_y_c coordinate = utils_itr::calculate_coordinat(m_itr.m_index, m_itr.LENGTH_RGB, m_itr.m_width);

    QColor colors = m_itr.m_img->pixelColor(coordinate.m_x, coordinate.m_y);

    switch (coordinate.m_color)
    {
        case 0 :
            colors.setRed(value);
            break;
        case 1 :
            colors.setGreen(value);
            break;
        case 2 :
            colors.setBlue(value);
            break;
    }

    m_itr.m_img->setPixelColor(coordinate.m_x,coordinate.m_y,colors);

    return *this;
}




