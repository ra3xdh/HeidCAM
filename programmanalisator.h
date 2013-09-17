#ifndef HEIDANALISATOR_H
#define HEIDANALISATOR_H

#include <QObject>
#include <QtGui>

class Programmanalisator : public QObject
{
    Q_OBJECT

private:

    bool KonvertX(QString *s, float* Q);
    bool KonvertY(QString *s, float* Q);
    bool KonvertZ(QString *s, float* Q);
    bool KonvertIX(QString *s, float* Q);
    bool KonvertIY(QString *s, float* Q);
    bool KonvertIZ(QString *s, float* Q);
    /*bool KonvertBulkForm1(QStringList *Komm);
    bool KonvertBulkForm2(QStringList *Komm);
    bool KonvertL(QStringList *Komm, int* Koord);*/
    QMap<int, int> LBL_lin;
    QMap<int, int> LBL_rep;
    QMap<int, bool> LBL_call;

    void Fehler(QString str);

protected:

    float Q1,Q2,Q3,Q4,Q5,Q6; // параметры для команд
    int I1;

public:

    int KommandAnalisis(QString* Kadr, int LNum);
    int Kommandabarbeiten(QString* Kadr, int LNum);

    Programmanalisator(QObject *parent = 0);

signals:

    void Kommand(int, float, float, float, float, float, float, int);
    void Vert_Hor(bool);
    void CallLBL(int);
    void fertig();
    void Progress(int);

public slots:
    void ProgramEinladen(QTextDocument* dok);

};

#endif // ANALISATOR_H
