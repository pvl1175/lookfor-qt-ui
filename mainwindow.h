#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void FillTree();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_testPshButton_clicked();

    void on_treeWidget_itemExpanded(QTreeWidgetItem *item);

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
