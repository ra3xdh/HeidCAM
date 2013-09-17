/****************************************************************************
**
** This file is part of the QtOpenCascade Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** Copyright (C) Peter Dolbey 2006-7. All rights reserved.
**
****************************************************************************/

#ifndef QOCCMAINWINDOW_H
#define QOCCMAINWINDOW_H

#include <QtGui/QMainWindow>
#include "qocc.h"

#include "ui/ui_qoccuimain.h"

#ifndef _V3d_Coordinate_HeaderFile
#include <V3d_Coordinate.hxx>
#endif

class Handle_AIS_InteractiveContext;
class QoccHandle;
class QoccViewerContext;
class QoccViewFrame;
class QoccViewWidget;
class QwwNavigationBar;
class QAction;
class QLabel;
class QMenu;
class QstdoutRedirector;

class QOCC_DECLSPEC QoccMainWindow : public QMainWindow, public Ui::QoccUIMain
{
    Q_OBJECT

public:

	QoccMainWindow();
	Handle_AIS_InteractiveContext& getContext();
	QoccHandle context();

private slots:
    void newFile();
    void open();
    void save();
    void print();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void about();
	void bottle();
    void aboutQt();
	void xyzPosition (V3d_Coordinate X,
					  V3d_Coordinate Y,
					  V3d_Coordinate Z);
	void addPoint (V3d_Coordinate X,
				   V3d_Coordinate Y,
				   V3d_Coordinate Z);
	void statusMessage (const QString aMessage);

private:
    void createActions();
    void createMenus();

    QTabBar *myTabBar;
    QTabWidget *myTabWidget;
    QWidget *myTab;

	QMenu *fileMenu;
    QMenu *editMenu;
	QMenu *viewMenu;
	QMenu *viewActionsMenu;
	QMenu *viewDisplayMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
	QMenu *gridMenu;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *printAction;
    QAction *exitAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *aboutAction;

	QAction *fitAction;
	QAction *fitAllAction;
	QAction *zoomAction;
	QAction *panAction;
	QAction *rotAction;

	QAction *gridXYAction;
	QAction *gridXZAction;
	QAction *gridYZAction;
	QAction *gridOnAction;
	QAction *gridOffAction;
	QAction *gridRectAction;
	QAction *gridCircAction;

	QAction *viewFrontAction;
	QAction *viewBackAction;
	QAction *viewTopAction;
	QAction *viewBottomAction;
	QAction *viewLeftAction;
	QAction *viewRightAction;
	QAction *viewAxoAction;
	QAction *viewResetAction;
	QAction *viewGridAction; /** Action for grid view */

	QAction *backgroundAction;

    QAction *aboutQtAction;

	//Sample Action
	QAction *bottleAction;

	// The OpenCASCADE Qt frame and context;
	QoccViewFrame*      myOCCFrame;
	QoccViewerContext*  myVC;

	QString				myLastFolder;
	QwwNavigationBar*	myNavigator;
	QstdoutRedirector*	myRedirector;

};

#endif //QOCCMAINWINDOW_H
