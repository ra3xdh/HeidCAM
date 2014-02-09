#ifndef TOOLTABLEDLG_H
#define TOOLTABLEDLG_H

#include <QDialog>
#include <QtGui>
#include "werkzeugtabelle.h"
#include "werkzeug.h"

class ToolTableDlg : public QDialog
{
    Q_OBJECT
private:
    QGridLayout* Top1;
    QVBoxLayout* L1;
    QHBoxLayout* L2;

    QPushButton* btnOK;
    QPushButton* btnCancel;
    QPushButton* btnNewTool;
    QPushButton* btnRemoveTool;
    QTableWidget* TabTools;

    Werkzeugtabelle* ToolsTab;

    QStringList lstV;

public:
    explicit ToolTableDlg(Werkzeugtabelle* wzTab, QWidget *parent = 0);

signals:

public slots:
    void slotNewTool();
    void slotRemoveTool();

};

#endif // TOOLTABLEDLG_H
