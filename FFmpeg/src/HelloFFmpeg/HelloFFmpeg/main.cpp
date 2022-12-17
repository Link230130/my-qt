#include "Widget.h"
#include <QtWidgets/QApplication>
#include <QDebug>



extern "C"
{
#include "libavcodec/avcodec.h"
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Widget w;
	w.show();
	return a.exec();
}
