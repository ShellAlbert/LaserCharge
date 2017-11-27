#include "mainui.h"
#include <QApplication>
#include "resmanager.h"
#include <QDebug>
#include <QFile>
#include <QSplashScreen>
#include <QDir>
#include "zdialog.h"
#include "zrsamanager.h"
extern "C"
{
    #include "openssl/applink.c"
}
int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    ZRSAManager rsaManager;
    rsaManager.createRSAKey("zsy");

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
