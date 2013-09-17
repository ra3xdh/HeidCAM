#include "qoccapplication.h"
#include "cam.h"
#include <iostream>
#include <sstream>

int main(int argc, char** argv)
{
   QoccApplication app(argc, argv);

   CAM mainwindow1; // создаётся главное окно
   mainwindow1.resize(500, 500); // размеры главного окна
   mainwindow1.show();  // показать главное окно

    return app.exec();
}
