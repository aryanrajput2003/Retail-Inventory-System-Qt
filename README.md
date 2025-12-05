# 📦 Retail Inventory Management System (Qt C++)

![Qt](https://img.shields.io/badge/Qt-6.0+-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey?style=for-the-badge)

A robust, desktop-based CRUD application designed to streamline retail inventory operations. Built using **C++** and the **Qt 6 Framework**, featuring a persistent file-based storage system and a responsive graphical user interface.

---

## 📸 Screenshots

![App Screenshot]( <img width="994" height="754" alt="image" src="https://github.com/user-attachments/assets/12601e56-87f7-4127-9828-728930518e1b" />)


---

## 🚀 Key Features

* **🛒 Product Management (CRUD):** * **Add:** Validated entry for ID, Name, Quantity, and Price.
    * **Update:** Modify stock levels and pricing for existing IDs.
    * **Delete:** Remove obsolete products from the database.
    * **View:** Real-time table visualization using `QTableWidget`.
* **🔍 Smart Search:** * Instantly filter the database to find products by unique ID.
* **💾 Persistent Storage:** * Implements a custom **File I/O backend** using `std::fstream`.
    * Data is serialized to a local `store_data.txt` file, ensuring records are saved between sessions.
* **⚡ Data Integrity:** * Automatic string formatting (spaces converted to underscores).
    * Input validation using `QSpinBox` and `QDoubleSpinBox` to prevent invalid data types.

---

## 🛠️ Technical Implementation

This project demonstrates the integration of **Object-Oriented C++** with **Event-Driven UI Programming**.

### 1. The Tech Stack
* **Language:** C++ (Standard Template Library - STL)
* **Framework:** Qt 6 (Qt Widgets Module)
* **IDE:** Qt Creator (MinGW 64-bit Compiler)
* **Database:** Flat-file database (`.txt`)

### 2. Architecture
The application follows a modular structure separating the **UI Logic** from the **Data Logic**:

* **`mainwindow.h`**: Defines the `Product` struct and function prototypes.
* **`mainwindow.cpp`**: Handles business logic, file parsing, and Signal/Slot connections.
* **`mainwindow.ui`**: XML-based UI layout designed in Qt Designer.

### 3. Key Code Snippet (File Parsing)
*Demonstrates parsing raw text data into C++ objects:*
```cpp
void MainWindow::loadDataFromFile() {
    ui->tableInventory->setRowCount(0); // Clear UI
    std::ifstream file("store_data.txt");
    Product p;
    
    // Read formatted data stream
    while(file >> p.id >> p.name >> p.quantity >> p.price) {
        int row = ui->tableInventory->rowCount();
        ui->tableInventory->insertRow(row);
        // ... (Populate Table)
    }
    file.close();
}
```

### ⚙️ Installation & Build
To run this project on your machine:

#### Prerequisites: Install Qt Creator and Qt 6.

#### Clone the Repo:

Bash

git clone ([https://github.com/YOUR_USERNAME/InventoryManager.git](https://github.com/aryanrajput2003/Retail-Inventory-System-Qt))
#### Open Project:

Open Qt Creator.

Select File > Open File or Project.

Choose the InventoryManager.pro (or CMakeLists.txt) file.

### Build & Run:

Select your Kit (e.g., Desktop Qt 6.x MinGW).

Press Ctrl + R (Run).

#### 🔮 Future Improvements
Multi-threading: Move file I/O operations to a separate QThread to prevent UI freezing during large data writes.

#### Database Migration: Upgrade from .txt files to SQLite for better scalability.

#### Network Sync: Implement QNetworkAccessManager to sync inventory with a remote server.

### 👤 Author
Aryan Rajput
