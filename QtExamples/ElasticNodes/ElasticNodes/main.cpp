/**
 * 这个工程是Qt官方Demo中的 elasticnodes
 */

#include "GraphWidget.h"
#include <QtWidgets/QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphWidget *w = new GraphWidget;

    QMainWindow mainWindow;
    mainWindow.setCentralWidget(w);
    mainWindow.show();
    return a.exec();
}
