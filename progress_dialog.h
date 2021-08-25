#ifndef PROGRESS_DIALOG_H
#define PROGRESS_DIALOG_H

#include <QDialog>


namespace Ui {
class Progress_Dialog;
}

class Progress_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Progress_Dialog(QWidget *parent = nullptr);
    ~Progress_Dialog();

public slots:
    void set_reset();
    void set_range(int min, int max);
    void set_progress(int value);
    void set_step(QString step);

private:
    Ui::Progress_Dialog *ui;
};

#endif // PROGRESS_DIALOG_H
