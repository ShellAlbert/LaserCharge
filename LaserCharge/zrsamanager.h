#ifndef ZRSAMANAGER_H
#define ZRSAMANAGER_H
#include <QDir>
#include <QString>
#include <QFile>
extern "C"
{
    #include <openssl/rsa.h>
    #include <openssl/pem.h>
    #include <openssl/bn.h>
    #include <openssl/bio.h>
    #include <openssl/evp.h>
}
class ZRSAManager
{
public:
    ZRSAManager();

    void createRSAKey(QString devId);
    void createSignature(QString devId);
};

#endif // ZRSAMANAGER_H
