#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void btn_click_num();
    void btn_click_operat();
    void btn_click_trig();
    void on_btn_del_clicked();
    void on_btn_c_clicked();
    void on_btn_res_clicked();
    void on_btn_help_clicked();
    void on_btn_opp_clicked();
    void on_btn_dot_clicked();
    void btn_click_exponent();

    void on_btn_MC_clicked();

    void on_btn_MR_clicked();

    void on_btn_Mplus_clicked();

    void on_btn_Mminus_clicked();

private:
    Ui::MainWindow *ui;

    QString n1, operat, n_mem;

    void enable_num_button(bool b);

    QString get_result(QString oper, QString num1, QString num2);

};
#endif // MAINWINDOW_H

