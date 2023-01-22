#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

void MyOpenGLWidget::initializeGL()
{
    //执行初始化操作，例如将glClearColor函数指向显卡中的函数，
    //如果不进行初始化，那么glClearColor这样的函数即为空，无法正常运行
    initializeOpenGLFunctions();
}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    //glClearColor(1.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{

}
