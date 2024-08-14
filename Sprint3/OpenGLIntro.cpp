#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "tiny_obj_loader.h"

// Function to read shader code from a file
std::string readShaderSource(const char* filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Could not open file: " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    return true;
}

bool initGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    return true;
}

// Function to load the OBJ file
bool loadOBJ(const std::string& filename, std::vector<float>& vertices) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool loading = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str(), nullptr, true);

    if (!warn.empty()) {
        std::cerr << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << "ERR: " << err << std::endl;
    }

    if (!loading) {
        return false;
    }

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);
        }
    }

    return true;
}

GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;
}

GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, glm::mat4& translation, glm::mat4& rotation, glm::mat4& scale) {
    float translationSpeed = 0.05f;
    float rotationAngle = glm::radians(30.0f); // Rotate by 30 degrees
    float scalingFactor = 1.1f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        translation = glm::translate(translation, glm::vec3(0.0f, translationSpeed, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        translation = glm::translate(translation, glm::vec3(0.0f, -translationSpeed, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        translation = glm::translate(translation, glm::vec3(-translationSpeed, 0.0f, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        translation = glm::translate(translation, glm::vec3(translationSpeed, 0.0f, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        rotation = glm::rotate(rotation, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        rotation = glm::rotate(rotation, -rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        scale = glm::scale(scale, glm::vec3(scalingFactor, scalingFactor, scalingFactor));
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        scale = glm::scale(scale, glm::vec3(1.0f / scalingFactor, 1.0f / scalingFactor, 1.0f / scalingFactor));
}

int main() {
    if (!initGLFW()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Assignment", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!initGLEW()) {
        return -1;
    }

    std::string vertexShaderSource = readShaderSource("vertexShader.glsl");
    std::string fragmentShaderSource = readShaderSource("fragmentShader.glsl");

    GLuint shaderProgram = createShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());

    // Load the object from file
    std::vector<float> vertices;
    if (!loadOBJ("C:/Users/Carson/Desktop/School/University/Summer 2024/COMP 371/Assignment 3/finalbottle.obj", vertices)) {
        std::cerr << "Failed to load OBJ file" << std::endl;
        return -1;
    }

    // Set up VAO and VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Enable wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Initialize transformation matrices
    glm::mat4 translation = glm::mat4(1.0f);
    glm::mat4 rotation = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);


    // Apply an initial rotation to align the object
    rotation = glm::rotate(rotation, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // Initialize projection matrix (orthographic projection)
    glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        processInput(window, translation, rotation, scale);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Combine the transformation matrices
        glm::mat4 transform = projection * translation * rotation * scale;
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // Set the aspect ratio uniform
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        unsigned int aspectRatioLoc = glGetUniformLocation(shaderProgram, "aspectRatio");
        glUniform1f(aspectRatioLoc, aspectRatio);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
