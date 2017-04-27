#ifndef CHECKDIALOG_H
#define CHECKDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "bdwordprocess.h"

namespace Ui {
class CheckDialog;
}

class CheckDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckDialog(QWidget *parent = 0);
    ~CheckDialog();

private slots:
    void on_pushButton_clicked();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
//    void paintEvent(QPaintEvent *event);
private:
    Ui::CheckDialog *ui;
    QPoint move_point; //移动的距离
    bool mouse_press;  //按下鼠标左键
};

#endif // CHECKDIALOG_H
