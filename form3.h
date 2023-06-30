#ifndef FORM3_H
#define FORM3_H

#include <QElapsedTimer>
#include <QUuid>
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
    void ShowPicture(const QString& fn,  const QString& sn, QUuid id);
    void HidePicture();

    void CountImage();
    QString GetButtonText(const QString &fn, const QString &sn);
private slots:
    void on_button_3_clicked();

private:
    Ui::Form3 *ui;
    QUuid _currentId;
    QElapsedTimer _imageElapsedTimer;
protected:
    void showEvent(QShowEvent *ev);    
};

#endif // FORM3_H
