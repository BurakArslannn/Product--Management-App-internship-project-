#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QFile>
#include <QMessageBox>
#include "xlsxdocument.h"

using namespace QXlsx;

struct Main_Data{
    QString projectName;
    QString brand;
    QString model;
    QString serialNo;
    QString quantity;
    QString price;
    QString description;
    QString date;
};

struct Main_Data Data;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    initWindow();
    initTable();
    initData();
    //loadExcel();

    QPixmap pix("C:/Users/burak/Desktop/anayurt/anayurt/product.jpg");
    ui->label_pic->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::initWindow(){

}*/


void MainWindow::initWindow()
{
    // Set window properties and other initializations here
    this->setWindowTitle("Product Manager Application");
    // You can set other properties such as size, position, etc.
}

void MainWindow::initData(){
    Data.projectName = "-";
    Data.brand = "-";
    Data.model = "-";
    Data.serialNo = "-";
    Data.quantity = "-";
    Data.price = "-";
    Data.description = "-";
    Data.date = "01.01.2000";
}

void MainWindow::initTable(){
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Product Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Brand")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Model")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Serial Number")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Piece")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Price")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("Explanation")));
    model->setHorizontalHeaderItem(7, new QStandardItem(QString("Purchase Date")));
}
void MainWindow::on_projectName_editingFinished()
{
    Data.projectName = ui->projectName->text();
    qDebug()<<Data.projectName;
}


void MainWindow::on_brand_editingFinished()
{
    Data.brand = ui->brand->text();
    qDebug()<<Data.brand;
}


void MainWindow::on_model_editingFinished()
{
    Data.model = ui->model->text();
    qDebug()<<Data.model;
}


void MainWindow::on_serialNo_editingFinished()
{
    Data.serialNo = ui->serialNo->text();
    qDebug()<<Data.serialNo;
}


void MainWindow::on_quantity_editingFinished()
{
    Data.quantity = ui->quantity->text();
    qDebug()<<Data.quantity;
}


void MainWindow::on_price_editingFinished()
{
    Data.price = ui->price->text();
    qDebug()<<Data.price;
}


void MainWindow::on_dateEdit_userDateChanged(const QDate &date)
{
    Data.date = date.toString("dd-MM-yyyy");
    qDebug() << Data.date;
}


void MainWindow::on_description_textChanged()
{
    Data.description = ui->description->toPlainText();
    qDebug()<<Data.description;
}


void MainWindow::on_addButton_clicked()
{
    //saveCSVSubmit();
    saveExcelSubmit();
    //loadExcel(); bir daha burada çağırmaya gerek yok hata çıkarsa tekrar gözden geçirilir
    qDebug() <<"loadExcel'den çıkış";
    QMessageBox msg(this);
    msg.about(this,"Info", "You add a new item succesfully");

}


void MainWindow::saveCSVSubmit(){
    qDebug()<<"ADD";
    QString file_dir = "./" + Data.projectName + ".xlsx";
    QFile file(file_dir);
    if(file.open(QFile::WriteOnly)){
        QTextStream stream(&file);
        stream<<"İsim, "<<Data.projectName<<Qt::endl;
        file.close();
    }
}


void MainWindow::saveExcelSubmit(){

    loadExcel();

    QVector<QString> appendVector;
    //appendVector.push_back(QString::number(row_num));
    appendVector.push_back(Data.projectName);
    appendVector.push_back(Data.brand);
    appendVector.push_back(Data.model);
    appendVector.push_back(Data.serialNo);
    appendVector.push_back(Data.quantity);
    appendVector.push_back(Data.price);
    appendVector.push_back(Data.description);
    appendVector.push_back(Data.date);


    Document xlsx("Ürünler.xlsx");


    for(int i=0; i<COL_SIZE; i++){
        xlsx.write(currentRow+2, i+1, QVariant(appendVector[i]));
    }


xlsx.save();



currentRow+=1;
loadExcel();

}

char MainWindow::nth_letter(int n){
    if (n < 1) n = 1;
    if (n > 29) n = 2;

    return "ABÇDEFGĞHIİJKLMNOÖPRSŞTUÜVYZ"[n-1];
}


void MainWindow::on_pushButton_clicked()
{

    loadExcel();
    QMessageBox::about(this,"Info", "Click the Ok button to see all items in the list");

}


void MainWindow::loadExcel(){

    Data_Excel.clear();

    Document xlsxR("Ürünler.xlsx");

    int totalRow = START_ROW;

    if(xlsxR.load()){
        bool finish = false;
        while(!finish){
            for(int i = 0; i < COL_SIZE; i++){
                int col = i + 1;
                Cell* cell = xlsxR.cellAt(totalRow, col);


                if(cell != NULL){
                    QVariant var = cell->readValue();
                    qDebug()<<var;
                    Data_Excel.push_back(var.toString());
                }
                else if(col == 1){
                        finish = true;
                    }

            }
            totalRow++;
        }
    }

    totalRow -= 3;

    int controlSum = 0;

    model->setRowCount(totalRow);
    for(int row=0; row < totalRow; row++){//hata burada

        for(int col = 0; col < COL_SIZE ;col++){//3 kez okuyor sonra hata veriyor

            QModelIndex index = model->index(row,col,QModelIndex());

            model->setData(index,Data_Excel[col+controlSum]);
        }
        controlSum+=8;
    }

    ui->readProducts->setModel(model);

    currentRow = totalRow;

}

void MainWindow::deleteExpense(int rowToDelete)
{
    int rowCount = currentRow;

    // Check if the row number is valid
    if (rowToDelete >= 0 && rowToDelete < rowCount)
    {
        // Calculate the starting index of the row to be deleted in the vector
        int startIndex = (rowToDelete * COL_SIZE);

        // Remove the elements corresponding to the row to be deleted from the Data_Excel vector
        Data_Excel.erase(Data_Excel.begin() + startIndex, Data_Excel.begin() + startIndex + COL_SIZE);
        qDebug() << Data_Excel;

        // Decrement the currentRow value after deleting a row
        currentRow = rowCount - 1;

        // Save the updated data to the Excel file
        saveExcelToFile();

        // Reload the data in the table view
        loadExcel();
    }
    else
    {
        // If the input row number is invalid, show an error message or handle accordingly
        qDebug() << "Invalid row number to delete.";
    }

}
void MainWindow::saveExcelToFile()
{
    // Clear the entire Excel file by removing it first
    QFile::remove("Ürünler.xlsx");

    // Create a new Document object with the file name
    Document xlsx("Ürünler.xlsx");

    // Write the data from the Data_Excel vector to the Excel file
    int rowCount = Data_Excel.size() / COL_SIZE;
    int vectorIndex = 0;
    for (int row = START_ROW; row < rowCount + START_ROW; row++)
    {
        for (int col = 1; col <= COL_SIZE; col++)
        {
            if (vectorIndex < Data_Excel.size())
            {
                QString cellValue = Data_Excel[vectorIndex];
                xlsx.write(row, col, QVariant(cellValue));
                vectorIndex++;
            }
        }
    }

    // Save the changes to the Excel file
    xlsx.save();
}
void MainWindow::on_readProducts_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        int clickedRow = index.row();
        deleteExpense(clickedRow);// Convert to the Excel row index
        QMessageBox::about(this,"Info", "Product deleted.");
        // Call the deleteExpense() function to delete the selected row
    }

}
