#include "widget.h"
#include "ui_widget.h"
#include "QProcess"
#include "myhighlighter.h"
#include <string.h>
#include<string>
#include<iostream>
#include<fstream>
#include "commonhelper.h"

using namespace std;


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setMaximumSize(1000,600);
    this->setMinimumSize(1000,600);

    this->setStyleSheet("font-size:16px");
    Widget::setWindowTitle("Min-C-Interpreter");

    configEditor = new CodeEditor();
    configEditor->setMode(EDIT);
    ui->gridLayout->addWidget(configEditor);
    new MyHighLighter(configEditor->document());   //语法高亮

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()     //打开按钮点击事件
{
    openFileSlot();
}


void Widget::openFileSlot()             //打开文件
{
    QString fileName = QFileDialog::getOpenFileName(this,NULL,NULL,"*.h *.cpp *.txt");
    QString currentName = fileName;

    QFile file(fileName);

    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream textStream(&file);
        while(!textStream.atEnd()){
            configEditor->appendPlainText(textStream.readLine());
        }
    }else{
        return;
    }
}



void Widget::on_pushButton_2_clicked()       //清除所有代码
{
    configEditor->setPlainText("");
}

void Widget::on_pushButton_8_clicked()
{
    QString str = configEditor->toPlainText();
    string code = str.toStdString();
    ofstream file;
    file.open("test.txt");
    file << code;
    file.close();
    system("main.exe");
    return ;
}

void Widget::on_pushButton_4_clicked()
{
    CommonHelper::setStyle("style2.qss");
}

void Widget::on_pushButton_5_clicked()
{
    CommonHelper::setStyle("style.qss");
}

void Widget::saveFileSlot()             //保存文件
{
  QString fileName = QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());
  if(fileName.isEmpty()){
      return;
  }
  QFile *file = new QFile;
  file->setFileName(fileName);
  bool ok = file->open(QIODevice::WriteOnly);
  if(ok){
      QTextStream out(file);
      out<<configEditor->toPlainText();
      file->close();
      delete file;
  }else{
      return;
  }
}

void Widget::on_pushButton_3_clicked()
{
    saveFileSlot();
}
