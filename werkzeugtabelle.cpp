#include <QFile>
#include <QTextStream>
#include <QtGui>
#include <QMap>
#include "werkzeugtabelle.h"


Werkzeugtabelle::Werkzeugtabelle(QString filename, QObject *parent) :
    QObject(parent)
{
    wzTabfilename=filename;
    ToolNum=0;
}


void Werkzeugtabelle::ToolDef(int pos, float R, float H, float L, QString Name)
{
    if (wzTab.contains(pos)) WZleeren(pos);
    wzTab.insert(pos, new Werkzeug(R,H,L,Name,this));
}

void Werkzeugtabelle::ToolCall(int pos)
{
    ToolNum=pos;
}

void Werkzeugtabelle::WZleeren(int pos)
{
    if (wzTab.contains(pos)) {
        delete wzTab.value(pos);
        wzTab.remove(pos);
    }
}

float Werkzeugtabelle::Rwz()
{
    if (wzTab.contains(ToolNum)) {
       return wzTab.value(ToolNum)->Rwz();
    } else return -1;
}

float Werkzeugtabelle::Hwz()
{
    if (wzTab.contains(ToolNum)) {
       return wzTab.value(ToolNum)->Hwz();
    } else return -1;
}

float Werkzeugtabelle::Lwz()
{
    if (wzTab.contains(ToolNum)) {
       return wzTab.value(ToolNum)->Lwz();
    } else return -1;
}

QString Werkzeugtabelle::WZNam()
{
    if (wzTab.contains(ToolNum)) {
       return wzTab.value(ToolNum)->WZNam();
    } else return "";
}

int Werkzeugtabelle::WZAktiv()
{
    return ToolNum;
}

int Werkzeugtabelle::NWZ()
{
    return wzTab.count();
}

void Werkzeugtabelle::WZTabLaden(QString wztabfile)
{
    wzTabfilename=wztabfile;
    QFile wzTabfile(wzTabfilename);
    if (!wzTabfile.open(QIODevice::ReadOnly|QIODevice::Text)) {
        Fehler(tr("Ошибка открытия файла"));
        return;
    }

    QTextStream WZTs(&wzTabfile);
    while (!WZTs.atEnd()) {
        QString linie = WZTs.readLine();
        QStringList lst=linie.split(" ",QString::SkipEmptyParts);
        bool res=false;
        int N = lst.at(0).toInt(&res);
        if (!res) {
            Fehler(tr("Ошибка файла таблицы инструмента"));
            break;
        }
        res = false;
        float R = lst.at(2).toFloat(&res);
        if (!res) {
            Fehler(tr("Ошибка файла таблицы инструмента"));
            break;
        }
        res = false;
        float H = lst.at(3).toFloat(&res);
        if (!res) {
            Fehler(tr("Ошибка файла таблицы инструмента"));
            break;
        }
        res = false;
        float L = lst.at(4).toFloat(&res);
        if (!res) {
            Fehler(tr("Ошибка файла таблицы инструмента"));
            break;
        }
        ToolDef(N,R,H,L,lst.at(1));
    }
}

void Werkzeugtabelle::WZTabSpeichern(QString wztabfile)
{
    QFile wzTabfile(wztabfile);
    if (!wzTabfile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        Fehler(tr("Ошибка сохранения файла"));
        return;
    }
    QTextStream WZTs(&wzTabfile);

    QMap<int,Werkzeug*>::iterator it = wzTab.begin();
    for (;it!=wzTab.end();++it) {
        WZTs<<QString::number(it.key())<<"  "
           <<it.value()->WZNam()<<"  "
           <<it.value()->Rwz()<<"  "
           <<it.value()->Hwz()<<"  "
           <<it.value()->Lwz()<<"\n";
    }
    wzTabfile.close();
}

void Werkzeugtabelle::Fehler(QString s)
{
    QMessageBox *fehler=new QMessageBox(QMessageBox::Information,tr("Ошибка"),s,
                                      QMessageBox::Ok);
    fehler->exec();
    delete fehler;
}
