#ifndef UTILS_ITERATOR_H
#define UTILS_ITERATOR_H
#include <QImage>
#include <limits>

using namespace std;

bool is_enough_capacity(const QImage& image, const QByteArray& data);

template <typename Type_1, typename Type_2, typename Functor>
void transform_itr(Type_1 begin, Type_1 end, Type_2& input, Type_2& output, Functor func)
{
    for(; begin != end; ++begin, ++input, ++output)
    {
        *output = func(*begin, *input);
    }
}

namespace utils_itr
{
    struct x_y_c
    {
        size_t m_x;
        size_t m_y;
        size_t m_color;
    };

    x_y_c calculate_coordinat(size_t index, size_t length_rgb, size_t width);
}

namespace utils_itr_bit
{
    struct pos_byte_bit
    {
        size_t index_byte;
        size_t index_bit;
    };

    pos_byte_bit calculate_indexs_byte_bit(size_t length, size_t index_bit);

    //uint8_t nth_bit(uint8_t number, size_t position);

    uint8_t nth_bit(size_t number, size_t position);

    uint8_t insert_bit_in_byte(uint8_t bit, size_t pos_shift, uint8_t current_byte);

    //size_t insert_bit_in_byte(uint8_t bit, size_t pos_shift, size_t current_byte);

    uint8_t hide_data(uint8_t hidden_bit, uint8_t color_byte);

    uint8_t set_lowest_bit(uint8_t bit,  uint8_t byte);

    uint8_t read_data(uint8_t color);

    uint8_t get_lowest_bit(uint8_t number);
}

#endif // UTILS_ITERATOR_H
