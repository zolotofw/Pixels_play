#include "progress_dialog.h"
#include "ui_progress_dialog.h"


Progress_Dialog::Progress_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Progress_Dialog)
{
    ui->setupUi(this);
}

Progress_Dialog::~Progress_Dialog()
{
    delete ui;
}

void Progress_Dialog::set_reset()
{
    ui->progressBar_loading->reset();
}

void Progress_Dialog::set_range(int min, int max)
{
    ui->progressBar_loading->setRange(min, max);
}

void Progress_Dialog::set_progress(int value)
{
    ui->progressBar_loading->setValue(value);
}

void Progress_Dialog::set_step(QString step)
{
    ui->label->setText(step);
}
