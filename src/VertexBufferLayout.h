#ifndef OPENGL_VERTEXBUFFERLAYOUT_H
#define OPENGL_VERTEXBUFFERLAYOUT_H

#include <vector>

#define GLEW_STATIC

#include <GL/glew.h>

struct VertexBufferElement {
    unsigned int type; // OPEN_GL thing
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
        }
        // ASSERT(false)
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout()
            : m_Stride(0) { // TODO what is this called, some kind of default initializer?

    };

    void Push(unsigned int count, int gl_type) {
        switch (gl_type) {
            case GL_FLOAT:
                m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
                m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
                break;
            case GL_UNSIGNED_INT:
                m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
                m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
                break;
            case GL_UNSIGNED_BYTE:
                m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
                m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
                break;
        }
    }


    inline const std::vector<VertexBufferElement> GetElements() const &{ return m_Elements; }

    inline unsigned int GetStride() const { return m_Stride; }

};


#endif //OPENGL_VERTEXBUFFERLAYOUT_H
