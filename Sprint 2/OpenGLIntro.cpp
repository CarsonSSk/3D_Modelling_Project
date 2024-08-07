#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
    float rotationAngle = glm::radians(5.0f); // Rotate by 5 degrees
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

    std::string vertexShaderSource = readShaderSource("vertex_shader.glsl");
    std::string fragmentShaderSource = readShaderSource("fragment_shader.glsl");

    GLuint shaderProgram = createShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());

    // Define the vertex data for a triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Initialize transformation matrices
    glm::mat4 translation = glm::mat4(1.0f);
    glm::mat4 rotation = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

    // Initialize projection matrix (orthographic projection)
    glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        processInput(window, translation, rotation, scale);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Apply aspect ratio to the scaling transformation
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        glm::mat4 aspectScale = glm::scale(glm::mat4(1.0f), glm::vec3(aspectRatio, 1.0f, 1.0f));

        // Apply transformations in the correct order
        glm::mat4 transform = translation * rotation * aspectScale * scale;
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
