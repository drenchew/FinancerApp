#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<iostream>

#include"moneyapp.h"

#include<thread>
#include <future>
#include <thread>
#include<vector>


static QFont font1(const int size=10 ,bool bold=false)
{
    QFont f;
    f.setBold(bold);
    f.setPixelSize(size);
    return f;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->logs_label->setFont(font1(18,1));
    ui->leftLabel->setFont(font1(18,1));
    ui->targetLabel->setFont(font1(14,1));

    MoneyApp& appInstance = MoneyApp::instance();



    // Use std::async to execute read_target and load_logs in separate threads
    std::future<bool> readTargetFuture = std::async(std::launch::async, &MoneyApp::read_target, &appInstance);
    std::future<bool> loadLogsFuture = std::async(std::launch::async, &MoneyApp::load_logs, &appInstance);

    try {
        // Wait for both threads to finish and collect results
        bool readTargetResult = readTargetFuture.get();
        bool loadLogsResult = loadLogsFuture.get();

        std::cout<< "target res: "<< readTargetResult<<std::endl;
        std::cout<<  "loadLogsres: " <<loadLogsResult<<std::endl;


        // Update the UI accordingly
        if (!readTargetResult) {
            this->ui->errorMsg->setText("You need to set a target!!");
            ui->progressBar->setValue(0);
            return;
        }
        else
        {
            //QString::number(appInstance.view_target())

            ui->targetLabel->setText(QString::number(appInstance.view_target()));
        }

        if (!loadLogsResult) {
            appInstance.clear_labelTxt();
            appInstance.add_constr();

            {
               // QFont f;
               // f.setBold(true);
               // f.setPixelSize(18);
              //  ui->logs_label->setFont(font1(18,1));
            }

            ui->logs_label->setText(appInstance.get_labelTxt());
            appInstance.clear_labelTxt();
            ui->progressBar->setValue(appInstance.getIncreasePercent());


            std::ostringstream ostr;
            ostr<< appInstance.viewLogsSum() << " \\ " << appInstance.view_target();
            ui->leftLabel->setText(QString::fromStdString(ostr.str()));

            return;
        }
        else
        {
            ui->progressBar->setValue(69);
        }

        ui->progressBar->setValue(0);
    } catch (const std::exception& e) {
        // Print or log the exception details for debugging
        qDebug() << "Exception caught in MainWindow constructor: " << e.what();

        // Handle the exception gracefully, e.g., show an error message to the user
        this->ui->errorMsg->setText("An error occurred: " + QString(e.what()));
        ui->progressBar->setValue(0);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    MoneyApp& appInstance = MoneyApp::instance();

    QString qstr = ui->amount->text();
    ui->amount->clear();
    appInstance.set_date(ui->calendarUI->selectedDate());

    // Use std::async to run appInstance.add in a separate thread
    std::future<StateCode> futureResult = std::async([&appInstance, qstr]() {
        return appInstance.add(qstr.toStdString());
    });

    // You can do other UI updates here while the add function is running in the background
   // ui->progressBar->setValue(0);
    // Wait for the background task to complete and get the result
    StateCode resultCode = futureResult.get();

    // Handle the result as needed
    switch (resultCode) {
    case StateCode::SUCCESS :   ui->errorMsg->setText("Keep it up!"); break;
    case StateCode::INVALID_INPUT :ui->errorMsg->setText("Invalid Input!"); return;
    case StateCode::INVALID_TARGET :ui->errorMsg->setText("Please Set A Target!"); return;
    case StateCode::LOGS_FAILED :ui->errorMsg->setText("Cannot Save The Data."); return;
    }

    ui->logs_label->setText(appInstance.get_labelTxt());
  //  std::cout<< "txt: " << appInstance.get_labelTxt().toStdString()<< std::endl;

    appInstance.clear_labelTxt();


    std::ostringstream ostr;
    ostr<< appInstance.viewLogsSum() << " \\ " << appInstance.view_target();

    ui->leftLabel->setText(QString::fromStdString(ostr.str()));
    ui->progressBar->setValue(appInstance.getIncreasePercent());
}



void MainWindow::on_changeTargetBtn_clicked()
{
   MoneyApp& appInstance = MoneyApp::instance();
    QString val = ui->targetInput->text();

   bool del = ui->clearHistory->isChecked();
    if(del== true)
   {
    this->ui->logs_label->setText("Cleared");
    ui->progressBar->setValue(0);

   }

    appInstance.change_target(val.toDouble(),del);


    std::ostringstream ostr;
    ostr<< appInstance.viewLogsSum() << " \\ " << appInstance.view_target();
    ui->leftLabel->setText(QString::fromStdString(ostr.str()));
    ui->targetLabel->setText(QString::number(appInstance.view_target()));
    ui->progressBar->setValue(appInstance.getIncreasePercent());
}

