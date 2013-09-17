#include "wztabdlg.h"

WZTabdlg::WZTabdlg(Werkzeugtabelle* wzTab, QWidget *parent) :
    QDialog(parent)
{
    WZTab=wzTab;

    kn_OK = new QPushButton(tr("ОК"),this);
    kn_Abbrechen = new QPushButton(tr("Отмена"),this);
    kn_NeuWZ = new QPushButton(tr("Добавить инструмент"),this);
    kn_WZleeren = new QPushButton(tr("Удалить инструмент"),this);
    connect(kn_OK,SIGNAL(clicked()),this,SLOT(accept()));
    connect(kn_OK,SIGNAL(clicked()),wzTab,SLOT(WZTabSpeichern()));
    connect(kn_Abbrechen,SIGNAL(clicked()),this,SLOT(reject()));
    connect(kn_NeuWZ,SIGNAL(clicked()),this,SLOT(NeuWZ()));
    connect(kn_WZleeren,SIGNAL(clicked()),this,SLOT(WZleeren()));

    TabWZ = new QTableWidget(WZTab->NWZ(),5,this);
    QStringList lstH;
    lstH<<"N"<<tr("Имя инструмента")<<tr("Радиус R")<<tr("Ширина h")<<tr("Длина L");
    TabWZ->setHorizontalHeaderLabels(lstH);
    //QStringList lstV;
    for (int i=0; i<(WZTab->NWZ());i++) {
        lstV<<QString::number(i);
    }
    TabWZ->setVerticalHeaderLabels(lstV);

    int N=WZTab->WZAktiv();

    for (int i=0;i<WZTab->NWZ();i++) {
        WZTab->ToolCall(i);
        QTableWidgetItem* swz = new QTableWidgetItem;
        swz->setText(QString::number(i));
        TabWZ->setItem(i,0,swz);
        swz = new QTableWidgetItem;
        swz->setText(WZTab->WZNam());
        TabWZ->setItem(i,1,swz);
        swz = new QTableWidgetItem;
        swz->setText(QString::number(WZTab->Rwz()));
        TabWZ->setItem(i,2,swz);
        swz = new QTableWidgetItem;
        swz->setText(QString::number(WZTab->Hwz()));
        TabWZ->setItem(i,3,swz);
        swz = new QTableWidgetItem;
        swz->setText(QString::number(WZTab->Lwz()));
        TabWZ->setItem(i,4,swz);

    }

    WZTab->ToolCall(N);

    L1 = new QVBoxLayout;
    L2 = new QHBoxLayout;
    L1->addWidget(TabWZ,7);
    TabWZ->resize(700,300);
    L2->addStretch(1);
    L2->addWidget(kn_NeuWZ);
    L2->addWidget(kn_WZleeren);
    L2->addWidget(kn_OK);
    L2->addWidget(kn_Abbrechen);
    L2->addStretch(1);
    L1->addLayout(L2);

    setWindowTitle(tr("Таблица инструментов"));
    resize(500,300);

    setLayout(L1);
}

void WZTabdlg::NeuWZ()
{
    TabWZ->setRowCount(TabWZ->rowCount()+1);
}

void WZTabdlg::WZleeren()
{
    TabWZ->setRowCount(TabWZ->rowCount()-1);
}
