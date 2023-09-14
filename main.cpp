#include "mainwindow.h"

#include <QApplication>
#include<Qtimer>

#include"moneyapp.h"

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;

    MoneyApp& appInstance = MoneyApp::instance();




    w.show();





    return a.exec();
}
