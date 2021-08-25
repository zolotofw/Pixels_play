#ifndef IMAGE_H
#define IMAGE_H
#include <QImage>
#include <QImageReader>
#include "iterator_image.h"
#include "iterator_bit.h"
#include "utils_iterator.h"

enum Formats
{
    JPG,
    PNG,
    UNSUPPORTED
};

class Interface_Image;

namespace utl_img
{    
    Formats detect_format_image( const QString& path);
    std::unique_ptr<Interface_Image> create_img(const QString& path);
}

class Interface_Image
{
public:
    virtual void hide(const QByteArray& array) = 0;
    virtual void hide(const QByteArray& array,  const std::function<void(uint32_t)>& functor) = 0;
    virtual QByteArray load(size_t length) = 0;
    virtual QByteArray load(size_t length, const std::function<void(uint32_t)>& functor) = 0;
    virtual bool save(const QString& path) = 0;

};

class Image : public Interface_Image
{
public:
    Image();
    Image(const QString& path);
    Image(const Image& another);

    void hide(const QByteArray& array) override;
    void hide(const QByteArray& array,  const std::function<void(uint32_t)>& signal_prog_bar) override;
    QByteArray load(size_t length) override;
    QByteArray load(size_t length, const std::function<void(uint32_t)>& signal_prog_bar) override;
    bool save(const QString& path) override;

protected:
    QImage m_hide_image;
    iterator_image m_position;
};


#endif // IMAGE_H
