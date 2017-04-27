#include "checkdialog.h"
#include "ui_checkdialog.h"
#include <QPainter>
#include <QDebug>
#define WORD_WARNING  QStringLiteral("您Word程序已经打开，麻烦您手动关闭后再继续")
#define WORD_WARNING_1  QStringLiteral("您还存在Word程序已打开，麻烦您手动关闭后再继续")

CheckDialog::CheckDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    mouse_press = false;
    ui->label->setStyleSheet("QLabel{\
                             font: 10pt \"微软雅黑\";\
                             color:#E6E6E6;\
                             background-color: transparent;\
                         }");
        qDebug()<<Q_FUNC_INFO<<ui->topWidget->geometry();
}

CheckDialog::~CheckDialog()
{
    delete ui;
}

void CheckDialog::on_pushButton_clicked()
{
    BDWordProcess wordPro;
    //word 已经不存在啦
    if(!wordPro.checkWordExist()){
        ui->label->setText(WORD_WARNING);
        ui->label->setStyleSheet("QLabel{\
                                 font: 10pt \"微软雅黑\";\
                                 color:#E6E6E6;\
                                 background-color: transparent;\
                             }");
        this->accept();
    }else{
        ui->label->setText(WORD_WARNING_1);
        ui->label->setStyleSheet("QLabel{\
                                 font: 10pt \"微软雅黑\";\
                                 color:red;\
                                 background-color: transparent;\
                             }");
    }
}

void CheckDialog::mousePressEvent(QMouseEvent *event)
{
    if(!ui->topWidget->rect().contains(mapFromGlobal(event->globalPos())))return;
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }else{
       mouse_press = false;
    }
    //窗口移动距离
    move_point = event->globalPos() - pos();
}

void CheckDialog::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void CheckDialog::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}
