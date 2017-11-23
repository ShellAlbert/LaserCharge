#include "mainui.h"
#include <QApplication>
#include "resmanager.h"
#include <QDebug>
#include <QFile>
#include <QSplashScreen>
#include <QDir>
#include "zdialog.h"
extern "C"{
    #include "openssl/ssl.h"
    #include "openssl/sha.h"
    #include "openssl/aes.h"
}

std::string sha256(const std::string str)
{
    char buf[2];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::string newString = "";
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(buf,"%02x",hash[i]);
        newString = newString + buf;
    }
    return newString;
}
void createRSAKey(QString devId)
{
    QString keyPath=QDir::currentPath()+"/key";
    QDir keyDir;
    if(!keyDir.exists(keyPath))
    {
        keyDir.mkpath(keyPath);
    }
    BIGNUM *bne=BN_new();
    qint32 ret=BN_set_word(bne,RSA_F4);
    RSA *rsa=RSA_new();
    ret=RSA_generate_key_ex(rsa,1024,bne,NULL);
    if(ret<0)
    {
        qDebug()<<"failed to generate RSA key!";
        return;
    }
    QString fileName=keyPath+"/"+devId+".pem";
    QByteArray baFileName=fileName.toLatin1();
    FILE *fpPrivate=fopen(baFileName.data(),"wb");
    if(fpPrivate)
    {
        PEM_write_RSAPrivateKey(fpPrivate,rsa,NULL,NULL,0,NULL,NULL);
        fclose(fpPrivate);
    }else{
        qDebug()<<"failed to dump private key to file";
    }
}
int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    std::string str = "Hello World";
    qDebug() << QString::fromStdString(sha256(str));
    //createRSAKey("11111111");

    QSplashScreen splash(QPixmap(":/icons/images/splash.png"));
    splash.show();
    app.processEvents();

    splash.showMessage("loading history data...",Qt::AlignLeft|Qt::AlignBottom);
    ZResManager *gManager=ZResManager::ZGetInstance();
    QStringList provinceList;
    QStringList cityList;
    QStringList cinemaList;
    QStringList deviceList;
    if(gManager->ZCreateIfItNotExist()<0)
    {
        ZDialogErrMsg dia("Cannot start without database!");
        dia.exec();
        return -1;
    }
    gManager->ZLoadProvince(provinceList);
    gManager->ZLoadCity(cityList);
    gManager->ZLoadCinema(cinemaList);
    gManager->ZLoadDevice(deviceList);
    //    qDebug()<<provinceList;
    //    qDebug()<<cityList;
    //    qDebug()<<cinemaList;
    //    qDebug()<<deviceList;

    splash.showMessage("loading UI skin...",Qt::AlignLeft|Qt::AlignBottom);
    //QFile file(":/ui/skins/gray.qss");
    QFile file(":/ui/skins/lightYellow.qss");
    if(file.open(QIODevice::ReadOnly))
    {
        QString qss=file.readAll();
        app.setStyleSheet(qss);
        file.close();
    }

    splash.showMessage("creating main window...",Qt::AlignLeft|Qt::AlignBottom);
    MainUI win;
    win.ZCreateProvinceNodes(provinceList);
    win.ZCreateCityNodes(cityList);
    win.ZCreateCinemaNodes(cinemaList);
    win.ZCreateDeviceNodes(deviceList);
    win.showMaximized();
    splash.finish(&win);

    return app.exec();
}
