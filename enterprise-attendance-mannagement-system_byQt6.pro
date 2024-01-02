QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common_em.cpp \
    dep_admin.cpp \
    dep_change.cpp \
    dep_fenpei.cpp \
    department_set.cpp \
    depm.cpp \
    empl.cpp \
    employee_set.cpp \
    login.cpp \
    main.cpp \
    pss_change.cpp \
    publicdb.cpp \
    resi.cpp \
    resi_superadmin.cpp \
    superadmin.cpp

HEADERS += \
    common_em.h \
    dep_admin.h \
    dep_change.h \
    dep_fenpei.h \
    department_set.h \
    depm.h \
    empl.h \
    employee_set.h \
    login.h \
    pss_change.h \
    publicdb.h \
    resi.h \
    resi_superadmin.h \
    superadmin.h

FORMS += \
    common_em.ui \
    dep_admin.ui \
    dep_change.ui \
    dep_fenpei.ui \
    department_set.ui \
    depm.ui \
    empl.ui \
    employee_set.ui \
    login.ui \
    pss_change.ui \
    resi.ui \
    resi_superadmin.ui \
    superadmin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    logo.qrc
