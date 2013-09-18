#include <math.h>
#include "freser.h"
#include "operation.h"




Freser::Freser(const Handle_AIS_InteractiveContext& aContext,
               QWidget *parent,
               Qt::WindowFlags f) : QoccViewWidget(aContext, parent, f | Qt::MSWindowsOwnDC)
{

   //xRot=-60; yRot=0; zRot=-60; zTra=0; yTra=0; nSca=1;
   Horisontal = false;
   Erstenpunkt = true;

   werkstuck1= new Werkstuck(aContext, this); // создаём деталь

   WZTab = new Werkzeugtabelle("/home/vvk/.heidcam/wztabelleV",this);
   //WZTabH = new Werkzeugtabelle("/home/vvk/.heidcam/wztabelleH",this);
   WZTab->ToolDef(0,5,2,100,"WZ_FRAS10");
   WZTab->ToolDef(1,10,3,100,"WZ_FRAS10");
   WZTab->ToolCall(0);

   BF_typ = Freser::Rect;

   connect(this,SIGNAL(Loschen()),werkstuck1,SLOT(Einbau()));
}




void Freser::Fresen(int Kod, float X1, float Y1, float Z1, float X2, float Y2, float Z2, int I1)

{
    float Xc,Yc,Zc,R,H;

    switch (Kod) {
    case BULK_FORM1 : break;

    case BULK_FORM2 : switch (BF_typ) {
                         case Freser::Rect : werkstuck1->BulkForm(X1,Y1,Z1,X2,Y2,Z2); // заготовки
                         break;
                         case Freser::ZYL_X : Xc=X1;
                                              Yc=(Y1+Y2)/2;
                                              Zc=(Z1+Z2)/2;
                                              R=abs((Z2-Z1)/2);
                                              H=abs(X2-X1);
                                              werkstuck1->BulkFormCylindrusX(Xc,Yc,Zc,H,R);
                                              break;
                         case Freser::ZYL_Z : Xc=(X1+X2)/2;
                                              Yc=(Y1+Y2)/2;
                                              Zc=Z2;
                                              R=abs((Y2-Y1)/2);
                                              H=abs(Z2-Z1);
                                              werkstuck1->BulkFormCylindrusZ(Xc,Yc,Zc,H,R);
                                              break;
                         default : break;
                      }
                      break;
    case FRES_X     : if (Horisontal) werkstuck1->LHX(X1,WZTab->Rwz(),WZTab->Hwz());
                      else werkstuck1->LX(X1,WZTab->Rwz(),WZTab->Lwz()); // простые ходы
                      break;
    case FRES_Y     : if (Horisontal) werkstuck1->LHY(X1,WZTab->Rwz(),WZTab->Hwz());
                      else werkstuck1->LY(X1,WZTab->Rwz(),WZTab->Lwz());
                      break;
    case FRES_Z     : if (Horisontal) werkstuck1->LHZ(X1,WZTab->Rwz(),WZTab->Hwz());
                      else werkstuck1->LZ(X1,WZTab->Rwz(),WZTab->Lwz());
                      break;
    case FRES_IX    : if (Horisontal) werkstuck1->LHIX(X1,WZTab->Rwz(),WZTab->Hwz());
                      else werkstuck1->LIX(X1,WZTab->Rwz(),WZTab->Lwz());// инкременты
                      break;
    case FRES_IY    : if (Horisontal) werkstuck1->LHIY(X1,WZTab->Rwz(),WZTab->Hwz());
                      else werkstuck1->LIY(X1,WZTab->Rwz(),WZTab->Lwz()); // инкременты
                      break;
    case FRES_IZ    : if (Horisontal) werkstuck1->LHIZ(X1,WZTab->Rwz(),WZTab->Hwz());
                      else werkstuck1->LIZ(X1,WZTab->Rwz(),WZTab->Lwz());// инкременты
                      break;
    case TOOL_CALL  : WZTab->ToolCall(I1);
                      break;
    default : break;
    }

}

 void Freser::Abarbeiten(void)

 {
    emit Loschen();
 }

 void Freser::Einstwechsel(bool e)
 {
     Horisontal = e;
 }

 void Freser::WS_wechsel_ZylX()
 {
     BF_typ = Freser::ZYL_X;
 }

 void Freser::WS_wechsel_ZylZ()
 {
     BF_typ = Freser::ZYL_Z;
 }

 void Freser::WS_wechsel_Rect()
 {
     BF_typ = Freser::Rect;
 }

 bool Freser::istLangs()
 {
     return Horisontal;
 }


 void Freser::mouseDoubleClickEvent(QMouseEvent *)
 {
     if (Erstenpunkt) werkstuck1->Flache1wahlen();
     else { werkstuck1->Flache2wahlen();
            werkstuck1->Abstandmessen();
     }
     Erstenpunkt=!Erstenpunkt;
     //qDebug()<<Erstenpunkt;
 }
