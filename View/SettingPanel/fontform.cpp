#include "fontform.h"
#include "ui_fontform.h"
#include <QColorDialog>
#include <QTextStream>
#include <QSettings>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercem.h>
#include <QDebug>

FontForm::FontForm(core::ContextPtr context, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontForm),
    context_(context),
    configer_(context->getComponent<core::IConfigMgr>(nullptr))
{
    ui->setupUi(this);
    createPanel();
}

FontForm::~FontForm()
{
    delete ui;
}

void FontForm::createPanel()
{
    ui->renkLabel->setAutoFillBackground(true);

    setStyleSheet("QCheckBox{font-family:arial;font-size:13px;border-radius:2px;color:#000000;}"
                  "QCheckBox::indicator:checked{color:#FF0000}"
                  "QLabel,QRadioButton{background:transparent;color:#000000;font-family:arial;font-size:13px;}"
                  "QComboBox{background:transparent;border:1px solid #d7d7d7; border-radius: 3px; padding: 1px 3px 1px 3px;}"
                  "QComboBox:editable{background:transparent;}"
                  "QComboBox::down-arrow:on {top: 1px;left: 1px;}"
                  "QGroupBox{font-family:arial;font-size:13px;color:#000000;}"
                  "QFontComboBox{background:white;border:1px solid #d7d7d7; border-radius: 3px; padding: 1px 3px 1px 3px;}"
                  "QPushButton{color: #f0f0f0;border: 1px solid #bbbbbb;font: 8pt \"Arial\";border-radius: 6px;padding: 5px;background: qradialgradient(cx: 0.3, cy: -0.4,fx: 0.3, fy: -0.4,radius: 3, stop: 0 #828282, stop: 1 #969696);min-width: 80px;}"
                  "QPushButton:hover {background: qradialgradient(cx: 0.3, cy: -0.4,fx: 0.3, fy: -0.4,radius: 3, stop: 0 #828282, stop: 1 #969696);}"
                  "QPushButton:pressed {background: qradialgradient(cx: 0.4, cy: -0.1,fx: 0.4, fy: -0.1,radius: 3, stop: 0 #828282, stop: 1 #969696);}");

    QString fileText = "";
    QFile file(":/View/SettingPanel/exampleText.txt");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        fileText = in.readAll();
    }

    textPrevious_ = configer_->createSciObject(fileText, this);
    textPrevious_->setGeometry(10, 260, 700, 320);
    textLexerCem_ = dynamic_cast<QsciLexerCem*>(textPrevious_->lexer());

    readSetting();

    connect(ui->checkBox_4, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxProcess(int)));
    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxProcess(int)));
    connect(ui->checkBox_2, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxProcess(int)));
    connect(ui->checkBox_3, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxProcess(int)));
    connect(ui->fontSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(onSizeProcess(int)));
    connect(ui->fontComboBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(onChangedFont(QFont)));
    textPrevious_->show();
}

void FontForm::readSetting()
{
    const bool showLineNumber = configer_->getProperty("editor/showLineNumber", true).toBool();
    ui->checkBox_4->setChecked(showLineNumber);

    const QString editorCharFont = configer_->getProperty("editor/editorCharFont", "").toString();
    QFont font;
    font.fromString(editorCharFont);
    ui->fontComboBox->setCurrentIndex(ui->fontComboBox->findText(font.family()));

    const bool bold = configer_->getProperty("editor/bold", false).toBool();
    ui->checkBox->setChecked(bold);
    font.setBold(bold);
    const bool italic = configer_->getProperty("editor/italic", false).toBool();
    ui->checkBox_2->setChecked(italic);
    font.setItalic(italic);
    const bool underline = configer_->getProperty("editor/underline", false).toBool();
    ui->checkBox_3->setChecked(underline);
    font.setUnderline(underline);

    const int editorCharSize = configer_->getProperty("editor/editorCharSize", 13).toInt();
    ui->fontSizeSlider->setValue(editorCharSize);
    font.setPointSize(editorCharSize);

    const QString editorCharColor = configer_->getProperty("editor/editorCharColor", "#000000").toString();
    QColor color;
    color.setNamedColor(editorCharColor);
    ui->renkLabel->setPalette(QPalette(color));
    ui->renkLabel->setAutoFillBackground(true);
    ui->renkLabel->show();

    const QString editorBGColor = configer_->getProperty("editor/editorBGColor", "#FFFFFF").toString();
    QColor bgcolor;
    bgcolor.setNamedColor(editorBGColor);
    ui->label_2->setPalette(QPalette(bgcolor));
    ui->label_2->setAutoFillBackground(true);
    ui->label_2->show();
}

void FontForm::onSizeProcess(int size)
{
    configer_->setProperty("editor/editorCharSize", size);
    ui->fontSizeSlider->setValue(size);
    configer_->configSciObject(textPrevious_);
}

void FontForm::onChangedFont(QFont font)
{
    configer_->setProperty("editor/editorCharFont", font.toString());
    ui->fontComboBox->setCurrentIndex(ui->fontComboBox->findText(font.family()));
    configer_->configSciObject(textPrevious_);
}

void FontForm::onCheckBoxProcess(int)
{
    if (ui->checkBox_4->isChecked())
    {
        configer_->setProperty("editor/showLineNumber", true);
    }
    else
    {
        configer_->setProperty("editor/showLineNumber", false);
    }

    if (ui->checkBox->isChecked())
    {
        configer_->setProperty("editor/bold", true);
    }
    else
    {
        configer_->setProperty("editor/bold", false);
    }

    if (ui->checkBox_2->isChecked())
    {
        configer_->setProperty("editor/italic", true);
    }
    else
    {
        configer_->setProperty("editor/italic", false);
    }

    if (ui->checkBox_3->isChecked())
    {
        configer_->setProperty("editor/underline", true);
    }
    else
    {
        configer_->setProperty("editor/underline", false);
    }
    configer_->configSciObject(textPrevious_);
}

void FontForm::on_renkButton_clicked()
{
    QColorDialog diag;

    QPalette palette = ui->renkLabel->palette();
    QColor bColor=diag.getColor(palette.color(QPalette::ColorRole::Background));

    if(bColor.isValid())
    {
        ui->renkLabel->setPalette(QPalette(bColor));
        ui->renkLabel->setAutoFillBackground(true);

        QString colorStr = bColor.name();
        configer_->setProperty("editor/editorCharColor", colorStr);
        configer_->configSciObject(textPrevious_);
    }
}

void FontForm::on_pushButton_clicked()
{
    QColorDialog diag;

    QPalette palette = ui->label_2->palette();
    QColor bColor=diag.getColor(palette.color(QPalette::ColorRole::Background));

    if(bColor.isValid())
    {
        ui->label_2->setPalette(QPalette(bColor));
        ui->label_2->setAutoFillBackground(true);

        QString colorStr = bColor.name();
        configer_->setProperty("editor/editorBGColor", colorStr);
        configer_->configSciObject(textPrevious_);
    }
}
