#include "ProgramCharact.h"

/*  Конструкторы и деструктор*/
    ProgramCharact::ProgramCharact(){}
    ProgramCharact::ProgramCharact(QString NName,  QString NManufacturer, long long NSize, int NYear, QString NOS)
        :Name(NName),  Manufacturer(NManufacturer), Size(NSize), Year(NYear), OS(NOS)
    {

    }
/*  Getters Setters*/
    QString ProgramCharact::GetManufacturer(){return Manufacturer;}
    long long ProgramCharact::GetSize(){return Size;}
    QString ProgramCharact::GetName(){return Name;}
    int ProgramCharact::GetYear(){return Year;}
    QString ProgramCharact::GetOS(){return OS;}

    void ProgramCharact::SetManufacturer(QString NManufacturer){Manufacturer=NManufacturer;}
    void ProgramCharact::SetSize(long long NSize){Size=NSize;}
    void ProgramCharact::SetName(QString NName){Name=NName;}
    void ProgramCharact::SetYear(int NYear){Year=NYear;}
    void ProgramCharact::SetOS(QString NOS){OS=NOS;}
