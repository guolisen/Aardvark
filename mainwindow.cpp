#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<int> l;
    l.push_back(20);
    l.push_back(80);
    ui->splitter->setSizes(l);
}
MainWindow::~MainWindow()
{
    delete ui;
}
