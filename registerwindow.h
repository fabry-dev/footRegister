#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H
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
#include "box.h"
#include "keyboard.h"

enum states { inputName,inputEmail,inputScores,submited };



class registerWindow:public QLabel
{
    Q_OBJECT

public:
    registerWindow(QWidget *parent = 0,QString PATH="");
    ~registerWindow();
    void start();


private:

    QString PATH;
    QPixmap registerAImg,registerEImg,bgImg2,boxImg,scoreAImg,scoreEImg;
    void insertPlayer(QString name, QString email, int score1, int score2, int score3);
    void getPlayers();
    void dropTable();
    void createTable();
    void getTopPlayers();
    void initDb();
    QLabel *nameLbl,*emailLbl,*scoreLbl,*score1Lbl,*score2Lbl,*score3Lbl,*showNameLbl;
    QString nameTxt,emailTxt;
    void updEmail();
    void updName();
    void updScore();
    QFont font;
    states gameState;
    void getCharacter(QString c);
    void gotoScoreSelection(void);
    std::vector<int>scoreStates;
    std::vector<box*>scoreBoxes;
    void goArabic();
    void goEnglish();
    bool arabic;
    keyboard *enKeys;
    keyboard *arKeys;
    void submit();
    void updShowName();
    int score1,score2,score3;

protected:
    void mousePressEvent( QMouseEvent* ev );

private slots:
    void getScoreUpdate(int id,int state);

};




#endif // REGISTERWINDOW_H

