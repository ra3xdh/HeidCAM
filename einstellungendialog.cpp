#include "einstellungendialog.h"

Einstellungendialog::Einstellungendialog(bool VH, QWidget *parent) :
    QDialog(parent)
{
    gruppeVH = new QButtonGroup(this);
    gruppeZQ = new QButtonGroup(this);
    vertical = new QRadioButton(tr("Вертикально-фрезерный"),this);
    horisont = new QRadioButton(tr("Горизонтально-фрезерный"),this);
    zyl_H = new QRadioButton(tr("Цилиндрическая в делительной головке"), this);
    zyl_V = new QRadioButton(tr("Цилиндрическая на поворотном столе"), this);
    quad = new QRadioButton(tr("Пямоугольная"), this);
    gruppeVH->addButton(vertical,1);
    gruppeVH->addButton(horisont,2);
    gruppeZQ->addButton(zyl_H,1);
    gruppeZQ->addButton(zyl_V,2);
    gruppeZQ->addButton(quad,3);
    horisont->setChecked(VH);
    vertical->setChecked(!VH);
    quad->setChecked(true);
    //connect(vertical,SIGNAL(toggled(bool)),this,SLOT(istVert(bool)));
    //connect(horisont,SIGNAL(toggled(bool)),this,SLOT(istHor(bool)));

    kn_OK = new QPushButton(tr("OK"),this);
    kn_Abbrechen = new QPushButton(tr("Отмена"),this);

    connect(kn_OK,SIGNAL(clicked()),this,SLOT(accept()));
    connect(kn_Abbrechen,SIGNAL(clicked()),this,SLOT(reject()));

    Hoch = new QGridLayout(this);

    Hoch->addWidget(vertical,0,0,1,6,Qt::AlignLeft);
    Hoch->addWidget(horisont,1,0,1,6,Qt::AlignLeft);
    Hoch->addWidget(zyl_H,0,6,1,16,Qt::AlignLeft);
    Hoch->addWidget(zyl_V,1,6,1,16,Qt::AlignLeft);
    Hoch->addWidget(quad,2,6,1,16,Qt::AlignLeft);
    Hoch->addWidget(kn_OK,3,1,Qt::AlignRight);
    Hoch->addWidget(kn_Abbrechen,3,2);

    setWindowTitle(tr("Выбор типа обработки"));

    setLayout(Hoch);
}

bool Einstellungendialog::istVert()
{
    return vertical->isChecked();
}

bool Einstellungendialog::istHor()

{
    return horisont->isChecked();
}

bool Einstellungendialog::istZylX()
{
    return zyl_H->isChecked();
}

bool Einstellungendialog::istZylZ()
{
    return zyl_V->isChecked();
}

bool Einstellungendialog::istQuad()
{
    return quad->isChecked();
}
