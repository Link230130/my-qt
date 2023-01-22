#include "myopenglwidget.h"

//顶点数据
float vertices[] = {
    -0.5f,-0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    0.0f,0.5f,0.0f
};

//顶点着色器源数据
const char* vertexShaderSource = "#version 330 core\n"
                                 "layout(location = 0) in vec3 aPos;\n"
                                 "void main(){\n"
                                 "gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
                                 "}\0";

//片段着色器源数据
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main(){\n"
                                   "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
                                   "}\0";

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

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

    //为当前绑定到target的缓冲区对象创建一个新的数据存储
    //如果data不是NULL，则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER,sizeof (vertices),vertices,GL_STATIC_DRAW);

    //告知显卡如何解析缓冲里的属性值
    //参数：第0个属性，有3个值，每个值为float，不标准化，步长，偏移量
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof (float),(void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);
    //解绑VAO和VBO
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

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
}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //着色器
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,3);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{

}
