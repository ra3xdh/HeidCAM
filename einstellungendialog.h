#ifndef EINSTELLUNGENDIALOG_H
#define EINSTELLUNGENDIALOG_H

#include <QDialog>
#include <QtGui>

class Einstellungendialog : public QDialog
{
    Q_OBJECT

private:

    QButtonGroup* gruppeVH;
    QButtonGroup* gruppeZQ;

    QRadioButton* vertical;
    QRadioButton* horisont;

    QRadioButton* zyl_H;
    QRadioButton* zyl_V;
    QRadioButton* quad;

    QPushButton* kn_OK;
    QPushButton* kn_Abbrechen;

    QGridLayout* Hoch;

public:
    explicit Einstellungendialog(bool VH,QWidget *parent = 0);

    bool istVert();
    bool istHor();

    bool istZylX();
    bool istZylZ();
    bool istQuad();

signals:

public slots:


};

#endif // EINSTELLUNGENDIALOG_H
