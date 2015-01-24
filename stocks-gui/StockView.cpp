#include "StockView.h"
#include <QDebug>
#include <QJsonValue>

StockView::~StockView()
{

}

void StockView::wheelEvent(QWheelEvent* event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    // Don't call superclass handler here
    // as wheel is normally used for moving scrollbars
}

void StockView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF point = mapToScene(event->pos());

    QString s;
    s += "Date: " + (*a)[(int)point.x()].toArray()[0].toString();
    s += ", Close: " + (*a)[(int)point.x()].toArray()[4].toDouble() * 100;

    emit update_status(s);
}
