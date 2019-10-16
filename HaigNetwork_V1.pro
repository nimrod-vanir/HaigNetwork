#-------------------------------------------------
#
# Project created by QtCreator 2014-12-15T13:39:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HaigNetwork_V1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    admin_main.cpp \
    admin_createaclub.cpp \
    admin_listofclubs.cpp \
    admin_listofflaggedstudents.cpp \
    admin_removestudent.cpp \
    president_main.cpp \
    president_viewclubattendance.cpp \
    president_editclubattendance.cpp \
    president_addmember.cpp \
    president_removemembers.cpp \
    admin_editclubattendance.cpp \
    globals.cpp \
    admin_individualclubinformation.cpp \
    admin_adduser.cpp \
    addstudenttoclub.cpp \
    createnewstudent.cpp \
    president_addnewclubmeeting.cpp

HEADERS  += mainwindow.h \
    admin_main.h \
    admin_createaclub.h \
    admin_listofclubs.h \
    admin_listofflaggedstudents.h \
    admin_removestudent.h \
    president_main.h \
    president_viewclubmembers.h \
    president_main.h \
    president_viewclubattendance.h \
    president_editclubattendance.h \
    president_addmember.h \
    president_removemembers.h \
    admin_editclubattendance.h \
    globals.h \
    admin_individualclubinformation.h \
    admin_adduser.h \
    addstudenttoclub.h \
    createnewstudent.h \
    president_addnewclubmeeting.h

FORMS    += mainwindow.ui \
    admin_main.ui \
    admin_createaclub.ui \
    admin_listofclubs.ui \
    admin_listofflaggedstudents.ui \
    admin_removestudent.ui \
    president_main.ui \
    president_main.ui \
    president_viewclubattendance.ui \
    president_editclubattendance.ui \
    president_addmember.ui \
    president_removemembers.ui \
    admin_editclubattendance.ui \
    admin_individualclubinformation.ui \
    admin_adduser.ui \
    addstudenttoclub.ui \
    createnewstudent.ui \
    president_addnewclubmeeting.ui

RESOURCES += \
    iconpngs.qrc
