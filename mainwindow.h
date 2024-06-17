#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSqlDatabase>

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

    void on_actCalculator_triggered();
    void on_actJump_triggered();
    void on_actSort_triggered();
    void on_actPrime_triggered();
    void on_actFactorial_triggered();
    void on_actRange_triggered();
    void on_actCoins_triggered();

//----------------------------------------------

    void on_pushAdd_clicked();
    void on_pushDelete_clicked();

    void sum();
    void ave();
    void max();
    void min();

//----------------------------------------------

    void on_pb_calculation_clicked();

//----------------------------------------------

    void on_pushAdd_2_clicked();
    void on_pushDelete_2_clicked();
    void comparison();

//----------------------------------------------

    void on_Check1_clicked();

    void on_Check2_clicked();

//----------------------------------------------

    void on_pb_calculation_3_clicked();

//----------------------------------------------

    void on_pb_showRange_clicked();

    /////////////////////////////////////

    void on_pbChangeNum_clicked();

    void on_pbCalculation_clicked();

    void ranges(int of, int to, float one, float two, int& range, QVector<float>& Range);

    /////////////////////////////////////

    void on_pbChangeNum_2_clicked();

    void on_pbChangeRange_clicked();

//----------------------------------------------

    void on_pb_calculation_5_clicked();

    void coinsCalculation(QVector<int> coins, int numCoins, int money, int index, int memory[],int& modes);

//----------------------------------------------

    void on_pb_login_clicked();
    void database(QString Address);
    void Disabled(int booL);

    void on_actAbout_triggered();

//----------------------------------------------

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
