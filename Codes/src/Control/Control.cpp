/*
    Computacion Grafica [ CCOMP7-1 ]

    Integrantes:
        Andre Alvarez

*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Matriz.h"
#include "Poligono.h"
#include <cmath> 


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);





// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int angule = 45;

int inctime = 10;
float radio = 0.25 + 0.1;

vector<float> vertices = {
    //-------------------------------------------------------  triangle -----------------------//
     0.1f,  -0.1f, 0.0f,  // bottom right
     -0.1f, -0.1f, 0.0f,  // bottom left
     0.0f,   0.1f, 0.0f,  // top
      //------------------------------------------------------- square ------------------------//
     
     0.25f + 0.1f,  0.1f, 0.0f,  // top left
     0.25f + 0.1f,  -0.1f, 0.0f,  // bottom left
     0.25f + 3 * 0.1f,  -0.1f, 0.0f,  // bottom right

     0.25f + 3 * 0.1f,  0.1f, 0.0f,  // top right
     0.25f + 0.1f,  0.1f, 0.0f,  // top left
     0.25f + 3 * 0.1f,  -0.1f, 0.0f,  // bottom right

     //------------------------------------------------------- diamond ------------------------//
     0.25f + 3 * 0.1f + 0.25f ,  0.0f, 0.0f,  //  left
     0.25f + 3 * 0.1f + 0.25f + 0.1f,  0.1f, 0.0f,  // bottom
     0.25f + 3 * 0.1f + 0.25f + 0.1f,  -0.1f, 0.0f,  // top

     0.25f + 3 * 0.1f + 0.25f + 2 * 0.1f ,  0.0f, 0.0f,  //  right
     0.25f + 3 * 0.1f + 0.25f + 0.1f,  0.1f, 0.0f,  // bottom
     0.25f + 3 * 0.1f + 0.25f + 0.1f,  -0.1f, 0.0f  // top
};




const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";


matrix create_m_vertices(vector<float> vertices, int index)
{
    vector<float> m_vertices = vector<float>(vertices.begin() + index, vertices.begin() + index + 3);
    m_vertices.push_back(1.0f);
    return matrix(m_vertices);
}

void apply(matrix m, int num_triangules, int indice)
{
    for (int i = indice; i < 9 * num_triangules; i += 3)
    {
        matrix m_vertices = create_m_vertices(vertices, i);
        //m_vertices.print();
        matrix res = m.mult(m_vertices);
        //res.print();
        vertices[i] = res.m[0][0];
        vertices[i + 1] = res.m[1][0];
        vertices[i + 2] = res.m[2][0];

    }

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

}


float circle(float x)
{
    return sqrt((radio * radio) - (x * x)) + 0.1;
}

bool grow = true;


//--------------------------------------------------CRECER TRAINGE ---------------------------------------
void scaleTriangule(float variation)   
{
    //cout << vertices[0]<<endl;
    float size = abs(vertices[0] - vertices[1]);

    if (size > 0.4)
    {
        grow = false;

    }
    if (!grow)
    {
        variation = variation * -1;
    }

    if (size < 0.2)
    {
        grow = true;

    }

    vector<float> s_axis = { 1.0f + variation, 1.0f + variation,1.0f };
    matrix S = matrix::GenScale(s_axis, 4);
    apply(S, 1, 0);

}


float square_variationx = 0.05;
float square_variationy = 0.1;

bool c_up = true;
bool rotation = true;//para elegir el tipo de rotacion del cuadrado



//-----------------------------Mover Cuadrado--------------------------------//
void moveSquare()
{

    matrix RZ = matrix::GenRotate(angule, 'z', 4);

    if (rotation)
        apply(RZ, 3, 9);
    else
    {
        if (vertices[9] >= radio)
        {
            c_up = false;
            square_variationx *= -1;
        }

        float y;
        if (vertices[9] + square_variationx > radio || vertices[9] + square_variationx < -radio)
            y = 0;
        else if (c_up)
            y = circle(vertices[9] + square_variationx);
        else if (!c_up)
            y = -circle(vertices[9] + square_variationx);

        square_variationy = y - vertices[10];
        vector<float> t_axis = { square_variationx,square_variationy,0.0f };
        matrix T = matrix::GenTranslation(t_axis, 4);
        apply(T, 3, 9);
    }

}


float diamond_variationx = 0.1;
float diamond_variationy = 0.1;
bool up = true;
bool tleft = true;

//------------------------------Moviemiento del Rombo-----------------------//
void moveDiamond()
{
    float variationx = 0;
    float variationy = 0;

    if (vertices[28] <= 1 - 0.1 && up) //eje y+
    {

        variationy = diamond_variationy;
    }
    else if (vertices[27] >= -1 && tleft) //eje x-
    {
        variationx = -diamond_variationx;
    }
    else if (vertices[28] >= -1 + 0.1) //eje y-
    {
        up = false;
        variationy = -diamond_variationy;
    }

    else if (vertices[27] <= 1 - 3 * 0.1) //eje x+
    {
        tleft = false;
        variationx = diamond_variationx;

    }
    else {
        up = true;
        tleft = true;
    }


    vector<float> t_axis = { variationx,variationy,0.0f };
    matrix T = matrix::GenTranslation(t_axis, 4);
    apply(T, 5, 27);
}


//-------------------------------------------- LLamo las animaciones ------------------------------//
void animation(float inc)  
{
    scaleTriangule(inc);
    moveSquare();
    moveDiamond();
}


int main()
{
    cout << circle(radio);
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }



    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);





    int rateofanimation = 0;
    int limit = 100;



    float s_color = 1.0f;
    float t_color = 1.0f;
    float d_color = 1.0f;

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, t_color, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, s_color, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 3, 6);

        vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, d_color, 1.0f);
        glDrawArrays(GL_TRIANGLES, 9, 6);
        //cout <<"rate "<< rateofanimation << endl;

        //animar a las figuras cuando rateofanimation sobre pase a 100
        if (rateofanimation >= 200) {
           
            rateofanimation = 0;
            animation(0.05);
            
        }


        rateofanimation += inctime;

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
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int teminc;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{



    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        if (inctime != 0) {
            teminc = inctime;
            inctime = 0;

        }
        else
            inctime = teminc;

    }

    if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        inctime += 5;
        inctime = inctime % 50;
    }

    if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        inctime -= 5;
        if (inctime == 0)
        {
            inctime = 5;
        }
    }


    if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        angule += 15;
        cout << "angule: " << angule << endl;
    }

    if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        angule -= 15;
        cout << "angule: " << angule << endl;
    }




}