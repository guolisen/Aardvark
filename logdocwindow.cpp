#include <QtWidgets>
#include <QDebug>
#include <QMdiArea>
#include <QRandomGenerator>
#include "logdocwindow.h"
#include "ui_logdocwindow.h"
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercmake.h>
#include <Qsci/qscilexercem.h>


LogDocWindow::LogDocWindow(QMdiArea* mdi, TextEditorConfigPtr configer, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogDocWindow),
    curFile_(""),
    mdi_(mdi)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
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
    createPopMenu();

    connect(textMain_, SIGNAL(indicatorClicked(int, int, Qt::KeyboardModifiers)),
            this, SLOT(IndicatorClicked(int, int, Qt::KeyboardModifiers)));
}

LogDocWindow::~LogDocWindow()
{
    delete ui;
    delete textMain_;
    delete textLexer_;
}

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

void LogDocWindow::IndicatorClicked(int line, int index, Qt::KeyboardModifiers state)
{
    if(!state.testFlag(Qt::ControlModifier))
    {
        return;
    }

    int totleLine = textMain_->lines();
    bool tokenTag = false;
    for (int i=0; i< totleLine; ++i)
    {
        int lev = textMain_->SendScintilla(QsciScintillaBase::SCI_GETFOLDLEVEL, (long)i);
        QString lineStr = textMain_->text(i);

        if (lineStr.contains("UIS_UpgradeServices", Qt::CaseInsensitive))
        {
            tokenTag = true;
            int levelNext = QsciScintillaBase::SC_FOLDLEVELBASE;

            QString nextLineStr = textMain_->text(i + 1);
            if (!nextLineStr.contains("UIS_UpgradeServices", Qt::CaseInsensitive))
                ++levelNext;
            lev |= levelNext << 16;
            lev |= QsciScintillaBase::SC_FOLDLEVELHEADERFLAG;
            textMain_->SendScintilla(QsciScintillaBase::SCI_SETFOLDLEVEL, (long)i, (long)lev);
            //textMain_->SendScintilla(QsciScintillaBase::SCI_HIDELINES, (long)i, (long)i);
        }
        else
        {
            int levelCurrent = (QsciScintillaBase::SC_FOLDLEVELBASE << 16) + QsciScintillaBase::SC_FOLDLEVELBASE; //0x4000400
            if (tokenTag)
                levelCurrent = 0x4010401;

            QString nextLineStr = textMain_->text(i + 1);
            if (nextLineStr.contains("UIS_UpgradeServices", Qt::CaseInsensitive))
            {
                int levelNext = 0x400 << 16;
                levelCurrent &= 0x0000FFFF;
                levelCurrent += levelNext;
            }

            textMain_->SendScintilla(QsciScintillaBase::SCI_SETFOLDLEVEL, (long)i, (long)levelCurrent);
            //textMain_->SendScintilla(QsciScintillaBase::SCI_SHOWLINES, (long)i, (long)i);
        }


    }

}

void LogDocWindow::findNextClick()
{
    QString findText = findEdit_->text();
    if (findText.isEmpty())
        return;
    findStr(findText, -1);
}

bool LogDocWindow::findStr(const QString& targetStr, int indicatorNum)
{
    return textMain_->findFirst(targetStr, regexAct_->isChecked(),
                                caseAct_->isChecked(), wordAct_->isChecked(), true, indicatorNum);
}

void LogDocWindow::clearIndicator(const QString& keyWord, int indicator)
{
    IndicatorMap::iterator indIter = indicatorMap_.find(indicator);
    indicatorMap_.erase(indIter);
    IndicatorKeyWordMap::iterator iter = indicatorKeyWordMap_.find(keyWord);
    indicatorKeyWordMap_.erase(iter);

    int line = -1;
    int index = -1;
    textMain_->lineIndexFromPosition(textMain_->length(), &line, &index);
    textMain_->clearIndicatorRange(0, 0, line, index, indicator);
}

bool LogDocWindow::isSetIndicator(int lineFrom, int indexFrom, int lineTo, int indexTo, int indicatorNumber)
{
    IndicatorMap::iterator iter = indicatorMap_.find(indicatorNumber);
    if (iter == indicatorMap_.end())
        return false;

    IndicatorEntry key(lineFrom, indexFrom, lineTo, indexTo);
    if(iter.value() == key)
        return true;

    return false;
}

void LogDocWindow::addIndicator(int lineFrom, int indexFrom, int lineTo, int indexTo, int indicatorNumber)
{
    if (isSetIndicator(lineFrom, indexFrom, lineTo, indexTo, indicatorNumber))
        return;
    IndicatorEntry indicator(lineFrom, indexFrom, lineTo, indexTo);
    indicatorMap_[indicatorNumber] = indicator;
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
    IndicatorKeyWordMap::iterator iter = indicatorKeyWordMap_.begin();
    for(; iter != indicatorKeyWordMap_.end(); ++iter)
    {
        if (keyWord.contains(iter.key(), Qt::CaseInsensitive) ||
                iter.key().contains(keyWord, Qt::CaseInsensitive))
            return iter.value();
    }

    KeyWordEntry entry;
    entry.indicatorNum = textMain_->indicatorDefine(QsciScintilla::RoundBoxIndicator);
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

    KeyWordEntry indicator = createIndicatorNum(findText);
    if (indicator.isWrap)
        return;

    //textMain_->setIndicatorForegroundColor(indicator.keyWordColor, indicator.indicatorNum);
    textMain_->setIndicatorDrawUnder(true, indicator.indicatorNum);
    //textMain_->setIndicatorOutlineColor(indicator.keyWordColor, indicator.indicatorNum);

    if (!findStr(findText, indicator.indicatorNum))
        return;

    int lineFrom = -1;
    int indexFrom = -1;
    int lineTo = -1;
    int indexTo = -1;
    textMain_->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    addIndicator(lineFrom, indexFrom, lineTo, indexTo, indicator.indicatorNum);

    while(textMain_->findNext())
    {
        textMain_->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
        if (isSetIndicator(lineFrom, indexFrom, lineTo, indexTo, indicator.indicatorNum))
        {
            setWrapComplete(findText);
            return;
        }
    }
}

void LogDocWindow::newWinTest()
{
    TextEditorConfigPtr configer = std::make_shared<TextEditorConfig>();
    LogDocWindow *child = new LogDocWindow(mdi_, configer, this);
    mdi_->addSubWindow(child);

    child->getSci()->setDocument(textMain_->document());

    Q_FOREACH (QTabBar* tab, mdi_->findChildren<QTabBar *>())
    {
        int index = tab->currentIndex() + 1;
        tab->setTabTextColor(index, QColor(160, 0, 160));
    }

    child->setNewContent(findEdit_->text());
    child->setWindowTitle(findEdit_->text());
    child->show();
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
    //aroundAct_->setCheckable(true);
    connect(aroundAct_, SIGNAL(triggered()), this, SLOT(newWinTest()));

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

void LogDocWindow::setNewContent(QString tag)
{
    int totleLine = textMain_->lines();
    for (int i=0; i< totleLine; ++i)
    {
        QString lineStr = textMain_->text(i);
        if (lineStr.contains(tag, Qt::CaseInsensitive))
        {
            textMain_->SendScintilla(QsciScintillaBase::SCI_SHOWLINES, (long)i, (long)i);
        }
        else
        {
            textMain_->SendScintilla(QsciScintillaBase::SCI_HIDELINES, (long)i, (long)i);
        }
    }
}
