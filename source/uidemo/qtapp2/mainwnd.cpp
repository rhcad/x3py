#include "mainwnd.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{
}

#include "moc_mainwnd.cpp"
