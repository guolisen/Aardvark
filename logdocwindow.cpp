#include <QtWidgets>
#include "logdocwindow.h"
#include "ui_logdocwindow.h"
#include <Qsci/qsciscintilla.h>

LogDocWindow::LogDocWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogDocWindow),
    curFile_("")
{
    ui->setupUi(this);
    textMain_ = new QsciScintilla(this);
    //QscilexerCpp *textLexer = new QscilexerCpp

    setCentralWidget(textMain_);
    setAttribute(Qt::WA_DeleteOnClose);
    readSetting();
}

LogDocWindow::~LogDocWindow()
{
    delete ui;
}

void LogDocWindow::readSetting()
{
    QSettings settings;

    const bool showLineNumber = settings.value("editor/showLineNumber", true).toBool();
    textMain_->setMarginLineNumbers(textMain_->margins(), showLineNumber);

    const bool bold = settings.value("editor/bold", false).toBool();

    const bool italic = settings.value("editor/italic", false).toBool();

    const bool underline = settings.value("editor/underline", false).toBool();


    const int editorCharSize = settings.value("editor/editorCharSize", 13).toInt();


    const QString editorCharColor = settings.value("editor/editorCharColor", "#000000").toString();
    QColor color;
    color.setNamedColor(editorCharColor);



    const QString editorCharFont = settings.value("editor/editorCharFont", "").toString();
    QFont font;
    font.fromString(editorCharFont);
    //ui->fontComboBox->setCurrentIndex(ui->fontComboBox->findText(font.family()));
    //ui->fontComboBox->setCurrentFont(font);
}

bool LogDocWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textMain_->setText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);

    return true;
}
