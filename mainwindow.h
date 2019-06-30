#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <QTableWidgetItem>

#include "api/Api.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void FillTree();
    void UpdateTable(const std::vector<lookfor9::api::Ad>& ad_list);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_treeWidget_itemExpanded(QTreeWidgetItem *item);

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();

    void on_pushButtonConnect_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
