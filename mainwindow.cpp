#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), pwd(new QLabel(tr("请设定密码"))),
    txt(new QLineEdit())
{
    ui->setupUi(this);
    pwd->setGeometry(100,  0, 100, 60);
    pwd->setParent(this);
    txt->setGeometry(180,20,150,30);
    txt->setPlaceholderText("请设定密码");
    txt->setEchoMode(QLineEdit::Password);
    txt->setParent(this);
    this->setWindowTitle("shutdown");
    this->setFixedSize(400, 150);
}

MainWindow::~MainWindow()
{
    delete ui;
}
