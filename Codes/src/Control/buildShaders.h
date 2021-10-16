#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>

void BuildShaders(unsigned int shaderProgram, const std::string vertexShaderFile,
                  const std::string fragmentShaderFile) {
  printf("Building shader. \n");
  printf("\tvertexShaderFile: %s\n", vertexShaderFile.c_str());
  printf("\tfragmentShaderFile: %s\n", fragmentShaderFile.c_str());

  char* vertexShaderSource = 0;
  long vlength;
  FILE* vertexFile = fopen(vertexShaderFile.c_str(), "rb");

  if (vertexFile) {
    fseek(vertexFile, 0, SEEK_END);
    vlength = ftell(vertexFile);
    fseek(vertexFile, 0, SEEK_SET);
    vertexShaderSource = (char*)malloc(vlength + 1);

    if (vertexShaderSource)
      fread(vertexShaderSource, 1, vlength, vertexFile);

    fclose(vertexFile);
    vertexShaderSource[vlength] = '\0';
  }

  char* fragmentShaderSource = 0;
  long flength;
  FILE* fragmentFile = fopen(fragmentShaderFile.c_str(), "rb");

  if (fragmentFile) {
    fseek(fragmentFile, 0, SEEK_END);
    vlength = ftell(fragmentFile);
    fseek(fragmentFile, 0, SEEK_SET);
    fragmentShaderSource = (char*)malloc(vlength + 1);

    if (fragmentShaderSource)
      fread(fragmentShaderSource, 1, vlength, fragmentFile);

    fclose(fragmentFile);
    fragmentShaderSource[vlength] = '\0';
  }

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s", infoLog);
  }

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s", infoLog);
  }

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n %s", infoLog);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
