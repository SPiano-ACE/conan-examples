/**
 * @file test_qt.cpp
 * @author BusyBox (busybox177634@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <QApplication>
#include <QWidget>
#include <QMainWindow>


int main(int argc, char** argv) 
{
    QApplication a(argc, argv);


    QWidget widget;
    widget.show();


    return a.exec();

}