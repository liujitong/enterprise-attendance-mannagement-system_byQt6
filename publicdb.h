#ifndef PUBLICDB_H
#define PUBLICDB_H
#include "qsqlerror.h"
#include "qsqlrecord.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QApplication>
extern QSqlDatabase db;
class publicdb
{
public:
    publicdb();
};

#endif // PUBLICDB_H
