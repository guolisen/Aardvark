#ifndef FONTFORM_H
#define FONTFORM_H

#include <QWidget>

namespace Ui {
class FontForm;
}

class FontForm : public QWidget
{
    Q_OBJECT

public:
    explicit FontForm(QWidget *parent = nullptr);
    ~FontForm();

private slots:
    void onCheckBoxProcess(int);
    void onSizeProcess(int);
    void on_renkButton_clicked();
    void onChangedFont(QFont font);
private:
    void createPanel();
    void readSetting();

    Ui::FontForm *ui;
};

#endif // FONTFORM_H
