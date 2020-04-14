#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plot.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Plot *a = new Plot(this);
    a->move(30,30);
}

MainWindow::~MainWindow()
{
    delete ui;
}
