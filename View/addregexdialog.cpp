#include "addregexdialog.h"
#include "ui_addregexdialog.h"

AddRegexDialog::AddRegexDialog(core::ContextPtr context, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRegexDialog),
    context_(context)
{
    ui->setupUi(this);
}

AddRegexDialog::~AddRegexDialog()
{
    delete ui;
}

QString AddRegexDialog::getRegexStr() const
{
    return ui->lineEdit->text();
}
