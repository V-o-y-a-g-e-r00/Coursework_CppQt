#ifndef PROGRAMCHARACT_H
#define PROGRAMCHARACT_H

#include <qstring.h>

class ProgramCharact
{
private:
    QString Name="-";
    QString Manufacturer="-";
    long long Size=0;
    int Year=0;
    QString OS="-";
public:
/*  Конструкторы и деструктор*/
    ProgramCharact();
    ProgramCharact(QString NName, QString NManufacture, long long NSize, int NYear, QString NOS);

/*  Getters Setters*/
    QString GetManufacturer();
    long long GetSize();
    QString GetName();
    int GetYear();
    QString GetOS();

    void SetManufacturer(QString NManufacturer);
    void SetSize(long long NSize);
    void SetName(QString NName);
    void SetYear(int NYear);
    void SetOS(QString NOS);
};

#endif // PROGRAMCHARACT_H
