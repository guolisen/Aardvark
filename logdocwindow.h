#ifndef LOGDOCWINDOW_H
#define LOGDOCWINDOW_H

#include <QMainWindow>

namespace Ui {
class LogDocWindow;
}
class QsciScintilla;
class QscilexerCpp;
class LogDocWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogDocWindow(QWidget *parent = nullptr);

    ~LogDocWindow();
    bool loadFile(const QString &fileName);
    QString currentFile() { return curFile_; }

private:
    void setCurrentFile(const QString& fileName) { curFile_ = fileName; }
    void readSetting();

private:
    Ui::LogDocWindow *ui;
    QsciScintilla *textMain_;
    QscilexerCpp *textLexer_;
    QString curFile_;

};

#endif // LOGDOCWINDOW_H
