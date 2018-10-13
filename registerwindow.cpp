#include "registerwindow.h"


#define nameX0 623
#define nameY0 376
#define nameX1 1293
#define nameY1 434

#define maxNameLength 40


#define emailX0 623
#define emailY0 507
#define emailX1 1293
#define emailY1 564
#define maxEmailLength 40

#define borderX 10

#define minNameSize 3
#define maxNameSize 20

#define maxEmailSize 20



#define scoreX0 1325
#define scoreY0 790
#define scoreX1 1400
#define scoreY1 850





#define scoreNbr 9

#define NOSCORE 0
#define WONSCORE 1
#define LOSTSCORE 2

#define BOX_X0 740
#define BOX_Y0 440

#define BOX_DELTAX 238
#define BOX_DELTAY 105

#define B_ENGLISH_X0 497
#define B_ENGLISH_Y0 948
#define B_ENGLISH_X1 636
#define B_ENGLISH_Y1 970

#define B_ARABIC_X0 1272
#define B_ARABIC_Y0 948
#define B_ARABIC_X1 1415
#define B_ARABIC_Y1 970




//english version

#define B_SUBMIT_X0e 1560
#define B_SUBMIT_Y0e 970
#define B_SUBMIT_X1e 1750
#define B_SUBMIT_Y1e 1030

#define scoreX0e 1350
#define scoreY0e 790
#define scoreX1e 1425
#define scoreY1e 850

#define score1X0e 1350
#define score1Y0e 430
#define score1X1e 1425
#define score1Y1e 490

#define score2X0e 1350
#define score2Y0e 535
#define score2X1e 1425
#define score2Y1e 595

#define score3X0e 1350
#define score3Y0e 640
#define score3X1e 1425
#define score3Y1e 700

#define showNameX0e 585
#define showNameY0e 790
#define showNameX1e 940
#define showNameY1e 850


//arabic version

#define B_SUBMIT_X0a 170
#define B_SUBMIT_Y0a 970
#define B_SUBMIT_X1a 360
#define B_SUBMIT_Y1a 1030

#define scoreX0a 525
#define scoreY0a 790
#define scoreX1a 600
#define scoreY1a 850

#define score1X0a 525
#define score1Y0a 430
#define score1X1a 600
#define score1Y1a 490

#define score2X0a 525
#define score2Y0a 535
#define score2X1a 600
#define score2Y1a 595

#define score3X0a 525
#define score3Y0a 640
#define score3X1a 600
#define score3Y1a 700

#define showNameX0a 585
#define showNameY0a 790
#define showNameX1a 1350
#define showNameY1a 850



registerWindow::registerWindow(QWidget *parent, QString PATH):QLabel(parent),PATH(PATH)
{


    boxImg.load(PATH+"check.png");

    enKeys = new keyboard(PATH+"keysE.cfg");
    arKeys = new keyboard(PATH+"keysA.cfg");

    scoreStates.resize(scoreNbr,NOSCORE);
    for(int i = 0;i<scoreNbr;i++)
    {
        int x,y;
        box *b = new box(this,PATH,i);
        y = BOX_Y0+(i/3)*BOX_DELTAY;
        x = BOX_X0+(i%3)*BOX_DELTAX ;
        b->move(x,y);
        b->hide();
        scoreBoxes.push_back(b);
        connect(b,SIGNAL(clicked(int,int)),this,SLOT(getScoreUpdate(int,int)));
    }


    registerAImg.load(PATH+"registerBGa.png");
    registerEImg.load(PATH+"registerBGe.png");
    scoreAImg.load(PATH+"scoreBGa.png");
    scoreEImg.load(PATH+"scoreBGe.png");

    bgImg2.load(PATH+"scoreBg.png");


    int id = QFontDatabase::addApplicationFont(PATH+"Dubai-Bold.ttf");
    font = QFont(QFontDatabase::applicationFontFamilies(id).at(0),50);



    emailLbl = new QLabel(this);
    emailLbl->resize(emailX1-emailX0,emailY1-emailY0);
    emailLbl->move(emailX0,emailY0);
    emailLbl->setAlignment(Qt::AlignCenter);
    emailLbl->setStyleSheet("QLabel { color : white; }");
    emailLbl->show();

    nameLbl = new QLabel(this);
    nameLbl->resize(nameX1-nameX0,nameY1-nameY0);
    nameLbl->move(nameX0,nameY0);
    nameLbl->setAlignment(Qt::AlignCenter);
    nameLbl->setStyleSheet("QLabel { color : white; }");
    nameLbl->show();

    scoreLbl = new QLabel(this);
    scoreLbl->resize(scoreX1e-scoreX0e,scoreY1e-scoreY0e);
    scoreLbl->move(scoreX0e,scoreY0e);
    scoreLbl->setAlignment(Qt::AlignCenter);
    scoreLbl->setStyleSheet("QLabel { color : white; }");
    scoreLbl->show();

    score1Lbl = new QLabel(this);
    score1Lbl->resize(score1X1e-score1X0e,score1Y1e-score1Y0e);
    score1Lbl->move(score1X0e,score1Y0e);
    score1Lbl->setAlignment(Qt::AlignCenter);
    score1Lbl->setStyleSheet("QLabel { color : white; }");
    score1Lbl->show();

    score2Lbl = new QLabel(this);
    score2Lbl->resize(score2X1e-score2X0e,score2Y1e-score2Y0e);
    score2Lbl->move(score2X0e,score2Y0e);
    score2Lbl->setAlignment(Qt::AlignCenter);
    score2Lbl->setStyleSheet("QLabel { color : white; }");
    score2Lbl->show();

    score3Lbl = new QLabel(this);
    score3Lbl->resize(score3X1e-score3X0e,score3Y1e-score3Y0e);
    score3Lbl->move(score3X0e,score3Y0e);
    score3Lbl->setAlignment(Qt::AlignCenter);
    score3Lbl->setStyleSheet("QLabel { color : white; }");
    score3Lbl->show();


    showNameLbl = new QLabel(this);
    showNameLbl->resize(showNameX1e-showNameX0e,showNameY1e-showNameY0e);
    showNameLbl->move(showNameX0e,showNameY0e);
    showNameLbl->setAlignment(Qt::AlignLeft);
    showNameLbl->setStyleSheet("QLabel { color : white; }");
    showNameLbl->show();

    initDb();
    // insertPlayer("bret","frederic.abry@gml.com",2,3,4);
    // getPlayers();

    arabic = true;

}


void registerWindow::start()
{
    if(arabic)
        goArabic();
    else
        goEnglish();


    showFullScreen();

    for(auto b:scoreBoxes)
        b->hide();

    gameState = inputName;
    emailTxt="";
    nameTxt="";
    updName();
    updEmail();



    emailLbl->show();
    nameLbl->show();
    showNameLbl->hide();
    score1Lbl->hide();
    score2Lbl->hide();
    score3Lbl->hide();
    scoreLbl->hide();

    //nameTxt = "غغغغغععع";
    //gotoScoreSelection();
    //   insertPlayer("Mireille","frederic.abry@gml.com",0,5,4);

}


void registerWindow::goArabic()
{


    emailTxt="";
    nameTxt="";
    updName();
    updEmail();
    arabic = true;
    setPixmap(registerAImg);
}


void registerWindow::goEnglish()
{

    emailTxt="";
    nameTxt="";
    updName();
    updEmail();
    arabic = false;
    setPixmap(registerEImg);
}





void registerWindow::getCharacter(QString c)
{
    QRegularExpression regExp("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");


    c.remove("\u202B");
    c.remove("\u202C");

    //qDebug()<<c;

    if(gameState == inputName)
    {
        if(c == "enter")
        {
            if(nameTxt.size()>minNameSize)
                gameState = inputEmail;

            return;
        }
        else if(c == "back")
        {
            if(nameTxt.size()>0)
            {
                nameTxt = nameTxt.remove(nameTxt.size()-1,1);
                updName();
            }
            return;
        }
        else if(c == "space")
        {
            if(nameTxt.size()<maxNameSize)
            {
                nameTxt.append(" ");
                updName();
            }
            return;
        }
        else
        {
            if(nameTxt.size()<maxNameSize)
            {
                nameTxt.append(c);
                updName();
            }
            return;
        }
    }
    else if(gameState == inputEmail)
    {
        if(c == "enter")
        {


            gotoScoreSelection();


            return;
        }
        else if(c == "back")
        {
            if(emailTxt.size()>0)
            {
                emailTxt = emailTxt.remove(emailTxt.size()-1,1);
                updEmail();
            }
            return;
        }
        else if(c == "space")
        {

            return;
        }
        else
        {

            emailTxt.append(c);
            updEmail();

            return;
        }
    }


}



void registerWindow::gotoScoreSelection()
{

    score1=score2=score3=0;
    gameState=inputScores;
    qDebug()<<"score selection";
    qDebug()<<"name: "<<nameTxt;
    qDebug()<<"email: "<<emailTxt;

    if(arabic)
    {
        setPixmap(scoreAImg);

        scoreLbl->setGeometry(scoreX0a,scoreY0a,scoreX1a-scoreX0a,scoreY1a-scoreY0a);
        score1Lbl->setGeometry(score1X0a,score1Y0a,score1X1a-score1X0a,score1Y1a-score1Y0a);
        score2Lbl->setGeometry(score2X0a,score2Y0a,score2X1a-score2X0a,score2Y1a-score2Y0a);
        score3Lbl->setGeometry(score3X0a,score3Y0a,score3X1a-score3X0a,score3Y1a-score3Y0a);


        showNameLbl->resize(showNameX1a-showNameX0a,showNameY1a-showNameY0a);
        showNameLbl->move(showNameX0a,showNameY0a);


    }
    else
    {
        setPixmap(scoreEImg);
        scoreLbl->setGeometry(scoreX0e,scoreY0e,scoreX1e-scoreX0e,scoreY1e-scoreY0e);
        score1Lbl->setGeometry(score1X0e,score1Y0e,score1X1e-score1X0e,score1Y1e-score1Y0e);
        score2Lbl->setGeometry(score2X0e,score2Y0e,score2X1e-score2X0e,score2Y1e-score2Y0e);
        score3Lbl->setGeometry(score3X0e,score3Y0e,score3X1e-score3X0e,score3Y1e-score3Y0e);

        showNameLbl->resize(showNameX1e-showNameX0e,showNameY1e-showNameY0e);
        showNameLbl->move(showNameX0e,showNameY0e);

    }


    emailLbl->hide();
    nameLbl->hide();
    showNameLbl->show();

    updShowName();

    for(auto b:scoreBoxes)
    {
        b->reset();
        b->show();
    }
    for(auto s:scoreStates)
        s=NOSCORE;

    scoreLbl->show();
    updScore();
}


void registerWindow::getScoreUpdate(int id, int state)
{
    scoreStates[id]=state;
    updScore();
}



QString convertToArabic(QString nb)
{

    return nb;


    QString enA = "0123456789";
    QString arA = "۰١۲۳۴۵۶۷۸۹";

    for(int j=0;j<nb.size();j++)
    {
        for (int i = 0;i<enA.size();i++)
        {
            if(nb[j]==enA[i])
            {
                nb[j]=arA[i];
                break;
            }
        }
    }

    return nb;

    QString buf = nb;

    for(int i =0;i<buf.size();i++)
    {
        buf[i]=nb[nb.size()-i-1];

    }

    return buf;
}


void registerWindow::updScore()
{

    score1=score2=score3 = 0;

    for(int i =0;i<scoreStates.size();i++)
    {
        if(i<=2)
            score1+=(scoreStates[i]==WONSCORE);
        else if(i<=5)
            score2+=(scoreStates[i]==WONSCORE)*3;
        else
            score3+=(scoreStates[i]==WONSCORE)*10;
    }
    QString scoreTxt = QString::number(score1+score2+score3);
    QString score1Txt = QString::number(score1);
    QString score2Txt = QString::number(score2);
    QString score3Txt = QString::number(score3);



    if(arabic)
    {
        scoreTxt=convertToArabic(scoreTxt);
        score1Txt=convertToArabic(score1Txt);
        score2Txt=convertToArabic(score2Txt);
        score3Txt=convertToArabic(score3Txt);


    }

    /*
    QFontMetrics metrics(font);
    QSize size = metrics.size(0, scoreTxt); //Get size of text
    float factorw = (scoreX1-scoreX0-2*borderX) / (float)size.width(); //Get the width factor
    float factorh = (scoreY1-scoreY0) / (float)size.height(); //Get the height factor
    float factor = qMin(factorw, factorh); //To fit contents in the screen select as factor
    //the minimum factor between width and height
    font.setPointSizeF(font.pointSizeF() * factor); //Set font size*/
    scoreLbl->setFont(font);
    score1Lbl->setFont(font);
    score2Lbl->setFont(font);
    score3Lbl->setFont(font);


    scoreLbl->setText(scoreTxt);
    score1Lbl->setText(score1Txt);
    score2Lbl->setText(score2Txt);
    score3Lbl->setText(score3Txt);


}


void registerWindow::submit()
{
    for(auto s: scoreStates)
    {
        if(s == NOSCORE)
            return;
    }

    gameState = submited;

    qDebug()<<"submit"<<nameTxt<<emailTxt;
    qDebug()<<score1<<score2<<score3;

    insertPlayer(nameTxt,emailTxt,score1,score2,score3);

    start();

}



void registerWindow::updEmail()
{
    QFontMetrics metrics(font);
    QSize size = metrics.size(0, emailTxt); //Get size of text
    float factorw = (emailX1-emailX0-2*borderX) / (float)size.width(); //Get the width factor
    float factorh = (emailY1-emailY0) / (float)size.height(); //Get the height factor
    float factor = qMin(factorw, factorh); //To fit contents in the screen select as factor
    //the minimum factor between width and height
    font.setPointSizeF(font.pointSizeF() * factor); //Set font size
    emailLbl->setFont(font);
    emailLbl->setText(emailTxt);
}

void registerWindow::updName()
{
    QFontMetrics metrics(font);
    QSize size = metrics.size(0, nameTxt); //Get size of text
    float factorw = (nameX1-nameX0-2*borderX) / (float)size.width(); //Get the width factor
    float factorh = (nameY1-nameY0) / (float)size.height(); //Get the height factor
    float factor = qMin(factorw, factorh); //To fit contents in the screen select as factor
    //the minimum factor between width and height
    font.setPointSizeF(font.pointSizeF() * factor); //Set font size
    nameLbl->setFont(font);
    nameLbl->setText(nameTxt);
}


void registerWindow::updShowName()
{
    QFontMetrics metrics(font);
    QSize size = metrics.size(0, nameTxt); //Get size of text
    float factorw = (showNameX1e-showNameX0e-2*borderX) / (float)size.width(); //Get the width factor
    float factorh = (showNameY1e-showNameY0e) / (float)size.height(); //Get the height factor
    float factor = qMin(factorw, factorh); //To fit contents in the screen select as factor
    //the minimum factor between width and height
    font.setPointSizeF(font.pointSizeF() * factor); //Set font size
    showNameLbl->setFont(font);
    showNameLbl->setText(nameTxt);
}



void registerWindow::initDb()
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

void registerWindow::insertPlayer(QString name, QString email,int score1,int score2,int score3)
{
    QDateTime timestamp = QDateTime::currentDateTime();

    QSqlQuery query;
    query.prepare("INSERT INTO players (name, email, score1, score2, score3, scoreTotal, date) VALUES (:name,:email,:score1,:score2,:score3,:scoreTotal,:datetime)");


    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":score1", score1);
    query.bindValue(":score2", score2);
    query.bindValue(":score3", score3);
    query.bindValue(":scoreTotal", score1+score2+score3);
    query.bindValue(":datetime", timestamp.toString("yyyy-MM-dd hh:mm:ss"));


    bool success = query.exec();
    if(!success)
    {
        qDebug() << query.lastError();
    }
}

void registerWindow::createTable()
{

    QSqlQuery query("CREATE TABLE players (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT, score1 INTEGER, score2 INTEGER, score3 INTEGER, scoreTotal INTEGER, date TIMESTAMP)");

    bool success = query.exec();

    if(!success)
    {
        qDebug() << query.lastError();
    }

}


void registerWindow::getPlayers()
{
    QSqlQuery query;
    query.prepare("SELECT id,name,email,score1,score2,score3,scoreTotal,date FROM players");
    query.exec();

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString email = query.value(2).toString();
        int score1 = query.value(3).toInt();
        int score2 = query.value(4).toInt();
        int score3 = query.value(5).toInt();
        int scoreTotal = query.value(6).toInt();
        QDateTime date = query.value(7).toDateTime();
        qDebug()<<id<<name<<email<<score1<<score2<<score3<<scoreTotal<<date;
    }
}


void registerWindow::getTopPlayers()
{
    QSqlQuery query;

    QDateTime timestamp = QDateTime::currentDateTime();
    QString date2 = timestamp.toString("yyyy-MM-dd hh:mm:ss");
    QString date1 = timestamp.toString("yyyy-MM-dd 00:00:00");



    qDebug()<<"top 10 players between: "<<date1<<"and"<<date2;

    //

    query.prepare("SELECT id,name,email,score1,score2,score3,scoreTotal,date FROM players WHERE date between :DATE1 and :DATE2 ORDER BY scoreTotal DESC LIMIT 10");
    query.bindValue(":DATE1", QVariant(date1));
    query.bindValue(":DATE2", QVariant(date2));
    query.exec();




    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString email = query.value(2).toString();
        int score1 = query.value(3).toInt();
        int score2 = query.value(4).toInt();
        int score3 = query.value(5).toInt();
        int scoreTotal = query.value(6).toInt();
        QDateTime date = (query.value(7).toDateTime());
        qDebug()<<id<<name<<email<<score1<<score2<<score3<<scoreTotal<<date.toString("yyyy-MM-dd hh:mm:ss");


    }
}


void registerWindow::dropTable()
{
    QSqlQuery query("DROP TABLE players");
    bool success = query.exec();
    if(!success)
    {
        qDebug() << query.lastError();
    }
}






registerWindow::~registerWindow()
{


}


void registerWindow::mousePressEvent( QMouseEvent* ev )
{
    QPoint pt = ev->pos();

    if((gameState == inputName)||(gameState == inputEmail))
        if((pt.x()>B_ARABIC_X0)&&(pt.y()>B_ARABIC_Y0)&&(pt.x()<B_ARABIC_X1)&&(pt.y()<B_ARABIC_Y1))
        {
            goArabic();
            return;
        }
        else if((pt.x()>B_ENGLISH_X0)&&(pt.y()>B_ENGLISH_Y0)&&(pt.x()<B_ENGLISH_X1)&&(pt.y()<B_ENGLISH_Y1))
        {
            goEnglish();
            return;
        }
        else
        {
            QString key;
            if(arabic)
                key = arKeys->getText(pt);
            else
                key = enKeys->getText(pt);

            if(key!="")
            {
                // qDebug()<<"input "<<key;

                getCharacter(key);
                return;
            }

        }

    else if(gameState==inputScores)
    {
        if((pt.x()>B_SUBMIT_X0e)&&(pt.y()>B_SUBMIT_Y0e)&&(pt.x()<B_SUBMIT_X1e)&&(pt.y()<B_SUBMIT_Y1e)&&(!arabic))
        {
            submit();
            return;
        }
        else if((pt.x()>B_SUBMIT_X0a)&&(pt.y()>B_SUBMIT_Y0a)&&(pt.x()<B_SUBMIT_X1a)&&(pt.y()<B_SUBMIT_Y1a)&&(arabic))
        {
            submit();
            return;
        }
    }

    qDebug()<<ev->pos();




}
