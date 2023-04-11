#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "operations.h"
#include <QMessageBox>
#define ERROR "12345e-99"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_0, &QPushButton::clicked, this, &MainWindow::btn_click_num);
    connect(ui->btn_1, &QPushButton::clicked, this, &MainWindow::btn_click_num);
    connect(ui->btn_2, &QPushButton::clicked, this, &MainWindow::btn_click_num);
    connect(ui->btn_3, &QPushButton::clicked, this, &MainWindow::btn_click_num);
    connect(ui->btn_4, &QPushButton::clicked, this, &MainWindow::btn_click_num);
    connect(ui->btn_5, &QPushButton::clicked, this, &MainWindow::btn_click_num);
    connect(ui->btn_6, &QPushButton::clicked, this, &MainWindow::btn_click_num);
    connect(ui->btn_7, &QPushButton::clicked, this, &MainWindow::btn_click_num);
    connect(ui->btn_8, &QPushButton::clicked, this, &MainWindow::btn_click_num);
    connect(ui->btn_9, &QPushButton::clicked, this, &MainWindow::btn_click_num);

    connect(ui->btn_add, &QPushButton::clicked,this, &MainWindow::btn_click_operat);
    connect(ui->btn_sub, &QPushButton::clicked,this, &MainWindow::btn_click_operat);
    connect(ui->btn_mul, &QPushButton::clicked,this, &MainWindow::btn_click_operat);
    connect(ui->btn_div, &QPushButton::clicked,this, &MainWindow::btn_click_operat);

    connect(ui->btn_sqrt, &QPushButton::clicked,this, &MainWindow::btn_click_exponent);
    connect(ui->btn_square,&QPushButton::clicked,this,&MainWindow::btn_click_exponent);
    connect(ui->btn_sin, &QPushButton::clicked,this, &MainWindow::btn_click_trig);
    connect(ui->btn_cos, &QPushButton::clicked,this, &MainWindow::btn_click_trig);
    connect(ui->btn_tg, &QPushButton::clicked,this, &MainWindow::btn_click_trig);
    connect(ui->btn_ctg,&QPushButton::clicked,this, &MainWindow::btn_click_trig);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enable_num_button(bool b){
    ui->btn_0->setEnabled(b);
    ui->btn_1->setEnabled(b);
    ui->btn_2->setEnabled(b);
    ui->btn_3->setEnabled(b);
    ui->btn_4->setEnabled(b);
    ui->btn_5->setEnabled(b);
    ui->btn_6->setEnabled(b);
    ui->btn_7->setEnabled(b);
    ui->btn_8->setEnabled(b);
    ui->btn_9->setEnabled(b);
}

void MainWindow::btn_click_num()
{
    ui->btn_del->setEnabled(true);
    if (!ui->lbl_num->text().contains("."))
        ui->btn_dot->setEnabled(true);
    QPushButton *btn = (QPushButton* )sender();
    if (ui->lbl_num->text().size() > 18){
        QMessageBox::warning(this, "Error", "Вы ввели слишком большое число");
    } else{
        if (ui->lbl_num->text() == "0"){
            ui->lbl_num->setText(btn->text());
        } else if (ui->lbl_num->text() == "-0"){
            ui->lbl_num->setText("-" + btn->text());
        } else if (ui->lbl_num->text() == "0."){
            ui->lbl_num->setText( "0." + btn->text());
            ui->btn_dot->setEnabled(false);
        } else
            ui->lbl_num->setText(ui->lbl_num->text() + btn->text());

        if (ui->lbl_num->text() != "0" || ui->lbl_num->text() != "-0" || ui->lbl_num->text() != "0."){
            ui->btn_add->setEnabled(true);
            ui->btn_sub->setEnabled(true);
            ui->btn_mul->setEnabled(true);
            ui->btn_div->setEnabled(true);

        }
    }
}

void MainWindow::btn_click_operat()
{
    QPushButton *btn = (QPushButton *)sender();
    n1 = ui->lbl_num->text();
    operat = btn->text();
    ui->lbl_num->setText("0");
    enable_num_button(true);
    ui->btn_res->setEnabled(true);

}

void MainWindow::btn_click_trig(){
    QString result = "0";
    QString num = ui->lbl_num->text();
    QPushButton *btn = (QPushButton *)sender();
    QString function = btn->text();
    result = get_result(function, num, "0");

    if (result == ERROR || result == "inf" || result == "-inf")
        QMessageBox::warning(this, "Error", "Значение не определено");
    else
        ui->lbl_num->setText(result);
}

void MainWindow::on_btn_del_clicked()
{
    QString str = ui->lbl_num->text();
    str.chop(1);

    if (str.isEmpty())
        str = "0";
    if (!str.contains("."))
        ui->btn_dot->setEnabled(true);
    ui->lbl_num->setText(str);
}


void MainWindow::on_btn_c_clicked()
{
    enable_num_button(true);
    n1 = "0";
    operat = "";

    ui->lbl_num->setText("0");
}


void MainWindow::on_btn_res_clicked()
{
    ui->btn_res->setEnabled(false);
    QString result = "0";
    QString num2 = ui->lbl_num->text();

    result = get_result(operat, n1, num2);
    if (result == ERROR){
        QMessageBox::warning(this, "ERROR", "На ноль делить нельзя!");
    }else
        ui->lbl_num->setText(result);

   n1 = "0";
   operat = "";

   if(result.contains("."))
       ui->btn_dot->setEnabled(false);

   if (result.contains("e") || result == "inf" || result == "-inf"){
       ui->btn_del->setEnabled(false);
       enable_num_button(false);
   }
}

void MainWindow::on_btn_help_clicked()
{
    QMessageBox::information(this, "Helper", "Уважаемый пользователь, здесь приведены основные правила использования калькулятора: \n"
                                             "1) Нельзя делить на ноль \n"
                                             "2) Нельзя вводить числа длинной больше 18 \n"
                                             "3) Кнопка +/- изменяет знак числа на противоположный \n");
}


void MainWindow::on_btn_opp_clicked()
{
    QString str = ui->lbl_num->text();
    if (str.contains("-")){
        str.replace("-", "");
        ui->lbl_num->setText(str);
    } else
        ui->lbl_num->setText("-" + str);
}


void MainWindow::on_btn_dot_clicked()
{
    if (!ui->lbl_num->text().contains(".")){
        ui->lbl_num->setText(ui->lbl_num->text() + ".");
    }
    ui->btn_dot->setEnabled(false);
}


void MainWindow::btn_click_exponent()
{
    QString num = ui->lbl_num->text();
    QPushButton *btn = (QPushButton *)sender();
    QString operat = btn->text();
    QString result = get_result(operat, num, "0");

    if (result == ERROR || result == "inf")
        QMessageBox::warning(this, "Error", "Значение не определено!");
    else{
        ui->lbl_num->setText(result);
        if (result.contains("e")){
            enable_num_button(false);
            ui->btn_del->setEnabled(false);
            ui->btn_dot->setEnabled(false);
        }else{
            enable_num_button(true);
            ui->btn_del->setEnabled(true);
            if (!ui->lbl_num->text().contains("."))
                ui->btn_dot->setEnabled(true);

        }
    }
}


void MainWindow::on_btn_MC_clicked()
{
    n_mem = "0";
}


void MainWindow::on_btn_MR_clicked()
{
    ui->lbl_num->setText(n_mem);
    if (ui->lbl_num->text().contains("e")){
        enable_num_button(false);
        ui->btn_del->setEnabled(false);
        ui->btn_dot->setEnabled(false);
    }
}


void MainWindow::on_btn_Mplus_clicked()
{
    n_mem = QString::number(n_mem.toDouble() + ui->lbl_num->text().toDouble());
}


void MainWindow::on_btn_Mminus_clicked()
{
    n_mem = QString::number(n_mem.toDouble() - ui->lbl_num->text().toDouble());
}


QString MainWindow::get_result(QString oper, QString num1, QString num2){
    struct operators arguments;
    arguments.num1 = (num1).toDouble();
    arguments.num2 = (num2).toDouble();
    QByteArray temp = oper.toLatin1();
    arguments.operation = temp.data();

    return execute(arguments) != ERROR_NUM ? QString::number(execute(arguments)) : ERROR;
}

