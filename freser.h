#ifndef FRESER_H
#define FRESER_H

#include "qoccviewwidget.h"
#include <QtGui>
#include "werkstuck.h"
#include "werkzeugtabelle.h"

class Freser : public QoccViewWidget
{
    Q_OBJECT

   protected:
      void mouseDoubleClickEvent(QMouseEvent *);



   public:

      enum WS_Typ {ZYL_X, ZYL_Z, Rect};

      Werkstuck* werkstuck1;
      Werkzeugtabelle* WZTab;
      //Werkzeugtabelle* WZTabH;

      Freser(const Handle_AIS_InteractiveContext& aContext,
             QWidget *parent,
             Qt::WindowFlags f);

      bool istLangs();

public slots:
   void Fresen(int Kod, float X1, float Y1, float Z1, float X2, float Y2, float Z2, int I1);
   void Abarbeiten(void);
   void Einstwechsel(bool e);
   void WS_wechsel_ZylX();
   void WS_wechsel_ZylZ();
   void WS_wechsel_Rect();

signals:
      void Loschen();

private:

   bool Horisontal;
   bool Erstenpunkt;

   WS_Typ BF_typ;

};
#endif
