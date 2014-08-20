#ifndef QGRAPHICSVIEWCUSTOM_H
#define QGRAPHICSVIEWCUSTOM_H

#include <QGraphicsView>

class QGraphicsViewCustom : public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsViewCustom(QWidget *v = NULL) : QGraphicsView(v)
    {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    }

protected:
    void wheelEvent(QWheelEvent* event);


private:
};

#endif // QGRAPHICSVIEWCUSTOM_H
