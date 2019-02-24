#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QtDebug>
#include "codeeditor.h"
#include "myhighlighter.h"
#include "typedef.h"
#include "string"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void openFileSlot();
    void saveFileSlot();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    CodeEditor *configEditor;
};


#endif // WIDGET_H
