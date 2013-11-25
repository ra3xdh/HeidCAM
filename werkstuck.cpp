#include <BRep_Tool.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgo_Cut.hxx>
#include <BRepAlgo_Fuse.hxx>

#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepExtrema_DistanceSS.hxx>
#include <BRepExtrema_DistShapeShape.hxx>

#include <BRepFilletAPI_MakeFillet.hxx>

#include <BRepLib.hxx>

#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>

#include <GC_Root.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeSegment.hxx>

#include <GCE2d_MakeSegment.hxx>

#include <gp.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Dir.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>

#include <Geom_CylindricalSurface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Surface.hxx>
#include <Geom_TrimmedCurve.hxx>

#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>

#include <TopExp_Explorer.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>

#include <TopTools_ListOfShape.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>

#include <StepAP214.hxx>

#include <math.h>
#include "werkstuck.h"
#include "operation.h"

#define PI 3.14159

Werkstuck::Werkstuck(Handle_AIS_InteractiveContext VC, QObject *parent) :
    QObject(parent)
{
    Erstmal=true;
    VC1=VC;
    Xstart=0; Ystart=0; Zstart=0;
    Xf=0.15; Yf=0.15; Zf=0.15;
    Xwz=0; Ywz=0; Zwz=0;
    Rundtisch=0;

    BulkForm(0,0,0,150,150,50);

    LX(75,10,50);
    LY(75,10,50);
    LZ(25,10,50);
    LX(25,10,50);
    LY(35,10,50);

    LZ(55,10,50);
    LX(0,10,50);
    LY(0,10,50);
    LZ(49,10,50);
   /* for (int i=0;i<10;i++) {
        LX(150,10,50);
        LY(150,10,50);
        LX(0,10,50);
        LY(0,10,50);
        LIZ(-1,10,50);
    }*/

    Einbau();
}



void Werkstuck::Einbau()
{
    //WS = BRepAlgoAPI_Cut(WS,WZweg);

    Handle(AIS_Shape) AIS_WS=new AIS_Shape(WS);
    VC1->CloseAllContexts();
    VC1->SetDisplayMode(AIS_WS,1,Standard_True);
    VC1->SetMaterial(AIS_WS,Graphic3d_NOM_STEEL,false);
    VC1->SetColor(AIS_WS, Quantity_NOC_RED);
    VC1->Display(AIS_WS, Standard_True);
    VC1->OpenLocalContext();
    VC1->ActivateStandardMode(TopAbs_FACE);

}



void Werkstuck::AddVertex (double x, double y, double z, Handle_AIS_InteractiveContext theContext)
{
        TopoDS_Vertex aVertex=BRepBuilderAPI_MakeVertex( gp_Pnt(x,y,z) );
        Handle(AIS_Shape) AISVertex = new AIS_Shape(aVertex);
        // context is the handle to an AIS_InteractiveContext object.
        theContext->Display(AISVertex);
}

void Werkstuck::ShowOrigin ( Handle_AIS_InteractiveContext theContext )
{
        AddVertex ( 0.0, 0.0, 0.0, theContext);
}




void Werkstuck::BulkForm(float Xmin, float Ymin, float Zmin, float Xmax, float Ymax, float Zmax)
{

    Xstart=Xmax+10; //начальное положение инструмента
    Ystart=Ymax+10; // за заготовкой
    Zstart=Zmax+10;
    Xwz=Xstart;
    Ywz=Ystart;
    Zwz=Zstart;
    H0=Zmax;
    Xfmin=Xmin; Xfmax=Xmax;
    Yfmin=Ymin; Yfmax=Ymax;

    gp_Pnt punkt1(Xmin, Ymin, Zmin);
    gp_Pnt punkt2(Xmin, Ymax, Zmin);
    gp_Pnt punkt3(Xmax, Ymax, Zmin);
    gp_Pnt punkt4(Xmax, Ymin, Zmin);

    Handle(Geom_TrimmedCurve) aSeg1 = GC_MakeSegment(punkt1 , punkt2);
    Handle(Geom_TrimmedCurve) aSeg2 = GC_MakeSegment(punkt2 , punkt3);
    Handle(Geom_TrimmedCurve) aSeg3 = GC_MakeSegment(punkt3 , punkt4);
    Handle(Geom_TrimmedCurve) aSeg4 = GC_MakeSegment(punkt4 , punkt1);

    TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge(aSeg1);
    TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge(aSeg2);
    TopoDS_Edge aEdge3 = BRepBuilderAPI_MakeEdge(aSeg3);
    TopoDS_Edge aEdge4 = BRepBuilderAPI_MakeEdge(aSeg4);

    TopoDS_Wire Basis  = BRepBuilderAPI_MakeWire(aEdge1 , aEdge2 , aEdge3, aEdge4);

    TopoDS_Face FlacheBasis = BRepBuilderAPI_MakeFace(Basis);

    gp_Vec PrismVec(0 , 0 , Zmax-Zmin);

    TopoDS_Shape sBulkForm = BRepPrimAPI_MakePrism(FlacheBasis , PrismVec);

    WS = sBulkForm;

    Erst_weg = true;
}

void Werkstuck::BulkFormCylindrusZ(float Xc, float Yc, float Zc, float H, float R)
{
    gp_Pnt punkt_zent(Xc,Yc,Zc-H);
    gp_Dir wsNormal = gp::DZ();
    gp_Ax2 wsAchse(punkt_zent,wsNormal);

    BRepPrimAPI_MakeCylinder zLZ(wsAchse,R,H);
    WS = zLZ.Shape();

    Xstart=Xc;
    Ystart=Yc;
    Zstart=Zc;
    Xwz=Xstart;
    Ywz=Ystart;
    Zwz=Zstart;
    H0=Zc;
    Xfmin=Xc-R; Xfmax=Xc+R;
    Yfmin=Yc-R; Yfmax=Yc+R;

    Erst_weg = true;
}

void Werkstuck::BulkFormCylindrusX(float Xc, float Yc, float Zc, float H, float R)
{
    gp_Pnt punkt_zent(Xc-H,Yc,Zc);
    gp_Dir wsNormal = gp::DX();
    gp_Ax2 wsAchse(punkt_zent,wsNormal);

    BRepPrimAPI_MakeCylinder zWS(wsAchse,R,H);
    WS = zWS.Shape();

    Erst_weg = true;

    Xstart=Xc;
    Ystart=Yc;
    Zstart=Zc+R+5;
    Xwz=Xstart;
    Ywz=Ystart;
    Zwz=Zstart;
    H0=Zc+R;
    Xfmax=Xc; Xfmin=Xc-H;
    Yfmax=Yc+R; Xfmin=Yc-R;
}

void Werkstuck::LX(float endPunkt, float Rwz, float Lwz, float Rwz2) // прямое фрезерование по оси Х
          // endPunkt - конечная точка
{
    if (Zwz<H0) {
        gp_Pnt punkt1(Xwz,Ywz-Rwz,Zwz);
        gp_Pnt punkt2(Xwz,Ywz+Rwz,Zwz);
        gp_Pnt punkt3(endPunkt,Ywz+Rwz,Zwz);
        gp_Pnt punkt4(endPunkt,Ywz,Zwz);
        if (endPunkt>=Xwz) punkt4.SetX(endPunkt+Rwz);
        else punkt4.SetX(endPunkt-Rwz);
        gp_Pnt punkt6(Xwz,Ywz,Zwz);
        if (endPunkt>=Xwz) punkt6.SetX(Xwz-Rwz);
        else punkt6.SetX(Xwz+Rwz);

        gp_Pnt punkt5(endPunkt,Ywz-Rwz,Zwz);


        //Handle(Geom_TrimmedCurve) aSeg1 = GC_MakeSegment(punkt1 , punkt2);
        Handle(Geom_TrimmedCurve) aSeg1 = GC_MakeArcOfCircle(punkt1,punkt6 ,punkt2);
        Handle(Geom_TrimmedCurve) aSeg2 = GC_MakeSegment(punkt2 , punkt3);
        Handle(Geom_TrimmedCurve) aSeg3 = GC_MakeArcOfCircle(punkt3,punkt4 ,punkt5);
        Handle(Geom_TrimmedCurve) aSeg4 = GC_MakeSegment(punkt5 , punkt1);

        TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge(aSeg1);
        TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge(aSeg2);
        TopoDS_Edge aEdge3 = BRepBuilderAPI_MakeEdge(aSeg3);
        TopoDS_Edge aEdge4 = BRepBuilderAPI_MakeEdge(aSeg4);

        TopoDS_Wire Basis  = BRepBuilderAPI_MakeWire(aEdge1 , aEdge2 , aEdge3, aEdge4);

        TopoDS_Face FlacheBasis = BRepBuilderAPI_MakeFace(Basis);

        gp_Vec PrismVec(0 , 0 , Lwz);

        TopoDS_Shape sLX = BRepPrimAPI_MakePrism(FlacheBasis , PrismVec);

        if (Rwz2>0) {
            BRepFilletAPI_MakeFillet mkFillet(sLX);
            TopExp_Explorer aEdgeExplorer(sLX , TopAbs_EDGE);

            while(aEdgeExplorer.More()){
            TopoDS_Edge aEdge = TopoDS::Edge(aEdgeExplorer.Current());
            mkFillet.Add(Rwz2 , aEdge);
            aEdgeExplorer.Next();
            }
            sLX = mkFillet.Shape();
        }

        WS = BRepAlgo_Cut(WS,sLX);
        /*if (Erst_weg) {
            WZweg = sLX;
            Erst_weg = false;
        } else {
            WZweg = BRepAlgoAPI_Fuse(WZweg,sLX);
        }*/
    }
    Xwz = endPunkt;
}

void Werkstuck::LY(float endPunkt, float Rwz, float Lwz, float Rwz2) // прямое фрезерование по оси Х
          // endPunkt - конечная точка
{
    if (Zwz<H0) {
        gp_Pnt punkt1(Xwz-Rwz,Ywz,Zwz);
        gp_Pnt punkt2(Xwz+Rwz,Ywz,Zwz);
        gp_Pnt punkt3(Xwz+Rwz,endPunkt,Zwz);
        gp_Pnt punkt4(Xwz,endPunkt,Zwz);
        if (endPunkt>=Ywz) punkt4.SetY(endPunkt+Rwz);
        else punkt4.SetY(endPunkt-Rwz);

        gp_Pnt punkt5(Xwz-Rwz,endPunkt,Zwz);


        Handle(Geom_TrimmedCurve) aSeg1 = GC_MakeSegment(punkt1 , punkt2);
        Handle(Geom_TrimmedCurve) aSeg2 = GC_MakeSegment(punkt2 , punkt3);
        Handle(Geom_TrimmedCurve) aSeg3 = GC_MakeArcOfCircle(punkt3,punkt4 ,punkt5);
        Handle(Geom_TrimmedCurve) aSeg4 = GC_MakeSegment(punkt5 , punkt1);

        TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge(aSeg1);
        TopoDS_Edge aEdge2 = BRepBuilderAPI_MakeEdge(aSeg2);
        TopoDS_Edge aEdge3 = BRepBuilderAPI_MakeEdge(aSeg3);
        TopoDS_Edge aEdge4 = BRepBuilderAPI_MakeEdge(aSeg4);

        TopoDS_Wire Basis  = BRepBuilderAPI_MakeWire(aEdge1 , aEdge2 , aEdge3, aEdge4);

        TopoDS_Face FlacheBasis = BRepBuilderAPI_MakeFace(Basis);

        gp_Vec PrismVec(0 , 0 , Lwz);

        TopoDS_Shape sLY = BRepPrimAPI_MakePrism(FlacheBasis , PrismVec);

        if (Rwz2>0) {
            BRepFilletAPI_MakeFillet mkFillet(sLY);
            TopExp_Explorer aEdgeExplorer(sLY , TopAbs_EDGE);

            while(aEdgeExplorer.More()){
            TopoDS_Edge aEdge = TopoDS::Edge(aEdgeExplorer.Current());
            mkFillet.Add(Rwz2 , aEdge);
            aEdgeExplorer.Next();
            }
            sLY = mkFillet.Shape();
        }

        WS = BRepAlgo_Cut(WS,sLY);
        /*if (Erst_weg) {
            WZweg = sLY;
            Erst_weg = false;
        } else {
            WZweg = BRepAlgoAPI_Fuse(WZweg,sLY);
        }*/
    }
    Ywz=endPunkt;
}


void Werkstuck::LZ(float endPunkt, float Rwz, float Lwz, float Rwz2) // прямое фрезерование по оси Z
          // endPunkt - конечная точка
{
    Zwz=endPunkt;

    if (Zwz<H0) {

        gp_Pnt punkt_zent(Xwz,Ywz,Zwz);
        gp_Dir wzNormal = gp::DZ();
        gp_Ax2 wzAchse(punkt_zent,wzNormal);

        BRepPrimAPI_MakeCylinder zLZ(wzAchse,Rwz,Lwz);
        TopoDS_Shape sLZ=zLZ.Shape();

        if (Rwz2>0) {
            BRepFilletAPI_MakeFillet mkFillet(sLZ);
            TopExp_Explorer aEdgeExplorer(sLZ , TopAbs_EDGE);

            while(aEdgeExplorer.More()){
            TopoDS_Edge aEdge = TopoDS::Edge(aEdgeExplorer.Current());
            mkFillet.Add(Rwz2 , aEdge);
            aEdgeExplorer.Next();
            }
            sLZ = mkFillet.Shape();
        }

        WS = BRepAlgo_Cut(WS,sLZ);
        /*if (Erst_weg) {
            WZweg = sLZ;
            Erst_weg = false;
        } else {
            WZweg = BRepAlgoAPI_Fuse(WZweg,sLZ);
        }*/
    }

}

void Werkstuck::LIX(float dX, float Rwz, float Lwz)
// фрезерование прямое в инкрементах
{
    LX(Xwz+dX,Rwz, Lwz);
}

void Werkstuck::LIY(float dY, float Rwz, float Lwz)
// фрезерование прямое в инкрементах
{
    LY(Ywz+dY,Rwz,Lwz);
}

void Werkstuck::LIZ(float dZ, float Rwz, float Lwz)
// фрезерование прямое в инкрементах
{
    LZ(Zwz+dZ,Rwz,Lwz);
}

void Werkstuck::LHX(float endPunkt, float Rwz, float Hwz) // гориз. прямое фрезерование по оси Х
          // endPunkt - конечная точка
{
    Xwz=endPunkt;
}

void Werkstuck::LHZ(float endPunkt, float Rwz, float Hwz) //гориз. прямое фрезерование по оси Х
          // endPunkt - конечная точка
{
    Zwz=endPunkt;
}


void Werkstuck::LHY(float endPunkt, float Rwz, float Hwz) //гориз. прямое фрезерование по оси Z
          // endPunkt - конечная точка
{
    if (Zwz<(H0+Rwz)) {
        gp_Pnt punkt_zent(Xwz,Ywz,Zwz);
        gp_Dir wzNormal = gp::DY();
        gp_Ax2 wzAchse(punkt_zent,wzNormal);

        BRepPrimAPI_MakeCylinder zLHY(wzAchse,Rwz,endPunkt-Ywz);
        TopoDS_Shape sLHY=zLHY.Shape();
        WS = BRepAlgoAPI_Cut(WS,sLHY);
    }
    Ywz=endPunkt;
}

void Werkstuck::LHIX(float dX, float Rwz, float Hwz)
{
    LHX(Xwz+dX,Rwz,Hwz);
}

void Werkstuck::LHIY(float dY, float Rwz, float Hwz)
{
    LHY(Ywz+dY,Rwz,Hwz);
}

void Werkstuck::LHIZ(float dZ, float Rwz, float Hwz)
{
    LHZ(Zwz+dZ,Rwz,Hwz);
}

void Werkstuck::RundtischEin(float Ecke)
{
    Rundtisch=Ecke;
}

void Werkstuck::IGESExportieren()
{
    IGESControl_Controller::Init();
    IGESControl_Writer *schreiber = new IGESControl_Writer( Interface_Static::CVal( "XSTEP.iges.unit" ),
                                                            Interface_Static::IVal( "XSTEP.iges.writebrep.mode" ) );
    //Interface_Static::SetIVal("write.iges.brep.mode",1);
    bool res1 = schreiber->AddShape(WS);
    QString str = QFileDialog::getSaveFileName();
    if (str.isEmpty()) return;
    schreiber->ComputeModel();
    bool res2 = schreiber->Write(str.toStdString().c_str());
    if (res1&&res2) Meldung(tr("Экспорт в IGES успешно!"));
    delete schreiber;
}

void Werkstuck::STEPExportieren()
{
    STEPControl_Writer *schreiber = new STEPControl_Writer();
    Interface_Static::SetCVal("write.step.schema","AP203");
    schreiber->Model(true);
    STEPControl_StepModelType mode = STEPControl_ManifoldSolidBrep;
    schreiber->Transfer(WS,mode);
    QString str = QFileDialog::getSaveFileName();
    if (str.isEmpty()) return;
    bool res1 = schreiber->Write(str.toStdString().c_str());
    if (res1) Meldung(tr("Экспорт в STEP успешно!"));
    delete schreiber;

}


void Werkstuck::Meldung(QString str)
{
    QMessageBox *meldung=new QMessageBox(QMessageBox::Information,tr("Сообщение"),str,
                                      QMessageBox::Ok);
    meldung->exec();
    delete meldung;
}

void Werkstuck::Flache1wahlen()
{
    F1 = VC1->DetectedShape();
    Handle(AIS_Shape) AF1=new AIS_Shape(F1);
    VC1->HilightWithColor(AF1,Quantity_NOC_GREEN);
}

void Werkstuck::Flache2wahlen()
{
    F2 = VC1->DetectedShape();
}

void Werkstuck::Abstandmessen()
{
    BRepExtrema_DistShapeShape *Abstandmesser = new BRepExtrema_DistShapeShape(F1,F2);
    if (Abstandmesser->IsDone()) Meldung(tr("Расстояние :")+QString::number(Abstandmesser->Value())+tr("мм"));
    delete Abstandmesser;
    Handle(AIS_Shape) AF1=new AIS_Shape(F1);
    VC1->HilightWithColor(AF1,Quantity_NOC_GRAY);
}
