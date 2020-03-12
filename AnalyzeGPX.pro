QT += quick xml

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Controller/controller.cpp \
        Licenses/licenses.cpp \
        Model/garmingpxfile.cpp \
        ModelView/garminlistmodel.cpp \
        ModelView/garmintreemodel.cpp \
        Model/garmintreenode.cpp \
        Utils/resoucehandling.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Licenses/01_License_BSD-4 License.txt \
    Licenses/03_License_lgpl-3.0.txt \
    qtquickcontrols2.conf
    README.md

INCLUDEPATH += $$PWD/Controller $$PWD/Model $$PWD/ModelView

HEADERS += \
    Controller/controller.h \
    Licenses/licenses.h \
    Model/garmingpxfile.h \
    ModelView/garminlistmodel.h \
    ModelView/garmintreemodel.h \
    Model/garmintreenode.h \
    Utils/resoucehandling.h


LICENSE_FILES.files = $$PWD/Licenses/01_License_BSD-4.txt \
                      $$PWD/Licenses/03_License_lgpl-3.0.txt
LICENSE_FILES.path = Contents/Resources

macx {
    ICON = Icons/AppIcon.icns
    QMAKE_BUNDLE_DATA += LICENSE_FILES
    # Needed to enfore light mode. Qt has still problems with dartk mode
    QMAKE_INFO_PLIST = Info.plist
}


