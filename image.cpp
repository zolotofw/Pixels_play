#include "image.h"
#include <QFile>

namespace utl_img
{
    Formats detect_format_image( const QString& path)
    {
        QByteArray img_format = QImageReader::imageFormat(path);

        QList<QByteArray> kinds_img = QImageReader::supportedImageFormats();

        switch (kinds_img.indexOf(img_format))
        {
            case 5 :
            case 6 :
                return JPG;

            case 9 :
                return PNG;

            default :
                return UNSUPPORTED;
        }
    }

    std::unique_ptr<Interface_Image> create_img(const QString& path)
    {
        switch (detect_format_image(path))
        {
            case JPG :
                break;

            case PNG :
                 return unique_ptr<Interface_Image>(new Image(path));

            case UNSUPPORTED:
            throw QString("UNSUPPORTED");
        }

        return nullptr;
    }
}


Image::Image()
{

}

Image::Image(const QString& path)
      : m_hide_image(path), m_position(&m_hide_image, 0)
{

}

Image::Image(const Image& another)
      :m_hide_image(another.m_hide_image), m_position(another.m_position)
{

}

void Image::hide(const QByteArray& array)
{
    bool check = is_enough_capacity(m_hide_image, array);
    assert(check);

    m_position = std::transform(const_iterator_bit(array, 0),const_iterator_bit(array, array.size() * 8),
                   const_iterator_bit(array, 0), m_position, utils_itr_bit::set_lowest_bit);
}

void Image::hide(const QByteArray& array, const std::function<void(uint32_t)>& signal_prog_bar)
{
    bool check = is_enough_capacity(m_hide_image, array);
    assert(check);

    const_iterator_bit begin_bit(array, 0);
    const_iterator_bit end_bit(array, array.size() * 8);

    for(unsigned int i = 0; begin_bit != end_bit; ++i, ++begin_bit, ++m_position)
    {
        *m_position = utils_itr_bit::set_lowest_bit(*begin_bit, *m_position);
        signal_prog_bar(i);
    }
}

QByteArray Image::load(size_t length)
{
    QByteArray array;
    array.reserve(length);

    iterator_image last(m_position + length * 8);

    std::transform(m_position, last, iterator_bit(array, 0), utils_itr_bit::get_lowest_bit);
    m_position = last;

    return array;
}


QByteArray Image::load(size_t length, const std::function<void(uint32_t)>& signal_prog_bar)
{
    QByteArray array;
    array.reserve(length);

    iterator_image last(m_position + length * 8);

    iterator_bit read_bit(array, 0);
    for(unsigned int i = 0; m_position != last; ++i, ++m_position, ++read_bit)
    {
        *read_bit = utils_itr_bit::get_lowest_bit(*m_position);
        signal_prog_bar(i);
    }

    return array;
}

bool Image::save(const QString& path)
{
    return m_hide_image.save(path);
}
