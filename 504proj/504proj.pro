QT       += core gui network charts sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11 qaxcontainer resources_big

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    advance.cpp \
    advancedsinglesearch.cpp \
    advancesearch.cpp \
    agreement/agreement.cpp \
    agreement/agreementanalysis.cpp \
    baseband.cpp \
    basicform.cpp \
    basicinfo.cpp \
    basicinfoedit.cpp \
    battleform.cpp \
    battleformline.cpp \
    childfile.cpp \
    combolabel.cpp \
    config/configinfo.cpp \
    customtableform.cpp \
    customtableformline.cpp \
    customtablewidget.cpp \
    dataadvance.cpp \
    datageshanmanage.cpp \
    datamanage.cpp \
    delaytest.cpp \
    directoryselect.cpp \
    downloadtest.cpp \
    filedownloadrquest.cpp \
    fileinfo.cpp \
    filelog.cpp \
    firstwindow.cpp \
    gemanage.cpp \
    geshan.cpp \
    geshanadvance.cpp \
    healthdata.cpp \
    loginfo.cpp \
    main.cpp \
    mainwindow.cpp \
    mission.cpp \
    missionbasicinfo.cpp \
    missionmacroinfo.cpp \
    missionmanage.cpp \
    missionnewinsert.cpp \
    missionnewreview.cpp \
    missionsendwidget.cpp \
    missiontablewidget.cpp \
    mutifile.cpp \
    processentity.cpp \
    progress.cpp \
    receievedata.cpp \
    remotedata.cpp \
    secondentity.cpp \
    sendfile/sendfile.cpp \
    config/1.cpp \
    singleprogress.cpp \
    station.cpp \
    stationmanage.cpp \
    stationselect.cpp \
    stationshow.cpp \
    stationshowmulty.cpp \
    user.cpp \
    usermanage.cpp \
    util.cpp \
    util/bytemethod.cpp \
    writefiledata.cpp \
    agreement/1.cpp \

HEADERS += \
    advance.h \
    advancedsinglesearch.h \
    advancesearch.h \
    agreement/agreement.h \
    agreement/agreementanalysis.h \
    baseband.h \
    basicform.h \
    basicinfo.h \
    basicinfoedit.h \
    battleform.h \
    battleformline.h \
    childfile.h \
    combolabel.h \
    config/configinfo.h \
    customtableform.h \
    customtableformline.h \
    customtablewidget.h \
    dataadvance.h \
    datageshanmanage.h \
    datamanage.h \
    delaytest.h \
    directoryselect.h \
    downloadtest.h \
    filedownloadrquest.h \
    fileinfo.h \
    filelog.h \
    firstwindow.h \
    gemanage.h \
    geshan.h \
    geshanadvance.h \
    head.h \
    healthdata.h \
    loginfo.h \
    mainwindow.h \
    mission.h \
    missionbasicinfo.h \
    missionmacroinfo.h \
    missionmanage.h \
    missionnewinsert.h \
    missionnewreview.h \
    missionsendwidget.h \
    missiontablewidget.h \
    mutifile.h \
    processentity.h \
    progress.h \
    receievedata.h \
    remotedata.h \
    secondentity.h \
    sendfile/sendfile.h \
    singleprogress.h \
    station.h \
    stationmanage.h \
    stationselect.h \
    stationshow.h \
    stationshowmulty.h \
    ui_missioninsert.h \
    ui_stationinsert.h \
    user.h \
    usermanage.h \
    util.h \
    util/bytemethod.h \
    writefiledata.h \
    agreement/1.h \

FORMS += \
    advancedsinglesearch.ui \
    advancesearch.ui \
    basicform.ui \
    basicinfoedit.ui \
    battleform.ui \
    combolabel.ui \
    customtableform.ui \
    customtablewidget.ui \
    datageshanmanage.ui \
    datamanage.ui \
    directoryselect.ui \
    firstwindow.ui \
    gemanage.ui \
    loginfo.ui \
    mainwindow.ui \
    missionmanage.ui \
    missionnewinsert.ui \
    missionnewreview.ui \
    missionsendwidget.ui \
    missiontablewidget.ui \
    progress.ui \
    singleprogress.ui \
    stationmanage.ui \
    stationselect.ui \
    stationshow.ui \
    stationshowmulty.ui \
    usermanage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res.qrc

DISTFILES += \
    image/FFFFFFFF.jpg \
    image/add.png \
    image/bk.jpeg \
    image/blue.jpg \
    image/blue2.jpg \
    image/delete.png \
    image/frame2.jpg \
    image/frame3.png \
    image/greenlight.png \
    image/kuang.jpg \
    image/kuang2.png \
    image/kuangnew.png \
    image/main.jpg \
    image/search.png \
    image/widgetbackground.jpg \
    image/wifi.jpeg \
    image/wifi.png \
