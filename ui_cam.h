/********************************************************************************
** Form generated from reading UI file 'cam.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAM_H
#define UI_CAM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CAM
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CAM)
    {
        if (CAM->objectName().isEmpty())
            CAM->setObjectName(QString::fromUtf8("CAM"));
        CAM->resize(800, 600);
        centralwidget = new QWidget(CAM);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(0, 1, 161, 371));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Nimbus Mono L"));
        font.setPointSize(10);
        textEdit->setFont(font);
        CAM->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CAM);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        CAM->setMenuBar(menubar);
        statusbar = new QStatusBar(CAM);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CAM->setStatusBar(statusbar);

        retranslateUi(CAM);

        QMetaObject::connectSlotsByName(CAM);
    } // setupUi

    void retranslateUi(QMainWindow *CAM)
    {
        CAM->setWindowTitle(QApplication::translate("CAM", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CAM: public Ui_CAM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAM_H
