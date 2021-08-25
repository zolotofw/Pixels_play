#ifndef ITR_BIT_OOP_H
#define ITR_BIT_OOP_H
#include "utils_iterator.h"

template<typename tools>
class itr_type
{
    public:
    virtual itr_type& operator++() = 0;
    virtual bool operator!=(itr_type& another) = 0;
    virtual tools operator*() = 0;
};

class tool_bit;


class itr_bit_oop : public itr_type <tool_bit>
{
    friend tool_bit;
public:
    itr_bit_oop(QByteArray& arr);
    itr_bit_oop(itr_bit_oop& obj);
    itr_bit_oop(QByteArray& arr, size_t length_arr);

    virtual itr_type<tool_bit>& operator++() override;
    virtual bool operator!=(itr_type<tool_bit>& another) override;
    tool_bit operator*();

private:
    QByteArray& m_byte_array;
    size_t m_index;
    const size_t LENGTH_BIT = 8;

};

class tool_bit
{
public:
    tool_bit(itr_bit_oop& itr);
    operator uint8_t();
    tool_bit& operator=(uint8_t bit);

private:
    itr_bit_oop& m_itr;
};


#endif // ITR_BIT_OOP_H
