QT       += core gui network charts sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11 qaxcontainer

DEFINES += ASIO_STANDALONE
DEFINES += CSV_IO_NO_THREAD

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH +=  $$PWD/include



LIBS        += -lws2_32

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
    advancesearch.cpp \
    advancesinglesearch.cpp \
    agreement/agreement.cpp \
    agreement/agreementanalusis.cpp \
    agreement/missionagreement.cpp \
    agreement/missionagreementanalusis.cpp \
    basebandmanage.cpp \
    basicform.cpp \
    basicinfo.cpp \
    basicinfoedit.cpp \
    battleform.cpp \
    battleformline.cpp \
    combolabel.cpp \
    config/configinfo.cpp \
    customtableform.cpp \
    customtableformline.cpp \
    customtablewidget.cpp \
    dataadvancesearch.cpp \
    datageshanmanage.cpp \
    datamanage.cpp \
    datasourcemanage.cpp \
    datastatistic.cpp \
    delaytest.cpp \
    directoryselect.cpp \
    downloadtest.cpp \
    entity/advance.cpp \
    entity/baseband.cpp \
    entity/childfile.cpp \
    entity/childfilewithparent.cpp \
    entity/dataadvance.cpp \
    entity/entityout/1.cpp \
    entity/entityout/logininfo.cpp \
    entity/entityout/planestream.cpp \
    entity/filelog.cpp \
    entity/geshan.cpp \
    entity/geshanadvance.cpp \
    entity/header.cpp \
    entity/mission.cpp \
    entity/missionbasicinfo.cpp \
    entity/missionmacroinfo.cpp \
    entity/processentity.cpp \
    entity/remotedata.cpp \
    entity/statistic.cpp \
    entity/user.cpp \
    filedata.cpp \
    filedownloadwidget.cpp \
    fileinfo.cpp \
    firstwindow.cpp \
    gemanage.cpp \
    geshanadvancesearch.cpp \
    healthdata.cpp \
    loginfo.cpp \
    main.cpp \
    mainwindow.cpp \
    missionallconfig.cpp \
    missionallconfigsingle.cpp \
    missionmanage.cpp \
    missionnewinsert.cpp \
    missionnewreview.cpp \
    missionsendwidget.cpp \
    missiontablewidget.cpp \
    mutifile.cpp \
    outtcpworker.cpp \
    progress.cpp \
    receievedata.cpp \
    remotedatasinglewidget.cpp \
    remotedatawidget.cpp \
    sendllfile/senddllfile.cpp \
    singlefilewidget.cpp \
    singleprogress.cpp \
    software_insert.cpp \
    station.cpp \
    stationmanage.cpp \
    stationselect.cpp \
    stationshow.cpp \
    stationshowmulty.cpp \
    usermanage.cpp \
    util/bytemethod.cpp \
    writefile/writefileworker.cpp \
    writefiledata.cpp \
    agreement/1.cpp \
    utils.cpp \
    configmodel.cpp \
    frameparserwithmodules.cpp



HEADERS += \
    advancesearch.h \
    advancesinglesearch.h \
    agreement/agreement.h \
    agreement/agreementanalusis.h \
    agreement/missionagreement.h \
    agreement/missionagreementanalusis.h \
    basebandmanage.h \
    basicform.h \
    basicinfo.h \
    basicinfoedit.h \
    battleform.h \
    battleformline.h \
    combolabel.h \
    config/configinfo.h \
    customtableform.h \
    customtableformline.h \
    customtablewidget.h \
    dataadvancesearch.h \
    datageshanmanage.h \
    datamanage.h \
    datasourcemanage.h \
    datastatistic.h \
    delaytest.h \
    directoryselect.h \
    downloadtest.h \
    entity/advance.h \
    entity/baseband.h \
    entity/childfile.h \
    entity/childfilewithparent.h \
    entity/dataadvance.h \
    entity/entityout/logininfo.h \
    entity/entityout/planestream.h \
    entity/filelog.h \
    entity/geshan.h \
    entity/geshanadvance.h \
    entity/header.h \
    entity/mission.h \
    entity/missionbasicinfo.h \
    entity/missionmacroinfo.h \
    entity/processentity.h \
    entity/remotedata.h \
    entity/statistic.h \
    entity/user.h \
    filedata.h \
    filedownloadwidget.h \
    fileinfo.h \
    firstwindow.h \
    gemanage.h \
    geshanadvancesearch.h \
    healthdata.h \
    interfaces.h \
    loginfo.h \
    mainwindow.h \
    missionallconfig.h \
    missionallconfigsingle.h \
    missionmanage.h \
    missionnewinsert.h \
    missionnewreview.h \
    missionsendwidget.h \
    missiontablewidget.h \
    module_interface.h \
    mutifile.h \
    outtcpworker.h \
    progress.h \
    receievedata.h \
    remotedatasinglewidget.h \
    remotedatawidget.h \
    sendllfile/senddllfile.h \
    singlefilewidget.h \
    singleprogress.h \
    software_insert.h \
    station.h \
    stationmanage.h \
    stationselect.h \
    stationshow.h \
    stationshowmulty.h \
    usermanage.h \
    util/bytemethod.h \
    writefile/writefileworker.h \
    writefiledata.h \
    agreement/1.h \
    util/1.h \
    writefile/1.h \
    frameparser_interface.h \
    module_interface.h \
    utils.h \
    cirqueue.h \
    configmodel.h \
    frameparserwithmodules.h \
    interfaces.h

include(ui/ui.pri)
include(network/network.pri)

FORMS += \
    advancesearch.ui \
    advancesinglesearch.ui \
    basebandmanage.ui \
    basicform.ui \
    basicinfoedit.ui \
    battleform.ui \
    combolabel.ui \
    customtableform.ui \
    customtablewidget.ui \
    dataadvancesearch.ui \
    datageshanmanage.ui \
    datamanage.ui \
    datasourcemanage.ui \
    datastatistic.ui \
    directoryselect.ui \
    filedata.ui \
    filedownloadwidget.ui \
    firstwindow.ui \
    gemanage.ui \
    geshanadvancesearch.ui \
    loginfo.ui \
    mainwindow.ui \
    missionallconfig.ui \
    missionallconfigsingle.ui \
    missionmanage.ui \
    missionnewinsert.ui \
    missionnewreview.ui \
    missionsendwidget.ui \
    missiontablewidget.ui \
    progress.ui \
    remotedatasinglewidget.ui \
    remotedatawidget.ui \
    singlefilewidget.ui \
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
    image/abort.png \
    image/add.png \
    image/begin.png \
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
    image/wifi.png \ \
    network/network.pri \
    ui/ui.pri
