#ifndef LOGDOCWINDOW_H
#define LOGDOCWINDOW_H

#include <QMainWindow>
#include <Qsci/qsciscintilla.h>

namespace Ui {
class LogDocWindow;
}

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

    Ui::LogDocWindow *ui;
    QsciScintilla *textMain_;
    QString curFile_;
};

#endif // LOGDOCWINDOW_H
