#ifndef FONTFORM_H
#define FONTFORM_H

#include <QWidget>
#include "texteditorconfig.h"

namespace Ui {
class FontForm;
}
class QsciScintilla;
class QsciLexerCMake;
class FontForm : public QWidget
{
    Q_OBJECT

public:
    explicit FontForm(TextEditorConfigPtr configer, QWidget *parent = nullptr);
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
    QsciScintilla* textPrevious_;
    QsciLexerCMake* textLexerCMake_;
    TextEditorConfigPtr configer_;
};

#endif // FONTFORM_H
