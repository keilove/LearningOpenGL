#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback2(GLFWwindow* window, int width, int height);
void processInput2(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
/*
��GLSL���Ա�д������ɫ�����������붥��
������Ҫ���ĵ�һ����������ɫ������GLSL(OpenGL Shading Language)��д������ɫ����
Ȼ����������ɫ����
�������ǾͿ����ڳ�����ʹ�����ˡ�
1 �汾
2 ʹ�� in �ؼ��� �ڶ�����ɫ�����������е����붥������(Input Vertex Attribute)������һ��vec3�������apos�� layout(location=0)�趨���������λ��ֵ
3 Ϊ�����ö�����ɫ������������Ǳ����λ�����ݸ�ֵ��Ԥ�����gl_Position����������Ļ����vec4���͵�
*/
//Ϊ��ʹOpenGLʹ������������Ҫ������ʱ��̬��������Դ����


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
/*
���������Ǵ��㴴��������Ⱦ�����ε���ɫ�����������Ǽ�������������ɫ�����Ϊ�˼�㣬���ǵ�fragment shaderһֱ����ٻ�ɫ
Ϊ��ʹOpenGLʹ������������Ҫ������ʱ��̬��������Դ����
*/
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"             //�������������out
"void main()\n"
"{\n"
"   FragColor = vec4(0.6f, 0.7f, 0.4f, 1.0f);\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback2);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------ Ϊ����openglʹ��������̬������ɫ��Դ����
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);           //����һ��������ɫ��
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);             //�����������ɫ��Դ�븽�ӵ���ɫ�������ϣ� 
                                                                            //������Ҫ�������ɫ��������Ϊ��һ��������
                                                                            //�ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ����
                                                                            //�����������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL
    glCompileShader(vertexShader);                                          //���������������������ܿ����ı���ɻ����ܿ�����
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);   //����Ƿ����ɹ�
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);   //��ȡ������Ϣ
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);   //ʹ��GL_FRAGMENT_SHADER������Ϊ��ɫ�����ͣ�
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //������ɫ�����ڶ������ˣ�ʣ�µ������ǰ�������ɫ���������ӵ�һ��������Ⱦ����ɫ������(Shader Program Object)�С�
    // link shaders
    /*
    ��ɫ���������(Shader Program Object)�Ƕ����ɫ���ϲ�֮������������ɵİ汾��
    ���Ҫʹ�øղű������ɫ�����Ǳ������������(Link)Ϊһ����ɫ���������Ȼ������Ⱦ�����ʱ�򼤻������ɫ������
    �Ѽ�����ɫ���������ɫ���������Ƿ�����Ⱦ���õ�ʱ��ʹ�á�
    ��������ɫ����һ�������ʱ�������ÿ����ɫ����������ӵ��¸���ɫ�������롣����������벻ƥ���ʱ�����õ�һ�����Ӵ���
    */
    unsigned int shaderProgram = glCreateProgram();         //����һ��������󣬷�������´����ĳ���ID����
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);                           //����������Ҫ��֮ǰ�������ɫ�����ӵ���������ϣ�
                                                            //Ȼ����glLinkProgram�������ǣ�
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //�ڰ���ɫ���������ӵ���������Ժ󣬼ǵ�ɾ����ɫ���������ǲ�����Ҫ�����ˣ�
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /*
    ���ڣ������Ѿ������붥�����ݷ��͸���GPU����ָʾ��GPU����ڶ����Ƭ����ɫ���д�������
    �Ϳ�Ҫ����ˣ�����û������OpenGL����֪��������ν����ڴ��еĶ������ݣ��Լ�������ν������������ӵ�������ɫ���������ϡ�
    ������Ҫ����OpenGL��ô����
    */


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    unsigned int VBO;           //����һ�����㻺��������������һ����һ�޶���ID������������洢������ɫ����һ���ڴ�
    glGenBuffers(1, &VBO);      //ʹ��glGenBuffers������һ������ID����һ��VBO����
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //OpenGL�кܶ໺��������ͣ����㻺�����Ļ���������GL_ARRAY_BUFFER��
                                        //OpenGL��������ͬʱ�󶨶�����壬ֻҪ�����ǲ�ͬ�Ļ������͡�(���㻺�桢��Ȼ��桢���߻���)
                                        //���ǿ���ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ���ϣ�
    //����һ��������ʹ�õ��κΣ���GL_ARRAY_BUFFERĿ���ϵģ�������ö����������õ�ǰ�󶨵Ļ���(VBO)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//��֮ǰ����Ķ������ݸ��Ƶ�������ڴ��
                                                                              //���ĸ�����������ϣ���Կ���ι�����������ݣ����ݲ���򼸺����䡢���ܶࡢ����ÿ�λ���ʱ���ı䣩


    unsigned int VAO;          //�����������
    glGenVertexArrays(1, &VAO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    //glVertexAttribPointer��������OpenGL����ν����������ݣ�Ӧ�õ�������������ϣ�
    /*
    ��һ������ָ������Ҫ���õĶ������ԡ����ǵ������ڶ�����ɫ����ʹ��layout(location = 0)������position�������Ե�λ��ֵ(Location)�������԰Ѷ������Ե�λ��ֵ����Ϊ0����Ϊ����ϣ�������ݴ��ݵ���һ�����������У������������Ǵ���0��
    �ڶ�������ָ���������ԵĴ�С������������һ��vec3������3��ֵ��ɣ����Դ�С��3��
    ����������ָ�����ݵ����ͣ�������GL_FLOAT(GLSL��vec*�����ɸ�����ֵ��ɵ�)��
    ���ĸ��������������Ƿ�ϣ�����ݱ���׼��(Normalize)�������������ΪGL_TRUE���������ݶ��ᱻӳ�䵽0�������з�����signed������-1����1֮�䡣���ǰ�������ΪGL_FALSE��
    �����������������(Stride)�������������������Ķ���������֮��ļ���������¸���λ��������3��float֮�����ǰѲ�������Ϊ3 * sizeof(float)��Ҫע�������������֪����������ǽ������еģ���������������֮��û�п�϶������Ҳ��������Ϊ0����OpenGL�������岽���Ƕ��٣�ֻ�е���ֵ�ǽ�������ʱ�ſ��ã���һ�������и���Ķ������ԣ����Ǿͱ����С�ĵض���ÿ����������֮��ļ���������ں���ῴ����������ӣ���ע: �����������˼��˵���Ǵ�������Եڶ��γ��ֵĵط�����������0λ��֮���ж����ֽڣ���
    ���һ��������������void*��������Ҫ���ǽ��������ֵ�ǿ������ת��������ʾλ�������ڻ�������ʼλ�õ�ƫ����(Offset)������λ������������Ŀ�ͷ������������0�����ǻ��ں�����ϸ�������������
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    /*
    �Զ�������λ��ֵ��Ϊ���������ö������ԣ���������Ĭ���ǽ��õ�
    */
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput2(window);

        // render
        // ------
        glClearColor(0.6f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);    //���ǿ��Ե���glUseProgram�������øմ����ĳ��������Ϊ���Ĳ������Լ�������������
                                        //��glUseProgram��������֮��ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������
                                        //��Ҳ����֮ǰд����ɫ��)��


        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        /*
        glDrawArrays������һ�����������Ǵ�����Ƶ�OpenGLͼԪ�����͡�
        ����������һ��ʼʱ˵��������ϣ�����Ƶ���һ�������Σ����ﴫ��GL_TRIANGLES������
        �ڶ�������ָ���˶����������ʼ����������������0��
        ���һ������ָ�����Ǵ�����ƶ��ٸ����㣬������3������ֻ�����ǵ���������Ⱦһ�������Σ���ֻ��3�����㳤��
        */
        glDrawArrays(GL_TRIANGLES, 0, 3);   
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}






// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput2(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback2(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}