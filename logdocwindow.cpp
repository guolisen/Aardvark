#include <QtWidgets>
#include "logdocwindow.h"
#include "ui_logdocwindow.h"

LogDocWindow::LogDocWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogDocWindow),
    curFile_("")
{
    ui->setupUi(this);
    textMain_ = new QsciScintilla(this);
    setCentralWidget(textMain_);
    setAttribute(Qt::WA_DeleteOnClose);

}

LogDocWindow::~LogDocWindow()
{
    delete ui;
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
