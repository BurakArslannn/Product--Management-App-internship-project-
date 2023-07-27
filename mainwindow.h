#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSystemTrayIcon;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_projectName_editingFinished();

    void on_brand_editingFinished();

    void on_model_editingFinished();

    void on_serialNo_editingFinished();

    void on_quantity_editingFinished();

    void on_price_editingFinished();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_description_textChanged();

    void on_addButton_clicked();

    void on_pushButton_clicked();

    void on_readProducts_doubleClicked(const QModelIndex &index);


private:

    Ui::MainWindow *ui;

    const static int COL_SIZE = 8;
    const static int START_ROW = 2;
    QVector<QString> appendVector;
    QVector<QString> Data_Excel;
    int row_num = 0;
    int currentRow;

    QStandardItemModel *model = new QStandardItemModel(row_num, COL_SIZE, this);

    void initWindow();
    void initTable();
    void initData();
    void loadExcel();
    void saveCSVSubmit();
    void saveExcelSubmit();
    void deleteExpense(int index);
    void saveExcelToFile();
    char nth_letter(int n);
};
#endif // MAINWINDOW_H
