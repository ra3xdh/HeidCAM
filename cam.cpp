#include <QtGui>
#include "cam.h"
#include "heidhighlighter.h"

CAM::CAM(QWidget* parent) : QMainWindow(parent)

{
    meinVC=new QoccViewerContext();
    freser1 = new Freser(meinVC->getContext(),this,Qt::MSWindowsOwnDC); // создаю динамический объект класса Freser
    Programmanalisator1 = new Programmanalisator(this);
    setCentralWidget(freser1); // обозначаю scene1 центральным виджетом в главном окне

    connect(Programmanalisator1, SIGNAL(Kommand(int,float,float,float,float,float,float,int)),
            freser1, SLOT(Fresen(int,float,float,float,float,float,float,int)));
    connect(Programmanalisator1,SIGNAL(Vert_Hor(bool)),freser1,SLOT(Einstwechsel(bool)));
    connect(Programmanalisator1,SIGNAL(fertig()),freser1,SLOT(Abarbeiten()));

    this->setWindowTitle("Heid CAM - IIA"); // название главного окна

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QDockWidget* prog_dock = new QDockWidget(tr("Программа"),this);
    programEdit = new progEditor(prog_dock);
    prog_dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    prog_dock->setWidget(programEdit);
    new HeidHighLighter(programEdit->document());
    connect(programEdit,SIGNAL(Programmgeladen(QString)),freser1->WZTab,SLOT(WZTabLaden(QString)));
    connect(programEdit,SIGNAL(Programmgespeichert(QString)),freser1->WZTab,SLOT(WZTabSpeichern(QString)));
    connect(programEdit,SIGNAL(changeWindowTitle(QString)),prog_dock,SLOT(setWindowTitle(QString)));

    createActions();
    createMenus();

    prog_dock->setFixedWidth(250);

    addDockWidget(Qt::LeftDockWidgetArea, prog_dock);
    this->showMaximized();

    prozent = new QProgressBar(this);
    statusBar()->addWidget(prozent);
    connect(Programmanalisator1,SIGNAL(Progress(int)),prozent,SLOT(setValue(int)));

    connect(this,SIGNAL(sigXCylinder()),freser1,SLOT(WS_wechsel_ZylX()));
    connect(this,SIGNAL(signalZCylinder()),freser1,SLOT(WS_wechsel_ZylZ()));
    connect(this,SIGNAL(sigBox()),freser1,SLOT(WS_wechsel_Rect()));

}


void CAM::createActions() // создать объекты действий и связать их со слотами
{
   fileOpen = new QAction(tr("Открыть"), this); // создать действие
   connect(fileOpen, SIGNAL(triggered()), programEdit, SLOT(slotLoad())); // связать сингалы и слоты

   fileSave = new QAction(tr("Сохранить"), this);
   connect(fileSave, SIGNAL(triggered()), programEdit, SLOT(slotSave()));
   fileSaveAs = new QAction(tr("Сохранить как"), this);
   connect(fileSaveAs,SIGNAL(triggered()),programEdit,SLOT(slotSaveAs()));

   NC_start = new QAction("NC start", this);
   connect(NC_start, SIGNAL(triggered()), this, SLOT(slotNCstart()));
   connect(this,SIGNAL(Programm(QTextDocument*)),Programmanalisator1,SLOT(ProgramEinladen(QTextDocument*)));
   Typ = new QAction(tr("Настройка обработки"), this);
   connect(Typ,SIGNAL(triggered()),this,SLOT(slotMaschineTypeSetup()));
   connect(this,SIGNAL(sigHorVertChanged(bool)),freser1,SLOT(Einstwechsel(bool)));
   IGES_export = new QAction(tr("Экспорт в IGES"),this);
   connect(IGES_export,SIGNAL(triggered()),freser1->werkstuck1,SLOT(IGESExportieren()));
   STEP_export = new QAction(tr("Экспорт в STEP"),this);
   connect(STEP_export,SIGNAL(triggered()),freser1->werkstuck1,SLOT(STEPExportieren()));

   ToolTableSetup = new QAction(tr("Таблица инструментов"), this);
   connect(ToolTableSetup,SIGNAL(triggered()),this,SLOT(slotSetupToolTable()));

   mUndo = new QAction(tr("Отмена"), this);
   mRedo = new QAction(tr("Повтор"), this);
   connect(mUndo,SIGNAL(triggered()),programEdit,SLOT(undo()));
   connect(mRedo,SIGNAL(triggered()),programEdit,SLOT(redo()));

   Axon = new QAction(tr("Изометрия"),this);
   connect(Axon,SIGNAL(triggered()),freser1,SLOT(viewAxo()));
   Rotate = new QAction(tr("Вращать"),this);
   connect(Rotate,SIGNAL(triggered()),freser1,SLOT(rotation()));
   Pan = new QAction(tr("Двигать"),this);
   connect(Pan,SIGNAL(triggered()),freser1,SLOT(pan()));
   Fit = new QAction(tr("Вписать в экран"),this);
   connect(Fit,SIGNAL(triggered()),freser1,SLOT(fitAll()));
}

void CAM::createMenus() // создать меню
{
   File_menu = menuBar()->addMenu(tr("Файл")); // добавить группу меню
   File_menu->addAction(fileOpen); // добавить в меню действие
   File_menu->addAction(fileSave);
   File_menu->addAction(fileSaveAs);
   File_menu->addAction(IGES_export);
   File_menu->addAction(STEP_export);

   Edit_menu = menuBar()->addMenu(tr("Правка"));
   Edit_menu->addAction(mUndo);
   Edit_menu->addAction(mRedo);

   View_menu = menuBar()->addMenu(tr("Вид"));
   View_menu->addAction(Axon);
   View_menu->addAction(Rotate);
   View_menu->addAction(Pan);
   View_menu->addAction(Fit);

   Maschine_menu = menuBar()->addMenu(tr("Деталь"));
   Maschine_menu->addAction(NC_start);
   Maschine_menu->addAction(Typ);
   Maschine_menu->addAction(ToolTableSetup);

}




void CAM::slotMaschineTypeSetup()

{
    Vert_Hor_dlg = new Einstellungendialog(freser1->istLangs(),this);
    if (Vert_Hor_dlg->exec()==QDialog::Accepted) {
        bool b = Vert_Hor_dlg->istHor();
        emit sigHorVertChanged(b);

        if (Vert_Hor_dlg->istZylX()) emit sigXCylinder();
        else
        if (Vert_Hor_dlg->istZylZ()) emit signalZCylinder();
        else
        if (Vert_Hor_dlg->istQuad()) emit sigBox();

    }

    delete Vert_Hor_dlg;
}

void CAM::slotSetupToolTable()
{
    toolTabDlg = new ToolTableDlg(freser1->WZTab,this);

    if (toolTabDlg->exec()==QDialog::Accepted) {
        qDebug()<<"111";
    }
    delete toolTabDlg;
}

void CAM::slotNCstart()
{
    //LoadBottle(meinVC->getContext());
    prozent->setValue(0);
    meinVC->deleteAllObjects();
    emit Programm(programEdit->document());
}


