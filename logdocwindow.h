#ifndef LOGDOCWINDOW_H
#define LOGDOCWINDOW_H

#include <QList>
#include <QMap>
#include <QMainWindow>
#include <Core/configmgr.h>

namespace Ui {
class LogDocWindow;
}
class QsciScintilla;
class QsciLexerCMake;
class QsciLexerCem;
class QLabel;
class QLineEdit;
class QPushButton;
class QMdiArea;
struct IndicatorEntry
{
    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;
    IndicatorEntry():
        lineFrom(-1), indexFrom(-1), lineTo(-1), indexTo(-1){}
    IndicatorEntry(int lineFrom, int indexFrom, int lineTo, int indexTo):
        lineFrom(lineFrom), indexFrom(indexFrom), lineTo(lineTo), indexTo(indexTo){}
    IndicatorEntry(const IndicatorEntry& other)
    {
        lineFrom = other.lineFrom;
        indexFrom = other.indexFrom;
        lineTo = other.lineTo;
        indexTo = other.indexTo;
    }
    bool operator==(const IndicatorEntry& r)
    {
        if(lineFrom != r.lineFrom)
            return false;
        if(indexFrom != r.indexFrom)
            return false;
        if(lineTo != r.lineTo)
            return false;
        if(indexTo != r.indexTo)
            return false;
    }
};

struct KeyWordEntry
{
    bool isWrap;
    int indicatorNum;
    QColor keyWordColor;

    KeyWordEntry():isWrap(false), indicatorNum(-1), keyWordColor(200,200,200) {}
};

typedef QMap<int, IndicatorEntry> IndicatorMap;
typedef QMap<QString, KeyWordEntry> IndicatorKeyWordMap;

enum COLORLEVEL
{
    DARKLEVEL,
    MIDLEVEL,
    LIGHTLEVEL
};

class LogDocWindow : public QMainWindow
{
    Q_OBJECT

public:
    LogDocWindow(QMdiArea* mdi, ConfigMgrPtr configer, QWidget *parent = nullptr);

    ~LogDocWindow();
    bool loadFile(const QString &fileName);
    QString currentFile() const { return curFile_; }
    QsciScintillaPtr getSci() const { return textMain_; }
    void setNewContent(QString);

private slots:
    void findNextClick();
    void markAllClick();
    void showPopMenu(const QPoint &point);

    void clearMarkClick();
    void IndicatorClicked(int line, int index, Qt::KeyboardModifiers state);
    void newWinTest();
private:
    void setCurrentFile(const QString& fileName) { curFile_ = fileName; }
    void createFindBar();
    bool findStr(const QString &targetStr, int indicatorNum);
    void clearIndicator(const QString& keyWord, int indicator);

    void addIndicator(int lineFrom, int indexFrom,
                      int lineTo, int indexTo, int indicatorNumber);
    KeyWordEntry createIndicatorNum(const QString &keyWord);
    bool isSetIndicator(int lineFrom, int indexFrom, int lineTo,
                        int indexTo, int indicatorNumber);
    QColor getRandomColor(COLORLEVEL colorLevel, int alpha);
    void setWrapComplete(const QString &keyWord);
    void createPopMenu();

private:
    Ui::LogDocWindow *ui;
    QsciScintillaPtr textMain_;
    QsciLexerCem* textLexer_;
    QString curFile_;

    QToolBar *fileToolBar_;
    QLabel* nameLabel_;
    QLineEdit* findEdit_;
    QPushButton* findNext_;
    QPushButton* markAll_;
    QAction *wordAct_;
    QAction *caseAct_;
    QAction *regexAct_;
    QAction *backslashAct_;
    QAction *aroundAct_;
    QAction *upAct_;
    QAction *closeAct_;
    QMdiArea* mdi_;

    IndicatorMap indicatorMap_;
    IndicatorKeyWordMap indicatorKeyWordMap_;

    QMenu* rightPopMenu_;
    ConfigMgrPtr config_;
};

#endif // LOGDOCWINDOW_H
