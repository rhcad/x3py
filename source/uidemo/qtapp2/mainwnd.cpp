#include "mainwnd.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{
}

#include "moc_mainwnd.cpp"
