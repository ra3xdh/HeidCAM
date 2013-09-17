#ifndef WERKZEUG_H
#define WERKZEUG_H

#include <QObject>

class Werkzeug : public QObject
{
    Q_OBJECT

private:

    float wzR, wzH, wzL, wzR2;
    QString wzName;

public:
    explicit Werkzeug(float R, float H, float L, QString Name, QObject *parent = 0);

    float Rwz();
    float Hwz();
    float Lwz();
    float Rwz2();

    QString WZNam();

signals:

public slots:

};

#endif // WERKZEUG_H
