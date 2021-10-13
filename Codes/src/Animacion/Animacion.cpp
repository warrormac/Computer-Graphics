/*
    Computacion Grafica [ CCOMP7-1 ]

    Integrantes:
        Andre Alvarez
        Alvaro Durand
        Cristobal Lecca
*/

#include "glad/glad.h"
#include <glfw/glfw3.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <cmath>
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
const unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 800;
const char* vertexShaderSource = "#version 330 core\n""uniform mat4 transform;\n""layout (location = 0) in vec3 aPos;\n"
"void main()\n""{\n""   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n""}\0";
const char* fragmentShaderSource = "#version 330 core\n""out vec4 FragColor;\n"
"void main()\n""{\n""   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n""}\n\0";

float rotX = 20.0f, rotY = 49.0f, rotZ = 77.0f;

float transX = 0.42f, transY = 0.79f, transZ = 0.725f;

float scalX = 0.1f, scalY = 0.1f, scalZ = 0.1f;

// Matriz identidad maestra
glm::mat4 trans = glm::mat4(1.0f);
glm::mat4 transA = glm::mat4(1.0f);
// Inversa
glm::mat4 transAinv = glm::mat4(1.0f);
// Matriz Translacion
glm::mat4 transB = glm::mat4(1.0f);
// Matriz Escalado
glm::mat4 transC = glm::mat4(1.0f);
// Matriz Rotacion
glm::mat4 transD = glm::mat4(1.0f);

glm::vec3 translationVector;
bool randomMove;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    unsigned int shaderProgram = glCreateProgram();
    unsigned int x = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glAttachShader(x, vertexShader);
    glAttachShader(x, fragmentShader);
    glLinkProgram(x);
    glGetProgramiv(x, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(x, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        0.75f, -0.5f, 0.0f,
        0.25f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
    };

    GLfloat cuadrado[] = {
    -0.40f,0.2f, 0.0f,
    0.50f,0.2f,0.0f,
    0.50f,-0.65f,0.0f,
    -0.40f,0.2f,0.0f,
    -0.40f,-0.65f,0.0f,
    0.50f,-0.65f,0.0f
    };
    unsigned int VBO[100], VAO[100];
    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cuadrado), cuadrado, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        if (randomMove) {
            translationVector.x += ((rand() % 2) * -0.02) + 0.01f;
            translationVector.y += ((rand() % 2) * -0.02) + 0.01f;
        }
        processInput(window);
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            transA = glm::rotate(transA, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
            transAinv = glm::inverse(transA);
            trans = transAinv;
        }
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            trans = glm::translate(transB, glm::vec3(transX, transY, transZ));
        }
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            trans = glm::scale(transC, glm::vec3(scalX, scalY, scalZ));
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            trans = glm::rotate(trans, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            trans = glm::translate(transB, glm::vec3(1.0f, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            trans = glm::translate(transB, glm::vec3(-1.0, 0.0, 0.0));
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            trans = glm::translate(transB, glm::vec3(0.00f, 1.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            trans = glm::translate(transB, glm::vec3(0.0f, -1.0f, 0.0f));
        }
        unsigned int transformar1 = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformar1, 1, GL_FALSE, glm::value_ptr(trans));

        unsigned int transformar2 = glGetUniformLocation(x, "transform");
        glUniformMatrix4fv(transformar2, 1, GL_FALSE, glm::value_ptr(trans));

        trans = glm::mat4(1.0f);
        transA = glm::mat4(1.0f);
        transB = glm::mat4(1.0f);
        transC = glm::mat4(1.0f);
        transD = glm::mat4(1.0f);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(x);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO[0]);
    glDeleteBuffers(1, &VBO[0]);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

