#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "room_simple.h"
#include "room_container.h"
#include "corridor_simple.h"
#include "corridor_random.h"
#include "room_builder.h"
#include <QDebug>
#include <QTime>

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
    qsrand(QTime::currentTime().msec());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generate()
{
    AbstractRoom* room = RoomBuilder::buildNewRoom(RoomBuilder::RANDOM_GALLERY);
    ContainerRoom* container = dynamic_cast<ContainerRoom *>(room);
    if (!container)
    {
        qDebug() << "ERROR: Something is wrong with casting a room";
    }
    scene->addItem(container);
    container->attach(QPointF(100,100), QPointF(100,101), NULL);
    for (QGraphicsItem *item: scene->items()) {
        AbstractRoom* room = dynamic_cast<AbstractRoom*>(item);
        if (room) {
            if (room->intersectsWithAnyInScene()) {
                room->setColor(Qt::red);
                ContainerRoom* containerRoom = dynamic_cast<ContainerRoom*>(room->parentItem());
                if (containerRoom) {
                    containerRoom->removeRoom(room->id());
                }
            }
        }
    }
}

void MainWindow::populateScene()
{
    scene = new QGraphicsScene;
    scene->setBackgroundBrush(Qt::gray);
    // Populate scene
    generate();
}


void MainWindow::on_btnGenerateRandom_clicked()
{
    if (!scene) {
        qDebug() << "ERROR: no scene";
        exit(-1);
    }
    scene->clear();
    scene->update();
    AbstractRoom::reInitIds();
    RoomBuilder::reInit();
    generate();
}
