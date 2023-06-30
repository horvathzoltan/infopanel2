#include "form3.h"
#include "helpers/logger.h"
#include "ui_form3.h"
#include <QDate>
#include <QDebug>
#include <QDir>
#include <QPicture>
#include <QScreen>
#include <QString>
#include "helpers/screenhelper.h"
#include "helpers/textfilehelper.h"
#include "settings.h"
#include "bi/constants.h"

extern Settings settings;
extern Constants constants;

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
    HidePicture();
    delete ui;
}

void Form3::on_button_3_clicked()
{
    qApp->exit();
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

void Form3::ShowPicture(const QString& fn, const QString& sn, QUuid id)
{
    bool change = _currentId!=id;
    ui->button_3->setText(GetButtonText(fn,sn));
    if(change){

        QPixmap p;
        p.load(fn);

        auto size = ui->label_3->size();
        auto p2 = p.scaled(size, Qt::KeepAspectRatio);//Qt::KeepAspectRatioByExpanding);

        qint64 elapsed = _imageElapsedTimer.elapsed();
        CountImage(elapsed);

        if(!_logImage1Path.isEmpty()){
            LogImage2(_logImage1Path,elapsed);
            _logImage1Path.clear();
        }
        ui->label_3->setPixmap(p2);
        _imageElapsedTimer.restart();
        _currentId = id;
        _logImage1Path = LogImage1(_currentId);
    }
}

void Form3::HidePicture(){
    ui->button_3->setText(GetButtonText("",""));
    qint64 elapsed = _imageElapsedTimer.elapsed();
    CountImage(elapsed);
    if(!_logImage1Path.isEmpty()){
        LogImage2(_logImage1Path,elapsed);
        _logImage1Path.clear();
    }

    ui->label_3->setText("Nincs tartalom");
    _currentId = QUuid();
    _logImage1Path = LogImage1(_currentId);
}

void Form3::CountImage(qint64 elapsed){
    bool hasPrevImage = !_currentId.isNull();
    if(hasPrevImage){
        QString fn = _currentId.toString(QUuid::WithoutBraces);
        static const QDir countDir(settings.CounterDirectory());
        QString filepath = countDir.filePath(fn);

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

QString Form3::LogImage1(QUuid id){
    auto most = QDateTime::currentDateTimeUtc();
    QString fn = constants.DeviceId()+'.'+most.date().toString("yyyy.MM.dd")+".log";
    static const QDir logDir(settings.LogDirectory());
    QString filepath = logDir.filePath(fn);

    QChar a = TextFileHelper::GetLastChar(filepath);
    QString msg((a!='\n')?"":"\n");
    msg += id.toString(QUuid::WithoutBraces)+';'
           +most.toString(Qt::DateFormat::ISODateWithMs);

    TextFileHelper::Save(msg, filepath, true);
    return filepath;
}

void Form3::LogImage2(const QString& filepath, qint64 elapsed){

    QString msg = ';'+QString::number(elapsed)+'\n';
    TextFileHelper::Save(msg, filepath, true);
}


