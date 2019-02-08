#include "fontform.h"
#include "ui_fontform.h"
#include <QColorDialog>
#include <QTextStream>
#include <QSettings>
#include <Qsci/qsciscintilla.h>
#include <QDebug>

FontForm::FontForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontForm)
{
    ui->setupUi(this);
    createPanel();
    readSetting();

    connect(ui->checkBox_4, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxProcess(int)));
    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxProcess(int)));
    connect(ui->checkBox_2, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxProcess(int)));
    connect(ui->checkBox_3, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxProcess(int)));
    connect(ui->fontSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(onSizeProcess(int)));
    connect(ui->fontComboBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(onChangedFont(QFont)));
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

    QsciScintilla* textPrevious = new QsciScintilla(this);
    textPrevious->setGeometry(10, 225, 700, 300);

    QFile file(":/SettingPanel/exampleText.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }

    QTextStream in(&file);
    textPrevious->setText(in.readAll());
    textPrevious->show();

}

void FontForm::readSetting()
{
    QSettings settings;

    const bool showLineNumber = settings.value("editor/showLineNumber", true).toBool();
    ui->checkBox_4->setChecked(showLineNumber);

    const bool bold = settings.value("editor/bold", false).toBool();
    ui->checkBox->setChecked(bold);
    const bool italic = settings.value("editor/italic", false).toBool();
    ui->checkBox_2->setChecked(italic);
    const bool underline = settings.value("editor/underline", false).toBool();
    ui->checkBox_3->setChecked(underline);

    const int editorCharSize = settings.value("editor/editorCharSize", 13).toInt();
    ui->fontSizeSlider->setValue(editorCharSize);

    const QString editorCharColor = settings.value("editor/editorCharColor", "#000000").toString();
    QColor color;
    color.setNamedColor(editorCharColor);
    ui->renkLabel->setPalette(QPalette(color));
    ui->renkLabel->setAutoFillBackground(true);

    const QString editorCharFont = settings.value("editor/editorCharFont", "").toString();
    QFont font;
    font.fromString(editorCharFont);
    ui->fontComboBox->setCurrentIndex(ui->fontComboBox->findText(font.family()));
    //ui->fontComboBox->setCurrentFont(font);
}

void FontForm::onSizeProcess(int size)
{
    QSettings settings;
    settings.setValue("editor/editorCharSize", size);
}

void FontForm::onChangedFont(QFont font)
{
    QSettings settings;
    settings.setValue("editor/editorCharFont", font.toString());
}


void FontForm::onCheckBoxProcess(int check)
{
    QSettings settings;
    if (ui->checkBox_4->isChecked())
    {
        settings.setValue("editor/showLineNumber", true);
    }
    else
    {
        settings.setValue("editor/showLineNumber", false);
    }

    if (ui->checkBox->isChecked())
    {
        settings.setValue("editor/bold", true);
    }
    else
    {
        settings.setValue("editor/bold", false);
    }

    if (ui->checkBox_2->isChecked())
    {
        settings.setValue("editor/italic", true);
    }
    else
    {
        settings.setValue("editor/italic", false);
    }

    if (ui->checkBox_3->isChecked())
    {
        settings.setValue("editor/underline", true);
    }
    else
    {
        settings.setValue("editor/underline", false);
    }

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
        QSettings settings;
        QString colorStr = bColor.name();
        settings.setValue("editor/editorCharColor", colorStr);
    }
}
