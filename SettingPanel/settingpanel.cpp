#include <QFont>
#include <QFontComboBox>
#include <QGroupBox>
#include "settingpanel.h"
#include "fontform.h"
#include <Qsci/qsciscintilla.h>

SettingPanel::SettingPanel(QWidget *parent)
    : QDialog(parent, Qt::FramelessWindowHint)
    , mousePress(false)
    , signFlag(false)
    , generalWidget(nullptr),
      fontWidget(nullptr)

{
    resize(900, 600);

    setStyleSheet("QTabWidget::pane{border:none;}"
                  "QTabWidget::tab-bar{alignment:left;}"
                  "QTabBar::tab{background:transparent;color:#000000;min-width:120px;min-height:35px;}"
                  "QTabBar::tab:hover{background:rgb(255, 255, 255, 255);}"
                  "QTabBar::tab:selected{background:white;border-color: white;color:green;padding-left:5px}"
                  "QListWidget{font-size:9;background:rgba(240,240,240,255);color:#000000;border:0px solid gray;padding:0px;}"
                  "QListWidget::item{font-size:9;width:100px;height:38px;border:0px solid gray;padding-left:24px;}"
                  "QListWidget::item:selected:active{font-size:9;background:#FFFFFF;color:#19649F;border-width:-1;}"
                  "QListWidget::item:selected{font-size:9;background:#FFFFFF;color:#19649F;}"
                  );


    rectMove = QRect(0, 0, width(), 35);

    tabWidget = new QTabWidget(this);
    tabWidget->setFocusPolicy(Qt::NoFocus);
    QWidget *tab1 = new QWidget(this);
    tab1->setStyleSheet("background:#FFFFFF");
    tabWidget->addTab(tab1, "General");
    QWidget *tab2 = new QWidget(this);
    tab2->setStyleSheet("background:#FFFFFF");
    tabWidget->addTab(tab2, "Editor");
    tabWidget->setCurrentIndex(0);

    contentsWidget = new QListWidget(this);
    contentsWidget->setFocusPolicy(Qt::NoFocus);
    connect(contentsWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotItemClicked(QListWidgetItem*)));

    scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("QScrollArea{background:transparent;}");
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFocusPolicy(Qt::NoFocus);
    //connect(scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));

    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slotCurrentChanged(int)));
    slotCurrentChanged(0);

    minButton = new EPushButton(this);
    minButton->setPixName(":/SettingPanel/min");
    minButton->setToolTip(tr("minimize"));
    connect(minButton, SIGNAL(clicked()), this, SLOT(showMinimized()));

    closeButton = new EPushButton(this);
    closeButton->setPixName(":/SettingPanel/close");
    closeButton->setToolTip(tr("close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

SettingPanel::~SettingPanel()
{

}

void SettingPanel::resizeEvent(QResizeEvent *event)
{
    tabWidget->setGeometry(0, 35, this->width(), this->height() - 35);
    contentsWidget->setGeometry(0, 71, 130, this->height() - 71);
    scrollArea->setGeometry(131, 72, this->width() - 132, this->height() - 73);
    minButton->move(width() - 27 - closeButton->width(), 6);
    closeButton->move(width() - 27, 6);
    //move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);  //by dw
    QWidget::resizeEvent(event);
}

void SettingPanel::initTabOneWidget()
{
    /************generalWidget**************/
    generalWidget = new QWidget(widgetScrollArea);
    generalWidget->show();
    QLabel *label = new QLabel(generalWidget);
    label->setText(tr("login:"));
    label->setGeometry(30, 10, 50, 30);
    label->show();
    QCheckBox *first = new QCheckBox(generalWidget);
    first->setFocusPolicy(Qt::NoFocus);
    first->setText(tr("start QQ when starting"));
    first->setGeometry(100, 10, 300, 30);
    first->show();
    QCheckBox *second = new QCheckBox(generalWidget);
    second->setFocusPolicy(Qt::NoFocus);
    second->setText(tr("login when starting QQ"));
    second->setGeometry(100, 40, 300, 30);
    second->show();
    QCheckBox *third = new QCheckBox(generalWidget);
    third->setFocusPolicy(Qt::NoFocus);
    third->setChecked(true);
    third->setText(tr("open the tips always"));
    third->setGeometry(100, 70, 300, 30);
    third->show();
    QCheckBox *forth = new QCheckBox(generalWidget);
    forth->setFocusPolicy(Qt::NoFocus);
    forth->setText(tr("open the previous session when logining"));
    forth->setGeometry(100, 100, 300, 30);
    forth->show();
    QCheckBox *five = new QCheckBox(generalWidget);
    five->setFocusPolicy(Qt::NoFocus);
    five->setText(tr("open the tips always"));
    five->setGeometry(100, 130, 300, 30);
    five->show();
    QCheckBox *sixth = new QCheckBox(generalWidget);
    sixth->setFocusPolicy(Qt::NoFocus);
    sixth->setChecked(true);
    sixth->setText(tr("start phone qq when leaving"));
    sixth->setGeometry(100, 160, 300, 30);
    sixth->show();
    QCheckBox *seventh = new QCheckBox(generalWidget);
    seventh->setFocusPolicy(Qt::NoFocus);
    seventh->setChecked(true);
    seventh->setText(tr("diskplay the waiting tips when logining"));
    seventh->setGeometry(100, 190, 300, 30);
    seventh->show();
    generalWidget->setGeometry(0, 0, 555, 220);

    widgetScrollArea->resize(555, 840+127);
}
void SettingPanel::initTabTwoWidget()
{
    TextEditorConfigPtr configer = std::make_shared<TextEditorConfig>();
    fontWidget = new FontForm(configer, widgetScrollArea);
    fontWidget->show();
    fontWidget->setGeometry(0, 0, 820, 800);
    widgetScrollArea->resize(1020, 800);
}


void SettingPanel::slotCurrentChanged(int index)
{
    contentsWidget->clear();
    scrollArea->takeWidget();
    generalWidget = nullptr;
    fontWidget = nullptr;

    widgetScrollArea = new QWidget(this);
    widgetScrollArea->setStyleSheet("background:transparent;");
    scrollArea->setWidget(widgetScrollArea);
    if (index == 0) {
        contentsWidget->addItem(tr("Common"));
        initTabOneWidget();
    }
    else if (index == 1){
        contentsWidget->addItem(tr("Font"));
        initTabTwoWidget();
    }

    if (contentsWidget->count() > 0) {
        contentsWidget->setCurrentRow(0);
    }
}

void SettingPanel::slotItemClicked(QListWidgetItem *item)
{
    signFlag = true ;
    QString itemText = item->text();
    QPoint widgetPos;
    if (tabWidget->currentIndex() == 0) {
        if (itemText == tr("General")) {
            widgetPos = generalWidget->pos();
            //scrollArea->verticalScrollBar()->setValue(widgetPos.y());
        }
    }
    else if (tabWidget->currentIndex() == 1) {
        if (itemText == tr("Font")) {
            widgetPos = fontWidget->pos();
            //scrollArea->verticalScrollBar()->setValue(widgetPos.y());
        }
    }
}

void SettingPanel::slotValueChanged(int value)
{
    if (tabWidget->currentIndex() == 0) {
        QListWidgetItem *generalItem = contentsWidget->item(0);
        if (!signFlag) {
            if (generalWidget) {
                if (!generalWidget->visibleRegion().isEmpty()) {
                    generalItem->setSelected(true);
                    return;
                }
                else {
                    generalItem->setSelected(false);
                }
            }
        }
    }
    else if (tabWidget->currentIndex() == 1) {
        QListWidgetItem *fontItem = contentsWidget->item(0);
        if (!signFlag) {
            if (fontWidget) {
                if (!fontWidget->visibleRegion().isEmpty()) {
                    fontItem->setSelected(true);
                    return;
                }
                else {
                    fontItem->setSelected(false);
                }
            }
        }
    }
    signFlag = false;
}

void SettingPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#F0F0F0"));
    painter.drawRect(this->rect());
    painter.setBrush(QColor("#069dd5"));
    painter.drawRect(rectMove);
    painter.setPen(QColor("#D7D7D7"));
    painter.drawLine(0, 70, this->width(), 70);
    QWidget::paintEvent(event);
}

void SettingPanel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && rectMove.contains(event->pos())) {
        mousePress = true;
    }
    movePoint = event->globalPos() - pos();
    QWidget::mousePressEvent(event);
}

void SettingPanel::mouseReleaseEvent(QMouseEvent *event)
{
    mousePress = false;
    QWidget::mouseReleaseEvent(event);
}

void SettingPanel::mouseMoveEvent(QMouseEvent *event)
{
    if(mousePress) {
        QPoint movePos = event->globalPos();
        move(movePos - movePoint);
    }
    QWidget::mouseMoveEvent(event);
}
