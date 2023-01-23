#include "myopenglwidget.h"

//顶点数据
float vertices[] = {
    //first triangle
    0.5f,0.5f,0.0f,     //top right
    0.5f,-0.5f,0.0f,    //bottom right
    -0.5f,0.5f,0.0f,    //top left
    //second triangle
    //0.5f,-0.5f,0.0f,    //bottom right
    -0.5f,-0.5f,0.0f,   //bottom left
    //-0.5f,0.5f,0.0f     //top left
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
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof (float),(void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);

    //解绑EBO需要在VAO解绑前执行，否则VAO无法正常记录，也就未达到解绑的目的。VBO则没有这一条限制
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    //解绑VAO和VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    /*OpenGL传统方式编译和链接着色器
    //创建和编译顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    //创建和编译片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    //链接着色器程序
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    //释放着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    */

    //采用QOpenGLShaderProgram进行着色器编译和链接
    //可以看到采用Qt封装的类可以极大简化程序
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
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        break;
    case Shape::Triangle:
        break;
    case Shape::Circle:
        break;
    case Shape::None:
        break;
    }

    //若要采用这种方式绘制，那么必须要解绑EBO，否则无法绘制。
    //VAO会记录下EBO的绑定与解除(不会记录VBO)，也就是说VAO记录下EBO绑定了，那么第四个参数就需要为0；
    //反之VAO记录下了EBO解绑，那么第四个参数就不能为0了
    //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,&indices);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{

}
