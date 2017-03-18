# Add files and directories to ship with the application
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

VERSION = 0.1.0
DEFINES += "APP_VERSION=\"\\\"$$VERSION\\\"\""

symbian {
    LIBS += -laknnotify \                           # Native messagebox
            -lhwrmvibraclient \                     # Vibra
            -lremconcoreapi -lremconinterfacebase \ # VolumeKeys

    ICON = Icon.svg

    TARGET.UID3 = 0xE1384038
    TARGET = NanoCounter

    vendorinfo = \
        "%{\"Vitalii Shunkov\"}" \
        ":\"Vitalii Shunkov\""

    my_deployment.pkg_prerules = vendorinfo
    DEPLOYMENT += my_deployment

    CONFIG(release, debug|release) {
        QMAKE_CXXFLAGS += -Os
    }
}

DEPLOYMENT.display_name = Nano Counter

# Smart Installer package's UID
# This UID is from the protected range 
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
#symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
# CONFIG += mobility
# MOBILITY +=

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/counter.cpp \
    src/settings.cpp \
    src/widgetsettings.cpp \
    src/xqvibra_p.cpp \
    src/xqvibra.cpp \
    src/backlightkeeper.cpp \
    src/volumekeys.cpp
HEADERS += \
    src/mainwindow.h \
    src/counter.h \
    src/settings.h \
    src/widgetsettings.h \
    src/xqvibra_p.h \
    src/xqvibra.h \
    src/backlightkeeper.h \
    src/volumekeys.h

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()
