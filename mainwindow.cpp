#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simpleroom.h"
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
    Attachable *attachable = new SimpleRoom();
    attachable->attach(QPointF(60, 60), QPointF(50, 50));
    QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(attachable);
    QGraphicsItem *item2 = new SimpleRoom();
    item2->setPos(QPointF(0, 0));
    scene->addItem(item);
    scene->addItem(item2);
}

