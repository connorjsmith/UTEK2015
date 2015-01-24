#ifndef STOCKVIEW_H
#define STOCKVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QJsonArray>

class StockView : public QGraphicsView
{
public:
    StockView(QWidget *&parent) : QGraphicsView(parent) {}
    ~StockView();

    void set_a(QJsonArray *a) {this->a = a;}

signals:
    void update_status(QString s);

protected:
    //Take over the interaction
    virtual void wheelEvent(QWheelEvent* event);

    void mouseMoveEvent(QMouseEvent *event);

    QJsonArray *a;
};

#endif // STOCKVIEW_H
