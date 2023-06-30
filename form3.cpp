#include "form3.h"
#include "helpers/logger.h"
#include "ui_form3.h"
#include <QDebug>
#include <QDir>
#include <QPicture>
#include <QScreen>
#include <QString>
#include "helpers/screenhelper.h"
#include "helpers/textfilehelper.h"
#include "settings.h"

extern Settings settings;

Form3::Form3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form3)
{
    ui->setupUi(this);
}

void Form3::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );
}

Form3::~Form3()
{
    delete ui;
}

void Form3::on_button_3_clicked()
{
    qApp->exit();
}

void Form3::ShowPicture(const QString& fn, const QString& sn, QUuid id)
{
    bool change = _currentId!=id;

    ui->button_3->setText(GetButtonText(fn,sn));
    if(change){
        QPixmap p;
        p.load(fn);

        auto size = ui->label_3->size();
        auto p2 = p.scaled(size, Qt::KeepAspectRatio);//Qt::KeepAspectRatioByExpanding);

        CountImage();
        ui->label_3->setPixmap(p2);
        _imageElapsedTimer.restart();
        _currentId = id;
    }
}

QString Form3::GetButtonText(const QString& fn, const QString& sn){
    auto screen = this->screen();
    QString msg = ScreenHelper::getScreenString(*screen);
    //auto size = ui->label_3->size();
    //QString msg2 ="@"+QString::number(size.width())+"x"+QString::number(size.height());
    QString bmsg("Bezár ["+msg+']');
        bool hasPicData = !(sn.isEmpty() && fn.isEmpty());
    if(hasPicData){
        bmsg += '\n'+sn+':'+fn;
    }
    return bmsg;
}

void Form3::CountImage(){
    bool hasPrevImage = !_currentId.isNull();
    if(hasPrevImage){
        QString fn = _currentId.toString(QUuid::WithoutBraces);//+".txt";
        static const QDir countDir(settings.CounterDirectory());
        QString filepath = countDir.filePath(fn);
        qint64 elapsed = _imageElapsedTimer.elapsed();
        QString msg = QStringLiteral("imageCounter(%1): %2ms").arg(fn).arg(elapsed);
        zInfo(msg);
        QString content;
        TextFileHelper::Load(filepath, &content);
        qint64 i;
        if(!content.isEmpty()){
            bool ok;
            i = content.toLongLong(&ok);
            if(ok){
                i+=elapsed;
            } else{
                zInfo("file corrupted:"+filepath);
                i=elapsed;
            }
        } else{
            i=elapsed;
        }
        content = QString::number(i);
        TextFileHelper::Save(content, filepath, false);
    }
}

void Form3::HidePicture(){
    ui->button_3->setText(GetButtonText("",""));
    CountImage();
    ui->label_3->setText("Nincs tartalom");
    _currentId = QUuid();
}
