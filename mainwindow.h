#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

namespace Ui {
class MainWindow;
}
class LogDocWindow;
class SettingPanel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void open();
private:
    bool openFile(const QString &fileName);
    bool loadFile(const QString &fileName);
    QMdiSubWindow *findMdiChild(const QString &fileName) const;
    LogDocWindow* createMdiChild();

    Ui::MainWindow *ui;
    SettingPanel* settingPanel_;
};

#endif // MAINWINDOW_H
