//----------------------------------------------------------------------------------------
/**
 * \file       CShaderProgram.cpp
 * \author     Hong Son Ngo
 * \date       2021/05/05
 * \brief      Class representing a shader program
 *
 * Initializes a shader program and handles setting of uniform variables
 *
*/
//----------------------------------------------------------------------------------------
#include "../include/CShaderProgram.h"
#include <iostream>

CShaderProgram::CShaderProgram(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
    GLuint shaders[] =
    {
      pgr::createShaderFromFile(GL_VERTEX_SHADER, vertexShaderFile),
      pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fragmentShaderFile),
      0
    };
   
    MProgram = pgr::createProgram(shaders);
    MInitiliazed = true;
}

CShaderProgram::CShaderProgram(const std::string& vertexShaderFile, const std::string& geometryShaderFile, const std::string& fragmentShaderFile)
{  
    GLuint shaders[] = {
      pgr::createShaderFromFile(GL_VERTEX_SHADER, vertexShaderFile),
      pgr::createShaderFromFile(GL_GEOMETRY_SHADER, geometryShaderFile),
      pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fragmentShaderFile),
      0
    };

    MProgram = pgr::createProgram(shaders);
    MInitiliazed = true;
}

void CShaderProgram::UseProgram()
{
    if (!MInitiliazed)
        return;
    glUseProgram(MProgram);
}

void CShaderProgram::SetBool(const std::string& name, bool value) const
{
    if (!MInitiliazed)
        return;
    GLint location = glGetUniformLocation(MProgram, name.c_str());
    glUniform1i(location, (int)value);
}

void CShaderProgram::SetInt(const std::string& name, int value) const
{
    if (!MInitiliazed)
        return;
    GLint location = glGetUniformLocation(MProgram, name.c_str());
    glUniform1i(location, value);
}

void CShaderProgram::SetFloat(const std::string& name, float value) const
{
    if (!MInitiliazed)
        return;
    GLint location = glGetUniformLocation(MProgram, name.c_str());
    glUniform1f(location, value);
}

void CShaderProgram::SetVec3(const std::string& name, glm::vec3 value) const
{
    if (!MInitiliazed)
        return;
    GLint location = glGetUniformLocation(MProgram, name.c_str());
    glUniform3fv(location, 1, &value[0]);
}

void CShaderProgram::SetVec4(const std::string& name, glm::vec4 value) const
{
    if (!MInitiliazed)
        return;
    GLint location = glGetUniformLocation(MProgram, name.c_str());
    glUniform4fv(location, 1, &value[0]);
}

void CShaderProgram::SetMat4(const std::string& name, const glm::mat4& value) const
{
    if (!MInitiliazed)
        return;
    GLint location = glGetUniformLocation(MProgram, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
