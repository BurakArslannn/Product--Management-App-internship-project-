#include "loginscreen.h"
#include "ui_loginscreen.h"
LoginScreen::LoginScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::on_pushButton_clicked()
{
    LoginScreen = new loginScreen(this);
}

