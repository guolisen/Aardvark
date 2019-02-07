#include "settingpanel.h"

SettingPanel::SettingPanel(QWidget *parent)
    : QDialog(parent, Qt::FramelessWindowHint)
    , mousePress(false)
    , signFlag(false)
    , loginWidget(NULL)
    , panelWidget(NULL)
    , statusWidget(NULL)
    , sessionWidget(NULL)
    , passwordWidget(NULL)
    , qqlockWidget(NULL)
    , spaceWidget(NULL)
{
    resize(700, 500);
    setStyleSheet("QCheckBox{font-family:arial;font-size:13px;border-radius:2px;color:#000000;}"
                  "QCheckBox::indicator:checked{color:#FF0000}"
                  "QTabWidget::pane{border:none;}"
                  "QTabWidget::tab-bar{alignment:left;}"
                  "QTabBar::tab{background:transparent;color:#000000;min-width:100px;min-height:35px;}"
                  "QTabBar::tab:hover{background:rgb(255, 255, 255, 255);}"
                  "QTabBar::tab:selected{border-color: white;color:green;padding-left:5px}"
                  "QListWidget{background:rgba(240,240,240,255);color:#000000;border:0px solid gray;padding:0px;}"
                  "QListWidget::item{width:94px;height:38px;border:0px solid gray;padding-left:24px;}"
                  "QListWidget::item:selected:active{background:#FFFFFF;color:#19649F;border-width:-1;}"
                  "QListWidget::item:selected{background:#FFFFFF;color:#19649F;}"
                  "QLabel,QRadioButton{background:transparent;color:#000000;font-family:arial;font-size:13px;}"

                  "QComboBox{border:1px solid #d7d7d7; border-radius: 3px; padding: 1px 3px 1px 3px;}"
                  "QComboBox:editable{background:transparent;}"
                  "QComboBox:!editable{background: #fbfbfb;color:#666666}"
                  "QComboBox::down-arrow:on {top: 1px;left: 1px;}"
                  "QComboBox QAbstractItemView::item{max-width:30px;min-height:20px;}"
                  );
    rectMove = QRect(0, 0, width(), 35);

    tabWidget = new QTabWidget(this);
    tabWidget->setFocusPolicy(Qt::NoFocus);
    QWidget *tab1 = new QWidget(this);
    tab1->setStyleSheet("background:#FFFFFF");
    QWidget *tab2 = new QWidget(this);
    tab2->setStyleSheet("background:#FFFFFF");
    QWidget *tab3 = new QWidget(this);
    tab3->setStyleSheet("background:#FFFFFF");
    tabWidget->addTab(tab1, QIcon(":/SettingPanel/setting.png"),tr("base setting"));
    tabWidget->addTab(tab2, QIcon(":/SettingPanel/home.png"), tr("secure setting"));
    tabWidget->addTab(tab3, QIcon(":/SettingPanel/status.png"), tr("power setting"));
    tabWidget->setCurrentIndex(0);

    contentsWidget = new QListWidget(this);
    contentsWidget->setFocusPolicy(Qt::NoFocus);
    connect(contentsWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotItemClicked(QListWidgetItem*)));

    scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("QScrollArea{background:transparent;}"
                              "QScrollBar::vertical{background:#35A739;border:-5px solid grey;margin:-2px 0px 0px 0px;width:8px;}"
                              "QScrollBar::horizontal{background:#35A739;border:0px solid #126691;height:10px;}"
                              "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:#D3D3D3;}"
                              );

    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
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
    /************loginWidget**************/
    loginWidget = new QWidget(widgetScrollArea);
    loginWidget->show();
    QLabel *label = new QLabel(loginWidget);
    label->setText(tr("login:"));
    label->setGeometry(30, 10, 50, 30);
    label->show();
    QCheckBox *first = new QCheckBox(loginWidget);
    first->setFocusPolicy(Qt::NoFocus);
    first->setText(tr("start QQ when starting"));
    first->setGeometry(100, 10, 300, 30);
    first->show();
    QCheckBox *second = new QCheckBox(loginWidget);
    second->setFocusPolicy(Qt::NoFocus);
    second->setText(tr("login when starting QQ"));
    second->setGeometry(100, 40, 300, 30);
    second->show();
    QCheckBox *third = new QCheckBox(loginWidget);
    third->setFocusPolicy(Qt::NoFocus);
    third->setChecked(true);
    third->setText(tr("open the tips always"));
    third->setGeometry(100, 70, 300, 30);
    third->show();
    QCheckBox *forth = new QCheckBox(loginWidget);
    forth->setFocusPolicy(Qt::NoFocus);
    forth->setText(tr("open the previous session when logining"));
    forth->setGeometry(100, 100, 300, 30);
    forth->show();
    QCheckBox *five = new QCheckBox(loginWidget);
    five->setFocusPolicy(Qt::NoFocus);
    five->setText(tr("open the tips always"));
    five->setGeometry(100, 130, 300, 30);
    five->show();
    QCheckBox *sixth = new QCheckBox(loginWidget);
    sixth->setFocusPolicy(Qt::NoFocus);
    sixth->setChecked(true);
    sixth->setText(tr("start phone qq when leaving"));
    sixth->setGeometry(100, 160, 300, 30);
    sixth->show();
    QCheckBox *seventh = new QCheckBox(loginWidget);
    seventh->setFocusPolicy(Qt::NoFocus);
    seventh->setChecked(true);
    seventh->setText(tr("diskplay the waiting tips when logining"));
    seventh->setGeometry(100, 190, 300, 30);
    seventh->show();
    loginWidget->setGeometry(0, 0, 555, 220);
    /************panelWidget**************/
    panelWidget = new QWidget(widgetScrollArea);
    panelWidget->show();
    QLabel *plabel = new QLabel(panelWidget);
    plabel->setText(tr("mainpanel:"));
    plabel->setGeometry(30, 10, 50, 30);
    plabel->show();
    QCheckBox *pfirst = new QCheckBox(panelWidget);
    pfirst->setChecked(true);
    pfirst->setFocusPolicy(Qt::NoFocus);
    pfirst->setText(tr("stays on top always"));
    pfirst->setGeometry(100, 10, 300, 30);
    pfirst->show();
    QCheckBox *psecond = new QCheckBox(panelWidget);
    psecond->setChecked(true);
    psecond->setFocusPolicy(Qt::NoFocus);
    psecond->setText(tr("hide when  skiming the edge of desktop"));
    psecond->setGeometry(100, 40, 300, 30);
    psecond->show();
    QCheckBox *pthird = new QCheckBox(panelWidget);
    pthird->setFocusPolicy(Qt::NoFocus);
    pthird->setChecked(true);
    pthird->setText(tr("display the icon of qq at the taskbar"));
    pthird->setGeometry(100, 70, 300, 30);
    pthird->show();
    QLabel *pforth = new QLabel(panelWidget);
    pforth->setText(tr("when closing the mainpanel:"));
    pforth->setGeometry(100, 100, 300, 30);
    pforth->show();
    QRadioButton *hideRadio = new QRadioButton(panelWidget);
    hideRadio->setFocusPolicy(Qt::NoFocus);
    hideRadio->setText(tr("hide at the taskbar and do not exit"));
    hideRadio->setGeometry(120, 130, 300, 30);
    hideRadio->show();
    QRadioButton *exitRadio = new QRadioButton(panelWidget);
    exitRadio->setFocusPolicy(Qt::NoFocus);
    exitRadio->setChecked(true);
    exitRadio->setText(tr("exit the program"));
    exitRadio->setGeometry(120, 160, 300, 30);
    exitRadio->show();
    panelWidget->setGeometry(0, 220, 555, 190);
    /************statusWidget**************/
    statusWidget = new QWidget(widgetScrollArea);
    statusWidget->show();
    QLabel *slabel = new QLabel(statusWidget);
    slabel->setText(tr("status:"));
    slabel->setGeometry(30, 10, 50, 30);
    slabel->show();
    QLabel *slabelsecond = new QLabel(statusWidget);
    slabelsecond->setText(tr("the status of logining:"));
    slabelsecond->setGeometry(100, 10, 150, 30);
    slabelsecond->show();
    QComboBox *combox = new QComboBox(statusWidget);
    combox->setFocusPolicy(Qt::NoFocus);
    //combox->setStyle(new QPlastiqueStyle); //bydw
    combox->addItems(QStringList() << tr("hide") << tr("oneline") << tr("busy") << tr("leave"));
    combox->setGeometry(200, 12, 80, 24);
    combox->show();
    QCheckBox *ssecond = new QCheckBox(statusWidget);
    ssecond->setChecked(true);
    ssecond->setFocusPolicy(Qt::NoFocus);
    ssecond->setText(tr("switch to busy when running the program of fullscreen"));
    ssecond->setGeometry(100, 40, 300, 30);
    ssecond->show();
    QCheckBox *sthird = new QCheckBox(statusWidget);
    sthird->setFocusPolicy(Qt::NoFocus);
    sthird->setChecked(true);
    sthird->setText(tr("auto replay when leaving or busy"));
    sthird->setGeometry(100, 70, 300, 30);
    sthird->show();
    QCheckBox *sforth = new QCheckBox(statusWidget);
    sforth->setFocusPolicy(Qt::NoFocus);
    sforth->setText(tr("lock the qq when do not moving"));
    sforth->setGeometry(100, 100, 300, 30);
    sforth->show();
    statusWidget->setGeometry(0, 410, 555, 130);
    /************sessionWidget**************/
    sessionWidget = new QWidget(widgetScrollArea);
    sessionWidget->show();
    QLabel *elabel = new QLabel(sessionWidget);
    elabel->setText(tr("session:"));
    elabel->setGeometry(30, 10, 50, 30);
    elabel->show();
    QCheckBox *efirst = new QCheckBox(sessionWidget);
    efirst->setChecked(true);
    efirst->setFocusPolicy(Qt::NoFocus);
    efirst->setText(tr("use colourful bubble to chat"));
    efirst->setGeometry(100, 10, 300, 30);
    efirst->show();
    QCheckBox *esecond = new QCheckBox(sessionWidget);
    esecond->setChecked(true);
    esecond->setFocusPolicy(Qt::NoFocus);
    esecond->setText(tr("do not dispaly ad"));
    esecond->setGeometry(100, 40, 300, 30);
    esecond->show();
    QCheckBox *ethird = new QCheckBox(sessionWidget);
    ethird->setFocusPolicy(Qt::NoFocus);
    ethird->setText(tr("auto pop the panel when having massage"));
    ethird->setGeometry(100, 70, 300, 30);
    ethird->show();
    QCheckBox *eforth = new QCheckBox(sessionWidget);
    eforth->setChecked(true);
    eforth->setFocusPolicy(Qt::NoFocus);
    eforth->setText(tr("use autorun magic and supper expression"));
    eforth->setGeometry(100, 100, 300, 30);
    eforth->show();
    QCheckBox *efive = new QCheckBox(sessionWidget);
    efive->setChecked(true);
    efive->setFocusPolicy(Qt::NoFocus);
    efive->setText(tr("use moving feeling to char"));
    efive->setGeometry(100, 130, 300, 30);
    efive->show();
    QCheckBox *esixth = new QCheckBox(sessionWidget);
    esixth->setFocusPolicy(Qt::NoFocus);
    esixth->setChecked(true);
    esixth->setText(tr("display the window of char at the sidebar"));
    esixth->setGeometry(100, 160, 300, 30);
    esixth->show();
    QCheckBox *eseventh = new QCheckBox(sessionWidget);
    eseventh->setFocusPolicy(Qt::NoFocus);
    eseventh->setChecked(true);
    eseventh->setText(tr("allow the moving window"));
    eseventh->setGeometry(100, 190, 300, 30);
    eseventh->show();
    QCheckBox *eeighth = new QCheckBox(sessionWidget);
    eeighth->setFocusPolicy(Qt::NoFocus);
    eeighth->setChecked(true);
    eeighth->setText(tr("dispaly search tips"));
    eeighth->setGeometry(100, 210, 300, 30);
    eeighth->show();
    QCheckBox *enineth = new QCheckBox(sessionWidget);
    enineth->setFocusPolicy(Qt::NoFocus);
    enineth->setChecked(true);
    enineth->setText(tr("dispaly the history information"));
    enineth->setGeometry(100, 240, 300, 30);
    enineth->show();
    QCheckBox *etenth = new QCheckBox(sessionWidget);
    etenth->setFocusPolicy(Qt::NoFocus);
    etenth->setChecked(true);
    etenth->setText(tr("combine the session window"));
    etenth->setGeometry(100, 270, 300, 30);
    etenth->show();
    sessionWidget->setGeometry(0, 540, 555, 300 + 127);

    widgetScrollArea->resize(555, 840+127);
}

void SettingPanel::initTabTwoWidget()
{
    /************passwordWidget**************/
    passwordWidget = new QWidget(widgetScrollArea);
    passwordWidget->show();
    QLabel *label = new QLabel(passwordWidget);
    label->setText(tr("password:"));
    label->setGeometry(30, 10, 50, 30);
    label->show();
    QLabel *first = new QLabel(passwordWidget);
    first->setText(tr("do not remember the password:"));
    first->setGeometry(100, 10, 300, 30);
    first->show();
    QPushButton *second = new QPushButton(passwordWidget);
    second->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                          "QPushButton:hover{border-color:green;background:#bee7fd;}");
    second->setFocusPolicy(Qt::NoFocus);
    second->setText(tr("cancel to remember password"));
    second->setGeometry(100, 40, 90, 25);
    second->show();
    QLabel *third = new QLabel(passwordWidget);
    third->setText(tr("make sure safe,please alter password regularly"));
    third->setGeometry(100, 70, 300, 30);
    third->show();
    QPushButton *forth = new QPushButton(passwordWidget);
    forth->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                          "QPushButton:hover{border-color:green;color:#bee7fd;}");
    forth->setFocusPolicy(Qt::NoFocus);
    forth->setText(tr("alter password"));
    forth->setGeometry(100, 100, 60, 25);
    forth->show();
    QPushButton *forths = new QPushButton(passwordWidget);
    forths->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                          "QPushButton:hover{border-color:green;color:#bee7fd;}");
    forths->setFocusPolicy(Qt::NoFocus);
    forths->setText(tr("apply for protecting password"));
    forths->setGeometry(170, 100, 90, 25);
    forths->show();
    QLabel *five = new QLabel(passwordWidget);
    five->setText(tr("some servers will use special password"));
    five->setGeometry(100, 130, 300, 30);
    five->show();
    QPushButton *sixth = new QPushButton(passwordWidget);
    sixth->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(240,240,240);border-radius:3px;}"
                          "QPushButton:hover{border-color:green;color:#bee7fd;}");
    sixth->setFocusPolicy(Qt::NoFocus);
    sixth->setText(tr("manager special password"));
    sixth->setGeometry(100, 160, 90, 25);
    sixth->show();
    passwordWidget->setGeometry(0, 0, 555, 190);
    /************qqlockWidget**************/
    qqlockWidget = new QWidget(widgetScrollArea);
    qqlockWidget->show();
    QLabel *qlabel = new QLabel(qqlockWidget);
    qlabel->setText(tr("qqlock:"));
    qlabel->setGeometry(30, 10, 50, 30);
    qlabel->show();
    QRadioButton *firstRadio = new QRadioButton(qqlockWidget);
    firstRadio->setFocusPolicy(Qt::NoFocus);
    firstRadio->setChecked(true);
    firstRadio->setText(tr("qq password is used to unlock"));
    firstRadio->setGeometry(100, 10, 300, 30);
    firstRadio->show();
    QRadioButton *secondRadio = new QRadioButton(qqlockWidget);
    secondRadio->setFocusPolicy(Qt::NoFocus);
    secondRadio->setText(tr("special password is used to unlock"));
    secondRadio->setGeometry(100, 40, 300, 30);
    secondRadio->show();
    qqlockWidget->setGeometry(0, 190, 555, 70);
    widgetScrollArea->resize(555, 190+70+360);
}

void SettingPanel::initTabThreeWidget()
{
    /************loginWidget**************/
    spaceWidget = new QWidget(widgetScrollArea);
    spaceWidget->show();
    QLabel *label = new QLabel(spaceWidget);
    label->setText(tr("spacepermission:"));
    label->setGeometry(30, 10, 60, 30);
    label->show();
    QCheckBox *first = new QCheckBox(spaceWidget);
    first->setFocusPolicy(Qt::NoFocus);
    first->setChecked(true);
    first->setText(tr("newly log and photos display on qq"));
    first->setGeometry(100, 10, 300, 30);
    first->show();
    QCheckBox *second = new QCheckBox(spaceWidget);
    second->setFocusPolicy(Qt::NoFocus);
    second->setText(tr("update sign when updating chat"));
    second->setGeometry(100, 40, 300, 30);
    second->show();
    QCheckBox *third = new QCheckBox(spaceWidget);
    third->setFocusPolicy(Qt::NoFocus);
    third->setChecked(true);
    third->setText(tr("notice you when you log is republished"));
    third->setGeometry(100, 70, 300, 30);
    third->show();
    QCheckBox *forth = new QCheckBox(spaceWidget);
    forth->setFocusPolicy(Qt::NoFocus);
    forth->setChecked(true);
    forth->setText(tr("notice you when you have new tips"));
    forth->setGeometry(100, 100, 300, 30);
    forth->show();
    QCheckBox *five = new QCheckBox(spaceWidget);
    five->setFocusPolicy(Qt::NoFocus);
    five->setChecked(true);
    five->setText(tr("display your newly application"));
    five->setGeometry(100, 130, 300, 30);
    five->show();
    spaceWidget->setGeometry(0, 0, 555, 160);
    widgetScrollArea->resize(555, 160);
}

void SettingPanel::slotCurrentChanged(int index)
{
    contentsWidget->clear();
    scrollArea->takeWidget();
    loginWidget = NULL;
    panelWidget = NULL;
    statusWidget = NULL;
    sessionWidget = NULL;
    passwordWidget = NULL;
    qqlockWidget = NULL;
    spaceWidget = NULL;

    widgetScrollArea = new QWidget(this);
    widgetScrollArea->setStyleSheet("background:transparent;");
    scrollArea->setWidget(widgetScrollArea);
    if (index == 0) {
        contentsWidget->addItem(tr("login"));
        contentsWidget->addItem(tr("mainpanel"));
        contentsWidget->addItem(tr("status"));
        contentsWidget->addItem(tr("session"));
        initTabOneWidget();
    }
    else if (index == 1){
        contentsWidget->addItem(tr("password"));
        contentsWidget->addItem(tr("qqlock"));
        initTabTwoWidget();
    }
    else if (index == 2) {
        contentsWidget->addItem(tr("spacepermission"));
        initTabThreeWidget();
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
        if (itemText == tr("mainpanel")) {
            widgetPos = panelWidget->pos();
            //scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (itemText == tr("status")) {
            widgetPos = statusWidget->pos();
            //scrollArea->verticalScrollBar()->setValue(widgetPos.y());
        }
        else if (itemText == tr("session")) {
            widgetPos = sessionWidget->pos();
            //scrollArea->verticalScrollBar()->setValue(widgetPos.y());
        }
        else if (itemText == tr("login")) {
            widgetPos = loginWidget->pos();
            //scrollArea->verticalScrollBar()->setValue(widgetPos.y());
        }
    }
    else if (tabWidget->currentIndex() == 1) {
        if (itemText == tr("password")) {
            widgetPos = passwordWidget->pos();
            //scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (itemText == tr("qqlock")) {
            widgetPos = qqlockWidget->pos();
            //scrollArea->verticalScrollBar()->setValue(widgetPos.y());
        }
    }
}

void SettingPanel::slotValueChanged(int value)
{
    if (tabWidget->currentIndex() == 0) {
        QListWidgetItem *loginItem = contentsWidget->item(0);
        QListWidgetItem *panelItem = contentsWidget->item(1);
        QListWidgetItem *statusItem = contentsWidget->item(2);
        QListWidgetItem *sessionItem = contentsWidget->item(3);
        if (!signFlag) {
            if (loginWidget && panelWidget && statusWidget && sessionWidget) {
                if (!loginWidget->visibleRegion().isEmpty()) {
                    loginItem->setSelected(true);
                    return;
                }
                else {
                    loginItem->setSelected(false);
                }
                if (!panelWidget->visibleRegion().isEmpty()) {
                    panelItem->setSelected(true);
                    return;
                }
                else {
                    panelItem->setSelected(false);
                }
                if (!statusWidget->visibleRegion().isEmpty()) {
                    statusItem->setSelected(true);
                    return;
                }
                else {
                    statusItem->setSelected(false);
                }
                if (!sessionWidget->visibleRegion().isEmpty()) {
                    sessionItem->setSelected(true);
                    return;
                }
                else {
                    sessionItem->setSelected(false);
                }
            }
        }
    }
    else if (tabWidget->currentIndex() == 1) {
        QListWidgetItem *passwordItem = contentsWidget->item(0);
        QListWidgetItem *qqlockItem = contentsWidget->item(1);
        if (!signFlag) {
            if (passwordWidget && qqlockWidget) {
                if (!passwordWidget->visibleRegion().isEmpty()) {
                    passwordItem->setSelected(true);
                    return;
                }
                else {
                    passwordItem->setSelected(false);
                }
                if (!qqlockWidget->visibleRegion().isEmpty()) {
                    qqlockItem->setSelected(true);
                    return;
                }
                else {
                    qqlockItem->setSelected(false);
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
