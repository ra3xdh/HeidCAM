#include "programmanalisator.h"
#include "operation.h"
#include <QtGui>

Programmanalisator::Programmanalisator(QObject *parent) :
    QObject(parent)
{

}


void Programmanalisator::ProgramEinladen(QTextDocument* dok)

{
    LBL_lin.clear();
    LBL_rep.clear();
    LBL_call.clear();
    unsigned int Nstr = dok->lineCount();

    for (unsigned int i=0; i<(dok->lineCount()); i++ ) {

        QString* Kadr= new QString(dok->findBlockByLineNumber(i).text());

        int Res = Kommandabarbeiten(Kadr, i);

        if (Res<0) {
            QString str1=tr("Ошибка: Строка: ")+QString::number(i); // ошибка - выдадим сообщение
            Fehler(str1);
        } else if (Res>0) {
            i=LBL_lin[I1];
            qDebug()<<"linie"<<I1;
        }

        int progress=(int)(((i+1)*100)/Nstr);
        qDebug()<<progress<<"%";
        emit Progress(progress);
        delete Kadr;
    }

    emit fertig();
}

int Programmanalisator::Kommandabarbeiten(QString* Kadr, int LNum)
{
    int Typ=KommandAnalisis(Kadr, LNum); // анализируем кадр

    if (Typ<0) {

        return -1;
    }

    switch (Typ) { // выдача сигнала по результатам команды
    case BULK_FORM1 : break;
    case BULK_FORM2 : emit Kommand(BULK_FORM2, Q1, Q2, Q3, Q4, Q5, Q6, 0);
                      break;
    case FRES_X     : emit Kommand(FRES_X,Q1,0,0,0,0,0,0);
                      break;
    case FRES_Y     : emit Kommand(FRES_Y,Q1,0,0,0,0,0,0);
                      break;
    case FRES_Z     : emit Kommand(FRES_Z,Q1,0,0,0,0,0,0);
                      break;
    case FRES_IX    : emit Kommand(FRES_IX,Q1,0,0,0,0,0,0);
                      break;
    case FRES_IY    : emit Kommand(FRES_IY,Q1,0,0,0,0,0,0);
                      break;
    case FRES_IZ    : emit Kommand(FRES_IZ,Q1,0,0,0,0,0,0);
                      break;
    case TOOL_CALL  : emit Kommand(TOOL_CALL,0,0,0,0,0,0,I1);
                      break;
    case LBL_CALL   : return I1;
                      break;
    default : break;

    }
    return 0;
}


int Programmanalisator::KommandAnalisis(QString* Kadr, int LNum)
{
    QStringList Komm=Kadr->split(" ",QString::SkipEmptyParts);

    if (Komm.isEmpty()) return 0; // пропуск пустых строк

    if (Komm.first().at(0)==';') return 0; // комментарий

    if (Komm.first().contains(QRegExp("[0-9]{1,2}"))) Komm.removeFirst();
    //  отсекаем номер кадра
    qDebug()<<Komm;

    //1-я строка заготовки
    if ((Komm[0]=="BULK")&&(Komm[1]=="FORM")&&(Komm[2]=="0.1")) {
        Komm.removeFirst();
        Komm.removeFirst();
        Komm.removeFirst();
        qDebug()<<Komm;

        if (KonvertX(&Komm.first(),&Q1)) Komm.removeFirst();
        else return -1;
        if (KonvertY(&Komm.first(),&Q2)) Komm.removeFirst();
        else return -1;
        if (KonvertZ(&Komm.first(),&Q3)) Komm.removeFirst();
        else return -1;

        return BULK_FORM1; // конец обработки
    } else if ((Komm[0]=="BULK")&&(Komm[1]=="FORM")&&(Komm[2]=="0.2")) { // 2-я строка заготовки
        Komm.removeFirst();
        Komm.removeFirst();
        Komm.removeFirst();
        qDebug()<<Komm;

        if (KonvertX(&Komm.first(),&Q4)) Komm.removeFirst();
        else return -1;
        if (KonvertY(&Komm.first(),&Q5)) Komm.removeFirst();
        else return -1;
        if (KonvertZ(&Komm.first(),&Q6)) Komm.removeFirst();
        else return -1;

        return BULK_FORM2;
    } else if (Komm[0]=="L") {
        Komm.removeFirst();

        if (KonvertIX(&Komm.first(),&Q1)) return FRES_IX;
        else if (KonvertX(&Komm.first(),&Q1)) return FRES_X;
        else if (KonvertIY(&Komm.first(),&Q1)) return FRES_IY;
        else if (KonvertY(&Komm.first(),&Q1)) return FRES_Y;
        else if (KonvertIZ(&Komm.first(),&Q1)) return FRES_IZ;
        else if (KonvertZ(&Komm.first(),&Q1)) return FRES_Z;
        else return -1;
    } else if ((Komm[0]=="TOOL")&&(Komm[1]=="CALL")) {
        bool res=false;
        if (Komm.at(3)=="Y") emit Vert_Hor(true);
        if (Komm.at(3)=="Z") emit Vert_Hor(false);
        I1=Komm.at(2).toInt(&res);
        if (res) return TOOL_CALL;
        else return -1;
    } else if (Komm[0]=="LBL") {
        bool res=false;
        int N = Komm.at(1).toInt(&res);
        if (!res) return -1;
        if (LBL_rep.contains(N)||(LBL_call.contains(N))||(LBL_lin.contains(N)))  {
            Fehler(tr("Метка ")+QString::number(N)+tr(" задана дважды"));
            return -2;
        }
        if (!LBL_rep.contains(N)) LBL_rep.insert(N, 0);
        if (!LBL_call.contains(N)) LBL_call.insert(N, false);
        if (!LBL_lin.contains(N)) LBL_lin.insert(N, LNum);
        return LBL_SET;
    } else if (Komm[0]=="CALL"&&Komm[1]=="LBL") {
        bool res=false;
        int N = Komm.at(2).toInt(&res);
        if (!res) return -1;
        if (LBL_call.contains(N)) {
            if (!LBL_call[N]) {
                bool res = false;
                QString s=Komm.at(3);
                LBL_rep[N]=s.remove(0,3).toInt(&res);
                if (!res) return -1;
                LBL_call[N]=true;
                I1=N;
                return LBL_CALL;
            } else {
                LBL_rep[N]--;
                if (LBL_rep[N]!=0) return LBL_CALL;
            }
        }
    }
    return 0; // неопознанная команда
}

bool Programmanalisator::KonvertX(QString *s, float *Q)

{
    if (s->at(0)=='X') {
        s->remove(0, 1);
        bool res=false;
        *Q=s->toFloat(&res);
        return res; // ошибка
    } else return false;
}

bool Programmanalisator::KonvertY(QString *s, float *Q)

{
    if (s->at(0)=='Y') {
        s->remove(0, 1);
        bool res=false;
        *Q=s->toFloat(&res);
        return res; // ошибка
    } else return false;
}

bool Programmanalisator::KonvertZ(QString *s, float *Q)

{
    if (s->at(0)=='Z') {
        s->remove(0, 1);
        bool res=false;
        *Q=s->toFloat(&res);
        return res; // ошибка
    } else return false;
}

bool Programmanalisator::KonvertIX(QString *s, float *Q)

{
    if ((s->at(0)=='I')&&(s->at(1)=='X')) {  // проход в инкрементах по Х
        s->remove(0, 2);
        bool res=false;
        *Q=s->toFloat(&res);
        return res; // ошибка
    } else return false;
}

bool Programmanalisator::KonvertIY(QString *s, float *Q)

{
    if ((s->at(0)=='I')&&(s->at(1)=='Y')) {  // проход в инкрементах по Х
        s->remove(0, 2);
        bool res=false;
        *Q=s->toFloat(&res);
        return res; // ошибка
    } else return false;
}

bool Programmanalisator::KonvertIZ(QString *s, float *Q)

{
    if ((s->at(0)=='I')&&(s->at(1)=='Z')) {  // проход в инкрементах по Х
        s->remove(0, 2);
        bool res=false;
        *Q=s->toFloat(&res);
        return res; // ошибка
    } else return false;
}

void Programmanalisator::Fehler(QString str)
{
    QMessageBox *fehler=new QMessageBox(QMessageBox::Information,tr("Ошибка"),str,
                                      QMessageBox::Ok);
    fehler->exec();
    delete fehler;
}
