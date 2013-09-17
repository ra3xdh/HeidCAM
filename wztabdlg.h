#ifndef WZTABDLG_H
#define WZTABDLG_H

#include <QDialog>
#include <QtGui>
#include "werkzeugtabelle.h"
#include "werkzeug.h"

class WZTabdlg : public QDialog
{
    Q_OBJECT
private:
    QGridLayout* Hoch;
    QVBoxLayout* L1;
    QHBoxLayout* L2;

    QPushButton* kn_OK;
    QPushButton* kn_Abbrechen;
    QPushButton* kn_NeuWZ;
    QPushButton* kn_WZleeren;
    QTableWidget* TabWZ;

    Werkzeugtabelle* WZTab;

    QStringList lstV;

public:
    explicit WZTabdlg(Werkzeugtabelle* wzTab, QWidget *parent = 0);

signals:

public slots:
    void NeuWZ();
    void WZleeren();

};

#endif // WZTABDLG_H
