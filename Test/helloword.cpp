////glew + glfw
//#include <iostream>		
//using namespace std;
//#define GLEW_STATIC     
//#include <GL/glew.h>    
//#include <GLFW/glfw3.h> 
////#include<glad/glad.h>
//const GLint WIDTH = 800, HEIGHT = 600;		// 先设置窗口以及其大小								
//int main1()
//{
//	glfwInit();								//初始化，使用glfw来打开一个窗口
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						// 缩放窗口的关闭
//	GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Hello, friend! I'm a openGL window!", nullptr, nullptr);
//	int screenWidth, screenHeight;
//	glfwGetFramebufferSize(window_1, &screenWidth, &screenHeight);  // 获得实际占用的帧缓存大小
//	if (nullptr == window_1)			//判断窗口输出是否成功
//	{
//		cout << "Failed to create GLFW window" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window_1);   // 捕获当前窗口，准备对当前窗口进行画图
//	glewExperimental = GL_TRUE;
//	if (glewInit() != GLEW_OK)			// 判断glew初始化是否成功
//	{
//		cout << "Failed to initialise GLEW" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glViewport(0, 0, screenWidth, screenHeight);	// 设置视口的大小
//	while (!glfwWindowShouldClose(window_1))
//	{
//		glfwPollEvents();
//		glClearColor(0.1f, 0.8f, 0.7f, 1.0f);		// 分别是红、绿、蓝、透明度的四个参数。RGB三原色+透明度
//		glClear(GL_COLOR_BUFFER_BIT);
//		glfwSwapBuffers(window_1);					// 双缓存模式
//	}
//	glfwTerminate();								// 如果循环结束：glfw关闭
//	return 0;
//}
//
