#define GLEW_STATIC

#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"


struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2]; // one for vertex shader one for fragment shader
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                // set mode to vertex
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                // set mode to fragment
                type = ShaderType::FRAGMENT;
            }
        } else {
            // creative use of arrays and ShaderType enum to avoid explicitly branching.
            ss[(int) type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()}; // Creating a ShaderProgramSource object in one line.
}

static unsigned int CompileShader(unsigned int type, const std::string &source) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str(); //alternatively &source[0];
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length]; // Did this used to give an error for allocating unknown size to stack? Why no Alloca needed?
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs); // should be doing detach instead of delete for debugging or something

    return program;
}

int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); // Set the frame rate to same as screen refresh rate

    if (glewInit() != GLEW_OK) {
        std::cout << "glewInit() failed" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[8] = { // Array of three vertex positions
            -.5f, -.5f,
            0.5f, -.5f,
            0.5f, 0.5f,
            -.5f, 0.5f
    };
    // Note that a "vertex" in the context of graphics can mean more than just position, like,
    // texture coordinates, normals, colors, binormals, tangents, etc.

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    unsigned int vertexArrayObjectId;
    glGenVertexArrays(1, &vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);

    VertexBuffer vertexBuffer(positions, 8 * sizeof(float));
    // vb.Bind(); // Not necessary

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void *) 0);
    // the line of code above is the one that actually binds the GL_ARRAY_BUFFER with the vertexArray

    IndexBuffer indexBuffer(indices, 6);

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    // std::cout << "Vertex Source: " << std::endl;
    // std::cout << source.VertexSource << std::endl;
    // std::cout << "Fragment Source: " << std::endl;
    // std::cout << source.FragmentSource << std::endl;

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    // ASSERT(location != -1); TODO how to properly do assertions in C++
    // Note that the uniform location may be invalid and that might be fine. It might just not be used in the shader
    // and thus automatically removed from it.
    glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);

    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(location, r, 0.3f, 0.8f, 1.0f);

        indexBuffer.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (r > 1.0f) {
            increment = -0.05f;
        } else if (r < 0) {
            increment = 0.05f;
        }

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}