#ifndef FONTFORM_H
#define FONTFORM_H

#include <QWidget>
#include <Core/configmgr.h>
#include <Core/appcontext.h>

namespace Ui {
class FontForm;
}
class QsciScintilla;
class QsciLexerCem;
class FontForm : public QWidget
{
    Q_OBJECT

public:
    FontForm(core::ContextPtr context, QWidget *parent = nullptr);
    ~FontForm();

private slots:
    void onCheckBoxProcess(int);
    void onSizeProcess(int);
    void on_renkButton_clicked();
    void onChangedFont(QFont font);
    void on_pushButton_clicked();

private:
    void createPanel();
    void readSetting();

    Ui::FontForm *ui;
    QsciScintillaPtr textPrevious_;
    QsciLexerCem* textLexerCem_;
    core::ContextPtr context_;
    core::ConfigMgrPtr configer_;
};

#endif // FONTFORM_H
