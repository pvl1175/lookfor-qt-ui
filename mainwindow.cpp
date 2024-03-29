#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QHeaderView> 
#include <QDateTime>

#include <thrift/stdcxx.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "api/Api.h"
#include "client.h"

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace lookfor9::api;

QDebug operator<<(QDebug out, const std::string& str)
{
	out << QString::fromStdString(str);
	return out;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0, 0);
    ui->splitter->setStretchFactor(1, 1);

    ui->treeWidget->setHeaderLabel("Недв.");
	ui->treeWidget->setColumnCount(1);

    ui->tableWidget->insertRow(1);

    QHeaderView *verticalHeader = ui->tableWidget->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(18);

    ui->lineEditIp->setText("127.0.0.1");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FillTree()
{
    auto ip = ui->lineEditIp->text();

    if(ip.size() == 0)
        return;

    ui->treeWidget->clear();

    Client c{ip.toStdString()};
    std::vector<TreeInfo> ti_list;
    c.TreeChildren(ti_list, -1975);

    QList<QTreeWidgetItem*> items;
    std::for_each(ti_list.begin(), ti_list.end(), [&](auto ti)
    {
        QTreeWidgetItem* a = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString::fromStdString(ti.Name)));
        a->insertChild(0, new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString::fromStdString("..."))));
        a->setData(0, Qt::UserRole, QVariant(ti.Id));
        items.append(a);
    });

    ui->treeWidget->insertTopLevelItems(0, items);
}

void MainWindow::on_treeWidget_itemExpanded(QTreeWidgetItem *item)
{
    auto ip = ui->lineEditIp->text();

    if(ip.size() == 0)
        return;

    Client c{ip.toStdString()};
    std::vector<TreeInfo> ti_list;
    c.TreeChildren(ti_list, item->data(0, Qt::UserRole).toInt());

    if(ti_list.size() != 0)
        foreach(auto i, item->takeChildren()) delete i;

    QList<QTreeWidgetItem*> items;
    std::for_each(ti_list.begin(), ti_list.end(), [&](auto ti)
    {
        QTreeWidgetItem* a = new QTreeWidgetItem((QTreeWidget*)0,
                                                 QStringList(QString::fromStdString(ti.Name)));
        if(ti.HasChildren)
            a->insertChild(0, new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString::fromStdString("..."))));
        a->setData(0, Qt::UserRole, QVariant(ti.Id));
        items.append(a);
    });

    item->insertChildren(0, items);
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
}

void MainWindow::UpdateTable(const std::vector<Ad>& ad_list)
{
    ui->tableWidget->setSortingEnabled(false);
    ui->tableWidget->clearContents();

    ui->tableWidget->setRowCount(ad_list.size());

    for(size_t i = 0; i < ad_list.size(); i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(ad_list[i].Id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ad_list[i].Title)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(ad_list[i].Price)));

        auto dt = QDate::fromString(QString::fromStdString(ad_list[i].AvitoTime), "dd.MM.yyyy");
        auto c = new QTableWidgetItem();
        c->setData(Qt::DisplayRole, dt);
        ui->tableWidget->setItem(i, 3, c);

        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(ad_list[i].Address)));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(ad_list[i].OwnerName)));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::fromStdString(ad_list[i].OwnerPhone)));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString::fromStdString(ad_list[i].UserType)));
        ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QString::fromStdString(ad_list[i].PhoneInfo)));
        ui->tableWidget->setItem(i, 9, new QTableWidgetItem(QString::fromStdString(ad_list[i].Location)));
        ui->tableWidget->setItem(i, 10, new QTableWidgetItem(QString::fromStdString(ad_list[i].Lat)));
        ui->tableWidget->setItem(i, 11, new QTableWidgetItem(QString::fromStdString(ad_list[i].Lng)));
    }

    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->childCount() == 1)
        return;

    auto ip = ui->lineEditIp->text();

    if(ip.size() == 0)
        return;

    Client c{ip.toStdString()};

    std::vector<Ad> ad_list;
    c.AdsByTree(ad_list, item->data(0, Qt::UserRole).toInt(), -1);
    UpdateTable(ad_list);
}

void MainWindow::on_pushButton_clicked()
{
    auto query = ui->lineEdit->text();
    if(query.size() == 0)
        return;

    auto ip = ui->lineEditIp->text();

    if(ip.size() == 0)
        return;

    Client c{ip.toStdString()};

    std::vector<Ad> ad_list;
    c.AdsByQuery(ad_list, ui->lineEdit->text().toStdString(), -1);
    UpdateTable(ad_list);
}

void MainWindow::on_pushButtonConnect_clicked()
{
    FillTree();
}
