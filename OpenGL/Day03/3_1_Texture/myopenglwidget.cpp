#include "myopenglwidget.h"

//顶点数据
float vertices[] = {
    //positions       //colors        //texture coords
    0.5f,0.5f,0.0f,   1.0f,0.0f,0.0f, 1.0f,1.0f,    //top right
    0.5f,-0.5f,0.0f,  0.0f,1.0f,0.0f, 1.0f,0.0f,    //bottom right
    -0.5f,0.5f,0.0f,  0.0f,0.0f,1.0f, 0.0f,1.0f,    //top left
    -0.5f,-0.5f,0.0f, 1.0f,1.0f,0.0f, 0.0f,0.0f     //bottom left
};

unsigned int indices[] = {
    //first triangle
    0,1,2,
    //second triangle
    1,2,3
};


MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&VAO);
    //glDeleteShader(shaderProgram);
    doneCurrent();
}

void MyOpenGLWidget::drawShape(MyOpenGLWidget::Shape shape)
{
    m_shape = shape;
    update();
}

void MyOpenGLWidget::setWireFrame(bool wireframe)
{
    makeCurrent();
    if(wireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    doneCurrent();
    update();
}

void MyOpenGLWidget::initializeGL()
{
    //执行初始化操作，例如将glClearColor函数指向显卡中的函数，
    //如果不进行初始化，那么glClearColor这样的函数即为空，无法正常运行
    initializeOpenGLFunctions();

    //创建VBO和VAO对象
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);

    //绑定VBO和VAO对象
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindVertexArray(VAO);

    //创建并绑定EBO
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储
    //如果data不是NULL，则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER,sizeof (vertices),vertices,GL_STATIC_DRAW);

    //告知显卡如何解析缓冲里的属性值
    //参数：第0个属性，有3个值，每个值为float，不标准化，步长，偏移量
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof (float),(void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);
    //第二个属性：colors
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 8*sizeof (float),(void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);
    //第三个属性：texture coords
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof (float),(void*)(sizeof(float)*6));
    glEnableVertexAttribArray(2);

    //解绑EBO需要在VAO解绑前执行，否则VAO无法正常记录，也就未达到解绑的目的。VBO则没有这一条限制
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    //使用QOpenGLTexture进行纹理贴图
    //由于Qt的坐标系和OpenGL的坐标Y轴相反，因此需要镜像翻转一下
    qTexture = new QOpenGLTexture(QImage(":/Resources/Images/wall.jpg").mirrored());

    //解绑VAO、VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    //采用QOpenGLShaderProgram进行着色器编译和链接
    qShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/Resources/Shaders/shapes.vert");
    qShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/Resources/Shaders/shapes.frag");
    qShaderProgram.link();
}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //着色器
    //glUseProgram(shaderProgram);  //采用OpenGL传统方式绑定着色器
    qShaderProgram.bind();  //采用Qt封装的QOpenGLShaderProgram方式绑定
    glBindVertexArray(VAO);
    //直接使用Buffer里数据绘制
    //glDrawArrays(GL_TRIANGLES,0,6);
    //利用EBO进行绘制
    switch (m_shape) {
    case Shape::Rect:
        qTexture->bind(0);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        break;
    case Shape::Triangle:
        break;
    case Shape::Circle:
        break;
    case Shape::None:
        break;
    }
}

void MyOpenGLWidget::resizeGL(int w, int h)
{

}
