#include "werkzeug.h"

Werkzeug::Werkzeug(float R, float H, float L, QString Name, QObject *parent) :
    QObject(parent)
{
    wzR=R; wzH=H; wzL=L; wzName=Name;
}


float Werkzeug::Rwz()
{
    return wzR;
}

float Werkzeug::Lwz()
{
    return wzL;
}

float Werkzeug::Hwz()
{
    return wzH;
}

float Werkzeug::Rwz2()
{
    return wzR2;
}

QString Werkzeug::WZNam()
{
    return wzName;
}
