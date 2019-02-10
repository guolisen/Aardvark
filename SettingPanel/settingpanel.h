#ifndef SETTINGPANEL_H
#define SETTINGPANEL_H

#include <QtGui>
#include <QDialog>
#include <QListWidgetItem>
#include <QScrollArea>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include "epushbutton.h"

class SettingPanel : public QDialog
{
    Q_OBJECT

public:
    SettingPanel(QWidget *parent = 0);
    ~SettingPanel();

protected:
     void paintEvent(QPaintEvent *event);
     void mousePressEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void resizeEvent(QResizeEvent *event);

private:
     void initTabOneWidget();
     void initTabTwoWidget();

private slots:
     void slotCurrentChanged(int index);
     void slotItemClicked(QListWidgetItem *item);
     void slotValueChanged(int value);

private:
    QPoint movePoint;
    bool mousePress;
    EPushButton *minButton;
    EPushButton *closeButton;
    QRect rectMove;
    QTabWidget *tabWidget;
    QListWidget *contentsWidget;
    QWidget *widgetScrollArea;
    QScrollArea *scrollArea;
    QWidget *generalWidget;
    QWidget *fontWidget;
    bool signFlag;
    QPropertyAnimation* animation_;
};

#endif // SETTINGPANEL_H
