#include <QtGui>
#include "progRedakt.h"

// ----------------------------------------------------------------------
progRedakt::progRedakt(QWidget* pwgt/*=0*/) : QTextEdit(pwgt)
{
}

// ----------------------------------------------------------------------
void progRedakt::slotLoad()
{
    QString str = QFileDialog::getOpenFileName();
    if (str.isEmpty()) {
        return;
    }

    QFile file(str);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        setPlainText(stream.readAll());
        file.close();

        m_strFileName = str;
        emit changeWindowTitle(m_strFileName);
        emit Programmgeladen(m_strFileName+"wztab");
    }
}

// ----------------------------------------------------------------------
void progRedakt::slotSave()
{
    if (m_strFileName.isEmpty()) {
        slotSaveAs();
        return;
    }

    QFile file(m_strFileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << toPlainText();
        file.close();
        emit changeWindowTitle(m_strFileName);
        emit Programmgespeichert(m_strFileName+"wztab");
    }
}

// ----------------------------------------------------------------------
void progRedakt::slotSaveAs()
{
    QString str = QFileDialog::getSaveFileName(0, m_strFileName);
    if (!str.isEmpty()) {
        m_strFileName = str;
        slotSave();
        emit Programmgespeichert(m_strFileName+"wztab");
    }
}

QString progRedakt::Programmname()
{
    return m_strFileName;
}
