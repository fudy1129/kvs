#*****************************************************************************
#  $Id$
#*****************************************************************************

#=============================================================================
#  sources and headers
#=============================================================================
VIEWER_HEADERS += \
Viewer/GlobalBase.h \
Viewer/ScreenBase.h \
Viewer/QtScreenSupport.h \
Viewer/KVSKey.h \
Viewer/KVSMouseButton.h \


VIEWER_SOURCES += \
Viewer/ScreenBase.cpp \
Viewer/GlobalBase.cpp \


HEADERS += $$VIEWER_HEADERS
SOURCES += $$VIEWER_SOURCES


#=============================================================================
#  install
#=============================================================================
VIEWER_INSTALL_HEADERS.files = $$VIEWER_HEADERS
VIEWER_INSTALL_HEADERS.path  = $$KVS_DIR/include/SupportQt/Viewer

INSTALLS += VIEWER_INSTALL_HEADERS
