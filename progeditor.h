#ifndef PROG_EDIT_H
#define PROG_EDIT_H

#include <QTextEdit>

// ======================================================================
class progEditor: public QTextEdit {
Q_OBJECT
private:
    QString m_strFileName;

public:
    QString Programmname();
    progEditor(QWidget* pwgt = 0);

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
