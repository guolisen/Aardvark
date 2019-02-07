#include <QTabBar>
#include <QFileDialog>
#include "mainwindow.h"
#include "logdocwindow.h"
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

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *newAct = new QAction(tr("&Open"), this);
    newAct->setShortcuts(QKeySequence::Open);
    newAct->setStatusTip(tr("Open a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(newAct);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    const QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        openFile(fileName);
}

bool MainWindow::openFile(const QString &fileName)
{
    if (QMdiSubWindow *existing = findMdiChild(fileName)) {
        ui->mdiArea->setActiveSubWindow(existing);
        return true;
    }
    const bool succeeded = loadFile(fileName);
    if (succeeded)
        statusBar()->showMessage(tr("File loaded"), 2000);
    return succeeded;
}

bool MainWindow::loadFile(const QString &fileName)
{
    LogDocWindow *child = createMdiChild();
    const bool succeeded = child->loadFile(fileName);
    if (succeeded)
        child->show();
    else
        child->close();
    //MainWindow::prependToRecentFiles(fileName);
    return succeeded;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName) const
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()) {
        LogDocWindow *mdiChild = qobject_cast<LogDocWindow *>(window->widget());
        if (mdiChild->currentFile() == canonicalFilePath)
            return window;
    }

    return nullptr;
}

LogDocWindow *MainWindow::createMdiChild()
{
    LogDocWindow *child = new LogDocWindow;
    ui->mdiArea->addSubWindow(child);

#ifndef QT_NO_CLIPBOARD
    //connect(child, &QTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
    //connect(child, &QTextEdit::copyAvailable, copyAct, &QAction::setEnabled);
#endif

    return child;
}
