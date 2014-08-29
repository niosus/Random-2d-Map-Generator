#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "room_simple.h"
#include "room_container.h"
#include "corridor_simple.h"
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
    ContainerRoom* container = new SimpleCorridor(400, 400);
    scene->addItem(container);
    ContainerRoom* container2 = new SimpleCorridor(400);
    container2->addRoom(AbstractRoom::WALL_LEFT, 0.2, new SimpleRoom);
    container->attach(QPointF(2,2), QPointF(1,1), NULL);
    container->addRoom(AbstractRoom::WALL_LEFT, 0.2, container2);

//    container->addConnector("wl", 0.2);
//    container->addConnector("wl", 0.7);
//    container->addConnector("wb", 0);
//    container->addConnector("wr", 0.5);

//    ContainerRoom* container2 = new SimpleCorridor(900);
//    container2->addConnector("wr", 0.2);
//    container2->addConnector("wr", 0.3);
//    container2->addConnector("wr", 0.5);
//    container2->addConnector("wl", 0.5);

//    ContainerRoom* container3 = new SimpleCorridor(400);
//    container3->addConnector("wr", 0.1);
//    QVector<AbstractRoom*> rooms3;
//    rooms3.append(new SimpleCorridor(900));

//    QVector<AbstractRoom*> rooms2;
//    for (int i = 0; i < container2->currentFreeConnectors() - 1; ++i)
//    {
//        rooms2.append(new SimpleRoom);
//    }
//    QVector<AbstractRoom*> rooms;
//    for (int i = 0; i < container->currentFreeConnectors() - 1; ++i)
//    {
//        rooms.append(new SimpleRoom);
//    }
//    rooms.append(container2);
//    rooms2.append(container3);

//    container->addRoomsToConnectors(rooms);
//    container2->addRoomsToConnectors(rooms2);
//    container3->addRoomsToConnectors(rooms3);
}

