#ifndef box_H
#define box_H


#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"





class cEventFilter: public QObject
{
    Q_OBJECT
public:
    cEventFilter();
    ~cEventFilter();

protected:
    bool eventFilter(QObject* object,QEvent* event);
};





class box:public QLabel
{
    Q_OBJECT

public:
    box(QWidget *parent = 0, QString PATH="", int id=0);
    ~box();
    QLabel *red,*green,*tick;
    QPixmap redPx,greenPx,tickPx;
    int state;
    void reset();

private:
    QString PATH;
    int id;
    void goYes();
    void goNo();


protected:
    void mousePressEvent( QMouseEvent* ev );

signals:
    void clicked(int id,int activestate);



};








#endif // SPLASH_H
