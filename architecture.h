#ifndef ARCHITECTURE_H
#define ARCHITECTURE_H

#include <QString>


class Architecture
{
public:
    QString vendorMessage();

    QString getMicroArchitecture();
    QString getCore();
    void setMicroArchitecture(QString newMicroArchitecture);
    void setCore(QString newCore);
    virtual bool mapArchitecture()=0;
        void setLeaf01H();

protected:
    QString registerToMessage(unsigned int registerValue);




    QString core;
    int extendedFamily;
    int extendedModel;
    int type;
    int family;
    int model;
    int stepping;
    QString microArchitecture;
    bool matched;




};

#endif // ARCHITECTURE_H
