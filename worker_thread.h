#ifndef WORKED_THREAD_H
#define WORKED_THREAD_H
#include <QThread>

class Worked_Thread : public QThread
{
Q_OBJECT

signals:
    void progress_range(int min, int max);
    void progress_value(int value);
    void progress_step(QString message);

};

class Worker_Thread_Hide : public Worked_Thread //,public QThread
{

public:
    Worker_Thread_Hide(){};
    Worker_Thread_Hide(const QString& path_img, const QString& path_data, const QString& path_save);

    void run()override;

private:
    QString m_path_img;
    QString m_path_data;
    QString m_path_save;

};

class Worker_Thread_Load : public Worked_Thread
{

public:
    Worker_Thread_Load(const QString& path_img, const QString& path_save);

    void run()override;

private:
    QString m_path_img;
    QString m_path_save;
};

#endif // WORKED_THREAD_H
