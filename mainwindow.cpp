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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateScene()
{
    scene = new QGraphicsScene;
    // Populate scene
    int width = 100;
    int height = 100;
    QColor color = QColor::fromRgb(0, 0, 0);
    Attachable *attachable = new SimpleRoom(color, width, height);
    attachable->attach(QPointF(60, 60), QPointF(50, 50));
    QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(attachable);
    QGraphicsItem *item2 = new SimpleRoom(color, width, height);
    item2->setPos(QPointF(0, 0));
    scene->addItem(item);
    scene->addItem(item2);
}
