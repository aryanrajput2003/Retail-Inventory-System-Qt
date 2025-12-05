#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableInventory->setColumnCount(4);
    ui->tableInventory->setHorizontalHeaderLabels({"ID", "Name", "Qty", "Price"});

    loadDataFromFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAdd_clicked() {
    int id = ui->inputId->text().toInt();
    string name = ui->inputName->text().toStdString();
    int qty = ui->inputQty->value();
    double price = ui->inputPrice->value();

    if(name.empty() || id == 0) {
        QMessageBox::warning(this, "Error", "ID and Name cannot be empty!");
        return;
    }

    std::replace(name.begin(), name.end(), ' ', '_');

    Product p = {id, name, qty, price};
    saveToFile(p);

    loadDataFromFile();

    ui->inputId->clear();
    ui->inputName->clear();
    ui->inputQty->setValue(0);
    ui->inputPrice->setValue(0.0);
}

void MainWindow::on_btnUpdate_clicked() {
    int targetId = ui->inputId->text().toInt();
    if(targetId == 0) {
        QMessageBox::warning(this, "Error", "Enter an ID to Update.");
        return;
    }

    vector<Product> products;
    ifstream file("store_data.txt");
    Product p;
    bool found = false;

    while(file >> p.id >> p.name >> p.quantity >> p.price) {
        if(p.id == targetId) {
            found = true;
            p.name = ui->inputName->text().toStdString();
            std::replace(p.name.begin(), p.name.end(), ' ', '_'); // Apply underscore logic
            p.quantity = ui->inputQty->value();
            p.price = ui->inputPrice->value();
        }
        products.push_back(p);
    }
    file.close();

    if(found) {
        rewriteFile(products); 
        loadDataFromFile();  
        QMessageBox::information(this, "Success", "Product Updated!");
    } else {
        QMessageBox::warning(this, "Error", "ID not found. Cannot Update.");
    }
}

void MainWindow::on_btnSearch_clicked() {
    int searchId = ui->inputId->text().toInt();

    if(searchId == 0) {
        loadDataFromFile();
        return;
    }

    ui->tableInventory->setRowCount(0); 
    ifstream file("store_data.txt");
    Product p;
    bool found = false;

    while(file >> p.id >> p.name >> p.quantity >> p.price) {
        if(p.id == searchId) {
            int row = ui->tableInventory->rowCount();
            ui->tableInventory->insertRow(row);
            ui->tableInventory->setItem(row, 0, new QTableWidgetItem(QString::number(p.id)));
            ui->tableInventory->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.name)));
            ui->tableInventory->setItem(row, 2, new QTableWidgetItem(QString::number(p.quantity)));
            ui->tableInventory->setItem(row, 3, new QTableWidgetItem(QString::number(p.price)));
            found = true;
        }
    }
    file.close();

    if(!found) {
        QMessageBox::information(this, "Search", "Product Not Found.");
        loadDataFromFile(); 
    }
}

void MainWindow::on_btnDelete_clicked() {
    int targetId = ui->inputId->text().toInt();
    if(targetId == 0) return;

    vector<Product> products;
    ifstream file("store_data.txt");
    Product p;
    bool found = false;

    while(file >> p.id >> p.name >> p.quantity >> p.price) {
        if(p.id == targetId) found = true;
        else products.push_back(p);
    }
    file.close();

    if(found) {
        rewriteFile(products);
        loadDataFromFile();
        QMessageBox::information(this, "Success", "Product Deleted.");
    } else {
        QMessageBox::warning(this, "Error", "ID not found.");
    }
}

void MainWindow::saveToFile(const Product &p) {
    ofstream file("store_data.txt", ios::app);
    if(file.is_open()) {
        file << p.id << " " << p.name << " " << p.quantity << " " << p.price << endl;
        file.close();
    }
}

void MainWindow::rewriteFile(const vector<Product> &allProducts) {
    ofstream file("store_data.txt", ios::trunc);
    for(const auto &p : allProducts) {
        file << p.id << " " << p.name << " " << p.quantity << " " << p.price << endl;
    }
    file.close();
}

void MainWindow::loadDataFromFile() {
    ui->tableInventory->setRowCount(0);
    ifstream file("store_data.txt");
    if(!file.is_open()) return;

    Product p;
    while(file >> p.id >> p.name >> p.quantity >> p.price) {
        int row = ui->tableInventory->rowCount();
        ui->tableInventory->insertRow(row);
        ui->tableInventory->setItem(row, 0, new QTableWidgetItem(QString::number(p.id)));
        ui->tableInventory->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.name)));
        ui->tableInventory->setItem(row, 2, new QTableWidgetItem(QString::number(p.quantity)));
        ui->tableInventory->setItem(row, 3, new QTableWidgetItem(QString::number(p.price)));
    }
    file.close();
}
void MainWindow::on_btnExit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you want to close the application?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}


