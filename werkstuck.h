#ifndef WERKSTUCK_H
#define WERKSTUCK_H

#include <QtGui>
#include "qoccinternal.h"
#include "qoccviewercontext.h"

class Werkstuck : public QObject
{
    Q_OBJECT

private:

    Handle_AIS_InteractiveContext VC1;

    TopoDS_Shape WS;

    TopoDS_Shape WZweg;

    TopoDS_Shape F1, F2;
    TopoDS_Shape fBasis;


    bool Erstmal;
    bool Erst_weg;

    float Xf,Yf,Zf; // размеры заготовки в единицах
    float Xstart, Ystart, Zstart; // начало фрезерования в миллиметрах
    float Xwz,Ywz,Zwz; // текущее положение центра иструмента
    float WZR; // радиус инструмента то же что и Q108
    float H0; // координата поверхности заготовки
    float Rundtisch; // поворотный стол
    float Xfmin, Yfmin, Xfmax, Yfmax; // границы заготовки

    void AddVertex (double x, double y, double z, Handle_AIS_InteractiveContext theContext);
    void ShowOrigin ( Handle_AIS_InteractiveContext theContext );

    void Meldung(QString str);

public:
    explicit Werkstuck(Handle_AIS_InteractiveContext VC, QObject *parent = 0);

    void BulkForm(float Xmin, float Ymin, float Zmin, float Xmax, float Ymax, float Zmax);
    // заготовка Xmin и т.п - коорд.заготовки
    void BulkFormCylindrusZ(float Xc, float Yc, float Zc, float H, float R);
    //заготовка цилиндрическая по оси Z на повортном столе
    void BulkFormCylindrusX(float Xc, float Yc, float Zc, float H, float R);
    //заготовка цилиндрическая в делительной головке
    void LX(float endPunkt, float Rwz, float Lwz, float Rwz2=0);
    // фрезерование по прямой линии по оси Х
    void LY(float endPunkt, float Rwz, float Lwz, float Rwz2=0);
    // фрезерование по прямой линии по оси Y
    void LZ(float endPunkt, float Rwz, float Lwz, float Rwz2=0);
    // фрезерование по прямой линии по оси Z
    void LIX(float dX, float Rwz, float Lwz);
    // фрезерование в инкрементах по прямой линии по оси Х
    void LIY(float dY, float Rwz, float Lwz);
    // фрезерование в инкрементах по прямой линии по оси Y
    void LIZ(float dZ, float Rwz, float Lwz);
    // фрезерование в инкрементах по прямой линии по оси Z
    void LHX(float endPunkt, float Rwz, float Hwz);
    // фрезерование горизонтальное по прямой линии по оси Х
    void LHY(float endPunkt, float Rwz, float Hwz);
    // фрезерование горизонтальное по прямой линии по оси Y
    void LHZ(float endPunkt, float Rwz, float Hwz);
    // фрезерование горизонтальное по прямой линии по оси Z
    void LHIX(float dX, float Rwz, float Hwz);
    // фрезерование в инкрементах горизонтальное по прямой линии по оси Х
    void LHIY(float dY, float Rwz, float Hwz);
    // фрезерование в инкрементах горизонтальное по прямой линии по оси Y
    void LHIZ(float dZ, float Rwz, float Hwz);
    // фрезерование в инкрементах горизонтальное по прямой линии по оси Z
    void RundtischEin(float Ecke);
    // повернуть поворотный стол

signals:

public slots:
    void Einbau(void);
    void IGESExportieren(void);
    void STEPExportieren(void);
    void Flache1wahlen();
    void Flache2wahlen();
    void Abstandmessen();

};

#endif // WERKSTUCK_H
