#include <QtWidgets>
#include <QDebug>
#include <QRandomGenerator>
#include "logdocwindow.h"
#include "ui_logdocwindow.h"
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercmake.h>
#include <Qsci/qscilexercem.h>

void LogDocWindow::clearMarkClick()
{
    int line = -1;
    int index = -1;
    textMain_->getCursorPosition(&line, &index);
    QString posWord = textMain_->wordAtLineIndex(line, index);
    qDebug() << posWord;

    int indicator = -1;
    QString keyStr = "";
    IndicatorKeyWordMap::iterator iter = indicatorKeyWordMap_.begin();
    for(; iter != indicatorKeyWordMap_.end(); ++iter)
    {
        keyStr = iter.key();
        if (posWord.contains(keyStr, Qt::CaseInsensitive))
        {
            qDebug() << "Indicator: " << iter->indicatorNum;
            indicator = iter->indicatorNum;
            break;
        }
    }
    if (indicator < 0)
        return;
    clearIndicator(keyStr, indicator);
}
void LogDocWindow::createPopMenu()
{
    rightPopMenu_ = new QMenu(this);
    rightPopMenu_->addAction(tr("&Copy"), textMain_, SLOT(copy()));
    rightPopMenu_->addAction(tr("Clear Mark"), this, SLOT(clearMarkClick()));
    rightPopMenu_->addSeparator();
    rightPopMenu_->addAction(tr("Select All"), textMain_, SLOT(selectAll()));

    connect(textMain_, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showPopMenu(const QPoint&)));

    textMain_->setContextMenuPolicy(Qt::CustomContextMenu);
}

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
    setCentralWidget(textMain_);

    configer->Config(textMain_);

    setAttribute(Qt::WA_DeleteOnClose);

    createFindBar();
    createPopMenu();

    connect(textMain_, SIGNAL(indicatorClicked(int, int, Qt::KeyboardModifiers)), this, SLOT(IndicatorClicked(int, int, Qt::KeyboardModifiers)));

}

void LogDocWindow::IndicatorClicked(int line, int index, Qt::KeyboardModifiers state)
{
    state.testFlag(Qt::ControlModifier);
}

LogDocWindow::~LogDocWindow()
{
    delete ui;
    delete textMain_;
    delete textLexer_;
}

void LogDocWindow::findNextClick()
{
    QString findText = findEdit_->text();
    if (findText.isEmpty())
        return;
    findStr(findText);
}

bool LogDocWindow::findStr(const QString& targetStr)
{
    //wordAct_->isChecked();
    //caseAct_->isChecked();
    //regexAct_->isChecked();
    //backslashAct_->isChecked();
    //aroundAct_->isChecked();
    //upAct_->isChecked();
    return textMain_->findFirst(targetStr, regexAct_->isChecked(), caseAct_->isChecked(), wordAct_->isChecked(), aroundAct_->isChecked());
}

void LogDocWindow::clearIndicator(const QString& keyWord, int indicator)
{
    indicatorMap_[indicator].clear();
    IndicatorKeyWordMap::iterator iter = indicatorKeyWordMap_.find(keyWord);
    indicatorKeyWordMap_.erase(iter);
    //TODO: range
    int line = -1;
    int index = -1;
    textMain_->lineIndexFromPosition(textMain_->length(), &line, &index);
    textMain_->clearIndicatorRange(0, 0, line, index, indicator);
}

bool LogDocWindow::isSetIndicator(int lineFrom, int indexFrom, int lineTo, int indexTo, int indicatorNumber)
{
    QList<IndicatorEntry> list = getIndicatorList(lineFrom, indexFrom,
                                                  lineTo, indexTo, indicatorNumber);
    IndicatorEntry key(lineFrom, indexFrom, lineTo, indexTo);
    Q_FOREACH(IndicatorEntry indicator, list)
    {
        if(indicator == key)
            return true;
    }

    return false;
}

QList<IndicatorEntry> LogDocWindow::getIndicatorList(int lineFrom, int indexFrom, int lineTo, int indexTo, int indicatorNumber)
{
    IndicatorMap::iterator iter = indicatorMap_.find(indicatorNumber);
    if (iter == indicatorMap_.end())
        return QList<IndicatorEntry>();
    IndicatorEntry key(lineFrom, indexFrom, lineTo, indexTo);

    return indicatorMap_[indicatorNumber];
}

bool LogDocWindow::isSetIndicatorFirst(int lineFrom, int indexFrom, int lineTo, int indexTo, int indicatorNumber)
{
    QList<IndicatorEntry> list = getIndicatorList(lineFrom, indexFrom,
                                                  lineTo, indexTo, indicatorNumber);
    IndicatorEntry key(lineFrom, indexFrom, lineTo, indexTo);
    if(list.isEmpty())
        return false;
    if(list[0] == key)
        return true;

    return false;
}

struct CompareIndicator
{
bool operator()(IndicatorEntry& left, IndicatorEntry& right)
{
    if (left > right)
    {
        return true;
    }
    return false;
}
};
void LogDocWindow::addIndicator(const QString& keyWord, int lineFrom, int indexFrom, int lineTo, int indexTo, int indicatorNumber)
{
    if (isSetIndicator(lineFrom, indexFrom, lineTo, indexTo, indicatorNumber))
        return;
    IndicatorEntry indicator(lineFrom, indexFrom, lineTo, indexTo);
    indicatorMap_[indicatorNumber].push_back(indicator);
    //QList<IndicatorEntry>& list = indicatorMap_[indicatorNumber];
    qSort(indicatorMap_[indicatorNumber].begin(), indicatorMap_[indicatorNumber].end(), CompareIndicator());
}

void LogDocWindow::setWrapComplete(const QString& keyWord)
{
    IndicatorKeyWordMap::iterator iter = indicatorKeyWordMap_.find(keyWord);
    if (iter == indicatorKeyWordMap_.end())
        return;
    iter->isWrap = true;
}

KeyWordEntry LogDocWindow::createIndicatorNum(const QString& keyWord)
{
    IndicatorKeyWordMap::iterator iter = indicatorKeyWordMap_.find(keyWord);
    if (iter != indicatorKeyWordMap_.end())
        return indicatorKeyWordMap_[keyWord];

    KeyWordEntry entry;
    entry.indicatorNum = textMain_->indicatorDefine(QsciScintilla::FullBoxIndicator);
    entry.keyWordColor = getRandomColor(LIGHTLEVEL, 200);
    indicatorKeyWordMap_[keyWord] = entry;

    return entry;
}

void LogDocWindow::showPopMenu(const QPoint &point)
{
    rightPopMenu_->exec(mapToGlobal(point));
}

QColor LogDocWindow::getRandomColor(COLORLEVEL colorLevel, int alpha)
{
#if 1
    switch(colorLevel)
    {
        case DARKLEVEL:
            return QColor(QRandomGenerator::global()->bounded(0, 100),
                          QRandomGenerator::global()->bounded(0, 100),
                          QRandomGenerator::global()->bounded(0, 100), alpha);
        case MIDLEVEL:
            return QColor(QRandomGenerator::global()->bounded(100, 150),
                          QRandomGenerator::global()->bounded(100, 150),
                          QRandomGenerator::global()->bounded(100, 150), alpha);
        case LIGHTLEVEL:
            return QColor(QRandomGenerator::global()->bounded(150, 200),
                          QRandomGenerator::global()->bounded(150, 200),
                          QRandomGenerator::global()->bounded(150, 200), alpha);
    }
#endif
#if 0
     QStringList colorNames = QColor::colorNames();

     int index = QRandomGenerator::global()->bounded(0, colorNames.size());

     QColor color(colorNames[index]);
    color.setAlpha(alpha);

    return color;
#endif
    return QColor(200,200,200,alpha);
}
void LogDocWindow::markAllClick()
{
    QString findText = findEdit_->text();
    if (findText.isEmpty())
        return;

    if (!findStr(findText))
        return;

    KeyWordEntry indicator = createIndicatorNum(findText);
    if (indicator.isWrap)
        return;
    textMain_->setIndicatorForegroundColor(indicator.keyWordColor, indicator.indicatorNum);
    textMain_->setIndicatorDrawUnder(true, indicator.indicatorNum);
    do
    {
        int lineFrom = -1;
        int indexFrom = -1;
        int lineTo = -1;
        int indexTo = -1;

        textMain_->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
        if (aroundAct_->isChecked())
        {
            if (isSetIndicatorFirst(lineFrom, indexFrom, lineTo, indexTo, indicator.indicatorNum))
            {
                setWrapComplete(findText);
                return;
            }
        }
        if (isSetIndicator(lineFrom, indexFrom, lineTo, indexTo, indicator.indicatorNum))
        {
            return;
        }

        textMain_->fillIndicatorRange(lineFrom, indexFrom, lineTo, indexTo, indicator.indicatorNum);
        addIndicator(findText, lineFrom, indexFrom, lineTo, indexTo, indicator.indicatorNum);
    }
    while(textMain_->findNext());
}

void LogDocWindow::createFindBar()
{
    fileToolBar_ = new QToolBar(this);
    addToolBar(Qt::BottomToolBarArea, fileToolBar_);
    nameLabel_ = new QLabel(tr("Find:"));
    findEdit_ = new QLineEdit;
    findEdit_->setGeometry(0,0,500,35);
    findEdit_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    findNext_ = new QPushButton(tr("Find Next"));
    findNext_->setStatusTip(tr("Find Next"));
    connect(findNext_, SIGNAL(clicked()), this, SLOT(findNextClick()));

    markAll_ = new QPushButton(tr("Mark All"));
    connect(markAll_, SIGNAL(clicked()), this, SLOT(markAllClick()));

    wordAct_ = new QAction(QIcon(":/res/FindTB/word24"), tr("&Word"), this);
    wordAct_->setCheckable(true);
    caseAct_ = new QAction(QIcon(":/res/FindTB/case24"), tr("&Case"), this);
    caseAct_->setCheckable(true);
    regexAct_ = new QAction(QIcon(":/res/FindTB/regex24"), tr("&Regex"), this);
    regexAct_->setCheckable(true);
    backslashAct_ = new QAction(QIcon(":/res/FindTB/backslash24"), tr("&Backslash"), this);
    backslashAct_->setCheckable(true);
    aroundAct_ = new QAction(QIcon(":/res/FindTB/around24"), tr("&Around"), this);
    aroundAct_->setCheckable(true);
    upAct_ = new QAction(QIcon(":/res/FindTB/up24"), tr("&Up"), this);
    upAct_->setCheckable(true);
    closeAct_ = new QAction(QIcon(":/res/SettingPanel/close_pressed"), tr("&Close"), this);

    fileToolBar_->addAction(closeAct_);
    fileToolBar_->addWidget(nameLabel_);
    fileToolBar_->addWidget(findEdit_);
    fileToolBar_->addSeparator();
    fileToolBar_->addWidget(findNext_);
    fileToolBar_->addWidget(markAll_);
    fileToolBar_->addAction(wordAct_);
    fileToolBar_->addAction(caseAct_);
    fileToolBar_->addAction(regexAct_);
    fileToolBar_->addAction(backslashAct_);
    fileToolBar_->addAction(aroundAct_);
    fileToolBar_->addAction(upAct_);
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
