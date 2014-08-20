#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simpleroom.h"
#include "container_room.h"
#include "simplecorridor.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    populateScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateScene()
{
    scene = new QGraphicsScene;
    // Populate scene
    ContainerRoom* container = new SimpleCorridor(400);
    container->addConnector("wl", 0.2);
    container->addConnector("wl", 0.7);
    container->addConnector("wb", 0);
    container->addConnector("wr", 0.5);

    ContainerRoom* container2 = new SimpleCorridor(600);
    container2->addConnector("wr", 0.2);
    container2->addConnector("wr", 0.5);
    container2->addConnector("wl", 0.5);
    container2->addConnector("wl", 0.7);
    QVector<AbstractRoom*> rooms2;
    for (int i = 0; i < container2->currentFreeConnectors(); ++i)
    {
        rooms2.append(new SimpleRoom);
    }
    QVector<AbstractRoom*> rooms;
    for (int i = 0; i < container->currentFreeConnectors() - 1 ; ++i)
    {
        rooms.append(new SimpleRoom);
    }
    rooms.append(container2);

    container->addRoomsToConnectors(rooms);
    container2->addRoomsToConnectors(rooms2);

    container->attach(QPointF(0,0), QPointF(1,1));

    container->registerToScene(scene);



//    QVector<Attachable*> objects;
//    for (qreal i = 0; i < 400; i += 100)
//    {
//        objects.append(new SimpleRoom());
//        objects.back()->attach(QPointF(i, i), QPointF(i + 10, i + 5));
//        QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(objects.back());
//        scene->addItem(item);
//    }
}

