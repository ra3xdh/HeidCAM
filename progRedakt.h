#ifndef PROG_REDAKT_H
#define PROG_REDAKT_H

#include <QTextEdit>

// ======================================================================
class progRedakt: public QTextEdit {
Q_OBJECT
private:
    QString m_strFileName;

public:
    QString Programmname();
    progRedakt(QWidget* pwgt = 0);

signals:
    void changeWindowTitle(const QString&);
    void Programmgeladen(QString);
    void Programmgespeichert(QString);

public slots:
    void slotLoad  ();
    void slotSave  ();
    void slotSaveAs();
};
#endif
