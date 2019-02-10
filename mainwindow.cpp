#include <QTabBar>
#include <QFileDialog>
#include <QListView>
#include <QDockWidget>
#include "mainwindow.h"
#include "logdocwindow.h"
#include "SettingPanel/settingpanel.h"
#include "ui_mainwindow.h"
#include "texteditorconfig.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);

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

    QMenu *confgiMenu = menuBar()->addMenu(tr("&Config"));
    QAction *settingAct = new QAction(tr("&Preferences"), this);
    settingAct->setShortcuts(QKeySequence::Preferences);
    settingAct->setStatusTip(tr("Open Preferences"));
    connect(settingAct, &QAction::triggered, this, [this](){
        SettingPanel w(this);
        if (w.exec() != QDialog::Accepted)
            return;
    });
    confgiMenu->addAction(settingAct);

    setDockNestingEnabled(true);
    QDockWidget *dw = new QDockWidget;
    dw->setWidget(new QListView);
    //dw->setObjectName("dock1");
    dw->setWindowTitle("dock2");
    addDockWidget(Qt::LeftDockWidgetArea, dw);
    QDockWidget *dw1 = new QDockWidget;
    dw1->setWidget(new QListView);
    //dw1->setObjectName("dock3");
    dw1->setWindowTitle("dock4");
    addDockWidget(Qt::LeftDockWidgetArea, dw1);
    tabifyDockWidget(dw, dw1);
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
    {
        child->setWindowTitle(QFileInfo(fileName).fileName());
        child->show();
    }
    else
        child->close();

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
    TextEditorConfigPtr configer = std::make_shared<TextEditorConfig>();
    LogDocWindow *child = new LogDocWindow(configer);
    ui->mdiArea->addSubWindow(child);

#ifndef QT_NO_CLIPBOARD
    //connect(child, &QTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
    //connect(child, &QTextEdit::copyAvailable, copyAct, &QAction::setEnabled);
#endif

    return child;
}
