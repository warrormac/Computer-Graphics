/*
    Computacion Grafica [ CCOMP7-1 ]

    Integrantes:
        Andre Alvarez

*/


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.5);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
"}\n\0";
const char* fragmentShaderGreen =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
" FragColor = vec4(0.196f, 0.98f, 0.196f, 1.0f);\n"
"}\n";

const char* fragmentShaderGreenDarker =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
" FragColor = vec4(0.146f, 0.55f, 0.146f, 1.0f);\n"
"}\n";

const char* fragmentShaderRed =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
" FragColor = vec4(0.8f, 0.0f, 0.0f, 1.0f);\n"
"}\n";

const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n\0";

const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.75f, 0.83f, 0.47f, 0.5f);\n"
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int fragmentGreen;
    fragmentGreen = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentGreen, 1, &fragmentShaderGreen, NULL);
    glCompileShader(fragmentGreen);

    unsigned int fragmentGreenDarker;
    fragmentGreenDarker = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentGreenDarker, 1, &fragmentShaderGreenDarker, NULL);
    glCompileShader(fragmentGreenDarker);

    unsigned int fragmentRed;
    fragmentRed = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentRed, 1, &fragmentShaderRed, NULL);
    glCompileShader(fragmentRed);

    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // the second fragment shader that outputs the color yellow
    unsigned int shaderProgramOrange = glCreateProgram();
    unsigned int shaderProgramYellow = glCreateProgram(); // the second shader program

    glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderOrange);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShaderYellow);
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    // Shader Program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    unsigned int shaderGreen;
    shaderGreen = glCreateProgram();
    glAttachShader(shaderGreen, vertexShader);
    glAttachShader(shaderGreen, fragmentGreen);
    glLinkProgram(shaderGreen);

    unsigned int shaderGreenDarker;
    shaderGreenDarker = glCreateProgram();
    glAttachShader(shaderGreenDarker, vertexShader);
    glAttachShader(shaderGreenDarker, fragmentGreenDarker);
    glLinkProgram(shaderGreenDarker);

    unsigned int shaderRed;
    shaderRed = glCreateProgram();
    glAttachShader(shaderRed, vertexShader);
    glAttachShader(shaderRed, fragmentRed);
    glLinkProgram(shaderRed);

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cuadrados[] = {
        //---------------Quads de Esquinas------------------------------------//


      0.6f,0.6f,0.0f,   //Cuadrado top derecha
      0.6f,0.8f,0.0f,
      0.8f,0.6f,0.0f,

      0.8f,0.8f,0.0f,
      0.8f,0.6f,0.0f,
      0.6f,0.8f,0.0f,



      -0.6f,0.6f,0.0f,   //Cuadrado top izq
      -0.6f,0.8f,0.0f,
      -0.8f,0.6f,0.0f,

      -0.8f,0.8f,0.0f,
      -0.8f,0.6f,0.0f,
      -0.6f,0.8f,0.0f,

      0.6f,-0.6f,0.0f,   //Cuadrado bottom derecha
      0.6f,-0.8f,0.0f,
      0.8f,-0.6f,0.0f,

      0.8f,-0.8f,0.0f,
      0.8f,-0.6f,0.0f,
      0.6f,-0.8f,0.0f,


      -0.6f,-0.6f,0.0f,   //Cuadrado bottom izq
      -0.6f,-0.8f,0.0f,
      -0.8f,-0.6f,0.0f,

      -0.8f,-0.8f,0.0f,
      -0.8f,-0.6f,0.0f,
      -0.6f,-0.8f,0.0f,
    };

    float rec[] = {
        //------------------Rec de medios-------------------------------------//


        0.6f,0.58f,0.0f,   //Rec derecha mid
        0.8f,0.58f,0.0f,
        0.6f,-0.58f,0.0f,

        0.8f,-0.58f,0.0f,
        0.8f,0.58f,0.0f,
        0.6f,-0.58f,0.0f,


        -0.6f,0.58f,0.0f,   //Rec izq mid
        -0.8f,0.58f,0.0f,
        -0.6f,-0.58f,0.0f,

        -0.8f,-0.58f,0.0f,
        -0.8f,0.58f,0.0f,
        -0.6f,-0.58f,0.0f,


         0.58f,0.8f,0.0f,   //rec top mid
         0.58f,0.6f,0.0f,
        -0.58f,0.8f,0.0f,

        -0.58f,0.6f,0.0f,
        0.58f,0.6f,0.0f,
        -0.58f,0.8f,0.0f,


         0.58f,-0.8f,0.0f,   //rec bottom mid
         0.58f,-0.6f,0.0f,
        -0.58f,-0.8f,0.0f,

        -0.58f,-0.6f,0.0f,
        0.58f,-0.6f,0.0f,
        -0.58f,-0.8f,0.0f,
    };

    float borde[] = {
        //---------------------BORDE----------------------------------------//

        0.8f,0.82f,0.0f,   //BORDE TOP
        0.8f,0.8f,0.0f,
        -0.8f,0.8f,0.0f,

        -0.8f,0.82f,0.0f,
        -0.8f,0.8f,0.0f,
        0.8f,0.82f,0.0f,

        0.8f,-0.82f,0.0f,   //BORDE bottom
        0.8f,-0.8f,0.0f,
        -0.8f,-0.8f,0.0f,

        -0.8f,-0.82f,0.0f,
        -0.8f,-0.8f,0.0f,
        0.8f,-0.82f,0.0f,

         -0.8f,0.82f,0.0f,  //BORDE IZQ
         -0.82f,0.82f,0.0f,
         -0.8f,-0.8f,0.0f,

         -0.82f,-0.8f,0.0f,
         -0.8f,-0.8f,0.0f,
         -0.8f,0.82f,0.0f,


         0.8f,0.82f,0.0f,  //BORDE derecha
         0.82f,0.82f,0.0f,
         0.8f,-0.8f,0.0f,

         0.82f,-0.8f,0.0f,
         0.8f,-0.8f,0.0f,
         0.8f,0.82f,0.0f,
    };

    float stem[] = {

        // ---------------------STEM----------------------------------------//

            -0.035f,-0.24f,0.0f,     //176
            0.02f,-0.24f,0.0f,      //177
            0.02f,0.18f,0.0f,       //178

            -0.035f,0.18f,0.0f,      //179
            0.02f,0.18f,0.0f,       //178
            -0.035f,-0.24f,0.0f
    };

    float vertices[] = {

        0.6f,0.6f,0.0f,   //Cuadrado top derecha
      0.6f,0.8f,0.0f,
      0.8f,0.6f,0.0f,

      -0.6f,0.6f,0.0f,   //Cuadrado top izq
      -0.6f,0.8f,0.0f,
      -0.8f,0.6f,0.0f,

      0.6f,-0.6f,0.0f,   //Cuadrado bottom derecha
      0.6f,-0.8f,0.0f,
      0.8f,-0.6f,0.0f,

      -0.6f,-0.6f,0.0f,   //Cuadrado bottom izq
      -0.6f,-0.8f,0.0f,
      -0.8f,-0.6f,0.0f,



       0.6f,0.58f,0.0f,   //Rec derecha mid
        0.8f,0.58f,0.0f,
        0.6f,-0.58f,0.0f,


        -0.6f,0.58f,0.0f,   //Rec izq mid
        -0.8f,0.58f,0.0f,
        -0.6f,-0.58f,0.0f,


         0.58f,0.8f,0.0f,   //rec top mid
         0.58f,0.6f,0.0f,
        -0.58f,0.8f,0.0f,


         0.58f,-0.8f,0.0f,   //rec bottom mid
         0.58f,-0.6f,0.0f,
        -0.58f,-0.8f,0.0f,

        0.58f,-0.8f,0.0f,   //rec bottom mid
         0.58f,-0.6f,0.0f,
        -0.58f,-0.8f,0.0f,

        0.58f,-0.8f,0.0f,   //rec bottom mid
         0.58f,-0.6f,0.0f,
        -0.58f,-0.8f,0.0f,

        0.58f,-0.8f,0.0f,   //rec bottom mid
         0.58f,-0.6f,0.0f,
        -0.58f,-0.8f,0.0f,

        0.58f,-0.8f,0.0f,   //rec bottom mid
         0.58f,-0.6f,0.0f,
        -0.58f,-0.8f,0.0f,

        0.58f,-0.8f,0.0f,   //rec bottom mid
         0.58f,-0.6f,0.0f,
        -0.58f,-0.8f,0.0f,

        0.58f,-0.8f,0.0f,   //rec bottom mid
         0.58f,-0.6f,0.0f,
        -0.58f,-0.8f,0.0f,

        0.58f,-0.8f,0.0f,   //rec bottom mid
         0.58f,-0.6f,0.0f,
        -0.58f,-0.8f,0.0f,

        0.58f,-0.8f,0.0f,   //rec bottom mid
         0.58f,-0.6f,0.0f,
        

        
       


        //---------------------Hoja izq-------------------------------------//

            -0.002f,-0.608f,0.0f,   //E  48
            0.033f,-0.608f,0.0f,    //F  49
            0.104f,-0.607f,0.0f,    //G  50
            0.153f,-0.575f,0.0f,    //H  51
            0.183f,-0.526f,0.0f,    //I  52
            0.203f,-0.478f,0.0f,    //J  53
            0.234f,-0.404f,0.0f,    //K  54 
            0.247f,-0.341f,0.0f,    //L  55
            0.268f,-0.287f,0.0f,      //M  56
            0.294f,-0.232f,0.0f,    //N  57
            0.325f,-0.172f,0.0f,    //O  58
            0.374f,-0.108f,0.0f,    //P  59
            0.413f,-0.075f,0.0f,    //Q  60
            0.458f,-0.041f,0.0f,    //R  61
            0.503f,-0.01f,0.0f,     //S  62
            0.544f,-0.001f,0.0f,    //T  63
            0.59f,0.03f,0.0f,       //U  64
            0.591f,0.03f,0.0f,      //V  65
            0.534f,0.038f,0.0f,     //W  66
            0.486f,0.038f,0.0f,     //Z  67
            0.436f,0.038f,0.0f,     //A1 68
            0.386f,0.038f,0.0f,     //B1 69
            0.335f,0.033f,0.0f,     //C1 70
            0.294f,0.023f,0.0f,     //D1 71
            0.245f,0.006f,0.0f,     //E1 72
            0.207f,-0.012f,0.0f,    //F1 73
            0.166f,-0.034f,0.0f,    //G1 74
            0.121f,-0.058f,0.0f,    //H1 75
            0.089f,-0.083f,0.0f,    //I1 76
            0.061f,-0.111f,0.0f,    //J1 77
            0.04f,-0.138f,0.0f,     //K1 78
            0.02f,-0.17f,0.0f,      //L1 79
            0.0f,-0.222f,0.0f,      //M1 80
            -0.022f,-0.256f,0.0f,   //N1 81
            -0.035f,-0.311f,0.0f,   //O1 82
            -0.045f,-0.358f,0.0f,   //P1 83
            -0.05f,-0.402f,0.0f,    //Q1 84
            -0.051f,-0.444f,0.0f,   //R1 85
            -0.054f,-0.488f,0.0f,   //S1 86
            -0.056f,-0.524f,0.0f,   //T1 87
            -0.048f,-0.563f,0.0f,   //U1 88
            -0.043f,-0.212f,0.0f,   //V1 89 
            -0.064f,-0.171f,0.0f,   //W1 90
            -0.091f,-0.133f,0.0f,   //Z1 91
            -0.127f,-0.095f,0.0f,   //A2 92
            -0.164f,-0.058f,0.0f,   //B2 93
            -0.206f,-0.032f,0.0f,   //C2 94
            -0.254f,-0.013f,0.0f,   //D2 95
            -0.3f,0.0f,0.0f,        //E2 96
            -0.353f,0.011f,0.0f,    //F2 97
            -0.392f,0.014f,0.0f,    //G2 98
            -0.446f,0.012f,0.0f,    //H2 99
            -0.502f,0.012f,0.0f,    //I2 100
            -0.55f,0.012f,0.0f,     //J2 101
            -0.6f,0.0f,0.0f,        //K2 102
            -0.605f,-0.046f,0.0f,   //L2 103
            -0.565f,-0.046f,0.0f,   //M2 104
            -0.517f,-0.052f,0.0f,   //N2 105
            -0.488f,-0.064f,0.0f,   //O2 106
            -0.456f,-0.086f,0.0f,   //P2 107
            -0.428f,-0.124f,0.0f,   //Q2 108
            -0.405f,-0.168f,0.0f,   //R2 109
            -0.388f,-0.213f,0.0f,   //S2 110
            -0.372f,-0.254f,0.0f,   //T2 111
            -0.361f,-0.296f,0.0f,   //U2 112
            -0.342f,-0.347f,0.0f,   //V2 113
            -0.321f,-0.39f,0.0f,    //W2 114
            -0.301f,-0.43f,0.0f,    //Z2 115
            -0.28f,-0.472f,0.0f,    //A3 116
            -0.253f,-0.509f,0.0f,   //B3 117
            -0.228f,-0.54f,0.0f,    //C3 118
            -0.2f,-0.564f,0.0f,     //D3 119
            -0.168f,-0.587f,0.0f,   //E3 120 
            -0.125f,-0.603f,0.0f,   //F3 121
            -0.062f,-0.6f,0.0f,     //G3 122
            0.002f,-0.1f,0.0f,      //H3 123
            -0.044f,-0.102f,0.0f,   //K3 124
            -0.042f,0.146f,0.0f,    //L3 125
            -0.01f,0.146f,0.0f,     //M3 126
            -0.038f,0.146f,0.0f,    //N3 127
            0.022f,0.192f,0.0f,     //V3 128
            0.072f,0.206f,0.0f,     //W3 129
            0.129f,0.253f,0.0f,     //Z3 130
            0.169f,0.306f,0.0f,     //A4 131
            0.196f,0.358f,0.0f,     //B4 132
            0.22f,0.416f,0.0f,      //C4 133
            0.247f,0.474f,0.0f,     //D4 134
            0.281f,0.535f,0.0f,     //E4 135
            0.34f,0.594f,0.0f,      //F4 136
            0.372f,0.593f,0.0f,     //G4 137
            0.3f,0.595f,0.0f,       //H4 138
            0.236f,0.592f,0.0f,     //I4 139
            0.183f,0.584f,0.0f,     //J4 140
            0.139f,0.568f,0.0f,     //K4 141
            0.102f,0.55f,0.0f,     //L4 142
            0.07f,0.536f,0.0f,      //M4 143
            0.042f,0.489f,0.0f,     //N4 144
            0.018f,0.46f,0.0f,      //O4 145
            -0.002f,0.419f,0.0f,    //P4 146
            -0.021f,0.363f,0.0f,    //Q4 147
            -0.034f,0.178f,0.0f,    //R4 148
            -0.02f,0.286f,0.0f,     //S4 149
            -0.04f,0.422f,0.0f,     //T4 150
            -0.059f,0.466f,0.0f,    //U4 151
            -0.089f,0.507f,0.0f,    //V4 152
            -0.116f,0.541f,0.0f,    //W4 153
            -0.165f,0.567f,0.0f,    //Z4 154
            -0.208f,0.581f,0.0f,    //A5 155
            -0.255f,0.593f,0.0f,    //B5 156
            -0.3f,0.6f,0.0f,        //C5 157
            -0.345f,0.601f,0.0f,    //D5 158
            -0.4f,0.596f,0.0f,      //E5 159
            -0.434f,0.596f,0.0f,    //F5 160
            -0.344f,0.562f,0.0f,    //G5 161
            -0.314f,0.521f,0.0f,    //H5 162
            -0.29f,0.481f,0.0f,     //I5 163
            -0.278f,0.438f,0.0f,    //J5 164
            -0.266f,0.386f,0.0f,    //K5 165
            -0.252f,0.351f,0.0f,    //L5 166
            -0.237f,0.306f,0.0f,    //M5 167
            -0.208f,0.256f,0.0f,    //N5 168
            -0.174f,0.222f,0.0f,    //O5 169
            -0.136f,0.201f,0.0f,    //P5 170
            -0.102f,0.189f,0.0f,    //Q5 171
            -0.087f,0.59f,0.0f,     //S5 172
            -0.023f,0.642f,0.0f,    //T5 173
            0.019f,0.616f,0.0f,     //U5 174
            0.047f,0.579f,0.0f,     //V5 175
            -0.02f, -0.24f, 0.0f,     //176
             0.02f, -0.24f, 0.0f,      //177
             0.02f, 0.18f, 0.0f,       //178
            -0.02f, 0.18f, 0.0f,      //179
            -0.08f,0.182f,0.0f,     //180
            0.01f,0.18f,0.0f,       //181










    };
    
    unsigned int indices[] = {  // note that we start from 0!
       

        //  --------hoja derecha-----------  //

        64,65,66,
        63,66,64,

        67,66,63,
        62,67,63,

        62,67,68,
        61,68,62,

        61,68,69,
        60,69,61,

        60,69,70,
        59,70,60,

        59,70,72,
        58,72,59,

        58,72,73,
        57,73,58,

        57,73,74,
        56,74,57,

        56,74,75,
        55,75,56,

        55,75,76,
        54,76,55,

        54,76,77,
        53,77,54,

        53,77,78,
        52,78,53,

        52,78,79,
        51,79,52,

        51,79,80,
        50,80,51,

        50,80,81,
        49,81,82,

        48,82,49,
        48,82,83,

        88,83,48,
        88,48,84,

        88,48,85,
        88,48,86,

        88,48,87,
        78,53,52,

        78,50,51,
        49,50,79,

        49,50,80,
        49,50,81,

        49,50,82,
        80,81,49,

        80,81,49,


    //  ------------- hoja izq ------------//

        102, 100, 104,
        104, 101, 102,

        104, 101, 100,
        105, 100, 104,

        105, 100, 99,
        106, 99, 100,

        106, 99, 98,
        107, 98, 106,

        107, 98, 97,
        108, 97, 107,

        108, 97, 96,
        109, 96, 108,

        109, 96, 95,
        110, 95, 109,

        110, 95, 94,
        111, 94, 110,

        111, 93, 92,
        112, 92, 111,

        112, 92, 91,
        113, 91, 112,

        113, 91, 90,
        114, 90, 113,

        114, 90, 89,
        115, 89, 114,

        115, 89, 81,
        116, 115, 81,

        116, 117, 81,
        117, 118, 81,

        118, 119, 81,
        119, 120, 81,

        120, 121, 81,
        121, 122, 81,

        95,94,112,
        94,93,113,

        93,92,114,
        96,95,112,

        97,98,112,
        95,91,113,

        121, 86, 49,
            90, 80, 84,

    // ------------------- STEM ---------------//

        105,106,99,
        109,110,93,

        176,177,178,
        176,178,179,



    };

    unsigned int indices2[] = {
        // ------------------ FLOR ----------------//
        137,136,135,
        136,138,135,
        138,139,135,
        139,135,140,
        134,140,135,
        134,140,141,
        133,141,134,
        133,141,142,
        132,142,133,
        132,142,143,
        134,139,135,
        132,133,139,
        132,133,140,
        132,133,141,
        131,143,132,
        131,143,144,
        130,144,131,
        130,144,145,
        128,144,130,
        143,175,147,
        175,174,147,
        174,173,147,
        173,172,147,
        172,172,147,
        172,153,147,
        160,159,161,
        159,158,161,
        158,161,157,
        161,157,156,
        162,156,161,
        162,156,155,
        163,155,162,
        163,155,154,
        164,155,163,
        164,155,153,
        165,153,164,
        165,153,166,
        166,153,152,
        167,152,166,
        167,151,150,
        168,151,167,
        168,151,150,
        169,150,168,
        170,150,171,
        171,147,149,
        171,148,149,
        148,178,149,
        178,129,149,
        153,143,127,
        167,131,173,
        173,169,129,
        129,154,145,
        169,170,150,
        170,171,150,
        128,129,145,
        129,130,145,
        171,128,173,
        165,132,173,
        170,129,149,
        180,181,173,
        145,153,165,
        145,153,166,
        145,153,167,
        145,153,168,
        145,153,169,
        145,153,170,
        145,153,171,
        171,128,150,
        128,126,127,
        171,125,127,
        169,152,125,
        128,129,146,
        128,130,146,
        128,129,174,
        128,129,174
    };

    unsigned int VBO[8], VAO[8], EBO[4];
    glGenVertexArrays(8, VAO);
    glGenBuffers(8, VBO);
    glGenBuffers(4, EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cuadrados), cuadrados, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rec), rec, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[2]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(borde), borde, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[3]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(stem), stem, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[4]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[5]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
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

        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderGreenDarker);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 24);


        glUseProgram(shaderGreen);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 24);

        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAO[2]);
        glDrawArrays(GL_TRIANGLES, 0, 24);

        glUseProgram(shaderRed);
        glBindVertexArray(VAO[5]);
        glDrawElements(GL_TRIANGLES, 325, GL_UNSIGNED_INT, 0);

        glUseProgram(shaderGreenDarker);
        glBindVertexArray(VAO[3]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 3, 6);

        glUseProgram(shaderGreenDarker);
        glBindVertexArray(VAO[4]);
        glDrawElements(GL_TRIANGLES, 307, GL_UNSIGNED_INT, 0);

        

        //glDrawArrays(GL_TRIANGLES, 65, 68);
        //glDrawArrays(GL_TRIANGLES, 68, 71);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
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