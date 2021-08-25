#include "iterator_bit.h"

iterator_bit::iterator_bit(const iterator_bit& obj)
             : m_byte_array(obj.m_byte_array), m_index(obj.m_index)
{

}

iterator_bit::iterator_bit(QByteArray& arr, size_t index)
             :m_byte_array(arr), m_index(index)
{

}

itr_tool_bit iterator_bit::operator*()
{
    return itr_tool_bit(*this);
}

iterator_bit iterator_bit::operator++(int)
{
    iterator_bit temp(*this);

    ++m_index;

    return temp;
}

iterator_bit& iterator_bit::operator++()
{
    ++m_index;

    return *this;
}

iterator_bit iterator_bit::operator+(size_t index)
{
    assert(index < m_byte_array.size());

    iterator_bit temp(*this);
    temp.m_index += index;

    return temp;
}

bool iterator_bit::operator!=(const iterator_bit& another)
{
    return m_index != another.m_index;
}

itr_tool_bit::itr_tool_bit(iterator_bit& itr)
            :m_itr(itr)
{

}

iterator_bit& iterator_bit::operator=(iterator_bit &itr)
{
    m_byte_array = itr.m_byte_array;
    m_index = itr.m_index;

    return *this;
}

itr_tool_bit::operator uint8_t()
{
    utils_itr_bit::pos_byte_bit position
            = utils_itr_bit::calculate_indexs_byte_bit(LENGTH_BIT, m_itr.m_index);

    uint8_t current_byte = m_itr.m_byte_array[position.index_byte];
    uint8_t current_bit = utils_itr_bit::nth_bit(current_byte,position.index_bit);

    return current_bit;
}

itr_tool_bit& itr_tool_bit::operator=(uint8_t bit)
{
    utils_itr_bit::pos_byte_bit position
            = utils_itr_bit::calculate_indexs_byte_bit(LENGTH_BIT, m_itr.m_index);

    uint8_t current_byte = m_itr.m_byte_array[position.index_byte];
    uint8_t modify_byte = utils_itr_bit::insert_bit_in_byte(bit, position.index_bit, current_byte);
    m_itr.m_byte_array[position.index_byte] = modify_byte;

    return *this;
}

const_iterator_bit::const_iterator_bit(const const_iterator_bit& another)
                   : m_byte_array(another.m_byte_array), m_index(another.m_index)
{

}

const_iterator_bit::const_iterator_bit(const QByteArray& arr, size_t index)
                   : m_byte_array(arr), m_index(index)
{

}

uint8_t const_iterator_bit::operator*() const
{
    utils_itr_bit::pos_byte_bit position
            = utils_itr_bit::calculate_indexs_byte_bit(LENGTH_BIT, m_index);

    uint8_t current_byte = m_byte_array[position.index_byte];
    uint8_t current_bit = utils_itr_bit::nth_bit(current_byte,position.index_bit);

    return current_bit;
}

const_iterator_bit& const_iterator_bit::operator++()
{
    ++m_index;

    return *this;
}

const_iterator_bit const_iterator_bit::operator++(int)
{
    const_iterator_bit temp(*this);

    return temp;
}

bool const_iterator_bit::operator!=(const const_iterator_bit& another) const
{
    return m_index != another.m_index;
}




