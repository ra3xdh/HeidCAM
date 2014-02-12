#ifndef HEIDANALISATOR_H
#define HEIDANALISATOR_H

#include <QObject>
#include <QtGui>

class Programmanalisator : public QObject
{
    Q_OBJECT

private:

    bool ConvertX(QString *s, float* Q);
    bool ConvertY(QString *s, float* Q);
    bool ConvertZ(QString *s, float* Q);
    bool ConvertIX(QString *s, float* Q);
    bool ConvertIY(QString *s, float* Q);
    bool ConvertIZ(QString *s, float* Q);
    /*bool KonvertBulkForm1(QStringList *Komm);
    bool KonvertBulkForm2(QStringList *Komm);
    bool KonvertL(QStringList *Komm, int* Koord);*/
    QMap<int, int> LBL_lin;
    QMap<int, int> LBL_rep;
    QMap<int, bool> LBL_call;

    void errorMessage(QString str);

protected:

    float Q1,Q2,Q3,Q4,Q5,Q6; // параметры для команд
    int I1;

public:

    int parseCommand(QString* Kadr, int LNum);
    int processCommand(QString* Kadr, int LNum);

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
