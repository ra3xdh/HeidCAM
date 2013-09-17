######################################################################
# Automatically generated by qmake (2.01a) ?? ???? 24 18:30:45 2012
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += . $(CASROOT)/inc /opt/OpenCASCADE/inc

DEFINES += _OCC64

# Input
HEADERS += cam.h \
           einstellungendialog.h \
           freser.h \
           heidhighlighter.h \
           operation.h \
           programmanalisator.h \
           progRedakt.h \
           qocc.h \
           qoccapplication.h \
           qoccinputoutput.h \
           qoccinternal.h \
           qoccviewercontext.h \
           qoccviewwidget.h \
           werkstuck.h \
           werkzeug.h \
           werkzeugtabelle.h \
           wztabdlg.h
SOURCES += cam.cpp \
           einstellungendialog.cpp \
           freser.cpp \
           heidhighlighter.cpp \
           main.cpp \
           programmanalisator.cpp \
           progRedakt.cpp \
           qoccapplication.cpp \
           qoccinputoutput.cpp \
           qoccinternal.h.cpp \
           qoccviewercontext.cpp \
           qoccviewwidget.cpp \
           werkstuck.cpp \
           werkzeug.cpp \
           werkzeugtabelle.cpp \
           wztabdlg.cpp

        LIBS += -L$(CASROOT)/Linux/lib \
                -lFWOSPlugin \
                -lPTKernel \
                -lTKAdvTools \
                -lTKBin \
                -lTKBinL \
                -lTKBinXCAF \
                -lTKBO \
                -lTKBool \
                -lTKBRep \
                -lTKCAF \
                -lTKCDF \
                -lTKernel \
                -lTKFeat \
                -lTKFillet \
                -lTKG2d \
                -lTKG3d \
                -lTKGeomAlgo \
                -lTKGeomBase \
                -lTKHLR \
                -lTKIGES \
                -lTKLCAF \
                -lTKMath \
                -lTKMesh \
                -lTKMeshVS \
                -lTKOffset \
                -lTKOpenGl \
                -lTKPCAF \
                -lTKPLCAF \
                -lTKPrim \
                -lTKPShape \
                -lTKService \
                -lTKShapeSchema \
                -lTKShHealing \
                -lTKStdLSchema \
                -lTKStdSchema \
                -lTKSTEP \
                -lTKSTEP209 \
                -lTKSTEPAttr \
                -lTKSTEPBase \
                -lTKSTL \
                -lTKTopAlgo \
                -lTKV2d \
                -lTKV3d \
                -lTKVRML \
                -lTKXCAFSchema \
                -lTKXDEIGES \
                -lTKXDESTEP \
                -lTKXml \
                -lTKXmlL \
                -lTKXmlXCAF \
                -lTKXSBase \
                -lGL \


unix:!symbian:!maemo5:isEmpty(MEEGO_VERSION_MAJOR) {
    target.path = /opt/HeidCAM-II/bin
    INSTALLS += target
}
