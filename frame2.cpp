#include "frame2.h"
#include "qscreen.h"
#include "ui_frame2.h"
#include <QDebug>
#include <QPicture>
#include <QScreen>
#include "helpers/screenhelper.h"

Frame2::Frame2(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Frame2)
{
    ui->setupUi(this);
}

void Frame2::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );

    showEventHelper();
}

Frame2::~Frame2()
{
    delete ui;
}

void Frame2::on_pushButton_2_clicked()
{
    qApp->exit();
}

/**/

void Frame2::showEventHelper(){
    qDebug() << "show 2";

    QString fn = QStringLiteral("/home/pi/infopanel_pictures/1.jpg");

    QPixmap p;
    p.load(fn);

    auto screen = this->screen();//->geometry().size();
    QString msg = ScreenHelper::getScreenString(*screen);
    ui->pushButton_2->setText("Bezár ["+msg+']');

    auto size = ui->label_2->size();
    //auto size = this->geometry().size();
    auto p2 = p.scaled(size, Qt::KeepAspectRatioByExpanding);

    ui->label_2->setPixmap(p2);
}



