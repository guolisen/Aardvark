#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

namespace Ui {
class MainWindow;
}
class LogDocWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void open();

private:
    bool openFile(const QString &fileName);
    bool loadFile(const QString &fileName);
    QMdiSubWindow *findMdiChild(const QString &fileName) const;
    LogDocWindow* createMdiChild();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
