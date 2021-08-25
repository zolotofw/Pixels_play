#include "itr_bit_oop.h"

itr_bit_oop::itr_bit_oop(QByteArray& arr)
    : m_byte_array(arr), m_index(0)
{

}

itr_bit_oop::itr_bit_oop(itr_bit_oop& obj)
             : m_byte_array(obj.m_byte_array),m_index(obj.m_index)
{

}

itr_bit_oop::itr_bit_oop(QByteArray& arr, size_t length_arr)
            :m_byte_array(arr)
{
    m_index = LENGTH_BIT * length_arr;
}

itr_type<tool_bit>& itr_bit_oop::operator++()
{
    ++m_index;
    return *this;
}

bool itr_bit_oop::operator!=(itr_type<tool_bit> &another)
{
    itr_bit_oop an = static_cast<itr_bit_oop&>(another);
    return m_index != an.m_index;
}

tool_bit itr_bit_oop::operator*()
{
    return tool_bit( *this );
}

tool_bit::tool_bit(itr_bit_oop& ref)
         :m_itr(ref)
{

}

tool_bit::operator uint8_t()
{
    utils_itr_bit::pos_byte_bit position
            = utils_itr_bit::calculate_indexs_byte_bit(m_itr.LENGTH_BIT, m_itr.m_index);

    uint8_t current_byte = m_itr.m_byte_array[position.index_byte];
    uint8_t current_bit = utils_itr_bit::nth_bit(current_byte,position.index_bit);

    return current_bit;
}

tool_bit& tool_bit::operator=(uint8_t bit)
{
    utils_itr_bit::pos_byte_bit position
            = utils_itr_bit::calculate_indexs_byte_bit(m_itr.LENGTH_BIT, m_itr.m_index);

    uint8_t current_byte = m_itr.m_byte_array[position.index_byte];
    uint8_t modify_byte = utils_itr_bit::insert_bit_in_byte(bit, position.index_bit, current_byte);

    m_itr.m_byte_array[position.index_byte] = modify_byte;

    return *this;
}
