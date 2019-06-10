#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) {
    this->m_Count = count;

    glGenBuffers(1, &m_RendererID); //Instead of a return, gl will modify the buffer variable you provided a pointer to
    // &buffer thus represents a type of ID for a buffer which we can use later.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    // Notice there is no size specified. Next step is to add data to the buffer.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

