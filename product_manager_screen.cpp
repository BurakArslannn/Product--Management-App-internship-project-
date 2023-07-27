#include "product_manager_screen.h"
#include "ui_product_manager_screen.h"

Product_manager_screen::Product_manager_screen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Product_manager_screen)
{
    ui->setupUi(this);
}

Product_manager_screen::~Product_manager_screen()
{
    delete ui;
}
