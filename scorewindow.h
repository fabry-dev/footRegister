#ifndef scorewindow_H
#define scorewindow_H
#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"
#include <QtSql>
#include "qdatetime.h"
#include "QTime"
#include "qdebug.h"
#include "qfont.h"
#include "qfontdatabase.h"
#include <QtSql>
#include <QSqlQuery>




class scorewindow:public QLabel
{
    Q_OBJECT

public:
    scorewindow(QWidget *parent = 0,QString PATH="");
    ~scorewindow();
    void start();


private:
    QString PATH;
    QPixmap bgImg;
    QString bgNameA,bgNameE;

    void getTopPlayers();
    void initDb();
    void createTable();

    QFont font;
    QTimer *refreshTimer;

    bool arabic;

protected:
    void mousePressEvent( QMouseEvent* ev );

private slots:
    void drawScores();

};




#endif // scorewindow_H

