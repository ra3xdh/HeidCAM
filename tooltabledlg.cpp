#include "tooltabledlg.h"

ToolTableDlg::ToolTableDlg(Werkzeugtabelle* wzTab, QWidget *parent) :
    QDialog(parent)
{
    ToolsTab=wzTab;

    btnOK = new QPushButton(tr("ОК"),this);
    btnCancel = new QPushButton(tr("Отмена"),this);
    btnNewTool = new QPushButton(tr("Добавить инструмент"),this);
    btnRemoveTool = new QPushButton(tr("Удалить инструмент"),this);
    connect(btnOK,SIGNAL(clicked()),this,SLOT(accept()));
    connect(btnOK,SIGNAL(clicked()),wzTab,SLOT(WZTabSpeichern()));
    connect(btnCancel,SIGNAL(clicked()),this,SLOT(reject()));
    connect(btnNewTool,SIGNAL(clicked()),this,SLOT(slotNewTool()));
    connect(btnRemoveTool,SIGNAL(clicked()),this,SLOT(slotRemoveTool()));

    TabTools = new QTableWidget(ToolsTab->NWZ(),5,this);
    QStringList lstH;
    lstH<<"N"<<tr("Имя инструмента")<<tr("Радиус R")<<tr("Ширина h")<<tr("Длина L");
    TabTools->setHorizontalHeaderLabels(lstH);
    //QStringList lstV;
    for (int i=0; i<(ToolsTab->NWZ());i++) {
        lstV<<QString::number(i);
    }
    TabTools->setVerticalHeaderLabels(lstV);

    int N=ToolsTab->WZAktiv();

    for (int i=0;i<ToolsTab->NWZ();i++) {
        ToolsTab->ToolCall(i);
        QTableWidgetItem* swz = new QTableWidgetItem;
        swz->setText(QString::number(i));
        TabTools->setItem(i,0,swz);
        swz = new QTableWidgetItem;
        swz->setText(ToolsTab->WZNam());
        TabTools->setItem(i,1,swz);
        swz = new QTableWidgetItem;
        swz->setText(QString::number(ToolsTab->Rwz()));
        TabTools->setItem(i,2,swz);
        swz = new QTableWidgetItem;
        swz->setText(QString::number(ToolsTab->Hwz()));
        TabTools->setItem(i,3,swz);
        swz = new QTableWidgetItem;
        swz->setText(QString::number(ToolsTab->Lwz()));
        TabTools->setItem(i,4,swz);

    }

    ToolsTab->ToolCall(N);

    L1 = new QVBoxLayout;
    L2 = new QHBoxLayout;
    L1->addWidget(TabTools,7);
    TabTools->resize(700,300);
    L2->addStretch(1);
    L2->addWidget(btnNewTool);
    L2->addWidget(btnRemoveTool);
    L2->addWidget(btnOK);
    L2->addWidget(btnCancel);
    L2->addStretch(1);
    L1->addLayout(L2);

    setWindowTitle(tr("Таблица инструментов"));
    resize(500,300);

    setLayout(L1);
}

void ToolTableDlg::slotNewTool()
{
    TabTools->setRowCount(TabTools->rowCount()+1);
}

void ToolTableDlg::slotRemoveTool()
{
    TabTools->setRowCount(TabTools->rowCount()-1);
}
