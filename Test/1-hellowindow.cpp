#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//GLFW 显示窗口
//glad 管理OpenGL的函数指针 所以在调用任何OpenGL函数之前我们都要初始化GLAD
void framebuffer_size_callback1(GLFWwindow* window, int width, int height);
void processInput1(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main1()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();                                              //初始化GLFW                     
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);          //major（主版本号为3） 和 minor（次版本号也为3） 是创建上下文必须兼容的客户端API版本。
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);          //其确切行为取决于请求的客户端API，告诉GLFW我们的opengl版本为3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //告诉GLFW使用核心模式（core-profile,告诉他我们只能使用OpenGl的一个子集

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    //创建窗口对象
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello, friend! I'm a openGL window!", NULL, NULL); 
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //告诉opengl渲染窗口的尺寸大小，即视口（viewport），这样opengl才能知道怎样根据窗口大小显示数据和坐标
    /*
     并没有显示的传递参数
     glfwSetFramebufferSizeCallback函数的第一个参数是窗口指针，
     第二个参数是函数指针用于指定窗口变化时调用的回调函数
     在这种情况下这个函数会在窗口大小发生变化时自动将窗口指针和新的宽度和高度作为参数传递给注册的回调函数
     所以在framebuffer_size_callback函数中，我们不需要显式的传递函数，因为glfw会再调用回调函数时自动传递相应的参数
    */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback1);//创建完窗口我们就可以通知GLFW将我们窗口的上下文设置为当前线程的主上下文了。


    // glad: 管理OpenGL的函数指针 所以在调用任何OpenGL函数之前我们都要初始化GLAD
    // ---------------------------------------
    /*给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数。
    GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。*/
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // render loop 希望程序在我们主动关闭它之前不断地绘制图像并能够接受用户输入
    // -----------
    while (!glfwWindowShouldClose(window))  //每次循环开始前检查GLFW是否被要求退出
    {
        // input在GLFW实现一些输入控制（输入）
        // -----
        processInput1(window);

        // render渲染指令
        // ------
        glClearColor(0.6f, 0.3f, 0.3f, 1.0f);  //定义了一个颜色清空屏幕，且每个迭代开始都清屏，否则我们看到的是上一次迭代的渲染结果——状态设置函数
        glClear(GL_COLOR_BUFFER_BIT);          //清空屏幕的颜色缓冲 它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲，
                                               //可能的缓冲位有GL_COLOR_BUFFER_BIT——状态使用函数，
                                               //它使用了当前的状态来获取应该清除为的颜色。

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        /*这两行代码就是检查并调用事件，交换缓冲
        双缓冲(Double Buffer)
        应用程序使用单缓冲绘图时可能会存在图像闪烁的问题。 这是因为生成的图像不是一下子被绘制出来的，而是按照从左到右，由上而下逐像素地绘制而成的。
        最终图像不是在瞬间显示给用户，而是通过一步一步生成的，这会导致渲染的结果很不真实。为了规避这些问题，我们应用双缓冲渲染窗口应用程序。
        前缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制。
        当所有的渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓冲，这样图像就立即呈显出来，之前提到的不真实感就消除了。
        */
        glfwSwapBuffers(window);//函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
        glfwPollEvents();//函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate(); //删除释放掉之前分配的所有资源
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
//
//使用GLFW的glfwGetKey函数，它需要一个窗口以及一个按键作为输入。这个函数将会返回这个按键是否正在被按下
void processInput1(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); //如果按下回车，关闭GLFW,下一次while循环就是false，程序关闭
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
//这个视口的维度应该小于等于GLWF的维度，所以当用户改变窗口大小的时候，视口也应该被调整，所以对窗口设计一个回调函数（callback），他会在每次窗口调整大小的时候被调用
void framebuffer_size_callback1(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    //这个函数就是进行把Opengl的坐标（-1，1）转换为（映射到）屏幕坐标（800，600）
    glViewport(0, 0, width, height);   //设置窗口的维度 前两个参数控制窗口左下角的位置，后两个参数控制渲染窗口的宽度和高度（像素）  
}