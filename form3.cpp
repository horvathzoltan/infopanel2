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

void Form3::ShowPicture(const QString& fn){
    QPixmap p;
    p.load(fn);

    auto screen = this->screen();
    QString msg = ScreenHelper::getScreenString(*screen);
    ui->button_3->setText("Bezár ["+msg+']');

    //auto size = this->screen()->geometry().size();
    auto size = ui->label_3->size();
    //auto size = this->size();
    auto p2 = p.scaled(size, Qt::KeepAspectRatioByExpanding);

    ui->label_3->setPixmap(p2);
}
