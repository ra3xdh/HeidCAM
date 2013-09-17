#ifndef CAM_H
#define CAM_H

#include <QMainWindow>
#include <QtGui>
#include <freser.h>
#include "progRedakt.h"
#include "programmanalisator.h"
#include "einstellungendialog.h"
#include "wztabdlg.h"
#include "qoccviewercontext.h"


class CAM : public QMainWindow
{
    Q_OBJECT

private:

    QoccViewerContext* meinVC;
    Freser* freser1;
    Programmanalisator* Programmanalisator1;
    progRedakt* programEdit;
    Einstellungendialog* Vert_Hor_dlg;
    WZTabdlg* wzTabdlg;
    QProgressBar* prozent;

    // меню
    QMenu* File_menu;
    QAction* fileOffnen; // открыть файл
    QAction* fileSpeichern; // сохранить
    QAction* fileSpeichernAls; // сохранить как
    QAction* IGES_export;
    QAction* STEP_export;

          // меню
    QMenu* Maschine_menu; // меню машины
    QAction* NC_start; // запуск обработки
    QAction* Typ; // род работы
    QAction* WZTabeinst; // табл. инстр.

    QMenu* View_menu;
    QAction* Axon;
    QAction* Rotate;
    QAction* Pan;
    QAction* Fit;

    QMenu* Werkstuck_menu;


    QMenu* Edit_menu;
    QAction* Abbrechen;
    QAction* Wiederholen;

    void createMenus();
    void createActions();

public:
    CAM(QWidget* parent = 0);

public slots:
    void Einstwahlen();
    void WZTabwahlen();
    void NC_start_gedruckt();

signals:
    void Hor_Vert_gewahlt(bool);

    void ZylX_gewahlt();
    void ZylZ_gewahlt();
    void Rect_gewahlt();

    void Programm(QTextDocument*);
};


//void LoadBottle	( Handle_AIS_InteractiveContext theContext );

#endif // CAM_H
