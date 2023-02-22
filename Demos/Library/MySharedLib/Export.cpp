#include "mainwidget.h"

/*
 * 这是一个导出库，供UseSharedLib调用
*/

extern "C" Q_DECL_EXPORT void createInstace(void **p){
    *p = new MainWidget;
}
