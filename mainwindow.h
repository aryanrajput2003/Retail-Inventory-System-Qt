#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <fstream>
#include <vector>
#include <algorithm> // Needed for string replacement

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Product {
    int id;
    std::string name;
    int quantity;
    double price;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_btnSearch_clicked(); // NEW
    void on_btnUpdate_clicked(); // NEW

    void on_btnExit_clicked();

private:
    Ui::MainWindow *ui;

    // Helpers
    void loadDataFromFile();
    void saveToFile(const Product &p);
    void rewriteFile(const std::vector<Product> &allProducts);
};
#endif // MAINWINDOW_H
