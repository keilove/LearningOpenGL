#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//GLFW ��ʾ����
//glad ����OpenGL�ĺ���ָ�� �����ڵ����κ�OpenGL����֮ǰ���Ƕ�Ҫ��ʼ��GLAD
void framebuffer_size_callback1(GLFWwindow* window, int width, int height);
void processInput1(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main1()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();                                              //��ʼ��GLFW                     
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);          //major�����汾��Ϊ3�� �� minor���ΰ汾��ҲΪ3�� �Ǵ��������ı�����ݵĿͻ���API�汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);          //��ȷ����Ϊȡ��������Ŀͻ���API������GLFW���ǵ�opengl�汾Ϊ3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //����GLFWʹ�ú���ģʽ��core-profile,����������ֻ��ʹ��OpenGl��һ���Ӽ�

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    //�������ڶ���
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello, friend! I'm a openGL window!", NULL, NULL); 
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //����opengl��Ⱦ���ڵĳߴ��С�����ӿڣ�viewport��������opengl����֪���������ݴ��ڴ�С��ʾ���ݺ�����
    /*
     ��û����ʾ�Ĵ��ݲ���
     glfwSetFramebufferSizeCallback�����ĵ�һ�������Ǵ���ָ�룬
     �ڶ��������Ǻ���ָ������ָ�����ڱ仯ʱ���õĻص�����
     ���������������������ڴ��ڴ�С�����仯ʱ�Զ�������ָ����µĿ�Ⱥ͸߶���Ϊ�������ݸ�ע��Ļص�����
     ������framebuffer_size_callback�����У����ǲ���Ҫ��ʽ�Ĵ��ݺ�������Ϊglfw���ٵ��ûص�����ʱ�Զ�������Ӧ�Ĳ���
    */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback1);//�����괰�����ǾͿ���֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳����������ˡ�


    // glad: ����OpenGL�ĺ���ָ�� �����ڵ����κ�OpenGL����֮ǰ���Ƕ�Ҫ��ʼ��GLAD
    // ---------------------------------------
    /*��GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ�����
    GLFW�����ǵ���glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ�����*/
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // render loop ϣ�����������������ر���֮ǰ���ϵػ���ͼ���ܹ������û�����
    // -----------
    while (!glfwWindowShouldClose(window))  //ÿ��ѭ����ʼǰ���GLFW�Ƿ�Ҫ���˳�
    {
        // input��GLFWʵ��һЩ������ƣ����룩
        // -----
        processInput1(window);

        // render��Ⱦָ��
        // ------
        glClearColor(0.6f, 0.3f, 0.3f, 1.0f);  //������һ����ɫ�����Ļ����ÿ��������ʼ���������������ǿ���������һ�ε�������Ⱦ�������״̬���ú���
        glClear(GL_COLOR_BUFFER_BIT);          //�����Ļ����ɫ���� ������һ������λ(Buffer Bit)��ָ��Ҫ��յĻ��壬
                                               //���ܵĻ���λ��GL_COLOR_BUFFER_BIT����״̬ʹ�ú�����
                                               //��ʹ���˵�ǰ��״̬����ȡӦ�����Ϊ����ɫ��

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        /*�����д�����Ǽ�鲢�����¼�����������
        ˫����(Double Buffer)
        Ӧ�ó���ʹ�õ������ͼʱ���ܻ����ͼ����˸�����⡣ ������Ϊ���ɵ�ͼ����һ���ӱ����Ƴ����ģ����ǰ��մ����ң����϶��������صػ��ƶ��ɵġ�
        ����ͼ������˲����ʾ���û�������ͨ��һ��һ�����ɵģ���ᵼ����Ⱦ�Ľ���ܲ���ʵ��Ϊ�˹����Щ���⣬����Ӧ��˫������Ⱦ����Ӧ�ó���
        ǰ���屣�������������ͼ����������Ļ����ʾ�������еĵ���Ⱦָ����ں󻺳��ϻ��ơ�
        �����е���Ⱦָ��ִ����Ϻ����ǽ���(Swap)ǰ����ͺ󻺳壬����ͼ����������Գ�����֮ǰ�ᵽ�Ĳ���ʵ�о������ˡ�
        */
        glfwSwapBuffers(window);//�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
        glfwPollEvents();//���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate(); //ɾ���ͷŵ�֮ǰ�����������Դ
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
//
//ʹ��GLFW��glfwGetKey����������Ҫһ�������Լ�һ��������Ϊ���롣����������᷵����������Ƿ����ڱ�����
void processInput1(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); //������»س����ر�GLFW,��һ��whileѭ������false������ر�
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
//����ӿڵ�ά��Ӧ��С�ڵ���GLWF��ά�ȣ����Ե��û��ı䴰�ڴ�С��ʱ���ӿ�ҲӦ�ñ����������ԶԴ������һ���ص�������callback����������ÿ�δ��ڵ�����С��ʱ�򱻵���
void framebuffer_size_callback1(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    //����������ǽ��а�Opengl�����꣨-1��1��ת��Ϊ��ӳ�䵽����Ļ���꣨800��600��
    glViewport(0, 0, width, height);   //���ô��ڵ�ά�� ǰ�����������ƴ������½ǵ�λ�ã�����������������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�  
}