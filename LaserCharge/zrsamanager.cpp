#include "zrsamanager.h"
#include <QDebug>

ZRSAManager::ZRSAManager()
{

}
void ZRSAManager::createRSAKey(QString devId)
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
    //private Key.
    QString fileNamePrivate=keyPath+"/"+devId+"_private.pem";
    QByteArray baFileNamePrivate=fileNamePrivate.toLatin1();
    FILE *fpPrivate=fopen(baFileNamePrivate.data(),"wb");
    if(fpPrivate)
    {
        PEM_write_RSAPrivateKey(fpPrivate,rsa,NULL,NULL,0,NULL,NULL);
        fclose(fpPrivate);
    }else{
        qDebug()<<"failed to dump private key to file";
    }
    //public key.
    unsigned char *n_b = (unsigned char *)calloc(RSA_size(rsa), sizeof(unsigned char));
    unsigned char *e_b = (unsigned char *)calloc(RSA_size(rsa), sizeof(unsigned char));
    int n_size = BN_bn2bin(rsa->n, n_b);
    int b_size = BN_bn2bin(rsa->e, e_b);
    RSA *pubrsa = RSA_new();
    pubrsa->n = BN_bin2bn(n_b, n_size, NULL);
    pubrsa->e = BN_bin2bn(e_b, b_size, NULL);

    QString fileNamePublic=keyPath+"/"+devId+"_public.pem";
    QByteArray baFileNamePublic=fileNamePublic.toLatin1();
    FILE *fpPublic=fopen(baFileNamePublic.data(),"wb");
    if(fpPublic)
    {
        PEM_write_RSA_PUBKEY(fpPublic, pubrsa);
        fclose(fpPublic);
    }else{
        qDebug()<<"failed to dump public key to file";
    }

    RSA_free(pubrsa);
    RSA_free(rsa);
}
void ZRSAManager::createSignature(QString devId)
{

}
