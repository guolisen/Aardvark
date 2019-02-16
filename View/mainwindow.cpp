#include <QTabBar>
#include <QFileDialog>
#include <QListView>
#include <QDockWidget>
#include "mainwindow.h"
#include "logdocwindow.h"
#include "SettingPanel/settingpanel.h"
#include "ui_mainwindow.h"
#include <Core/configmgr.h>
#include <View/SettingPanel/settingpanel.h>


MainWindow::MainWindow(core::ContextPtr context, QWidget *parent) :
    QMainWindow(parent),
    context_(context),
    ui(new Ui::MainWindow),
    settingPanel_(new SettingPanel(context, this))
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
    ui->mdiArea->setDocumentMode(true);

    Q_FOREACH (QTabBar* tab, ui->mdiArea->findChildren<QTabBar *>())
    {
        tab->setDrawBase(false);
        tab->setExpanding(false);
        tab->setAutoFillBackground(true);
    }

    createMenu();
    createDock();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createDock()
{
    setDockNestingEnabled(true);
    QDockWidget *dw = new QDockWidget;
    dw->setWidget(new QListView);
    dw->setWindowTitle("dock2");
    addDockWidget(Qt::LeftDockWidgetArea, dw);
    QDockWidget *dw1 = new QDockWidget;
    dw1->setWidget(new QListView);
    dw1->setWindowTitle("dock4");
    addDockWidget(Qt::LeftDockWidgetArea, dw1);
    tabifyDockWidget(dw, dw1);
}

void MainWindow::createMenu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *newAct = new QAction(tr("&Open"), this);
    newAct->setShortcuts(QKeySequence::Open);
    newAct->setStatusTip(tr("Open a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(newAct);

    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    QAction *addRegexWinAct = new QAction(tr("&Add Regex Win"), this);
    addRegexWinAct->setStatusTip(tr("Add Regex Win"));
    connect(addRegexWinAct, &QAction::triggered, this, [this](){
        QMdiSubWindow* currentWin = ui->mdiArea->currentSubWindow();
        if (!currentWin)
            return;
        LogDocWindow* currentChild = dynamic_cast<LogDocWindow*>(currentWin->widget());
        if (!currentChild)
            return;
        currentChild->popAddRegexWin();
    });
    viewMenu->addAction(addRegexWinAct);

    QMenu *confgiMenu = menuBar()->addMenu(tr("&Config"));
    QAction *settingAct = new QAction(tr("&Preferences"), this);
    settingAct->setShortcuts(QKeySequence::Preferences);
    settingAct->setStatusTip(tr("Open Preferences"));
    connect(settingAct, &QAction::triggered, this, [this](){
        if (settingPanel_->exec() != QDialog::Accepted)
            return;
    });
    confgiMenu->addAction(settingAct);
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
    LogDocWindow *child = new LogDocWindow(ui->mdiArea, context_);
    ui->mdiArea->addSubWindow(child);

#ifndef QT_NO_CLIPBOARD
    //connect(child, &QTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
    //connect(child, &QTextEdit::copyAvailable, copyAct, &QAction::setEnabled);
#endif

    return child;
}
