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

   connect(this,SIGNAL(Loschen()),werkstuck1,SLOT(Einbau()));
}




void Freser::Fresen(int Kod, float X1, float Y1, float Z1, float X2, float Y2, float Z2, int I1)

{
    switch (Kod) {
    case BULK_FORM1 : break;
    case BULK_FORM2 : werkstuck1->BulkForm(X1,Y1,Z1,X2,Y2,Z2); // заготовки
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
