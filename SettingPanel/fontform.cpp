#include "fontform.h"
#include "ui_fontform.h"
#include <QColorDialog>
#include <QTextStream>
#include <QSettings>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercmake.h>
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
    delete textPrevious_;
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

    textPrevious_ = new QsciScintilla(this);
    textPrevious_->setGeometry(10, 260, 700, 320);
    textLexerCMake_ = new QsciLexerCMake;
    textPrevious_->setLexer(textLexerCMake_);

    QFile file(":/SettingPanel/exampleText.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }

    QTextStream in(&file);
    textPrevious_->setText(in.readAll());


    textPrevious_->setMarginType(0, QsciScintilla::NumberMargin);
    textPrevious_->setMarginWidth(0,30);
    textPrevious_->setCaretLineVisible(true);
    textPrevious_->setCaretLineBackgroundColor(Qt::lightGray);
    textPrevious_->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,QsciScintilla::SC_CP_UTF8);

    textPrevious_->show();

}

void FontForm::readSetting()
{
    QSettings settings;

    const bool showLineNumber = settings.value("editor/showLineNumber", true).toBool();
    ui->checkBox_4->setChecked(showLineNumber);
    textPrevious_->setMarginLineNumbers(0, showLineNumber);

    const QString editorCharFont = settings.value("editor/editorCharFont", "").toString();
    QFont font;
    font.fromString(editorCharFont);
    ui->fontComboBox->setCurrentIndex(ui->fontComboBox->findText(font.family()));

    const bool bold = settings.value("editor/bold", false).toBool();
    ui->checkBox->setChecked(bold);
    font.setBold(bold);
    const bool italic = settings.value("editor/italic", false).toBool();
    ui->checkBox_2->setChecked(italic);
    font.setItalic(italic);
    const bool underline = settings.value("editor/underline", false).toBool();
    ui->checkBox_3->setChecked(underline);
    font.setUnderline(underline);

    const int editorCharSize = settings.value("editor/editorCharSize", 13).toInt();
    ui->fontSizeSlider->setValue(editorCharSize);
    font.setPointSize(editorCharSize);
    //textPrevious_->setFont(font);
    textLexerCMake_->setFont(font);

    const QString editorCharColor = settings.value("editor/editorCharColor", "#000000").toString();
    QColor color;
    color.setNamedColor(editorCharColor);
    ui->renkLabel->setPalette(QPalette(color));
    ui->renkLabel->setAutoFillBackground(true);
    //textPrevious_->setColor(color);
    textLexerCMake_->setColor(color, 0);

    const QString editorBGColor = settings.value("editor/editorBGColor", "#FFFFFF").toString();
    QColor bgcolor;
    bgcolor.setNamedColor(editorBGColor);
    ui->label_2->setPalette(QPalette(bgcolor));
    ui->label_2->setAutoFillBackground(true);
    textLexerCMake_->setPaper(bgcolor);
}

void FontForm::onSizeProcess(int size)
{
    QSettings settings;
    settings.setValue("editor/editorCharSize", size);
    readSetting();
}

void FontForm::onChangedFont(QFont font)
{
    QSettings settings;
    settings.setValue("editor/editorCharFont", font.toString());
    readSetting();
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
    readSetting();
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
        readSetting();
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
        QSettings settings;
        QString colorStr = bColor.name();
        settings.setValue("editor/editorBGColor", colorStr);
        readSetting();
    }
}
