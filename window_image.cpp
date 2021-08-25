#include "window_image.h"
#include "ui_window_image.h"
#include <QFile>


Window_Image::Window_Image(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window_Image)
{
    ui->setupUi(this);
}

Window_Image::~Window_Image()
{
    std::for_each(garbage.begin(), garbage.end(),
                  static_cast<void(*)(void*)>(operator delete));

    delete ui;
}

QString Window_Image::file_dialog()
{
    QFileDialog file_dialog(this);
    file_dialog.exec();
    QStringList path_list = file_dialog.selectedFiles();

    return path_list.front();
}

void Window_Image::on_pushButton_path_image_clicked()
{
    QString path_image = file_dialog();
    ui->lineEdit_Path->setText(path_image);

    QString path_save = path_image;
    path_save.insert(path_save.lastIndexOf('.'), " - hidden");

    ui->lineEdit_Path_Save->setText(path_save);
}

void Window_Image::on_pushButton_path_data_clicked()
{
    QString path_data = file_dialog();
    ui->lineEdit_data->setText(path_data);
}

void Window_Image::on_pushButton_path_save_clicked()
{
    QString path_save = file_dialog();
    ui->lineEdit_Path_Save->setText(path_save);
}

void Window_Image::on_pushButton_Hide_clicked()
{
    QString path_image = ui->lineEdit_Path->text();
    QString path_data = ui->lineEdit_data->text();
    QString path_save = ui->lineEdit_Path_Save->text();

    m_worked_thread = new Worker_Thread_Hide(path_image, path_data, path_save);
    garbage.push_back(m_worked_thread);

    connect(m_worked_thread, &Worker_Thread_Hide::started, &wait_window, &Progress_Dialog::set_reset);
    connect(m_worked_thread, &Worker_Thread_Hide::progress_step, &wait_window, &Progress_Dialog::set_step);
    connect(m_worked_thread, &Worker_Thread_Hide::progress_range, &wait_window, &Progress_Dialog::set_range);
    connect(m_worked_thread, &Worker_Thread_Hide::progress_value, &wait_window, &Progress_Dialog::set_progress);
    connect(m_worked_thread, &Worker_Thread_Hide::started, &wait_window, &QDialog::exec);
    connect(m_worked_thread, &Worker_Thread_Hide::finished, &wait_window, &QDialog::accept);
    m_worked_thread->start();

    ui->lineEdit_Path->clear();
    ui->lineEdit_Path_Save->clear();
    ui->lineEdit_data->clear();
}

void Window_Image::on_pushButton_Image_hidden_clicked()
{
    QString path_img_hide = file_dialog();
    ui->lineEdit_Path_img_hidden->setText(path_img_hide);
}

void Window_Image::on_pushButton_Data_save_clicked()
{
    QString path_data_save = file_dialog();
    ui->lineEdit_Path_save_data->setText(path_data_save);
}

void Window_Image::on_pushButton_Load_clicked()
{
    QString path_image = ui->lineEdit_Path_img_hidden->text();
    QString path_save = ui->lineEdit_Path_save_data->text();

    m_worked_thread = new Worker_Thread_Load(path_image, path_save);
    garbage.push_back(m_worked_thread);

    connect(m_worked_thread, &Worker_Thread_Load::started, &wait_window, &Progress_Dialog::set_reset);
    connect(m_worked_thread, &Worker_Thread_Load::progress_step, &wait_window, &Progress_Dialog::set_step);
    connect(m_worked_thread, &Worker_Thread_Load::progress_range, &wait_window, &Progress_Dialog::set_range);
    connect(m_worked_thread, &Worker_Thread_Load::progress_value, &wait_window, &Progress_Dialog::set_progress);
    connect(m_worked_thread, &Worker_Thread_Load::started, &wait_window, &QDialog::exec);
    connect(m_worked_thread, &Worker_Thread_Load::finished, &wait_window, &QDialog::accept);
    m_worked_thread->start();

    ui->lineEdit_Path_img_hidden->clear();
    ui->lineEdit_Path_save_data->clear();
}

void Window_Image::on_pushButton_Cancel_Hide_clicked()
{
    ui->lineEdit_Path->clear();
    ui->lineEdit_data->clear();
    ui->lineEdit_Path_Save->clear();
}

void Window_Image::on_pushButton_Cancel_Load_clicked()
{
    ui->lineEdit_Path_img_hidden->clear();
    ui->lineEdit_Path_save_data->clear();
}
