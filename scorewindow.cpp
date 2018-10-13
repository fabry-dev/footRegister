#include "scorewindow.h"


#define nameX0 711
#define nameY0 360
#define nameX1 1198
#define nameY1 410

#define maxNameLength 40



#define borderX 10

#define REFRESHTIME 10


QString convertToArabic(QString nb);



scorewindow::scorewindow(QWidget *parent, QString PATH):QLabel(parent),PATH(PATH)
{
    hide();
    arabic = false;
    bgNameE = PATH+"scoreWallBGe.png";
    bgNameA = PATH+"scoreWallBGa.png";
    arabic = false;

    int id = QFontDatabase::addApplicationFont(PATH+"Dubai-Bold.ttf");
    font = QFont(QFontDatabase::applicationFontFamilies(id).at(0),23);

    initDb();

    refreshTimer = new QTimer(this);
    connect(refreshTimer,SIGNAL(timeout()),this,SLOT(drawScores()));

}


void scorewindow::start()
{
    refreshTimer->start(REFRESHTIME*1000);
    // insertPlayer("bret","frederic.abry@gml.com",2,3,4);
    // getPlayers();
    drawScores();
    showFullScreen();
}










#define zeroScorex 250
#define zeroScore1y 360
#define deltaScorey 48


void scorewindow::drawScores()
{
    QSqlQuery query;

    QDateTime timestamp = QDateTime::currentDateTime();
    QString date2 = timestamp.toString("yyyy-MM-dd hh:mm:ss");
    QString date1 = timestamp.toString("yyyy-MM-dd 00:00:00");

    qDebug()<<"top 10 players between: "<<date1<<"and"<<date2;

    query.prepare("SELECT id,name,email,score1,score2,score3,scoreTotal,date FROM players WHERE date between :DATE1 and :DATE2 ORDER BY scoreTotal DESC LIMIT 10");
    query.bindValue(":DATE1", QVariant(date1));
    query.bindValue(":DATE2", QVariant(date2));
    query.exec();

    QStringList names,scores,scores1,scores2,scores3;


    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        names.append(name);
        QString email = query.value(2).toString();
        int score1 = query.value(3).toInt();
        int score2 = query.value(4).toInt();
        int score3 = query.value(5).toInt();
        int scoreTotal = query.value(6).toInt();
        scores.append(QString::number(scoreTotal));
        scores1.append(QString::number(score1));
        scores2.append(QString::number(score2));
        scores3.append(QString::number(score3));
        QDateTime date = (query.value(7).toDateTime());
        //qDebug()<<id<<name<<email<<score1<<score2<<score3<<scoreTotal<<date.toString("yyyy-MM-dd hh:mm:ss");


    }



    if(arabic)
    {
        bgImg.load(bgNameA);
        QPainter p1(&bgImg);
        p1.setPen(QPen(Qt::white));
        p1.setFont(font);

        QString score,name;
        for (int i = 0;i<names.size();i++)
        {
            QString rank = QString("%1").arg(i+1, 2, 10, QChar('0'));
            p1.drawText(QRect(zeroScorex+1350,zeroScore1y+deltaScorey*i,100,100), Qt::AlignLeft, convertToArabic(rank));
            p1.drawText(QRect(zeroScorex+670,zeroScore1y+deltaScorey*i,560,100), Qt::AlignHCenter, names.at(i));
            p1.drawText(QRect(zeroScorex+485,zeroScore1y+deltaScorey*i,100,100), Qt::AlignHCenter,  convertToArabic(scores1.at(i)));
            p1.drawText(QRect(zeroScorex+485-160,zeroScore1y+deltaScorey*i,100,100), Qt::AlignHCenter,  convertToArabic(scores2.at(i)));
            p1.drawText(QRect(zeroScorex+485-160*2,zeroScore1y+deltaScorey*i,100,100), Qt::AlignHCenter, convertToArabic(scores3.at(i)));
            p1.drawText(QRect(zeroScorex-180,zeroScore1y+deltaScorey*i,200,100), Qt::AlignRight, convertToArabic(scores.at(i)));
        }




    }
    else
    {
        bgImg.load(bgNameE);
        QPainter p1(&bgImg);
        p1.setPen(QPen(Qt::white));
        p1.setFont(font);

        QString score,name;
        for (int i = 0;i<names.size();i++)
        {
            p1.drawText(QRect(zeroScorex,zeroScore1y+deltaScorey*i,1000,100), Qt::AlignLeft, QString("%1").arg(i+1, 2, 10, QChar('0')));
            p1.drawText(QRect(zeroScorex+197,zeroScore1y+deltaScorey*i,560,100), Qt::AlignHCenter, names.at(i));
            p1.drawText(QRect(zeroScorex+805,zeroScore1y+deltaScorey*i,100,100), Qt::AlignHCenter, scores1.at(i));
            p1.drawText(QRect(zeroScorex+965,zeroScore1y+deltaScorey*i,100,100), Qt::AlignHCenter, scores2.at(i));
            p1.drawText(QRect(zeroScorex+965+155,zeroScore1y+deltaScorey*i,100,100), Qt::AlignHCenter, scores3.at(i));
            p1.drawText(QRect(zeroScorex+1185,zeroScore1y+deltaScorey*i,200,100), Qt::AlignRight, scores.at(i));
        }
    }

    this->setPixmap(bgImg);

    arabic=!arabic;


}





void scorewindow::initDb()
{

    const QString DRIVER("QSQLITE");
    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setHostName("hostname");
    db.setDatabaseName(PATH+"footdb");
    db.setUserName("footuser");
    db.setPassword("footpassword");

    if(!db.open())
        qWarning() << "ERROR: " << db.lastError();

    qDebug()<<db.tables();

    //qDebug()<<db.record("players");
    //dropTable();
    //createTable();
    createTable();
}


void scorewindow::createTable()
{

    QSqlQuery query("CREATE TABLE players (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT, score1 INTEGER, score2 INTEGER, score3 INTEGER, scoreTotal INTEGER, date TIMESTAMP)");

    bool success = query.exec();

    if(!success)
    {
        qDebug() << query.lastError();
    }

}







void scorewindow::getTopPlayers()
{

}






scorewindow::~scorewindow()
{


}


void scorewindow::mousePressEvent( QMouseEvent* ev )
{
    QPoint pt = ev->pos();
    qDebug()<<ev->pos();

}
