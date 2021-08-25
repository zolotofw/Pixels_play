#include "utils_iterator.h"

bool is_enough_capacity(const QImage& image, const QByteArray& data)
{
    const size_t length_rgb = 3;
    const size_t length_bit = 8;

    size_t img_avaliable_size_in_bite = (image.width() * image.height() * length_rgb) - 16;

    size_t required_size_data_bit = data.size() * length_bit;

    return img_avaliable_size_in_bite > required_size_data_bit;
}

namespace utils_itr
{
    x_y_c calculate_coordinat(size_t index, size_t length_rgb, size_t width)
    {
        size_t pos_pix = index / length_rgb;
        size_t x = pos_pix % width;
        size_t y = pos_pix / width;
        size_t c = index % length_rgb;

        return { x, y, c };
    }
}

namespace utils_itr_bit
{
    pos_byte_bit calculate_indexs_byte_bit(size_t length, size_t index_bit)
    {
        size_t index_byte = index_bit / length;
        size_t i_bit = index_bit % length;

        return { index_byte, i_bit };
    }

//    uint8_t nth_bit(uint8_t number, size_t position)
//    {
//        uint8_t mask = (1 << position);
//        uint8_t highligted_bit = number & mask;

//        return highligted_bit >> position;
//    }

    uint8_t nth_bit(size_t value, size_t pos)
    {
        size_t mask = (1 << pos);
        size_t highligted_bit = value & mask;

        return highligted_bit >> pos;
    }

    uint8_t insert_bit_in_byte(uint8_t bit, size_t pos_shift, uint8_t current_byte)
    {
        uint8_t mask;

        if((int)bit)
        {
            mask = 1 << pos_shift;
            return mask | current_byte;
        }
        {
            mask = ~(1 << pos_shift);
            return mask & current_byte;
        }
    }

//    size_t insert_bit_in_byte(uint8_t bit, size_t pos_shift, size_t current_byte)
//    {
//        size_t mask;

//        if(bit)
//        {
//            mask = 1 << pos_shift;
//            return mask | current_byte;
//        }
//        {
//            mask = ~(1 << pos_shift);
//            return mask & current_byte;
//        }
//    }

    uint8_t hide_data(uint8_t hidden_bit, uint8_t color_byte)
    {
        uint8_t modify_byte = insert_bit_in_byte(hidden_bit, 0, color_byte);

        return modify_byte;
    }

    uint8_t set_lowest_bit(uint8_t set_bit,  uint8_t byte)
    {
        return (byte & 0b11111110) | set_bit;
    }

    uint8_t read_data(uint8_t color)
    {
        uint8_t find_bit = nth_bit(color, 0);

        return find_bit;
    }

    uint8_t get_lowest_bit(uint8_t number)
    {
        return number & 1;
    }
}
