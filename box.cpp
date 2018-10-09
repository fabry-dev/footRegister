#include "box.h"
#include "qdebug.h"
#include "qtimer.h"
#include "qrgb.h"


#define STATE_NONE 0
#define STATE_OK 1
#define STATE_NO 2


#define zoomWidth 800
#define zoomHeight 500

cEventFilter::cEventFilter():QObject()
{}

cEventFilter::~cEventFilter()
{}

bool cEventFilter::eventFilter(QObject* object, QEvent* event)
{



    return false;
}






box::box(QWidget *parent, QString PATH,int id):QLabel(parent),PATH(PATH),id(id)
{


    show();
    installEventFilter(new cEventFilter());
    resize(100,40);

    red=new QLabel(this);
    green=new QLabel(this);
    tick=new QLabel(this);

    red->resize(40,40);
    green->resize(40,40);
    red->move(50,0);
    green->move(0,0);



    redPx.load(PATH+"red.png");
    greenPx.load(PATH+"green.png");
    tickPx.load(PATH+"check.png");

    red->setPixmap(redPx);
    green->setPixmap(greenPx);
    tick->setPixmap(tickPx);

    red->show();
    green->show();
    tick->hide();

    show();


}


void box::reset()
{

state = STATE_NONE;
tick->hide();

}



void box::goNo()
{
    state=STATE_NO;
    tick->move(50,0);
    tick->show();
    emit clicked(id,state);
}


void box::goYes()
{
    state=STATE_OK;
    tick->move(0,0);
    tick->show();
    emit clicked(id,state);

}




void box::mousePressEvent( QMouseEvent* ev )
{
    QPoint pt = ev->pos();


    if(pt.x()<=40)
    {
        goYes();
    }
    else
    {
        goNo();
    }

}





box::~box()
{


}


