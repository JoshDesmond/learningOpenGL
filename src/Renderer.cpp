#include <iostream>
#include "Renderer.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR) {

    }
}

void GLCheckError() {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}
