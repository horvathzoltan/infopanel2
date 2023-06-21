#ifndef FORM3_H
#define FORM3_H

#include <QWidget>

namespace Ui {
class Form3;
}

class Form3 : public QWidget
{
    Q_OBJECT

public:
    explicit Form3(QWidget *parent = nullptr);
    ~Form3();

private slots:
    void on_button_3_clicked();

private:
    Ui::Form3 *ui;

protected:
    void showEvent(QShowEvent *ev);
    void showEventHelper();
};

#endif // FORM3_H
