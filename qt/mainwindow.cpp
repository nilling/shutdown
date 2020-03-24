#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), pwd(new QLabel(tr("请设定密码"))),
    txt(new QLineEdit()), buton(new QPushButton("确定")),
    tra(new QSystemTrayIcon()),tramenu(new QMenu()),
    quit_action(new QAction())
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
    createmenu();
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
    QString pasd = txt->text();
    if (pasd  == ""){
        QMessageBox::information(this, "提示", "密码不能为空", QMessageBox::Yes, QMessageBox::Yes);
    }else{
        QRegExp rx("^[a-zA-Z0-9_]*$");
        if (!rx.indexIn(pasd)){
            this->setHidden(true);
            tra->setIcon(QIcon(":/icon/1.png"));
            tra->setToolTip("shut down");
            tra->show();
            tra->showMessage("information", "shut down is running", QSystemTrayIcon::MessageIcon::Information);
            connect(tra, &QSystemTrayIcon::activated, this, &MainWindow::traevent);
            Server s(std::move(pasd.toStdString()));
            s.listend(nullptr);
        }else{
            QMessageBox::information(this, "提示", "密码只能包含数字、字母和下划线", QMessageBox::Yes, QMessageBox::Yes);
        }
    }
}

void MainWindow::createmenu(){
    quit_action->setParent(tramenu);
    quit_action->setText("退出");
    tramenu->addAction(quit_action);
    connect(quit_action, &QAction::triggered, this, &QApplication::quit);
    tra->setContextMenu(tramenu);
}

void MainWindow::showmenu(){
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
