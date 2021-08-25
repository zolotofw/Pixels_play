#ifndef WINDOW_IMAGE_H
#define WINDOW_IMAGE_H

#include <QMainWindow>
#include <QFileDialog>
#include <progress_dialog.h>
#include "worker_thread.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Window_Image; }
QT_END_NAMESPACE


class Window_Image : public QMainWindow
{
    Q_OBJECT

public:
    Window_Image(QWidget *parent = nullptr);
    ~Window_Image();
    QString file_dialog();

private slots:
    void on_pushButton_path_image_clicked();

    void on_pushButton_path_data_clicked();

    void on_pushButton_path_save_clicked();

    void on_pushButton_Load_clicked();

    void on_pushButton_Hide_clicked();

    void on_pushButton_Image_hidden_clicked();

    void on_pushButton_Data_save_clicked();

    void on_pushButton_Cancel_Hide_clicked();

    void on_pushButton_Cancel_Load_clicked();

private:
    Ui::Window_Image *ui;
    Progress_Dialog wait_window;
    Worked_Thread* m_worked_thread;
    QVector<QThread*> garbage;
};
#endif // WINDOW_IMAGE_H
