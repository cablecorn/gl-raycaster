#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstdio>

const char* vertexShaderSource = R"GLSL(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)GLSL";

const char* orangeFragmentShaderSource = R"GLSL(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
)GLSL";

const char* yellowFragmentShaderSource = R"GLSL(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 0.8f, 0.1f, 1.0f);
    }

)GLSL";

static const int WIDTH = 1024;
static const int HEIGHT = 512;

/* --- Callback Functions --- */
void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int main()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) // check if GLFW able to initialize
    {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Our window pointer to make a context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Raycaster", nullptr, nullptr);
    if (!window)
    {
        printf("Failed to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // Orange Triangle Shader Program
    unsigned int vertexShader; // allows us to dynamically compile glsl at runtime accessed by an ID
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // create said shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // fill shader object with our data
    glCompileShader(vertexShader); // compile the shader object

    unsigned int orangeFragmentShader; // create fragment shader object ID
    orangeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // create shader and room for fragment code
    glShaderSource(orangeFragmentShader, 1, &orangeFragmentShaderSource, NULL); // pull glsl code for fragment
    glCompileShader(orangeFragmentShader); // compile it

    unsigned int orangeShaderProgram; // create shader program object to link our shaders to
    orangeShaderProgram = glCreateProgram(); // creates object
    glAttachShader(orangeShaderProgram, vertexShader); // connect our vertex shader to the program
    glAttachShader(orangeShaderProgram, orangeFragmentShader); // connect our fragment shader to the program
    glLinkProgram(orangeShaderProgram); // all shaders added, now link everything

    unsigned int yellowFragmentShader;
    yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, NULL);
    glCompileShader(yellowFragmentShader);

    unsigned int yellowShaderProgram;
    yellowShaderProgram = glCreateProgram();
    glAttachShader(yellowShaderProgram, vertexShader);
    glAttachShader(yellowShaderProgram, yellowFragmentShader);
    glLinkProgram(yellowShaderProgram);

    glDeleteShader(vertexShader); // delete shaders since they're saved in program
    glDeleteShader(orangeFragmentShader);
    glDeleteShader(yellowFragmentShader);

    float vertices1[] = {
        -0.5f, 0.8f, 0.0f, // top 
        -0.2f, 0.2f, 0.0f, // bottom right
        -0.8f, 0.2f, 0.0f, // bottom left
    };
       // triangle 2
    float vertices2[] = {
         0.5f, -0.8f, 0.0f, // bottom
         0.2f, -0.2f, 0.0f, // top left 
         0.8f, -0.2f, 0.0f  // top right
    };

    /*unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };*/

    unsigned int VAOs[2], VBOs[2]; // create a Vertex Buffer Object
    glGenVertexArrays(2, VAOs); // create a VAO to hold our attrib pointers and all that
    glGenBuffers(2, VBOs); // give the VBO an ID to be recognized by the GPU

    glBindVertexArray(VAOs[0]); // VAO starts recording

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); // clear space for a VBO in GL_ARRAY_BUFFER to be stored in GPU memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW); // send actual raw data to our GL_ARRAY_BUFFER we binded

    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]); // start recording for VAO2

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    glViewport(0,0,WIDTH,HEIGHT); // tells OpenGL the size of the rendering window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // callback for glfw window to fix glviewport if resized

    while (!glfwWindowShouldClose(window))
    {
        /*--- input ---*/
        processInput(window); // checks if ESC pressed
        
        /*--- rendering commands ---*/
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // state-setting function
        glClear(GL_COLOR_BUFFER_BIT); // state-using function
        glUseProgram(orangeShaderProgram); // state-setting function to tell context to use THIS shader program
        glBindVertexArray(VAOs[0]); // plays recording
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(yellowShaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);

        /*--- check and call events and swap the buffers ---*/
        glfwSwapBuffers(window); // show the new frame
        glfwPollEvents(); // check for keyboard/mouse input
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}