#ifndef SERVER_H
#define SERVER_H

#include <bits/stdc++.h>
#include <winsock2.h>
#include <stdio.h>
#include <QMainWindow>
#include <QMessageBox>
#include <QCoreApplication>
#include "md5.h"
using namespace std;

const int port = 5972;
const char * const  anser[2] = {"0", "1"};


class Mainwindow;
class Server{
private:
    SOCKET socket_listen;
    string pwd;
    int wsa_init();
    int  shutd(string pass);

public:
    explicit Server(string s);
    ~Server();
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    void listend(QMainWindow * w);

};

#endif // SERVER_H
