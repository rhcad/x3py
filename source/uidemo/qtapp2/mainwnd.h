#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include "ui_app.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

private:
    Ui::AppClass ui;
};

#endif // APP_H
