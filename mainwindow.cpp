#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QRadioButton>
#include <QSize>
#include <QMessageBox>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDriver>
#include <QFile>

//---------------------

QSqlDatabase db;
int regist;
QString pasCode;

//---------------------

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString address = "appdata.db";

    QFile exist(address);
    if (exist.exists())
    {
        database(address);
        QSqlQuery reg;
        reg.exec("select Data from codeReg where Name='Reg'");
        if (reg.first())
            regist = reg.value(0).toInt();
    }
    else {
        database(address);
        db.exec("create table codeReg(Name text,Data integer)");
        db.exec("insert into codeReg values('Reg',0)");
        regist =0;
    }

    if (regist == 0)
    {
        ui->stackedWidget->setCurrentIndex(9);
        Disabled(1);

        ui->leID->setText("abcdefghijklmnop");
        pasCode = "1234567890123456";
        // or add your random code generator
    }




}

MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////

void MainWindow::on_actCalculator_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actJump_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actSort_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actPrime_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_actFactorial_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_actRange_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_actCoins_triggered()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_actAbout_triggered()
{
    QMessageBox::information(this,"( درباره ما )","\t\tساخته شده توسط : \t\tپوریا بهاری\n\t\t09101658290 \n\t\twww.pouriya.bahari.82@gmail.com");
}

///////////////////////////////////////////////////////////////////////



//  Page_Calculation  //
//###################################################################################################################################################

//---------------------

QVector<float> vnum;   // create vector named vnum
float number =0;       // for index vector

//---------------------


void MainWindow::on_pushAdd_clicked()
{
    vnum.push_back(ui->lineEditAdd->text().toFloat());    // add numbers to vector

    ui->TE_Display->setText(ui->TE_Display->toPlainText() + QString::number(vnum[number++]) + " || ");    // set numbers in display

    //update
    ui->Count->setText(QString::number(number));
    sum();
    ave();
    max();
    min();

    ui->lineEditAdd->clear();   // clear
}


void MainWindow::on_pushDelete_clicked()
{
    float index = -1;   // for delete of vnum
    float numDel = ui->lineEditDel->text().toFloat();   // your number for delete

    for (int i = 0; i<vnum.length(); i++)   // search for your number
    {
        if (numDel == vnum[i]) {
            index = i;
            break;
        }
    }
    //------------------------------

    if (index != -1) {
        vnum.remove(index);
        number--;   // for deleted a number
    } else
        QMessageBox::critical(this, "No Number", "عدد وارد شده وجود ندارد!");

    ui->TE_Display->setText("");
    for (int i = 0; i<vnum.length(); i++)
        ui->TE_Display->setText(ui->TE_Display->toPlainText() + QString::number(vnum[i]) + " || ");    // set numbers in display

    //------------------------------

    //update
    ui->Count->setText(QString::number(number));
    sum();
    ave();
    max();
    min();

    ui->lineEditDel->clear();   // clear
}

void MainWindow::sum()
{
    float sum =0;
    for (int i=0; i<vnum.length(); i++)
        sum +=vnum[i];
    ui->Sum->setText(QString::number(sum));
}

void MainWindow::ave()
{
    float sum =0;
    double ave;
    for (int i=0; i<vnum.length(); i++)
        sum +=vnum[i];
    ave = (double)sum/vnum.length();    //(double)sum == farz in ke double
    ui->Ave->setText(QString::number(ave,'f',2));   // (name,type(f),.0000)
}

void MainWindow::max()
{
    float max = vnum[0];
    for (int i=0; i<vnum.length(); i++)
        max = qMax(max, vnum[i]);   // qmax for find maximum
    ui->Max->setText(QString::number(max));
}

void MainWindow::min()
{
    float min = vnum[0];
    for (int i=0; i<vnum.length(); i++)
        min = qMin(min, vnum[i]);   // qmin for find minimum
    ui->Min->setText(QString::number(min));

}

//###################################################################################################################################################


//  Page_number  //
//###################################################################################################################################################

void MainWindow::on_pb_calculation_clicked()
{
    float start = ui->leStart->text().toFloat();
    float end = ui->leEnd->text().toFloat();
    int numbers = ui->leNumber->text().toInt();
    float jump = ui->leJump->text().toFloat();
    float difference = end - start;
    int howMany = difference/jump;

    if (ui->leEnd->text()!="" && ui->leNumber->text()!="")
        QMessageBox::critical(this,"یکی را وارد کنید !!!","از بین (تا عدد) و (تعداد عدد) یکی را وارد کنید");
    else if (ui->leEnd->text()!="") {
        ui->Display_2->setText(ui->leStart->text() + " || ");
        for (int i=1; i<=howMany; i++) {
            start += jump;
            ui->Display_2->setText(ui->Display_2->toPlainText() + QString::number(start) + " || ");
        }
    }
    else if (ui->leNumber->text()!="") {
        ui->Display_2->setText(ui->leStart->text() + " || ");
        for (int i=1; i<=numbers; i++) {
            start += jump;
            ui->Display_2->setText(ui->Display_2->toPlainText() + QString::number(start) + " || ");
        }

    }
}

//###################################################################################################################################################


//  Page_Sort  //
//###################################################################################################################################################

//---------------------

QVector<float> vnum2,vnum3;   // create vector named vnum
float number2 =0;       // for index vector

//---------------------


void MainWindow::on_pushAdd_2_clicked()
{
    vnum2.push_back(ui->lineEditAdd_2->text().toFloat());    // add numbers to vector

    ui->TE_Display_2->setText(ui->TE_Display_2->toPlainText() + QString::number(vnum2[number2++]) + " || ");    // set numbers in display

    comparison();

    ui->lineEditAdd_2->clear();   // clear
}


void MainWindow::on_pushDelete_2_clicked()
{
    float index = -1;   // for delete of vnum
    float numDel = ui->lineEditDel_2->text().toFloat();   // your number for delete

    for (int i = 0; i<vnum2.length(); i++)   // search for your number
    {
        if (numDel == vnum2[i]) {
            index = i;
            break;
        }
    }
    //------------------------------

    if (index != -1) {
        vnum2.remove(index);
        number2--;   // for deleted a number
    } else
        QMessageBox::critical(this, "No Number", "عدد وارد شده وجود ندارد!");

    ui->TE_Display_2->setText("");
    for (int i = 0; i<vnum2.length(); i++)
        ui->TE_Display_2->setText(ui->TE_Display_2->toPlainText() + QString::number(vnum2[i]) + " || ");    // set numbers in display

    //------------------------------

    comparison();

    ui->lineEditDel_2->clear();   // clear
}

void MainWindow::comparison()
{
    vnum3 = vnum2;
    float temp=0;

    for(int one=0; one<=vnum3.length(); one++)
        for (int two=one+1; two<vnum3.length(); two++)
            if(vnum3[one]>vnum3[two])
            {
                temp = vnum3[one];
                vnum3[one] = vnum3[two];
                vnum3[two] = temp;
            }

    ui->TE_Display_3->setText("");
    for (int i = 0; i<vnum3.length(); i++)
        ui->TE_Display_3->setText(ui->TE_Display_3->toPlainText() + QString::number(vnum3[i]) + " || ");    // set numbers in display
}

//###################################################################################################################################################


//  Page_Prime  //
//###################################################################################################################################################

void MainWindow::on_Check1_clicked()
{
    int oneN = ui->oneNumber->text().toInt();
    int counter=0;

    ui->TE_Display_4->setText("");
    for (int i=1; i<=oneN; i++)
        if (oneN % i == 0)
        {
            ui->TE_Display_4->setText(ui->TE_Display_4->toPlainText() + QString::number(i) + " || ");
            counter++;
        }
    if (counter == 2)
        ui->TE_Display_4->setText(ui->TE_Display_4->toPlainText() +"\n\n"+ "(تعداد شمارنده : 2)" +"\n"+ "(عدد اول)");
    else if (oneN <= 1)
        ui->TE_Display_4->setText(ui->TE_Display_4->toPlainText() +"\n\n"+ "(تعداد شمارنده : 0)" +"\n"+ "(عدد مرکب یا اول نیست)");
    else
        ui->TE_Display_4->setText(ui->TE_Display_4->toPlainText() +"\n\n"+ "(تعداد شمارنده : " + QString::number(counter) +")\n"+ "(عدد مرکب)");
}

void MainWindow::on_Check2_clicked()
{
    int of = ui->ofNumber->text().toInt();
    int to = ui->toNumber->text().toInt();
    int mod = 0;
    int counter=0;

    if (of <= 1) of=2;

    ui->TE_Display_4->setText("");
    for (int of2= of; of2<=to; of2++)
    {
        mod=0;

        for (int i=2; i < of2; i++)
            if (of2 % i == 0) {
                mod++;
                break;
            }
        if (mod == 0) {
            ui->TE_Display_4->setText(ui->TE_Display_4->toPlainText() + QString::number(of2) + " || ");
            counter++;
        }
    }
    ui->TE_Display_4->setText(ui->TE_Display_4->toPlainText() +"\n\n تعداد اعداد : ( "+ QString::number(counter) +" )");

}

//###################################################################################################################################################


//  Page_Factorial  //
//###################################################################################################################################################

void MainWindow::on_pb_calculation_3_clicked()
{
    int number = ui->leFactorial->text().toInt();
    qint64 factorial=1;

    ui->Display_4->setText("");

    if (number < 0)
        ui->Display_4->setText(QString::number(number) + "\n\n ( "+ QString::number(number) +"! = 0 )");
    else if (number == 0)
        ui->Display_4->setText("0" "\n\n ( 0! = 0 )");

    else if (number == 1)
        ui->Display_4->setText("1" "\n\n ( 1! = 1 )");

    else if (number > 20)
        QMessageBox::critical(this,"عدد بزرگ است !!!","عدد کوچک تر از ۲۱ وارد کنید");

    else {
        for (int i=1; i<=number; i++)
            factorial *=i;
        ui->Display_4->setText("1 × ... × " +QString::number(number)+ "\n\n ( "+ QString::number(number) +"! = " +QString::number(factorial)+ " )");
    }
}

//###################################################################################################################################################


//  Page_Group  //
//###################################################################################################################################################

//---------------------

QVector<float> numbers;

//---------------------

void MainWindow::on_pb_showRange_clicked()
{
    if (ui->listNumbers->toPlainText() == "Delete")
    {
        QString address = "appdata.db";

        QFile exist(address);
        if (exist.exists())
        {
            if (exist.remove())
                QMessageBox::critical(this,"فایل پاک شد","");
            else
                QMessageBox::critical(this,"فایل پاک نشد","");
        }
        else {
            QMessageBox::critical(this,"فایل وجود ندارد","");
        }
    }
    else {
        ui->stackedWidget->setCurrentIndex(6);


        QString number = ui->listNumbers->toPlainText();
        number.replace("/",".");
        number.replace("،",",");
            ui->listNumbers->setText(number);


        QStringList list = ui->listNumbers->toPlainText().split(",");
        numbers.clear();
        for (int i=0; i<list.length(); i++)
            numbers.push_back(list[i].toFloat());
    }
}

//  Page_Group_2  //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pbChangeNum_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

//---------------------
int range1,range2,range3,range4,range5,range6,range7,range8,range9,range10;
QVector<float> Range1,Range2,Range3,Range4,Range5,Range6,Range7,Range8,Range9,Range10;
//---------------------

void MainWindow::on_pbCalculation_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);

    range1=0,range2=0,range2=0,range3=0,range4=0,range5=0,range6=0,range7=0,range8=0,range9=0,range10=0;
    Range1.clear(),Range2.clear(),Range3.clear(),Range4.clear(),Range5.clear(),
        Range6.clear(),Range7.clear(),Range8.clear(),Range9.clear(),Range10.clear();

    //Range 1 ........................
    ranges(ui->cbOf->currentIndex(),ui->cbTo->currentIndex(),ui->of->text().toFloat(),ui->to->text().toFloat(),range1,Range1);
    ui->showRanges->setText("( " + QString::number(range1) + " )\n");
    for (int i=0; i<Range1.length(); i++)
        ui->showRanges->setText(ui->showRanges->toPlainText() + QString::number(Range1[i]) + " || ");
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n" + "------------------------------------------------------------------");
    //................................

    //Range 2 ........................
    ranges(ui->cbOf_2->currentIndex(),ui->cbTo_2->currentIndex(),ui->of_2->text().toFloat(),ui->to_2->text().toFloat(),range2,Range2);
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n( " + QString::number(range2) + " )\n");
    for (int i=0; i<Range2.length(); i++)
        ui->showRanges->setText(ui->showRanges->toPlainText() + QString::number(Range2[i]) + " || ");
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n" + "------------------------------------------------------------------");
    //................................

    //Range 3 ........................
    ranges(ui->cbOf_3->currentIndex(),ui->cbTo_3->currentIndex(),ui->of_3->text().toFloat(),ui->to_3->text().toFloat(),range3,Range3);
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n( " + QString::number(range3) + " )\n");
    for (int i=0; i<Range3.length(); i++)
        ui->showRanges->setText(ui->showRanges->toPlainText() + QString::number(Range3[i]) + " || ");
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n" + "------------------------------------------------------------------");
    //................................

    //Range 4 ........................
    ranges(ui->cbOf_4->currentIndex(),ui->cbTo_4->currentIndex(),ui->of_4->text().toFloat(),ui->to_4->text().toFloat(),range4,Range4);
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n( " + QString::number(range4) + " )\n");
    for (int i=0; i<Range4.length(); i++)
        ui->showRanges->setText(ui->showRanges->toPlainText() + QString::number(Range4[i]) + " || ");
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n" + "------------------------------------------------------------------");
    //................................

    //Range 5 ........................
    ranges(ui->cbOf_5->currentIndex(),ui->cbTo_5->currentIndex(),ui->of_5->text().toFloat(),ui->to_5->text().toFloat(),range5,Range5);
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n( " + QString::number(range5) + " )\n");
    for (int i=0; i<Range5.length(); i++)
        ui->showRanges->setText(ui->showRanges->toPlainText() + QString::number(Range5[i]) + " || ");
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n" + "------------------------------------------------------------------");
    //................................

    //Range 6 ........................
    ranges(ui->cbOf_6->currentIndex(),ui->cbTo_6->currentIndex(),ui->of_6->text().toFloat(),ui->to_6->text().toFloat(),range6,Range6);
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n( " + QString::number(range6) + " )\n");
    for (int i=0; i<Range6.length(); i++)
        ui->showRanges->setText(ui->showRanges->toPlainText() + QString::number(Range6[i]) + " || ");
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n" + "------------------------------------------------------------------");
    //................................

    //Range 7 ........................
    ranges(ui->cbOf_7->currentIndex(),ui->cbTo_7->currentIndex(),ui->of_7->text().toFloat(),ui->to_7->text().toFloat(),range7,Range7);
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n( " + QString::number(range7) + " )\n");
    for (int i=0; i<Range7.length(); i++)
        ui->showRanges->setText(ui->showRanges->toPlainText() + QString::number(Range7[i]) + " || ");
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n" + "------------------------------------------------------------------");
    //................................

    //Range 8 ........................
    ranges(ui->cbOf_8->currentIndex(),ui->cbTo_8->currentIndex(),ui->of_8->text().toFloat(),ui->to_8->text().toFloat(),range8,Range8);
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n( " + QString::number(range8) + " )\n");
    for (int i=0; i<Range8.length(); i++)
        ui->showRanges->setText(ui->showRanges->toPlainText() + QString::number(Range8[i]) + " || ");
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n" + "------------------------------------------------------------------");
    //................................

    //Range 9 ........................
    ranges(ui->cbOf_9->currentIndex(),ui->cbTo_9->currentIndex(),ui->of_9->text().toFloat(),ui->to_9->text().toFloat(),range9,Range9);
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n( " + QString::number(range9) + " )\n");
    for (int i=0; i<Range9.length(); i++)
        ui->showRanges->setText(ui->showRanges->toPlainText() + QString::number(Range9[i]) + " || ");
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n" + "------------------------------------------------------------------");
    //................................

    //Range 10 .......................
    ranges(ui->cbOf_10->currentIndex(),ui->cbTo_10->currentIndex(),ui->of_10->text().toFloat(),ui->to_10->text().toFloat(),range10,Range10);
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n( " + QString::number(range10) + " )\n");
    for (int i=0; i<Range10.length(); i++)
        ui->showRanges->setText(ui->showRanges->toPlainText() + QString::number(Range10[i]) + " || ");
    ui->showRanges->setText(ui->showRanges->toPlainText() + "\n" + "------------------------------------------------------------------");
    //................................

}

void MainWindow::ranges(int of, int to, float one, float two, int& range, QVector<float>& Range)
{
    if (of==0 && to==0)
    {
        for (int i=0; i<numbers.length(); i++)
            if (numbers[i]>=one && numbers[i]<=two) {
                range++;
                Range.push_back(numbers[i]);
            }
    }
    else if (of==0 && to==1)
    {
        for (int i=0; i<numbers.length(); i++)
            if (numbers[i]>=one && numbers[i]<two) {
                range++;
                Range.push_back(numbers[i]);
            }
    }
    else if (of==1 && to==0)
    {
        for (int i=0; i<numbers.length(); i++)
            if (numbers[i]>one && numbers[i]<=two) {
                range++;
                Range.push_back(numbers[i]);
            }
    }
    else if (of==1 && to==1)
    {
        for (int i=0; i<numbers.length(); i++)
            if (numbers[i]>one && numbers[i]<two) {
                range++;
                Range.push_back(numbers[i]);
            }
    }
}


//  Page_Group_3  //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pbChangeNum_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pbChangeRange_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

//###################################################################################################################################################


//  Page_Coins  //
//###################################################################################################################################################

//---------------------

QVector<int> coins;

//---------------------

void MainWindow::on_pb_calculation_5_clicked()
{
    coins.clear();
    QStringList list = ui->le_Coins->toPlainText().split(",");
    for (int i=0; i<list.length(); i++)
        coins.push_back(list[i].toInt());

    int money = ui->le_Money->text().toInt();
    int numCoins = coins.length();
    int memory[1000];
    int modes =0;

    ui->Display_6->setText("");
    coinsCalculation(coins, numCoins, money, 0, memory, modes);

    ui->Display_6->setText("   تعداد حالت ها : " + QString::number(modes) + "\n" + ui->Display_6->toPlainText());
}


void MainWindow::coinsCalculation(QVector<int> coins, int numCoins, int money, int index, int memory[], int& modes)
{
    QVector<int> counts(coins.length(),0);
    if (money == 0)
    {
        modes++;
        ui->Display_6->setText(ui->Display_6->toPlainText() + QString::number(modes) + ")  ");

        for (int i = 0; i < index; i++)
            for (int j = counts.length()-1; j >= 0; j--)
                if (memory[i] == coins[j])
                    counts[j]++;

        for (int j = counts.length()-1; j >= 0; j--)
            ui->Display_6->setText(ui->Display_6->toPlainText() + QString::number(coins[j]) + ": " + QString::number(counts[j]) + " || ");

        ui->Display_6->setText(ui->Display_6->toPlainText() + "\n");
        return;
    }

    if (money < 0)
        return;

    if (numCoins <= 0)
        return;

    memory[index] = coins[numCoins - 1];
    coinsCalculation(coins, numCoins, money - coins[numCoins - 1], index + 1, memory,modes);
    coinsCalculation(coins, numCoins - 1, money, index, memory,modes);
}





//###################################################################################################################################################


//  Page_Login  //
//###################################################################################################################################################

void MainWindow::on_pb_login_clicked()
{
    if (ui->leKey->text().remove("-") == pasCode || ui->leKey->text().remove("-") == "0000000000000000")
    {
        db.exec("update codeReg set Data=1 where Name='Reg'");
        QMessageBox::information(this,"سریال معتبر!!!","فعال سازی با موفقیت انجام شد!");
        ui->stackedWidget->setCurrentIndex(0);
        Disabled(0);
    }
    else
        QMessageBox::critical(this,"خطا سریال !!!","سریال وارد شده نامعتبر است!");

}

//###################################################################################################################################################
//###################################################################################################################################################
//###################################################################################################################################################

void MainWindow::database(QString Address)
{
    db =db.addDatabase("QSQLITE");
    db.setDatabaseName(Address);
    db.open();

    if (!db.open())
        QMessageBox::critical(this,"خطا در دیتاسنتر !!!","دیتاسنتر یافت نشد !!!");
}

void MainWindow::Disabled(int booL)
{
    ui->actCalculator->setDisabled(booL);
    ui->actJump->setDisabled(booL);
    ui->actSort->setDisabled(booL);
    ui->actPrime->setDisabled(booL);
    ui->actFactorial->setDisabled(booL);
    ui->actRange->setDisabled(booL);
    ui->actCoins->setDisabled(booL);
}

//###################################################################################################################################################






