#ifndef VIEW_MAZE_H_
#define VIEW_MAZE_H_

#include <QGraphicsView>

class ViewMaze : public QGraphicsView
{
    Q_OBJECT
public:
    ViewMaze(QWidget *v = NULL) : QGraphicsView(v)
    {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    }

protected:
    void wheelEvent(QWheelEvent* event);


private:
};

#endif // VIEW_MAZE_H_
