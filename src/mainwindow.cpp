#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/tmp/work/Memo.sqlite3");
    db.open();

    QSqlQuery query(db);
    query.exec("create table Memo(id INTEGER PRIMARY KEY AUTOINCREMENT, Memo text, Created text)");

    query.prepare("insert into Memo (Memo, Created) values (?, ?)");
    QString text = "someText";
    query.bindValue(0, text);
    QDateTime dt = QDateTime::currentDateTime();
    query.bindValue(1, dt.toString("yyyy-MM-dd HH:mm:ss.zzz"));
    query.exec();

    query.exec("select * from Memo WHERE Memo = '"+text+"'");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString memo = query.value(1).toString();
        qDebug() << QString("id(%1),memo(%2)").arg(id).arg(memo);
    }

    db.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
