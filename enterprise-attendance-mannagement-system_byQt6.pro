QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dep_change.cpp \
    dep_fenpei.cpp \
    department_set.cpp \
    depm.cpp \
    empl.cpp \
    employee_set.cpp \
    login.cpp \
    main.cpp \
    publicdb.cpp \
    resi.cpp \
    resi_superadmin.cpp \
    superadmin.cpp

HEADERS += \
    dep_change.h \
    dep_fenpei.h \
    department_set.h \
    depm.h \
    empl.h \
    employee_set.h \
    login.h \
    publicdb.h \
    resi.h \
    resi_superadmin.h \
    superadmin.h

FORMS += \
    dep_change.ui \
    dep_fenpei.ui \
    department_set.ui \
    depm.ui \
    empl.ui \
    employee_set.ui \
    login.ui \
    resi.ui \
    resi_superadmin.ui \
    superadmin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
