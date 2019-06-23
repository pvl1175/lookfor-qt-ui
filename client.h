#ifndef CLIENT_H
#define CLIENT_H

#include <QDebug>
#include <QString>

#include <memory>

#include <thrift/stdcxx.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "api/Api.h"

class Client
{
private:
    std::shared_ptr<apache::thrift::transport::TSocket> socket;
    std::shared_ptr<apache::thrift::transport::TTransport> transport;
    std::shared_ptr<apache::thrift::protocol::TProtocol> protocol;
    std::shared_ptr<lookfor9::api::ApiClient> api;

    void Open();
    void Close();

public:
    Client(const std::string& address = "127.0.0.1", int port = 9090);
    ~Client();

    QString Hello();
    QString PhoneInfo(const QString& phone);
    void TreeChildren(std::vector<lookfor9::api::TreeInfo>& list, int index);
    void AdsByTree(std::vector<lookfor9::api::Ad>& list, int index, short rowsCount);
};

#endif // CLIENT_H
