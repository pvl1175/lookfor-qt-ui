#include "client.h"

using namespace lookfor9::api;

Client::Client(const std::string& address, int port)
{
    socket = std::shared_ptr<apache::thrift::transport::TSocket>(new apache::thrift::transport::TSocket(address, port));
    transport = std::shared_ptr<apache::thrift::transport::TTransport>(new apache::thrift::transport::TBufferedTransport(socket));
    protocol = std::shared_ptr<apache::thrift::protocol::TProtocol>(new apache::thrift::protocol::TBinaryProtocol(transport));
    api = std::shared_ptr<ApiClient>(new ApiClient(protocol));

    Open();
}

Client::~Client()
{
    Close();
}

void Client::Open()
{
    try
    {
        transport->open();
        qDebug() << "Transport opened";
    }
    catch (...)
    {
        qDebug() << "thrift error: failed connect to node";
    }
}

void Client::Close()
{
    try
    {
        transport->close();
        qDebug() << "Transport closed";
    }
    catch (...)
    {
        qDebug() << "thrift error: failed disconnect from node";
    }
}

QString Client::Hello()
{
    try
    {
        std::string h{};
        api->Hello(h);
        return QString::fromStdString(h);
    }
    catch (...)
    {
        qDebug() << "thrift error: failed to call Hello";
    }
}

QString Client::PhoneInfo(const QString& phone)
{
    try
    {
        std::string ph_info{};
        api->PhoneInfo(ph_info, phone.toStdString());
        return QString::fromStdString(ph_info);
    }
    catch (...)
    {
        qDebug() << "thrift error: failed to call PhoneInfo";
    }
}

void Client::TreeChildren(std::vector<lookfor9::api::TreeInfo>& list, int index)
{
    try
    {
        api->TreeChildren(list, index);
    }
    catch (...)
    {
        qDebug() << "thrift error: failed to call TreeChildren";
    }
}

void Client::AdsByTree(std::vector<lookfor9::api::Ad> &list, int index, short rowsCount)
{
    try
    {
        api->AdsByTree(list, index, rowsCount);
    }
    catch (...)
    {
        qDebug() << "thrift error: failed to call AdsByTree";
    }
}


