#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), pwd(new QLabel(tr("请设定密码"))),
    txt(new QLineEdit()), buton(new QPushButton("确定")),
    tra(new QSystemTrayIcon())
{
    ui->setupUi(this);
    pwd->setGeometry(80,  3, 100, 60);
    setlabelfont(FONTSIZE);
    pwd->setParent(this);
    txt->setGeometry(180,20,150,30);
    txt->setPlaceholderText("请设定密码");
    txt->setEchoMode(QLineEdit::Password);
    txt->setParent(this);
    buton->setGeometry(140, 80, 100, 40);
    QObject::connect(buton,  &QPushButton::clicked, this, &MainWindow::butclicked);
    buton->setParent(this);
    this->setWindowTitle("shutdown");
    this->setFixedSize(400, 150);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setlabelfont(int size){
    QFont font;
    font.setPointSize(size);
    pwd->setFont(font);
}

void MainWindow::butclicked(){
    this->setHidden(true);
    tra->setIcon(QIcon(":/icon/1.png"));
    tra->setToolTip("shut down");
    tra->show();
    tra->showMessage("information", "shut down is running", QSystemTrayIcon::MessageIcon::Information);
    connect(tra, &QSystemTrayIcon::activated, this, &MainWindow::traevent);
}

void MainWindow::showmenu(){
    std::shared_ptr<QMenu> tramenu = std::make_shared<QMenu>(this);
    std::shared_ptr<QAction> quit_aciton = std::make_shared <QAction>(tramenu.get());
    quit_aciton->setText("退出");
    tramenu->addAction(quit_aciton.get());
    connect(quit_aciton.get(), &QAction::triggered, this, &QApplication::quit);
    tra->setContextMenu(tramenu.get());
    tramenu->show();
}

void MainWindow::traevent(QSystemTrayIcon::ActivationReason reson){
    switch (reson) {
    case  QSystemTrayIcon::Context:
        showmenu();
        break;
    default:
        break;
    }
}
