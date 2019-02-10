#include <QtWidgets>
#include "logdocwindow.h"
#include "ui_logdocwindow.h"
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercmake.h>
#include <Qsci/qscilexercem.h>

LogDocWindow::LogDocWindow(TextEditorConfigPtr configer, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogDocWindow),
    curFile_("")
{
    ui->setupUi(this);

    setStyleSheet("QCheckBox{font-family:arial;font-size:13px;border-radius:2px;color:#000000;}"
                  "QCheckBox::indicator:checked{color:#FF0000}"
                  "QLabel,QRadioButton{background:transparent;color:#000000;font-family:arial;font-size:15px;}"
                  "QComboBox{background:transparent;border:1px solid #d7d7d7; border-radius: 3px; padding: 1px 3px 1px 3px;}"
                  "QComboBox:editable{background:transparent;}"
                  "QComboBox::down-arrow:on {top: 1px;left: 1px;}"
                  "QGroupBox{font-family:arial;font-size:13px;color:#000000;}"
                  "QFontComboBox{background:white;border:1px solid #d7d7d7; border-radius: 3px; padding: 1px 3px 1px 3px;}"
                  "QPushButton{color: #f0f0f0;border: 1px solid #bbbbbb;font: 8pt \"Arial\";border-radius: 6px;padding: 5px;background: qradialgradient(cx: 0.3, cy: -0.4,fx: 0.3, fy: -0.4,radius: 3, stop: 0 #828282, stop: 1 #969696);min-width: 80px;}"
                  "QPushButton:hover {background: qradialgradient(cx: 0.3, cy: -0.4,fx: 0.3, fy: -0.4,radius: 3, stop: 0 #828282, stop: 1 #969696);}"
                  "QPushButton:pressed {background: qradialgradient(cx: 0.4, cy: -0.1,fx: 0.4, fy: -0.1,radius: 3, stop: 0 #828282, stop: 1 #969696);}");

    textMain_  = new QsciScintilla(this);
    textLexer_ = new QsciLexerCem(this);
    textMain_->setLexer(textLexer_);

    configer->Config(textMain_);

    setCentralWidget(textMain_);
    setAttribute(Qt::WA_DeleteOnClose);

    createFindBar();
}

LogDocWindow::~LogDocWindow()
{
    delete ui;
    delete textMain_;
    delete textLexer_;
}

void LogDocWindow::createFindBar()
{
    QToolBar *fileToolBar = new QToolBar(this);
    addToolBar(Qt::BottomToolBarArea, fileToolBar);
    QLabel* nameLabel_ = new QLabel(tr("Find:"));
    QLineEdit* findEdit_ = new QLineEdit;
    findEdit_->setGeometry(0,0,500,35);
    findEdit_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    QPushButton* findNext_ = new QPushButton(tr("Find Next"));
    QPushButton* markAll_ = new QPushButton(tr("Mark All"));

    QAction *wordAct = new QAction(QIcon(":/res/FindTB/word24"), tr("&Word"), this);
    wordAct->setCheckable(true);
    QAction *caseAct = new QAction(QIcon(":/res/FindTB/case24"), tr("&Case"), this);
    caseAct->setCheckable(true);
    QAction *regexAct = new QAction(QIcon(":/res/FindTB/regex24"), tr("&Regex"), this);
    regexAct->setCheckable(true);
    QAction *backslashAct = new QAction(QIcon(":/res/FindTB/backslash24"), tr("&Backslash"), this);
    backslashAct->setCheckable(true);
    QAction *aroundAct = new QAction(QIcon(":/res/FindTB/around24"), tr("&Around"), this);
    aroundAct->setCheckable(true);
    QAction *upAct = new QAction(QIcon(":/res/FindTB/up24"), tr("&Up"), this);
    upAct->setCheckable(true);
    //newAct->setShortcuts(QKeySequence::New);
    //newAct->setStatusTip(tr("Create a new file"));
    //connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    QAction *closeAct = new QAction(QIcon(":/res/SettingPanel/close_pressed"), tr("&Close"), this);
    fileToolBar->addAction(closeAct);
    fileToolBar->addWidget(nameLabel_);
    fileToolBar->addWidget(findEdit_);
    fileToolBar->addSeparator();
    fileToolBar->addWidget(findNext_);
    fileToolBar->addWidget(markAll_);
    fileToolBar->addAction(wordAct);
    fileToolBar->addAction(caseAct);
    fileToolBar->addAction(regexAct);
    fileToolBar->addAction(backslashAct);
    fileToolBar->addAction(aroundAct);
    fileToolBar->addAction(upAct);
}

bool LogDocWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textMain_->setText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);

    return true;
}
