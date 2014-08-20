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
    qreal width = 40;
    qreal height = 40;
    QColor color = QColor::fromRgb(0, 0, 0);
    QVector<Attachable*> objects;
    for (qreal i = 0; i < 200; i += 50)
    {
        objects.append(new SimpleRoom(color, width, height));
        objects.back()->attach(QPointF(i, i), QPointF(i + 10, i + 10));
        QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(objects.back());
        scene->addItem(item);
    }
}
