// DrawTriangle.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <Windows.h>

using namespace std;

GLuint VAO, VBO;				// 它俩是成对出现的
GLuint shaderProgram_1;

/* 第二步：编写顶点位置 */
GLfloat vertices_1[] =
{
	0.0f, 0.5f, 0.0f,		// 上顶点
	-0.5f, -0.5f, 0.0f,		// 左顶点
	0.5f, -0.5f, 0.0f,		// 右顶点

};


/* 第三步：编写顶点着色器 */
const GLchar* vertexCode_1 = "#version 330 core\n"		// 3.30版本
"layout(location = 0) in vec3 position_1;\n"			// 三个浮点数vector向量表示位置 position变量名
"void main()\n"
"{\n"
"gl_Position = vec4(position_1, 1.0f);\n"				// 核心函数(位置信息赋值)
"}\n";


/* 第四步：编写片元着色器(也称片段着色器) */
const GLchar* fragmentCode_1 = "#version 330 core\n"	// 版本信息
"out vec4 FragColor_1;\n"								//输出是四个浮点数构成的一个向量 RGB+aerfa
"void main()\n"
"{\n"
"FragColor_1 = vec4(0.5f, 0.75f, 0.25f, 1.0f);\n"
"}\n";

void InitScene()
{
	glewInit();
	GLuint vertexShader_1 = glCreateShader(GL_VERTEX_SHADER);		// 创建顶点着色器对象
	glShaderSource(vertexShader_1, 1, &vertexCode_1, NULL);			// 将顶点着色器的内容传进来
	glCompileShader(vertexShader_1);	// 编译顶点着色器
	GLint flag;							// 用于判断编译是否成功
	GLchar infoLog[512];				// 512个字符
	glGetShaderiv(vertexShader_1, GL_COMPILE_STATUS, &flag); // 获取编译状态
	if (!flag)
	{
		glGetShaderInfoLog(vertexShader_1, 512, NULL, infoLog);   // 缓冲池  
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	GLuint fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);		// 创建片元着色器对象
	glShaderSource(fragmentShader_1, 1, &fragmentCode_1, NULL);			// 将顶点着色器的内容传进来
	glCompileShader(fragmentShader_1);									// 编译顶点着色器
	glGetShaderiv(fragmentShader_1, GL_COMPILE_STATUS, &flag);			// 获取编译状态
	if (!flag)
	{
		glGetShaderInfoLog(fragmentShader_1, 512, NULL, infoLog);		// 缓冲池  
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	/*GLuint*/ shaderProgram_1 = glCreateProgram();
	glAttachShader(shaderProgram_1, vertexShader_1);
	glAttachShader(shaderProgram_1, fragmentShader_1);
	glLinkProgram(shaderProgram_1);
	glGetProgramiv(shaderProgram_1, GL_LINK_STATUS, &flag);
	if (!flag)
	{
		glGetProgramInfoLog(shaderProgram_1, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
	glDeleteShader(vertexShader_1);
	glDeleteShader(fragmentShader_1);

	//GLuint VAO, VBO;				// 它俩是成对出现的
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// 从显卡中划分一个空间出来
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);	// GL_STATIC_DRAW：静态的画图(频繁地读)

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 800, 600);
	glUseProgram(shaderProgram_1);		// 渲染调用着色器程序
	glBindVertexArray(VAO);				// 绑定 VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);	// 画三角形  从第0个顶点开始 一共画3次
	glBindVertexArray(0);				// 解绑定

	glFlush();
}

void onWindowClose()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram_1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("绘制三角形");
	glutPositionWindow(0, 0);
	glutReshapeWindow(800, 600);
	InitScene();
	glClearColor(0.1f, 0.8f, 0.7f, 1.0f);
	glutDisplayFunc(RenderScene);
	glutCloseFunc(onWindowClose);
	glutMainLoop();

	return 0;
}