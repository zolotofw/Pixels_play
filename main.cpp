#include "window_image.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window_Image w;
    w.show();
    return a.exec();
}
