QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Sparkle

VERSION = 1.0.0
QMAKE_TARGET_DESCRIPTION = Sparkle
win32:RC_ICONS += icons/sparkle.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    analyticswidget.cpp \
    charts/customchart.cpp \
    charts/customchartview.cpp \
    charts/linechart.cpp \
    charts/piechart.cpp \
    editablelabel.cpp \
    editabletextblock.cpp \
    english/Dialogs/changewordpaircategoriesdialog.cpp \
    english/Dialogs/createwordpairdialog.cpp \
    english/Dialogs/updatecategorylistdialog.cpp \
    english/ListComponents/wordpairwidget.cpp \
    english/ListComponents/wordpairwidgetitem.cpp \
    english/Utility/categorycolorselector.cpp \
    english/Widgets/dictionarywidget.cpp \
    english/Widgets/englishanalyticswidget.cpp \
    english/Widgets/timedtestwidget.cpp \
    english/englishwidget.cpp \
    english/wordpair.cpp \
    listwidget.cpp \
    listwidgetitem.cpp \
    main.cpp \
    mainwindow.cpp \
    notes/Dialogs/changenotecategoriesdialog.cpp \
    notes/Dialogs/createnotedialog.cpp \
    notes/ListComponents/notewidget.cpp \
    notes/ListComponents/notewidgetitem.cpp \
    notes/Utility/notecategoryselector.cpp \
    notes/Widgets/noteslistwidget.cpp \
    notes/note.cpp \
    notes/noteswidget.cpp \
    popupcontroller.cpp \
    popupwidget.cpp \
    qhotkey/qhotkey.cpp \
    qhotkey/qhotkey_win.cpp \
    remindercontroller.cpp \
    spendings/Dialogs/createproductdialog.cpp \
    spendings/ListComponents/productwidget.cpp \
    spendings/ListComponents/productwidgetitem.cpp \
    spendings/Utility/productcategoryselector.cpp \
    spendings/Widgets/productlistwidget.cpp \
    spendings/Widgets/spendingsanalyticswidget.cpp \
    spendings/product.cpp \
    spendings/spendingswidget.cpp \
    tasktracker/Dialogs/choosedatetimedialog.cpp \
    tasktracker/Dialogs/chooseperiodicitydialog.cpp \
    tasktracker/Dialogs/createtaskdialog.cpp \
    tasktracker/ListComponents/subtaskwidget.cpp \
    tasktracker/ListComponents/taskwidget.cpp \
    tasktracker/ListComponents/taskwidgetitem.cpp \
    tasktracker/Utility/timercontroller.cpp \
    tasktracker/Utility/timespan.cpp \
    tasktracker/Widgets/tasklistwidget.cpp \
    tasktracker/task.cpp \
    tasktracker/tasktrackerwidget.cpp

HEADERS += \
    analyticswidget.h \
    charts/customchart.h \
    charts/customchartview.h \
    charts/linechart.h \
    charts/piechart.h \
    editablelabel.h \
    editabletextblock.h \
    english/Dialogs/changewordpaircategoriesdialog.h \
    english/Dialogs/createwordpairdialog.h \
    english/Dialogs/updatecategorylistdialog.h \
    english/ListComponents/wordpairwidget.h \
    english/ListComponents/wordpairwidgetitem.h \
    english/Utility/categorycolorselector.h \
    english/Widgets/dictionarywidget.h \
    english/Widgets/englishanalyticswidget.h \
    english/Widgets/timedtestwidget.h \
    english/englishwidget.h \
    english/wordpair.h \
    listwidget.h \
    listwidgetitem.h \
    mainwindow.h \
    notes/Dialogs/changenotecategoriesdialog.h \
    notes/Dialogs/createnotedialog.h \
    notes/ListComponents/notewidget.h \
    notes/ListComponents/notewidgetitem.h \
    notes/Utility/notecategoryselector.h \
    notes/Widgets/noteslistwidget.h \
    notes/note.h \
    notes/noteswidget.h \
    popupcontroller.h \
    popupwidget.h \
    qhotkey/qhotkey.h \
    qhotkey/qhotkey_p.h \
    remindercontroller.h \
    spendings/Dialogs/createproductdialog.h \
    spendings/ListComponents/productwidget.h \
    spendings/ListComponents/productwidgetitem.h \
    spendings/Utility/productcategoryselector.h \
    spendings/Widgets/productlistwidget.h \
    spendings/Widgets/spendingsanalyticswidget.h \
    spendings/product.h \
    spendings/spendingswidget.h \
    tasktracker/Dialogs/choosedatetimedialog.h \
    tasktracker/Dialogs/chooseperiodicitydialog.h \
    tasktracker/Dialogs/createtaskdialog.h \
    tasktracker/ListComponents/subtaskwidget.h \
    tasktracker/ListComponents/taskwidget.h \
    tasktracker/ListComponents/taskwidgetitem.h \
    tasktracker/Utility/timercontroller.h \
    tasktracker/Utility/timespan.h \
    tasktracker/Widgets/tasklistwidget.h \
    tasktracker/task.h \
    tasktracker/tasktrackerwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
