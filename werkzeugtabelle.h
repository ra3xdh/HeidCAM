#ifndef WERKZEUGTABELLE_H
#define WERKZEUGTABELLE_H

#include <QObject>
#include <QMap>
#include "werkzeug.h"

class Werkzeugtabelle : public QObject
{
    Q_OBJECT

private:
    QMap<int,Werkzeug*> wzTab;
    int ToolNum;
    QString wzTabfilename;

    void Fehler(QString s);

public:

    int NWZ();
    void ToolCall(int pos);
    void ToolDef(int pos, float R, float H, float L, QString Name);
    void WZleeren(int pos);
    int WZAktiv();
    float Rwz();
    float Hwz();
    float Lwz();
    QString WZNam();   

    explicit Werkzeugtabelle(QString filename, QObject *parent = 0);

signals:

public slots:
    void WZTabSpeichern(QString wztabfile);
    void WZTabLaden(QString wztabfile);

};

#endif // WERKZEUGTABELLE_H
