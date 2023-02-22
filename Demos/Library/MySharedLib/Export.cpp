#include "mainwidget.h"

extern "C" Q_DECL_EXPORT void createInstace(void **p){
    *p = new MainWidget;
}
