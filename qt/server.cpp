#include "server.h"



Server::Server(string s): pwd(move(s)){
}

Server::~Server(){
    closesocket(socket_listen);
    WSACleanup();
}

int Server::wsa_init(){
    WORD sockversion = MAKEWORD(2,2);
    WSADATA wsadata;
    if (WSAStartup(sockversion, &wsadata) != 0){
        return 1;
    }
    return 0;
}

void Server::listend(QMainWindow* w){
    if (wsa_init() != 0){
        QMessageBox::information(w, "错误", "socket初始化失败",  QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    socket_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_listen == INVALID_SOCKET){
        QMessageBox::information(w, "错误", "socket初始化失败",  QMessageBox::Yes, QMessageBox::Yes);
        return ;
    }

    sockaddr_in  sin;
    memset(&sin, 0, sizeof(sockaddr));
    sin.sin_family = AF_INET;
    sin.sin_port = port;
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    if(bind(socket_listen, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR){
        QMessageBox::information(w, "错误", "socket bind失败",  QMessageBox::Yes, QMessageBox::Yes);
        return ;
    }

    if(listen(socket_listen, 5) == SOCKET_ERROR){
        QMessageBox::information(w, "错误", "socket listen失败",  QMessageBox::Yes, QMessageBox::Yes);
        return ;
    }

    SOCKET sclient;
    sockaddr_in sclientaddr;
    int lenaddr = sizeof(sclientaddr);
    char recvdata[255];
    string data;
    while(true){
        sclient = accept(socket_listen, (SOCKADDR*)&sclientaddr, &lenaddr);
        if(sclient == INVALID_SOCKET){
            //QMessageBox::information(w, "错误", "socket accept失败",  QMessageBox::Yes, QMessageBox::Yes);
            continue;
        }

        int ret = recv(sclient, recvdata, 255, 0);
        while (ret > 0){
            data += string(recvdata, recvdata+ret);
            memset(recvdata, 0, sizeof(recvdata));
            ret = recv(sclient, recvdata, 255, 0);
        }
        int res = shutd(data);
        if(res == 0){
            send(sclient, anser[0], sizeof(anser[0]), 0);
            closesocket(sclient);
            break;
        }else{
            send(sclient, anser[1], sizeof(anser[1]), 0);
        }
        data.clear();
        memset(recvdata, 0, sizeof(recvdata));
    }
}
\
int Server::shutd(string pass){
   string md5str = std::move(Md5().Encode(pwd));
   if  (md5str == pass){
        system("shutdown -s -t 60");
        return 0;
   }
   return 1;
}
