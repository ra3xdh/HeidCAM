#ifndef CAM_H
#define CAM_H

#include <QMainWindow>
#include <QtGui>
#include <freser.h>
#include "progeditor.h"
#include "programmanalisator.h"
#include "einstellungendialog.h"
#include "tooltabledlg.h"
#include "qoccviewercontext.h"


class CAM : public QMainWindow
{
    Q_OBJECT

private:

    QoccViewerContext* meinVC;
    Freser* freser1;
    Programmanalisator* Programmanalisator1;
    progEditor* programEdit;
    Einstellungendialog* Vert_Hor_dlg;
    ToolTableDlg* toolTabDlg;
    QProgressBar* prozent;

    // меню
    QMenu* File_menu;
    QAction* fileOpen; // открыть файл
    QAction* fileSave; // сохранить
    QAction* fileSaveAs; // сохранить как
    QAction* IGES_export;
    QAction* STEP_export;

          // меню
    QMenu* Maschine_menu; // меню машины
    QAction* NC_start; // запуск обработки
    QAction* Typ; // род работы
    QAction* ToolTableSetup; // табл. инстр.

    QMenu* View_menu;
    QAction* Axon;
    QAction* Rotate;
    QAction* Pan;
    QAction* Fit;

    QMenu* Part_menu;


    QMenu* Edit_menu;
    QAction* mUndo;
    QAction* mRedo;

    void createMenus();
    void createActions();

public:
    CAM(QWidget* parent = 0);

public slots:
    void slotMaschineTypeSetup();
    void slotSetupToolTable();
    void slotNCstart();

signals:
    void sigHorVertChanged(bool);

    void sigXCylinder();
    void signalZCylinder();
    void sigBox();

    void Programm(QTextDocument*);
};


//void LoadBottle	( Handle_AIS_InteractiveContext theContext );

#endif // CAM_H
