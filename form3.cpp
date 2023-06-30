#include "form3.h"
#include "ui_form3.h"
#include <QDebug>
#include <QPicture>
#include <QScreen>
#include "helpers/screenhelper.h"

Form3::Form3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form3)
{
    ui->setupUi(this);
}

void Form3::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );

    //showEventHelper();
}

Form3::~Form3()
{
    delete ui;
}

void Form3::on_button_3_clicked()
{
    qApp->exit();
}

/**/

void Form3::ShowPicture(const QString& fn, const QString& sn)
{
    QPixmap p;
    p.load(fn);

    auto screen = this->screen();
    QString msg = ScreenHelper::getScreenString(*screen);

    //auto size = this->screen()->geometry().size();
    auto size = ui->label_3->size();

    QString msg2 ="@"+QString::number(size.width())+"x"+QString::number(size.height());
    //auto size = this->size();
    auto p2 = p.scaled(size, Qt::KeepAspectRatio);//Qt::KeepAspectRatioByExpanding);

    ui->button_3->setText("Bezár ["+msg+']'+'\n'+"label:"+msg2+'\n'+sn+':'+fn);
    ui->label_3->setPixmap(p2);
}

void Form3::HidePicture(){

    auto screen = this->screen();
    QString msg = ScreenHelper::getScreenString(*screen);

    //auto size = this->screen()->geometry().size();
    auto size = ui->label_3->size();

    QString msg2 ="@"+QString::number(size.width())+"x"+QString::number(size.height());
    //auto size = this->size();

    ui->button_3->setText("Bezár ["+msg+']'+'\n'+"label:"+msg2);
    ui->label_3->setText("Nincs tartalom");
}
