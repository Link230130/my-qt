#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class MyOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget *parent = nullptr);
    ~MyOpenGLWidget();

    enum Shape{None,Rect,Triangle,Circle};

    void drawShape(Shape shape);
    void setWireFrame(bool wireframe);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    //着色器程序
    //unsigned int shaderProgram;

    Shape m_shape;
    QOpenGLShaderProgram qShaderProgram;
    QOpenGLTexture *qTexture;
signals:

public slots:
};

#endif // MYOPENGLWIDGET_H
