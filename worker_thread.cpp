#include <QFile>
#include "worker_thread.h"
#include "image.h"
#include <memory>


using namespace placeholders;

Worker_Thread_Hide::Worker_Thread_Hide(const QString& path_img, const QString& path_data, const QString& path_save)
                   : m_path_img(path_img), m_path_data(path_data), m_path_save(path_save)
{

}

void Worker_Thread_Hide::run()
{
    emit progress_step("Image open");
    std::unique_ptr<Interface_Image> img;
    try
    {
        img = utl_img::create_img(m_path_img);
    }
    catch (const QString& exp)
    {
        emit progress_step(exp);
        terminate();
        wait();
    }

    QFile file(m_path_data);
    QByteArray data;
    if(file.open(QIODevice::ReadOnly))
    {
        data = file.read(file.size());
    }

    size_t size = data.size();

    QByteArray data_size (reinterpret_cast<char*>(&size), sizeof (size));
    img->hide(data_size);

    unsigned int size_loading = data.size() * 8;
    emit progress_range(0, size_loading);

    emit progress_step("Data hide");
    img->hide(data, [this](int v)
                        {
                             this-> emit progress_value(v);
                        });

    emit progress_step("Data save");
    img->save(m_path_save);
}

Worker_Thread_Load::Worker_Thread_Load(const QString& path_img, const QString& path_save)
                   :m_path_img(path_img), m_path_save(path_save)
{

}

void Worker_Thread_Load::run()
{
    emit progress_step("Image open");
    std::unique_ptr<Interface_Image> img;

    try
    {
        img = utl_img::create_img(m_path_img);
    }
    catch (const QString& exp)
    {
        emit progress_step(exp);
        terminate();
        wait();
    }

    QByteArray data_size = img->load(sizeof (size_t));

    size_t length = *reinterpret_cast<size_t*>(data_size.data());
    emit progress_range(0, length);

    emit progress_step("Data load");
    QByteArray data = img->load(length, [this](int v)
                                         {
                                             this-> emit progress_value(v);
                                         });
    emit progress_step("Data write");
    QFile file_wr(m_path_save);
    if(file_wr.open(QIODevice::WriteOnly))
    {
        file_wr.write(data);
    }
}
