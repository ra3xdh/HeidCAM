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
    programEdit = new progRedakt(prog_dock);
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

}


void CAM::createActions() // создать объекты действий и связать их со слотами
{
   fileOffnen = new QAction(tr("Открыть"), this); // создать действие
   connect(fileOffnen, SIGNAL(triggered()), programEdit, SLOT(slotLoad())); // связать сингалы и слоты

   fileSpeichern = new QAction(tr("Сохранить"), this);
   connect(fileSpeichern, SIGNAL(triggered()), programEdit, SLOT(slotSave()));
   fileSpeichernAls = new QAction(tr("Сохранить как"), this);
   connect(fileSpeichernAls,SIGNAL(triggered()),programEdit,SLOT(slotSaveAs()));

   NC_start = new QAction("NC start", this);
   connect(NC_start, SIGNAL(triggered()), this, SLOT(NC_start_gedruckt()));
   connect(this,SIGNAL(Programm(QTextDocument*)),Programmanalisator1,SLOT(ProgramEinladen(QTextDocument*)));
   Typ = new QAction(tr("Настройка обработки"), this);
   connect(Typ,SIGNAL(triggered()),this,SLOT(Einstwahlen()));
   connect(this,SIGNAL(Hor_Vert_gewahlt(bool)),freser1,SLOT(Einstwechsel(bool)));
   IGES_export = new QAction(tr("Экспорт в IGES"),this);
   connect(IGES_export,SIGNAL(triggered()),freser1->werkstuck1,SLOT(IGESExportieren()));
   STEP_export = new QAction(tr("Экспорт в STEP"),this);
   connect(STEP_export,SIGNAL(triggered()),freser1->werkstuck1,SLOT(STEPExportieren()));

   WZTabeinst = new QAction(tr("Таблица инструментов"), this);
   connect(WZTabeinst,SIGNAL(triggered()),this,SLOT(WZTabwahlen()));

   Abbrechen = new QAction(tr("Отмена"), this);
   Wiederholen = new QAction(tr("Повтор"), this);
   connect(Abbrechen,SIGNAL(triggered()),programEdit,SLOT(undo()));
   connect(Wiederholen,SIGNAL(triggered()),programEdit,SLOT(redo()));

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
   File_menu->addAction(fileOffnen); // добавить в меню действие
   File_menu->addAction(fileSpeichern);
   File_menu->addAction(fileSpeichernAls);
   File_menu->addAction(IGES_export);
   File_menu->addAction(STEP_export);

   Edit_menu = menuBar()->addMenu(tr("Правка"));
   Edit_menu->addAction(Abbrechen);
   Edit_menu->addAction(Wiederholen);

   View_menu = menuBar()->addMenu(tr("Вид"));
   View_menu->addAction(Axon);
   View_menu->addAction(Rotate);
   View_menu->addAction(Pan);
   View_menu->addAction(Fit);

   Maschine_menu = menuBar()->addMenu(tr("Деталь"));
   Maschine_menu->addAction(NC_start);
   Maschine_menu->addAction(Typ);
   Maschine_menu->addAction(WZTabeinst);

}




void CAM::Einstwahlen()

{
    Vert_Hor_dlg = new Einstellungendialog(freser1->istLangs(),this);
    if (Vert_Hor_dlg->exec()==QDialog::Accepted) {
        bool b = Vert_Hor_dlg->istHor();
        emit Hor_Vert_gewahlt(b);
    }

    delete Vert_Hor_dlg;
}

void CAM::WZTabwahlen()
{
    wzTabdlg = new WZTabdlg(freser1->WZTab,this);

    if (wzTabdlg->exec()==QDialog::Accepted) {
        qDebug()<<"111";
    }
    delete wzTabdlg;
}

void CAM::NC_start_gedruckt()
{
    //LoadBottle(meinVC->getContext());
    prozent->setValue(0);
    meinVC->deleteAllObjects();
    emit Programm(programEdit->document());
}


