#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QObject>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QRegExp>
#include <QString>
#include <string>
#include <QMessageBox>

#include <memory>
#include "server.h"

const int FONTSIZE = 14;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLineEdit *txt;
    QLabel *pwd;
    QPushButton * buton;
    QSystemTrayIcon * tra;
    QMenu *tramenu;
    QAction * quit_action;
    void setlabelfont(int size);
    void butclicked();
    void showmenu();
    void createmenu();
    void traevent(QSystemTrayIcon::ActivationReason reson);

};

#endif // MAINWINDOW_H
