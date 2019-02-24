#include "widget.h"
#include <QFile>
#include <QApplication>
#include "commonhelper.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CommonHelper::setStyle("style.qss");

    Widget w;
    w.show();

    return a.exec();
}
