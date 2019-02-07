#include <QTabBar>
#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <Qsci/qsciscintilla.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<int> l;
    l.push_back(20);
    l.push_back(80);
    ui->splitter->setSizes(l);

    Q_FOREACH (QTabBar* tab, ui->mdiArea->findChildren<QTabBar *>())
    {
        tab->setDrawBase(false);
        tab->setExpanding(false);
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}
