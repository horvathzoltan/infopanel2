#ifndef FRAME2_H
#define FRAME2_H

#include <QFrame>

namespace Ui {
class Frame2;
}

class Frame2 : public QFrame
{
    Q_OBJECT

public:
    explicit Frame2(QWidget *parent = nullptr);
    ~Frame2();

protected:
    void showEvent(QShowEvent *event);
private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Frame2 *ui;
    void showEventHelper();

};

#endif // FRAME2_H
