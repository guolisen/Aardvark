#ifndef LOGDOCWINDOW_H
#define LOGDOCWINDOW_H

#include <QMainWindow>
#include "texteditorconfig.h"

namespace Ui {
class LogDocWindow;
}
class QsciScintilla;
class QsciLexerCMake;
class QsciLexerCem;
class LogDocWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogDocWindow(TextEditorConfigPtr configer, QWidget *parent = nullptr);

    ~LogDocWindow();
    bool loadFile(const QString &fileName);
    QString currentFile() { return curFile_; }

private:
    void setCurrentFile(const QString& fileName) { curFile_ = fileName; }

private:
    Ui::LogDocWindow *ui;
    QsciScintilla *textMain_;
    QsciLexerCem* textLexer_;
    QString curFile_;

};

#endif // LOGDOCWINDOW_H
