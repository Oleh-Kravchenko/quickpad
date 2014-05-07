#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ActionNew_triggered()
{
    ;
}

void MainWindow::on_ActionOpen_triggered()
{
    ;
}

void MainWindow::on_ActionAbout_triggered()
{
    QMessageBox msgBox(this);

    msgBox.windowTitle() = "QuickPad";
    msgBox.setText("(c) "__DATE__ " QuickPad <oleg@kaa.org.ua>");
    msgBox.exec();
}
