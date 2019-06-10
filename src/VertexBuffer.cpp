#include "Renderer.h"

#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    glGenBuffers(1, &m_RendererID); //Instead of a return, gl will modify the buffer variable you provided a pointer to
    // &buffer thus represents a type of ID for a buffer which we can use later.
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    // Notice there is no size specified. Next step is to add data to the buffer.
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
