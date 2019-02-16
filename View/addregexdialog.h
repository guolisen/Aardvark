#ifndef ADDREGEXDIALOG_H
#define ADDREGEXDIALOG_H

#include <QDialog>
#include <Core/appcontext.h>

namespace Ui {
class AddRegexDialog;
}

class AddRegexDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRegexDialog(core::ContextPtr context, QWidget *parent = nullptr);
    ~AddRegexDialog();

    QString getRegexStr() const;
private:
    Ui::AddRegexDialog *ui;
    core::ContextPtr context_;
};

#endif // ADDREGEXDIALOG_H
